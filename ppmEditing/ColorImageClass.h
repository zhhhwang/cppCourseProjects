#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

// Libraries
#include <iostream>
#include <string>
#include <fstream>

// Constants
#include "constants.h"

// Classes
#include "ColorClass.h"
#include "RectangleClass.h"
#include "RowColumnClass.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is the class definition. The ColorImageClass is just a 
// image. Some methods can be used to modify the image. 

class ColorImageClass
{
  public:
    // Default ctor
    ColorImageClass();

    // Default dtor
    ~ColorImageClass();

    // Read and write from file
    bool readFromFile(const string fileDirectory);
    void writeToFile(const string fileDirectory);

    // Draw a rectangle on the object
    void drawRectangle(RectangleClass &inRectangle,
                       ColorClass &targetColor,
                       bool fillIn); 

    // Add an annotation on the object
    bool addAnnotation(const string fileDirectory,
                       RowColumnClass &startRowCol,
                       ColorClass &targetColor);

    // Add another object on the object
    void addPPMImage(ColorImageClass &targetImg,
                     RowColumnClass &startRowCol,
                     ColorClass &transColor);

    // Initlaize all pixels to a given color
    void initializeTo(ColorClass &inColor);

    // Add image(s)
    bool addImageTo(ColorImageClass &rhsImg);

    // Obtain/change the color for a particular pixel
    bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
    bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);

    // Print out the entire image
    void printImage();

  private:
    // Attributes
    ColorClass** pixel;
    int rowNum;
    int colNum;
    // int rbgFullValue; Not sure if this is necessary

    // Helper function for checking bounrd
    bool indexCheckInternal(int rowIndex, int colIndex);

    // Helper function for read in by pixel
    bool checkInfile(ifstream &infile, int &outputInt);
};

#endif