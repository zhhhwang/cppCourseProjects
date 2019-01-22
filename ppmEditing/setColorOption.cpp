// Libraries
#include <iostream>
#include "setColorOption.h"

// Classes
#include "ColorClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is a global function implementation. It sets color
// according to users option. 

bool setColorOption(int colorOption, ColorClass &outColor)
{
  bool validOption = true;
  if (colorOption == COLOR_RED)
  {
    outColor.setToRed();
  }
  else if (colorOption == COLOR_GREEN)
  {
    outColor.setToGreen();
  }
  else if (colorOption == COLOR_BLUE)
  {
    outColor.setToBlue();
  }
  else if (colorOption == COLOR_BLACK)
  {
    outColor.setToBlack();
  }
  else if (colorOption == COLOR_WHITE)
  {
    outColor.setToWhite();
  }
  else
  {
    cout << "Invalid option! Please re-enter your option!" << endl;
    validOption = false;
  }

  return validOption;
}
