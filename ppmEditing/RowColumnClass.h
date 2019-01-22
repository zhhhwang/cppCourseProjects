#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

// Libraries
#include <iostream>

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class definition. The RowColumn Class is just a 
// matrix. Some methods can be used to modify the matrix. 

class RowColumnClass
{
  public:
    // Default ctor , copy ctor and value ctor
    RowColumnClass();
    RowColumnClass(const RowColumnClass &inRowCol);
    RowColumnClass(int inRow, int inCol);

    // Set row/col number manually
    void setRowCol(int inRow, int inCol);
    void setRowCol(RowColumnClass &inRowCol);
    void setRow(int inRow);
    void setCol(int inCol);

    // Obtain row/col value
    int getRow();
    int getCol();

    // Row/Column increment/decrement;
    void incrementRow();
    void incrementCol();
    void decrementRow();
    void decrementCol();

    // Check if two object has the same row and col
    bool checkSameRow(RowColumnClass &inRowCol);
    bool checkSameCol(RowColumnClass &inRowCol);

    // Add a RowColumnClass object value
    void addRowColTo(RowColumnClass &inRowCol);

    // Print out row column value
    void printRowCol();

  private:
    //Attributes
    int rowIndex;
    int colIndex;
};

#endif