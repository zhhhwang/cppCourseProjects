#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// Libraries
#include <iostream>

using namespace std;

// Author: Zhihao Huang
// Date: November 20, 2019
// Purpose: This is the global constants of the project 5. 

// First Event
const int FIRST_EVENT_TIME = 0;
const int FIRST_ID = 1;

// Using number to represent event categories
const int ARRIVE = 1;
const int IN_QUEUE = 2;
const int GET_SERVED = 3;
const int SERVE_DONE = 4;
const int LEAVE = 5;

// Ignore bad input
const int STREAM_IGNORE = 200;

// percentage
const int PERCENTAGE = 100;

// Empty list
const int EMPTY = 0;

// Server status
const int SERVER_BUSY = 1;
const int SERVER_NOT_BUSY = 0;

#endif