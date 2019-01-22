#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// Libraries
#include <string>

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is a global constants. All source code
// include this header file as needed. 

// ppm file consttants
const int RGB_FULL_VALUE = 255;
const int RGB_MIN_VALUE = 0;
const string PPM_FILE_IDENTIFIER = "P3";

// stream ignore
const int STREAM_IGNORE = 200;

// main menu option constants
const int ADD_RECTANGLE = 1;
const int ADD_PATTERN = 2;
const int ADD_IMAGE = 3;
const int OUTPUT_IMAGE = 4;
const int EXIT_PROGRAM = 5;

// rectangle option constants
const int UPP_LEFT_LWR_RIGHT = 1;
const int UPP_LEFT_DIMENSION = 2;
const int CENTER_DIMENSION = 3;

// rectangle fill constants
const int NO_FILL = 1;
const int YES_FILL = 2;

// color option constants
const int COLOR_RED = 1;
const int COLOR_GREEN = 2;
const int COLOR_BLUE = 3;
const int COLOR_BLACK = 4;
const int COLOR_WHITE = 5;

#endif