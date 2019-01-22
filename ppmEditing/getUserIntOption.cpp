// Libraries
#include <iostream>
#include <string>
#include "getUserIntOption.h"

// Constants
#include "constants.h"

using namespace std; 

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is a global function implementation. It reads in users options
// and check whether there is an error.

int getUserIntOption()
{
  int inputInt;
  cin >> inputInt;
  while (cin.fail() || inputInt <= 0)
  {
    cin.clear();
    cin.ignore(STREAM_IGNORE, '\n');
    cout << "Not a positive integer input! Please reenter: ";
    cin >> inputInt;
  }

  return inputInt;
}