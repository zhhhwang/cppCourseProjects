//Libraries
#include <iostream>
#include "RectangleClass.h"

// Classes
#include "RowColumnClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class implementation. The RectangleClass can help us 
// to draw rectangle easily. 

// Default ctor
RectangleClass::RectangleClass(){
  int initialRowColValue = 0;
  RowColumnClass initialRowCol(initialRowColValue, initialRowColValue);

  upperLeft.setRowCol(initialRowCol);
  lowerRight.setRowCol(initialRowCol);
}

// Value ctor: when given two Rowcolumn Class
RectangleClass::RectangleClass(RowColumnClass &inUpperLeft, 
                               RowColumnClass &inLowerRight)
{
  upperLeft.setRowCol(inUpperLeft);
  lowerRight.setRowCol(inLowerRight);
}

// Value ctor: when given one RowColumn Class, dimensions and the 
// location of the RowColumn Class (center/upper left)
RectangleClass::RectangleClass(RowColumnClass &inRowCol,
                               const int &inWidth, 
                               const int &inHeight, 
                               bool provideUpperLeft)
{
  if (provideUpperLeft)
  {
    RowColumnClass inLowerRight(inRowCol);
  
    for (int i = 0; i < inWidth; ++i)
    {
      inLowerRight.incrementRow();
    }
    for (int i = 0; i < inHeight; ++i)
    {
      inLowerRight.incrementCol();
    }

    upperLeft.setRowCol(inRowCol);
    lowerRight.setRowCol(inLowerRight);
  }
  else
  {
    RowColumnClass inUpperLeft(inRowCol);
    RowColumnClass inLowerRight(inRowCol);

    for (int i = 0; i < inWidth; ++i)
    {
      inUpperLeft.decrementRow();
      inLowerRight.incrementRow();
    }
    for (int i = 0; i < inHeight; ++i)
    {
      inUpperLeft.decrementCol();
      inLowerRight.incrementCol();
    }

    upperLeft.setRowCol(inUpperLeft);
    lowerRight.setRowCol(inLowerRight);
  }
}

// Return attribute1: upper left corner
void RectangleClass::getUppLeft(RowColumnClass &outUppLeft)
{
  outUppLeft.setRowCol(upperLeft.getRow(), upperLeft.getCol());
}

// Return attribute2: lower right cornor
void RectangleClass::getLwrRight(RowColumnClass &outLwrRight)
{
  outLwrRight.setRowCol(lowerRight.getRow(), lowerRight.getCol());
}

