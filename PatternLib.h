//Left during: allowing user to add, edit or remove segements of row pattern menu. 
/***********************************************************************************
* PatternLib.h 
* Author: Alexandra Bryant
* Last Edited: 6/26/16
* Current Project Description: Console application to build and adjust a simple 
* 2-Dimensional Pattern.
* Defines the structs for row and stich and the class for Pattern.
* Patterns are composed of rows, and rows are composed of stitches.
* Currently the Pattern object is one that can create a basic 2-Dimensional 
* pattern from user-generated input that can be dynamically adjusted and printed.
*------------------------------------------------------------------------------------
* Pattern will eventually be inherited as a base class for the sub class
* of 3-Dimensional patterns which have added features. Input will change from
* number of stiches/row and rows/pattern to given size dimensions in cm or inches,
* size of yarn, and size of hook. User will be able to visually drag and manipulate
* the rendering of the final object, and print out an accurate pattern for their 
* custom object.
************************************************************************************/
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

const int INITIAL_CAPACITY = 5;
//Physical dimensions needed for calculating the current size of any pattern.
//Default stitch given unsuable dimensions to flag that they are not based off user input.
struct stitch {
	string typeOfStitch = "";
	double stitchLen = -1;
	double stitchHeight = -1;
	double stitchWidth = -1;
	stitch& operator=(const stitch &);
};
//Rows grow and shrink in stitch number based on user input.
struct row {
	stitch *stitchList = new stitch[INITIAL_CAPACITY];
	int numStitchesInRow = 0;
	int availableStitchHolesForNextRow = 0;
	int r_capacity = INITIAL_CAPACITY;
	void copyRow(stitch *);
	void increaseSLCap(int);
	void halveSLCap();				//Needs written
	void addSegementOfRow();
	void editSegmentOfRow(int index);
	void replaceIntoRow(string, int, int, int);
	void deleteSegementOfRow(stitch *);
	void printRowDetails(int index);
};
//Patterns grow and shrink in row number based on user input.
class Pattern {
public:
	Pattern();
	string getName() { return patternName; }
	int getNumRows() { return numRows; }
	void printPattern();
	void addRow();
	void deleteRow();
	void setName();
	void increaseRLCap();
	void halveRLCap();
	void editPattern();
	int rowMenuChoice();
	void paMenu();
private:
	string patternName;
	int numRows;
	int p_capacity = INITIAL_CAPACITY;
	row *rowList = new row[INITIAL_CAPACITY];

};