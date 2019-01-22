#include <iostream>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "SimuClass.h"
#include "constants.h"
#include "random.h"


// Author: Zhihao Huang
// Date: November 25, 2019
// Purpose: This is the project 5 of EECS 402. The program can be used to 
// simulate the queue of a store.


int main()
{
  SimuClass storeSimulation;
  storeSimulation.run();

  return 0;
}
