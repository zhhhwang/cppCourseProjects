// Libraries
#include <iostream>
#include "SimuClass.h"

// Constants
#include "constants.h"

// Classes
#include "random.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "getUserIntInput.h"
#include "getUserDoubleInput.h"

using namespace std;

// Author: Zhihao Huang
// Date: November 25, 2019
// Purpose: This is the implementation of the simulation class. All the 
// simulation is implemented here.

SimuClass::SimuClass()
{
  int randomSeed = 0;
  cout << "Please specify the random seed (positive int): ";
  randomSeed = getUserIntInput();
  setSeed(randomSeed);

  cout << "The close time of the store is (int input): ";
  closeTime = getUserIntInput();

  cout << "The minimun of the uniform distribution is (int input): ";
  unifMin = getUserIntInput();

  cout << "The maximun of the uniform distribution is (int input): ";
  unifMax = getUserIntInput();

  cout << "The maximun length of the queue the cusmoter would tolerate ";
  cout << "(int input): ";
  longLine = getUserIntInput();

  cout << "The probability a cusmoter would leave if the line is too long ";
  cout << "(double input): ";
  pToLeave = getUserDoubleInput();

  cout << "The mean of the normal distribution ";
  cout << "(double input): ";
  normMean = getUserDoubleInput();

  cout << "The standard deviation of the normal distribution ";
  cout << "(double input): ";
  cin >> normStd;

  int initialVal = 0;
  totalCustomer = initialVal;
  serverBusyTime = initialVal;
  waitingCustomer = initialVal;
  earlyLeaveCustomer = initialVal;
  longestLine = initialVal;
  totalQueueTime = initialVal;
  totalTotalTime = initialVal;
  lastServeDone = initialVal;

  serverStatus = SERVER_NOT_BUSY;
}

void SimuClass::run()
{
  // Run Simulaiton
  cout << endl;
  cout << "############################" << endl;
  cout << "#### Simulation Begins! ####" << endl;
  cout << "############################" << endl;
  // First customer shows up
  scheduleEvent(ARRIVE, FIRST_EVENT_TIME, FIRST_ID);

  // Keep processing and scheduling event until close time and queue is empty
  while (eventList.getNumElems() != EMPTY)
  {
    processEvent();
  }

  cout << "############################" << endl;
  cout << "##### Simulation Ends! #####" << endl;
  cout << "############################" << endl;
  cout << endl;

  // Summary of statistics
  cout << "############################" << endl;
  cout << "#### Simulation Summary ####" << endl;
  cout << "############################" << endl;

  cout << "The total number of customer that showed up is: ";
  cout << totalCustomer << endl;

  cout << "The percentage of time the server was busy helping customers is: ";
  int actualCloseTime = 0;
  if (lastServeDone > closeTime)
  {
    actualCloseTime = lastServeDone;
  }
  else
  {
    actualCloseTime = closeTime;
  }
  cout << ((double) serverBusyTime / actualCloseTime) * PERCENTAGE;
  cout << " %" <<endl;

  cout << "The percentage of customers has to wait in line is: ";
  cout << ((double) waitingCustomer / (totalCustomer - earlyLeaveCustomer)) 
          * PERCENTAGE << " %" <<endl;

  cout << "The number of customers arrived but left due to excessive line ";
  cout << "length is: " << earlyLeaveCustomer << endl;

  cout << "The longest line throughout the simulation is: ";
  cout << longestLine << endl; 

  cout << "The average queue time is: ";
  cout << (double) totalQueueTime / 
          (totalCustomer - earlyLeaveCustomer) << endl;

  cout << "The average time of getting the food is: ";
  cout << (double) totalTotalTime / 
          (totalCustomer - earlyLeaveCustomer) << endl;
}

void SimuClass::scheduleEvent(const int &inType,
                              const int &inTime,
                              const int &inID)
{
  EventClass newEvent(inType, inTime, inID);
  eventList.insertValue(newEvent);
}

void SimuClass::processEvent()
{
  EventClass tempEvent;
  eventList.removeFront(tempEvent);

  if (tempEvent.getType() == ARRIVE)
  {
    totalCustomer++;
    int nextArr =  tempEvent.getTime() + getUniform(unifMin, unifMax);
    int currentID = tempEvent.getID();

    // schedule new arrival only happens before close time
    if (nextArr < closeTime)
    {
      scheduleEvent(ARRIVE, nextArr, ++currentID);
    }

    // If the line is too long, customer might leave
    // Otherwise, schedule in queue event
    if (queueLine.getNumElems() <= longLine)
    {
      cout << "Customer #" << tempEvent.getID() << " arrives at time ";
      cout << tempEvent.getTime() << "." << endl;
      scheduleEvent(IN_QUEUE, tempEvent.getTime(), tempEvent.getID());
    }
    else
    {
      cout << "Customer #" << tempEvent.getID() << " arrives at time ";
      cout << tempEvent.getTime() << ". There are " << queueLine.getNumElems();
      cout << " people ahead of him in the queue. He thinks about leaving as";
      cout << " the line is longer than " << longLine <<" people ..." << endl;

      if (getBinary(pToLeave))
      {
        scheduleEvent(LEAVE, tempEvent.getTime(), tempEvent.getID());
        earlyLeaveCustomer++;
      }
      else
      {
        scheduleEvent(IN_QUEUE, tempEvent.getTime(), tempEvent.getID());
      }
    }

    // Calculate statistics
    totalTotalTime -= tempEvent.getTime();
  }
  if (tempEvent.getType() == IN_QUEUE)
  {
    cout << "Customer #" << tempEvent.getID() << " gets in the queue";
    cout << " at time " << tempEvent.getTime() << "." << endl;

    // If there is no one in front of him, get served immediately
    if (queueLine.getNumElems() == EMPTY && serverStatus == SERVER_NOT_BUSY)
    {
      scheduleEvent(GET_SERVED, tempEvent.getTime(), tempEvent.getID());
      waitingCustomer--;
    }
    else
    {
      // Get the customer in the queue
      queueLine.enqueue(tempEvent.getID());
    }

    // Calculate statistics
    waitingCustomer++;
    totalQueueTime -= tempEvent.getTime();
  }
  if (tempEvent.getType() == GET_SERVED)
  {
    cout << "Customer #" << tempEvent.getID() << " is being served";
    cout << " at time " << tempEvent.getTime() << "." << endl;

    // Schedule serve done event
    int serveDuration = getNormal(normMean, normStd);
    scheduleEvent(SERVE_DONE, 
                  tempEvent.getTime() + serveDuration, 
                  tempEvent.getID());

    // Calculate statistics
    serverBusyTime += serveDuration;
    totalQueueTime += tempEvent.getTime();
    serverStatus = SERVER_BUSY;
  }
  if (tempEvent.getType() == SERVE_DONE)
  {
    cout << "Customer #" << tempEvent.getID() << " is done";
    cout << " at time " << tempEvent.getTime() << "." << endl;

    // Schedule leave event
    scheduleEvent(LEAVE, tempEvent.getTime(), tempEvent.getID());

    // Record the longest line
    if (queueLine.getNumElems() >= longestLine)
    {
      longestLine = queueLine.getNumElems();
    }

    // Schedule next customer to get served
    if (queueLine.getNumElems() != EMPTY)
    {
      int nextID = 0;
      queueLine.dequeue(nextID);
      scheduleEvent(GET_SERVED, tempEvent.getTime(), nextID);
    }
    else
    {
      serverStatus = SERVER_NOT_BUSY;
    }
  }
  if (tempEvent.getType() == LEAVE)
  {
    cout << "Customer #" << tempEvent.getID() << " leaves the store";
    cout << " at time " << tempEvent.getTime() << "." << endl;

    // Calculate statistics
    if (tempEvent.getTime() > lastServeDone)
    {
      lastServeDone = tempEvent.getTime();
    }
    totalTotalTime += tempEvent.getTime();
  }
}