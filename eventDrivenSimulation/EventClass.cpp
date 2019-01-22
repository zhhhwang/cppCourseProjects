// Libraries
#include <iostream>
#include "EventClass.h"

// Constants
#include "constants.h"

// Classes
#include "random.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: November 20, 2019
// Purpose: This is the implementation of the enent class. 

EventClass::EventClass()
{
  int initialValue = 1;
  eventType = initialValue;
  eventTime = initialValue;
  customerID = initialValue;
}

EventClass::EventClass(const EventClass &inEvent)
{
  eventType = inEvent.eventType;
  eventTime = inEvent.eventTime;
  customerID = inEvent.customerID;
}

EventClass::EventClass(int inType, int inTime, int inID)
{
  eventType = inType;
  eventTime = inTime;
  customerID = inID;
}

bool EventClass::operator>=(const EventClass &inEvent) const
{
  bool result = true;
  if (eventTime >= inEvent.eventTime)
  {
    result = true;
  }
  else
  {
    result = false;
  }

  return result;
}

int EventClass::getType() const
{
  return eventType;
}

int EventClass::getTime() const
{
  return eventTime;
}

int EventClass::getID() const
{
  return customerID;
}
