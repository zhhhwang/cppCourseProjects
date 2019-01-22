#ifndef _SIMU_CLASS_H_
#define _SIMU_CLASS_H_

// Libraries
#include <iostream>

// Constants
#include "constants.h"

// Classes
#include "random.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "getUserIntInput.h"

using namespace std;

// Author: Zhihao Huang
// Date: November 25, 2019
// Purpose: This is the prototype of the simulation class. All the 
// simulation can be done through this class. Simulation data will also 
// be kept as data member. 

class SimuClass
{
  private:
    // Store configures
    FIFOQueueClass<int> queueLine;
    SortedListClass<EventClass> eventList;

    // User specified configures
    int closeTime;
    int unifMin;
    int unifMax;
    int longLine;
    double pToLeave;
    double normMean;
    double normStd;

    // Statistics we are interested in
    int totalCustomer;
    int serverBusyTime;
    int waitingCustomer;
    int earlyLeaveCustomer;
    int longestLine;
    int totalQueueTime;
    int totalTotalTime;
    int lastServeDone;

    // Server Status
    int serverStatus;

  public:
    // Default ctor
    SimuClass();

    // Run the simulation
    void run();

    // Schedule events and put in event list
    void scheduleEvent(const int &inType, const int &inTime, const int &inID);

    // Process event
    void processEvent();
};

#endif