// Libraries
#include <iostream>
#include <string>
#include "callMenu.h"

// Constants
#include "constants.h"

// Classes
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "RectangleClass.h"

// Global functions
#include "printColorMenu.h"
#include "getUserIntOption.h"
#include "setColorOption.h"
#include "setFillOption.h"
#include "addRectangle.h"

using namespace std;

// Author: Zhihao Huang
// Date: October 31, 2019
// Purpose: This is a global function implementation. It is the entire process 
// of the user interface. 

void callMenu()
{
  // Initialize basis image
  int userOption = 0;
  string ppmDirectory;
  cout << "Enter string for PPM image file name to load: ";
  cin >> ppmDirectory;
  ColorImageClass basisImage;

  // Load basis image. Show error message if cannot open ppm file
  if (!basisImage.readFromFile(ppmDirectory))
  {
    cout << "Unable to load the basis image! Program fail!" << endl;
    return;
  }

  // User menu begin
  while (userOption != EXIT_PROGRAM)
  {
  	// Main menu
    cout << "1. Annotate image with rectangle" << endl; 
    cout << "2. Annotate image with pattern from file" << endl;
    cout << "3. Insert another image" << endl;
    cout << "4. Write out current image" << endl;
    cout << "5. Exit the program" << endl;
    cout << "Enter int for main menu choice: ";
    userOption = getUserIntOption();

    // User choose to add rectangle
    if (userOption == ADD_RECTANGLE)
    {
      int recOption = 0;
      bool validRecOption = false;
      
      // User choose method to add rectangle
      while (!validRecOption)
      {
      	// Add rectangle method menu
        cout << "1. Specify upper left "
             << "and lower right corners of rectangle" << endl;
        cout << "2. Specify upper left "
             << "corner and dimensions of rectangle" << endl;
        cout << "3. Specify extent from center of rectangle" << endl;
        cout << "Enter int for rectangle specification method: ";
        recOption = getUserIntOption();

        // Add rectangle with upper left and lower right
        if (recOption == UPP_LEFT_LWR_RIGHT)
        {
          // Initialize variables
          int uppRow = 0, uppCol = 0, lwrRow = 0, lwrCol = 0;
          RowColumnClass uppRowCol, lwrRowCol;
          
          // User input upper left and lower right
          cout << "Enter upper left corner row and column: ";
          uppRow = getUserIntOption();
          uppCol = getUserIntOption();
          cout << "Enter lower right corner row and column: ";
          lwrRow = getUserIntOption();
          lwrCol = getUserIntOption();

          // Create RowColumn Class
          uppRowCol.setRowCol(uppRow, uppCol);
          lwrRowCol.setRowCol(lwrRow, lwrCol);

          // Create Rectangle Class
          RectangleClass inRectangle(uppRowCol, lwrRowCol);
          
          // Add rectangle
          addRectangle(basisImage, inRectangle);
          validRecOption = true;
        }
        // Add rectangle with upper left and dimension
        else if (recOption == UPP_LEFT_DIMENSION)
        {
          // Initialize variables
          int uppRow = 0, uppCol = 0, rowNum = 0, colNum = 0;
          bool provideUpperLeft = true;
          RowColumnClass uppRowCol;
          
          // User input upper left and dimensions
          cout << "Enter upper left corner row and column: ";
          uppRow = getUserIntOption();
          uppCol = getUserIntOption();
          cout << "Enter int for number of rows: ";
          rowNum = getUserIntOption();
          cout << "Enter int for number of columns: ";
          colNum = getUserIntOption();

          // Create upper left RowColumn Class
          uppRowCol.setRowCol(uppRow, uppCol);

          // Create rectangle class providing uppder left
          RectangleClass inRectangle(uppRowCol,
                                     rowNum,
                                     colNum,
                                     provideUpperLeft);
          
          addRectangle(basisImage, inRectangle);
          validRecOption = true;
        }
        // Add rectangle with center and dimension
        else if (recOption == CENTER_DIMENSION)
        {
          // Initialize variables
          int centerRow = 0, centerCol = 0, halfRow = 0, halfCol = 0;
          bool provideUpperLeft = false;
          RowColumnClass inRowCol;
          
          // User input center RowColumn and dimension
          cout << "Enter rectangle center row and column: ";
          centerRow = getUserIntOption();
          centerCol = getUserIntOption();
          cout << "Enter int for half number of rows: ";
          halfRow = getUserIntOption();
          cout << "Enter int for half number of columns: ";
          halfCol = getUserIntOption();

          // Create center RowColumn
          inRowCol.setRowCol(centerRow, centerCol);

          // Create Rectangle class providing center
          RectangleClass inRectangle(inRowCol, 
                                     halfRow,
                                     halfCol,
                                     provideUpperLeft);
          
          // Add rectangle
          addRectangle(basisImage, inRectangle);
          validRecOption = true;
        }
        // User choose invalid rectangle option
        else
        {
          cout << "Invalid option. Please re-enter your option!" << endl;
        }
      }
    }
    // User choose to add pattern
    else if (userOption == ADD_PATTERN)
    {
      // Initialize user options
      string patternForInsertDir;
      ColorClass patternColor;
      RowColumnClass uppLeft;
      int rowNum = 0, colNum = 0, colorOption = 0;
      bool validColorOption = false;

      // cin directory of ppm for insert
      cout << "Enter string for file name containing pattern: ";
      cin >> patternForInsertDir;

      // cin upper left corner location
      cout << "Enter upper left corner of pattern row and column: ";
      rowNum = getUserIntOption();
      colNum = getUserIntOption();
      uppLeft.setRowCol(rowNum, colNum);

      // Select color
      while (!validColorOption)
      {
        printColorMenu();
        cout << "Enter int for pattern color: ";
        colorOption = getUserIntOption();
        validColorOption = setColorOption(colorOption, patternColor);
      }

      // insert pattern
      basisImage.addAnnotation(patternForInsertDir, uppLeft, patternColor);
    }
    // User choose to add image
    else if (userOption == ADD_IMAGE)
    {
      // Initialize user options
      string ppmForInsertDir;
      ColorImageClass ppmForInsert;
      ColorClass transColor;
      RowColumnClass uppLeft;
      int rowNum = 0, colNum = 0, colorOption = 0;
      bool validColorOption = false;

      // cin directory of ppm for insert
      cout << "Enter string for file name of PPM image to insert: ";
      cin >> ppmForInsertDir;
      
      if (ppmForInsert.readFromFile(ppmForInsertDir))
      {
        cout << "Enter upper left corner to insert image row and column: ";
        rowNum = getUserIntOption();
        colNum = getUserIntOption();
        uppLeft.setRowCol(rowNum, colNum);

        // Select color
        while (!validColorOption)
        {
          printColorMenu();
          cout << "Enter int for transparecy color: ";
          colorOption = getUserIntOption();
          validColorOption = setColorOption(colorOption, transColor);
        }

        // insert ppm
        basisImage.addPPMImage(ppmForInsert, uppLeft, transColor);
      }
    }
    // User choose to output current image
    else if (userOption == OUTPUT_IMAGE)
    {
      string outputDirectory;
      cout << "Enter string for PPM file name to output: ";
      cin >> outputDirectory;
      basisImage.writeToFile(outputDirectory);
    }
    // User choose to exit program
    else if (userOption == EXIT_PROGRAM)
    {
      ;
    }
    // User choose invalid options
    else
    {
      cout << "Invalid option. Please re-enter your option!" << endl;
      userOption = 0;
    }
  }
}