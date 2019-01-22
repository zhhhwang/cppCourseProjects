#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

// Libraries
#include <iostream>
#include <fstream>

// Constants
#include "constants.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class definition. The ColorClass is just a 
// pixel. Some methods can be used to modify the pixel. 

class ColorClass
{
  public:
    // Default ctor and value ctor
    ColorClass();
    ColorClass(int inRed, int inGreen, int inBlue);

    // Simply set the color to the specified ones
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();

    // Read and write color from file
    bool readColorFromFile(ifstream &infile);
    void writeColorToFile(ofstream &outfile, bool endOfRow);

    // check whether two object represent the same color
    bool checkSameColor(ColorClass &inColor);

    // Set the color to appointed values
    bool setTo(int inRed, int inGreen, int inBlue);

    // Set the the color to a given ColorClass object
    bool setTo(ColorClass &inColor);

    // Multiplies  RGB value by the adjustment factor 
    bool adjustBrightness(double adjFactor); 
  
    // Add/subtract a ColorClass object value 
    bool addColor(ColorClass &rhs); 
    bool subtractColor(ColorClass &rhs);

    // Print out RGB value
    void printComponentValues();

  private:
    // Attributes
    int redValue;
    int greenValue;
    int blueValue; 

    // Helper function for determining whether there is a clipping
    bool clipNumberInternal(); 
    int clipNumber(int targetNum, int minVal, int maxVal);
    
    // Helper function for checking reading RGB successfully
    bool checkInfile(ifstream &infile, int &outputInt);
};

# endif