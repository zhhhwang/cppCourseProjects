#ifndef _RECTANGLECLASS_H_
#define _RECTANGLECLASS_H_

// Libraries
#include <iostream>

// Classes
#include "RowColumnClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class definition. The RectangleClass can help us 
// to draw rectangle easily. 

class RectangleClass
{
  public:
    // ctors
    RectangleClass(); 
    RectangleClass(RowColumnClass &inUpperLeft, 
                   RowColumnClass &inLowerRight);
    RectangleClass(RowColumnClass &inRowCol,
                   const int &inWidth, 
                   const int &inHeight,
                   bool provideUpperLeft);


    // extract attributes
    void getUppLeft(RowColumnClass &outUppLeft);
    void getLwrRight(RowColumnClass &outLwrRight);

  private:
    // Attributes
    RowColumnClass upperLeft;
    RowColumnClass lowerRight;
};

#endif