// Libraries
#include <iostream>
#include <string>
#include "getUserIntInput.h"

// Constants
#include "constants.h"

using namespace std; 

// Author: Zhihao Huang
// Date: November 25, 2019
// Purpose: This is a global function implementation. It reads in users inputs
// and check whether there is an error.

double getUserDoubleInput()
{
  double inputInt;
  cin >> inputInt;
  while (cin.fail() || inputInt <= 0)
  {
    cin.clear();
    cin.ignore(STREAM_IGNORE, '\n');
    cout << "Not a double input! Please reenter: ";
    cin >> inputInt;
  }

  return inputInt;
}