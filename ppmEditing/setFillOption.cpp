// Libraries
#include <iostream>
#include "setFillOption.h"

// Constants
#include "constants.h"

// Global functions
#include "getUserIntOption.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is a global function implementation. It sets rectangle
// to be filled or not to be filled according to user's specifications.

bool setFillOption()
{
  bool fillRec = false, validOption = false;
  int userOption = 0;
  
  while (!validOption)
  {
    cout << "1. No" << endl << "2. Yes" << endl;
    cout << "Enter int for rectangle fill option: ";
    userOption = getUserIntOption();

    if (userOption == NO_FILL)
    {
      fillRec = false;
      validOption = true;
    }
    else if (userOption == YES_FILL)
    {
      fillRec = true;
      validOption = true;
    }
    else
    {
      cout << "Invalid option! Please re-enter your option!" << endl;
    }
  }

  return fillRec;
}
