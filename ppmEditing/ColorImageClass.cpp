// Libraries
#include <iostream>
#include <string>
#include <fstream>
#include "ColorImageClass.h"

// Constants
#include "constants.h"

// Classes
#include "ColorClass.h"
#include "RectangleClass.h"
#include "RowColumnClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class implementation. The ColorImageClass is just a 
// image. Some methods can be used to modify the image. 

// Default ctor
ColorImageClass::ColorImageClass()
{
  int initialSize = 0;
  
  pixel = NULL; 
  rowNum = initialSize;
  colNum = initialSize;
}

// Reading in object from a file
bool ColorImageClass::readFromFile(const string fileDirectory)
{
  string indicatorString;
  ifstream infile;
  int maxColorValue = 0;
  bool successReading = true;

  // Open file and check whether open is successful
  infile.open(fileDirectory.c_str()); 
  if (infile.fail())
  {
    cout << "Unable to open input file!" << endl;
    successReading = false;
    return successReading;
  }

  // Read in ppm image specification 
  infile >> indicatorString;
  infile >> colNum;
  infile >> rowNum;
  infile >> maxColorValue;

  // Check ppm image specification is by the book
  if (infile.eof())
  {
    cout << "End of file prior to reading the entire image!" << endl;
    successReading = false;
  }
  if (infile.fail())
  {
    cout << "PPM file contains unexpected value! Fail to read in!" << endl;
    successReading = false;
  } 
  if (indicatorString.compare(PPM_FILE_IDENTIFIER) ||
           maxColorValue != RGB_FULL_VALUE)
  {
    cout << "The input file is not a PPM file!" << endl;
    successReading = false;
  }

  // Reading image pixel by pixel
  pixel = new ColorClass*[rowNum];
  for (int i = 0; i < rowNum; ++i)
  {
    pixel[i] = new ColorClass[colNum];
  }

  for (int i = 0; i < rowNum; ++i)
  {
    for (int j = 0; j < colNum; ++j)
    {
      successReading = successReading && pixel[i][j].readColorFromFile(infile);
    }
  }
  infile.close();

  return successReading;
}

// Write out object to a file
void ColorImageClass::writeToFile(const string fileDirectory)
{
  ofstream outfile;

  outfile.open(fileDirectory.c_str());

  outfile << PPM_FILE_IDENTIFIER << endl;
  outfile << colNum << " " << rowNum << endl;
  outfile << RGB_FULL_VALUE << endl;

  int endOfRow = colNum - 1;
  for (int i = 0; i < rowNum; ++i)
  {
    for (int j = 0; j < colNum; ++j)
    {
      if (j == endOfRow)
      {
        pixel[i][j].writeColorToFile(outfile, j == endOfRow);
        outfile << endl;
      }
      else
      {
        pixel[i][j].writeColorToFile(outfile, j == endOfRow);
      }
    }
  }

  outfile.close();
}

// Default dtor
ColorImageClass::~ColorImageClass()
{

  for (int i = 0; i < rowNum; ++i)
  {
    delete [] pixel[i];
  }

  delete [] pixel;
}

// Draw a rectangle on object
void ColorImageClass::drawRectangle(RectangleClass &inRectangle,
                                    ColorClass &targetColor,
                                    bool fillIn)
{
  RowColumnClass startRowCol;
  RowColumnClass endRowCol;

  inRectangle.getUppLeft(startRowCol);
  inRectangle.getLwrRight(endRowCol);
  RowColumnClass currentRowCol(startRowCol); 

  for (; 
       currentRowCol.getRow() <= endRowCol.getRow(); 
       currentRowCol.incrementRow())
  {
    for (currentRowCol.setCol(startRowCol.getCol()); 
         currentRowCol.getCol() <= endRowCol.getCol(); 
         currentRowCol.incrementCol())
    {
      if (!fillIn)
      {
        if (currentRowCol.checkSameRow(startRowCol) ||
            currentRowCol.checkSameRow(endRowCol) ||
            currentRowCol.checkSameCol(startRowCol) ||
            currentRowCol.checkSameCol(endRowCol))
        {
          setColorAtLocation(currentRowCol, targetColor);
        }
      }
      else
      {
        setColorAtLocation(currentRowCol, targetColor);
      }

    }
  }
}

// Add an annotation on object
bool ColorImageClass::addAnnotation(const string fileDirectory,
                                    RowColumnClass &startRowCol,
                                    ColorClass &targetColor)
{
  int modifyIndicator = 1;
  int annoRowNum = 0, annoColNum = 0;
  bool successReading = true;

  ifstream infile;
  infile.open(fileDirectory.c_str());

  if (infile.fail())
  {
    cout << "Unable to open annotation file!" << endl;
    successReading = false;
    return successReading;
  }

  infile >> annoColNum;
  infile >> annoRowNum;

  if (infile.eof())
  {
    cout << "End of file prior to reading the entire annotation!" << endl;
    successReading = false;
    return successReading;
  }
  if (infile.fail())
  {
    cout << "Annotation file contains unexpected value!" << endl;
    successReading = false;
    return successReading;
  } 
  
  // Initialize the annotation matrix
  RowColumnClass currentRowCol(startRowCol);
  int** annoMatrix;
  annoMatrix = new int*[annoRowNum];
  for (int i = 0; i < annoRowNum; ++i)
  {
    annoMatrix[i] = new int[annoColNum];
  }

  for (int i = 0; i < annoRowNum; ++i)
  {
    for (int j = 0; j < annoColNum; ++j)
    {
      successReading = successReading && checkInfile(infile, annoMatrix[i][j]);
    }
  }
  infile.close();

  if (!successReading)
  {
    return successReading;
  }

  // Add annotation to image
  for (int i = 0; i < annoRowNum; ++i)
  {
    for (int j = 0; j < annoColNum; ++j)
    {
      if (annoMatrix[i][j] == modifyIndicator)
      {
        setColorAtLocation(currentRowCol, targetColor);
      }
      currentRowCol.incrementCol();
    }
    currentRowCol.incrementRow();
    currentRowCol.setCol(startRowCol.getCol());
  }

  // Free annotation matrix memory
  for (int i = 0; i < annoRowNum; ++i)
  {
    delete [] annoMatrix[i];
  }
  delete [] annoMatrix;

  return successReading; 
}

// Add an object on object
void ColorImageClass::addPPMImage(ColorImageClass &targetImg,
                                  RowColumnClass &startRowCol,
                                  ColorClass &transColor)
{
  RowColumnClass basiscurrentRowCol(startRowCol);
  RowColumnClass ppmCurrentRowCol(0, 0), ppmStartRowCol(0, 0);
  ColorClass colorForCompare, colorForModify;
  int targetImgRow = targetImg.rowNum, 
      targetImgCol = targetImg.colNum;

  for (; 
       ppmCurrentRowCol.getRow() < targetImgRow; 
       ppmCurrentRowCol.incrementRow())
  {
    for (ppmCurrentRowCol.setCol(ppmStartRowCol.getCol()); 
         ppmCurrentRowCol.getCol() < targetImgCol; 
         ppmCurrentRowCol.incrementCol())
    {
      targetImg.getColorAtLocation(ppmCurrentRowCol, colorForCompare);
      if (!transColor.checkSameColor(colorForCompare))
      {
        targetImg.getColorAtLocation(ppmCurrentRowCol, colorForModify);
        setColorAtLocation(basiscurrentRowCol, colorForModify);
      }
      basiscurrentRowCol.incrementCol();
    }
    basiscurrentRowCol.incrementRow();
    basiscurrentRowCol.setCol(startRowCol.getCol());
  }
}

// Initialize object with a given color
void ColorImageClass::initializeTo(ColorClass &inColor)
{
  for (int i = 0; i < rowNum; ++i)
  {
    for (int j = 0; j < colNum; ++j)
    {
      pixel[i][j].setTo(inColor);
    }
  }
}

// Helper function to check bound
bool ColorImageClass::indexCheckInternal(int rowIndex, int colIndex)
{
  bool validIndex = true;

  if (rowIndex >= rowNum || rowIndex < 0 ||
      colIndex >= colNum || colIndex < 0)
  {
    validIndex = false;
  }
  else
  {
    validIndex = true;
  }

  return validIndex;
}

// Helper function to check read in status
bool ColorImageClass::checkInfile(ifstream &infile, int &outputInt)
{
  bool goodStatus = true;

  infile >> outputInt;
  if (infile.eof())
  {
    infile.clear();
    goodStatus = false;
    cout << "End of file prior to reading the entire annotation!" << endl;
  }
  else if (infile.fail())
  {
    infile.clear();
    goodStatus = false;
    cout << "Annotation file contains non-int value!" << endl;
  }
  
  return goodStatus;
}

// Get the color of a particular pixel
bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol, 
                                         ColorClass &outColor)
{
  int rowIndex = inRowCol.getRow();
  int colIndex = inRowCol.getCol();

  bool validIndex = indexCheckInternal(rowIndex, colIndex);

  if (validIndex)
  {
    outColor.setTo(pixel[rowIndex][colIndex]);
  }

  return validIndex;
}

// Set color of a pixel
bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol, 
                                         ColorClass &inColor)
{
  int rowIndex = inRowCol.getRow();
  int colIndex = inRowCol.getCol();

  bool validIndex = indexCheckInternal(rowIndex, colIndex);

  if (validIndex)
  {
    pixel[rowIndex][colIndex].setTo(inColor);
  }

  return validIndex;
}

// Add another image onto the existing one
bool ColorImageClass::addImageTo(ColorImageClass &rhsImg)
{
  bool isClipped = false;

  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      isClipped = (pixel[i][j].addColor(rhsImg.pixel[i][j])) 
                  || isClipped;
    }
  }

  return isClipped;
}

// print out image RGB
void ColorImageClass::printImage()
{
  int endOfRow = colNum - 1; 

  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      pixel[i][j].printComponentValues();
      if (j != endOfRow)
      {
        cout << "--";
      }
    }
    cout << endl;
  }
}