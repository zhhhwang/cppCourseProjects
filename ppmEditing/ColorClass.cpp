// Libraries
#include <iostream>
#include <fstream>
#include "ColorClass.h"

// Constants
#include "constants.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class implementation. The ColorClass is just a 
// pixel. Some methods can be used to modify the pixel. 

// Default ctor
ColorClass::ColorClass()
{
  setTo(RGB_FULL_VALUE, RGB_FULL_VALUE, RGB_FULL_VALUE);
}

// Value ctor
ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
  setTo(inRed, inGreen, inBlue);
}

// Helper function for checking clipping
bool ColorClass::clipNumberInternal()
{
  bool isClipped = false;

  int tempRed = clipNumber(redValue, RGB_MIN_VALUE, RGB_FULL_VALUE);
  int tempGreen = clipNumber(greenValue, RGB_MIN_VALUE, RGB_FULL_VALUE);
  int tempBlue = clipNumber(blueValue, RGB_MIN_VALUE, RGB_FULL_VALUE);

  if(tempRed != redValue || tempGreen != greenValue || tempBlue != blueValue)
  {
    redValue = tempRed;
    greenValue = tempGreen;
    blueValue = tempBlue;

    isClipped = true;
  }

  return isClipped;
}

// Helper function for checking reading status
bool ColorClass::checkInfile(ifstream &infile, int &outputInt)
{
  bool goodStatus = true;

  infile >> outputInt;
  if (infile.eof())
  {
    infile.clear();
    goodStatus = false;
    cout << "End of file prior to reading the entire image!" << endl;
  }
  else if (infile.fail())
  {
    infile.clear();
    goodStatus = false;
    cout << "PPM file contains non-int value!" << endl;
  }
  
  return goodStatus;
}

// Helper function for clipping number
int ColorClass::clipNumber(int targetNum, int minVal, int maxVal)
{
  if (targetNum > maxVal)
  {
    targetNum = maxVal;
  }
  else if (targetNum < minVal)
  {
    targetNum = minVal;
  }

  return targetNum;
}

// Print out pixel RGB
void ColorClass::printComponentValues()
{

  cout << "R: " << redValue << " "
       << "G: " << greenValue << " "
       << "B: " << blueValue;
}

// Set pixel to a color
void ColorClass::setToBlack()
{
  setTo(RGB_MIN_VALUE, RGB_MIN_VALUE, RGB_MIN_VALUE);
}

// Set pixel to a color
void ColorClass::setToRed()
{
  setTo(RGB_FULL_VALUE, RGB_MIN_VALUE, RGB_MIN_VALUE);
}

// Set pixel to a color
void ColorClass::setToGreen()
{
  setTo(RGB_MIN_VALUE, RGB_FULL_VALUE, RGB_MIN_VALUE);
}

// Set pixel to a color
void ColorClass::setToBlue()
{
  setTo(RGB_MIN_VALUE, RGB_MIN_VALUE, RGB_FULL_VALUE);
}

// Set pixel to a color
void ColorClass::setToWhite()
{ 
  setTo(RGB_FULL_VALUE, RGB_FULL_VALUE, RGB_FULL_VALUE);
}

// Reading in RGB value from file
bool ColorClass::readColorFromFile(ifstream &infile)
{
  int inRed = 0, inGreen = 0, inBlue = 0;
  bool successReading = true;

  successReading = successReading && checkInfile(infile, inRed);
  successReading = successReading && checkInfile(infile, inGreen);
  successReading = successReading && checkInfile(infile, inBlue);

  setTo(inRed, inGreen, inBlue);
  return successReading;
}

// Write out RGB value to file
void ColorClass::writeColorToFile(ofstream &outfile, bool endOfRow)
{
  if (!endOfRow)
  {
    outfile << redValue << " ";
    outfile << greenValue << " ";
    outfile << blueValue << " ";
  }
  else
  {
    outfile << redValue << " ";
    outfile << greenValue << " ";
    outfile << blueValue;
  }
}

// Check whether two object has the same coloe
bool ColorClass::checkSameColor(ColorClass &inColor)
{
  return (inColor.redValue == redValue) &&
         (inColor.greenValue == greenValue) &&
         (inColor.blueValue == blueValue);
}

// Adjust color by user specified factor
bool ColorClass::adjustBrightness(double adjFactor)
{
  bool isClipped = false;

  redValue = (int)redValue * adjFactor;
  greenValue = (int)greenValue * adjFactor;
  blueValue = (int)blueValue * adjFactor;
  isClipped = clipNumberInternal();

  return isClipped;
}

// Set pixel to a color
bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
  bool isClipped = false;

  redValue = inRed;
  greenValue = inGreen;
  blueValue = inBlue;
  isClipped = clipNumberInternal();

  return isClipped;
}

// Set pixel to a color
bool ColorClass::setTo(ColorClass &inColor)
{  
  bool isClipped = setTo(inColor.redValue, 
                         inColor.greenValue, 
                         inColor.blueValue);

  return isClipped;
}

// Add two pixel by RGB
bool ColorClass::addColor(ColorClass &rhs)
{
  bool isClipped = false;

  redValue += rhs.redValue;
  greenValue += rhs.greenValue;
  blueValue += rhs.blueValue;
  isClipped = clipNumberInternal();

  return isClipped;
}

// subtract two pixel by RGB
bool ColorClass::subtractColor(ColorClass &rhs)
{
  bool isClipped = false;

  redValue -= rhs.redValue;
  greenValue -= rhs.greenValue;
  blueValue -= rhs.blueValue;
  isClipped = clipNumberInternal();

  return isClipped;
}