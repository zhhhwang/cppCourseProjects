// Libraries
#include <iostream>
#include "addRectangle.h"

// Constants
#include "constants.h"

// Classes
#include "ColorImageClass.h"
#include "RectangleClass.h"
#include "ColorClass.h"

// Global functions
#include "setFillOption.h"
#include "getUserIntOption.h"
#include "printColorMenu.h"
#include "setColorOption.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the global function implementation. It gets users option
// for rectangle color, and add a rectangle to the basis image. 

void addRectangle(ColorImageClass &basisImage, RectangleClass &inRectangle)
{
  int colorOption = 0;
  bool validColorOption = false, fillIn = false;
  ColorClass recColor;

  // User input color
  while (!validColorOption)
  {
    printColorMenu();
    cout << "Enter int for rectangle color: ";
    colorOption = getUserIntOption();
    validColorOption = setColorOption(colorOption, recColor);
  }

  fillIn = setFillOption();
  basisImage.drawRectangle(inRectangle, recColor, fillIn);
}