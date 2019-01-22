#ifndef _ADD_RECTANGLE_H_
#define _ADD_RECTANGLE_H_

// Libraries
#include <iostream>

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
// Purpose: This is the global function prototype. It gets users option for
// rectangle color, and add a rectangle to the basis image. 

void addRectangle(ColorImageClass &basisImage, RectangleClass &inRectangle);

#endif