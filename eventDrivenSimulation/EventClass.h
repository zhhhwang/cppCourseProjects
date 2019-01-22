#ifndef _EVENT_CLASS_H_
#define _EVENT_CLASS_H_

// Libraries
#include <iostream>

// Constants
#include "constants.h"

// Classes
#include "random.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: November 20, 2019
// Purpose: This is the propotype of event class. 

class EventClass
{
  private:
    int eventType; // Listed in the global constants
    int eventTime; // Ranging starting from 1
    int customerID; // Ranging starting from 1

  public:
    // ctor
    EventClass(); // Default
    EventClass(const EventClass &inEvent); // Copy ctor
    EventClass(int inType, int inTime, int inID); // Value ctor

    // Operator overloading for comparing event order
    bool operator>=(const EventClass &inEvent) const;

    // Obtaining data member from outside
    int getType() const;
    int getTime() const;
    int getID() const;

};

#endif  