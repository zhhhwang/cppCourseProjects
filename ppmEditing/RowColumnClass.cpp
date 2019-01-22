// Libraries
#include <iostream>
#include "RowColumnClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class implementation. The ColorImageClass is just a 
// image. Some methods can be used to modify the image. 

// Default ctor
RowColumnClass::RowColumnClass()
{
  int initialValue = -99999;
  rowIndex = initialValue;
  colIndex = initialValue;
}

// Copy ctor
RowColumnClass::RowColumnClass(const RowColumnClass &inRowCol)
{
  rowIndex = inRowCol.rowIndex;
  colIndex = inRowCol.colIndex;
}

// Value ctor
RowColumnClass::RowColumnClass(int inRow, int inCol)
{
  rowIndex = inRow;
  colIndex = inCol;
}

// Show row and column
void RowColumnClass::printRowCol()
{
  cout << "[" << rowIndex << "," << colIndex << "]";
}

// Set row and column with specified value
void RowColumnClass::setRowCol(int inRow, int inCol)
{
  rowIndex = inRow;
  colIndex = inCol;
}

// Set row and column with soecified object
void RowColumnClass::setRowCol(RowColumnClass &inRowCol)
{
  rowIndex = inRowCol.rowIndex;
  colIndex = inRowCol.colIndex;
}

// Add objects by row and column
void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
  rowIndex += inRowCol.rowIndex;
  colIndex += inRowCol.colIndex;
}

// Increment row 
void RowColumnClass::incrementRow()
{
  rowIndex++;
}

// Increment column
void RowColumnClass::incrementCol()
{
  colIndex++;
}

// Decrement row
void RowColumnClass::decrementRow()
{
  rowIndex--;
}

// Decrement column
void RowColumnClass::decrementCol()
{
  colIndex--;
}

// Check whether two object have the same row 
bool RowColumnClass::checkSameRow(RowColumnClass &inRowCol)
{
  return inRowCol.getRow() == rowIndex;
}

// check whether two object have the same column
bool RowColumnClass::checkSameCol(RowColumnClass &inRowCol)
{
  return inRowCol.getCol() == colIndex;
}

// Set row value
void RowColumnClass::setRow(int inRow)
{
  rowIndex = inRow;
}

// Set column value
void RowColumnClass::setCol(int inCol)
{
  colIndex = inCol;
}

// Get row value
int RowColumnClass::getRow()
{
  return rowIndex;
}

// Get column value
int RowColumnClass::getCol()
{
  return colIndex;
}