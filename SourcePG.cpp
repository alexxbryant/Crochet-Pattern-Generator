/***********************************************************************************
* Author: Alexandra Bryant
* Last Edited : 6 / 26 / 16
* Current Project Description : Console application to build and adjust a simple
* 2 - Dimensional Pattern.
* End Goal: Shiny user-friendly graphical application to allow a user to create
* visual renderings of their desired crochet projects with relative sizes labled in 
* inches or cm (depending on user choice). User will be able to manipulate those
* renderings based on mouse/tablet input or on numerical input and see the size changes
* in real time.
***********************************************************************************/
#include "PatternLib.h"

int main() {
	
	Pattern myPattern;
	myPattern.paMenu();
	myPattern.printPattern();
	return 0;
}