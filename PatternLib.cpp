#include "PatternLib.h"
#include <iostream>
//overloaded = operator for stitches
stitch& stitch::operator=(const stitch & arg) {
	typeOfStitch = arg.typeOfStitch;
	stitchHeight = arg.stitchHeight;
	stitchLen = arg.stitchLen;
	stitchWidth = arg.stitchWidth;
	return *this;
}
//Fills a new row with the contents of an old row
//Leave any excess capacity unpopulated
void row::copyRow(stitch *newSL) {
	int i = 0;
	for (; i < r_capacity; i++) {
		stitch *temp = new stitch;
		newSL[i] = *temp;
		newSL[i].typeOfStitch = stitchList[i].typeOfStitch;
	}
}
void row::increaseSLCap(int numAdded) {	//Increase the capacity of a row by the amount the user is attempting to add if it is full.
	//Replicate old stitchList
	stitch *incSL = new stitch[numStitchesInRow + numAdded];
	int i = 0;
	for (; i < r_capacity; i++) {
		stitch *temp = new stitch;
		incSL[i] = *temp;
		incSL[i].typeOfStitch = stitchList[i].typeOfStitch;
	}
	for (; i < numStitchesInRow + numAdded; i++) {
		stitch *temp = new stitch;
		incSL[i] = *temp;
	}
	r_capacity = numStitchesInRow + numAdded;
	//Delete old stitchList
	delete[] stitchList;
	//Point it at new stitchList
	stitchList = incSL;
}
Pattern::Pattern() {
	patternName = "Default Empty Pattern";
	numRows = 0;
}
//Menu navigates through basic adjustments to simple, 2-Dimensional pattern using input from the console.
//Input: user selects what they'd like to do with their pattern
void Pattern::paMenu() {
	int choice = 0;
	string choiceAlpha = "";
	cout << "Please select from the available options:" << endl;
	cout << "  1. Create or Edit Pattern \n  2. Print Pattern \n  3. Save Pattern \n  4. Exit" << endl;
	cin >> choiceAlpha;
	while (isalpha(choiceAlpha[0])) {
		cout << "Please enter a selection from the menu:" << endl;
		cout << "  1. Create or Edit Pattern \n  2. Print Pattern \n  3. Exit" << endl;
		cin >> choiceAlpha;
	}
	choice = stoi(choiceAlpha);
	if (choice == 1) {
		editPattern();
	}
	else if (choice == 2) {
		printPattern();
	}
	else if (choice == 3) {
		cout << "Save not yet created" << endl;
	}
	else if (choice == 4) {
		cout << "Thank you for using this Pattern Generator!" << endl;
		exit(0);
	}
	paMenu(); //Menu calls itself until the user elects to exit the program or enters another menu.
}
//Editing a pattern consists of making changes to rows.
//Input: user selects type of change to make
void Pattern::editPattern() {
	if (numRows == 0)
		setName();
	string choice = "";
	int choiceInt = 0;
	cout << "Edit Mode" << endl;
	cout << "Would you like to: " << endl
		<< "  1. Add a row to the pattern \n  2. Edit a row \n  3. Delete a row \n  4. Exit to Main Menu" << endl;
	cin >> choice;
	while (isalpha(choice[0])) {
		cout << "Please choose from the options available: " << endl;
		cout << "  1. Add a row to the pattern \n  2. Edit a row \n  3. Delete a row \n  4. Exit to Main Menu" << endl;
		cin >> choice;
	}
	choiceInt = stoi(choice);
	if (choiceInt == 1) {
		addRow();
	}
	else if (choiceInt == 2) {
		int rowIndex = 0;
		cout << "Select a row to be edited from the pattern: " << endl;
		printPattern();
		cin >> rowIndex;
		while (rowIndex < 0 || rowIndex > numRows) {
			cout << "Please select a row within the pattern! \n: ";
			cin >> rowIndex;
		}
		rowList[rowIndex].editSegmentOfRow(rowIndex);
	}
	else if (choiceInt == 3) {
		deleteRow();
	}
	else if (choiceInt == 4) {
		paMenu();
	}
	paMenu();		//***Change to give an error message and ask for correct input if user does not enter 1-4.
}
void Pattern::printPattern() {
	cout << "Pattern: " << patternName << endl;
	for (int i = 0; i < numRows; i++) {
		cout << i + 1 << ") ";

		for (int j = 0; j < rowList[i].numStitchesInRow; j++) {
			cout << rowList[i].stitchList[j].typeOfStitch << "   ";
		}
		cout << "(" << rowList[i].availableStitchHolesForNextRow << ")" << endl;
	}
}
void row::printRowDetails(int index) {
	cout << index << ") ";
	for (int i = 0; i < numStitchesInRow; i++) {
		cout << setw(6) << stitchList[i].typeOfStitch << "  ";
	}
	cout << endl;
	for (int i = 0; i < numStitchesInRow; i++) {
		cout << setw(6) << i;
	}
	cout << endl;
}
void Pattern::setName() {
	cout << "Enter a name for the pattern: ";
	cin.ignore();
	getline(cin, patternName);
}
//***Still in progress
//Takes in user input to select what sort of change they'd like to make to the stitches within a selected row.
int Pattern::rowMenuChoice() {
	int menuSelection = 0;
	while (menuSelection < 1 || menuSelection > 4) {
		cout << "Enter the number referring to what you'd like to do: " << endl;
		cout << "  1. Add a segment of stitches \n  2. Edit a segment \n  3. Delete a segment \n  4. Finished with this Row" << endl;
		cin >> menuSelection;
		if (menuSelection < 1 || menuSelection > 4)
			cout << "Please select a valid option from those listed.";
	}
	return menuSelection;
}
//***Change cascading if's to be replaced by rowMenuChoice (which should probably be converted into something more like paMenu())
void Pattern::addRow() {
	if (numRows >= p_capacity) {
		//Increase capacity for rows.
		increaseRLCap();
	}

	row *nextRow = new row;
	int menuSelection = 0;
	cout << "Add Row Selected - time to build a row!" << endl;
	menuSelection = rowMenuChoice();
	//Allow user to "add" "edit" or "delete" segements of row
	while (menuSelection != 4) {

		if (menuSelection = 1) {
			//Add segment
			nextRow->addSegementOfRow();
		}
		else if (menuSelection = 2) {
			//Edit segment

		}
		else if (menuSelection = 3) {
			//Delete segment

		}
		menuSelection = rowMenuChoice();
	}
	rowList[numRows] = *nextRow;
	numRows++;
}
//Deletese selected rows. 
//If the user has deleted over 3/4 of the rows initially added, halve the current capacity for rows.
void Pattern::deleteRow() {
	printPattern();
	cout << "Enter the number of the row you would like to delete: ";
	int selection;
	cin >> selection;
	selection--;
	for (int i = selection; i < numRows - 1; i++) {
		rowList[i] = rowList[i + 1];
	}
	numRows--;
	if (numRows < (p_capacity / 4)) {
		//***halve numRows
	}
}

void Pattern::increaseRLCap() {
	//Replicate old rowList
	row *doubledRL = new row[numRows * 2];
	int i = 0;
	for (; i < p_capacity; i++) {
		row *tempRow = new row;
		doubledRL[i] = *tempRow;
		tempRow->r_capacity = rowList[i].r_capacity;
		tempRow->numStitchesInRow = rowList[i].numStitchesInRow;
		rowList[i].copyRow(tempRow->stitchList);
		//Allocate any excess buffer memory with placeholder stitches
		for (int j = 0; j < tempRow->numStitchesInRow; j++) {
			stitch *tempStitch = new stitch;
			tempStitch->stitchHeight = -1;
			tempStitch->stitchLen = -1;
			tempStitch->stitchWidth = -1;
			tempStitch->typeOfStitch = "un-utilized";
			tempRow->stitchList[j] = *tempStitch;
		}
	}
	//Deallocate old pattern memory
	for (int i = 0; i < p_capacity; i++) {
		delete[] rowList[i].stitchList;
		rowList[i].stitchList = NULL;
	}
	delete[] rowList;
	rowList = doubledRL;
	p_capacity = numRows * 2;
}
//If numRows is using a quarter or less of the pattern capacity, halve the pattern capacity for rows
void Pattern::halveRLCap() {
	//Replicate old rowList
	row *halvedRL = new row[p_capacity / 2];
	int i = 0;
	for (; i < numRows; i++) {
		row *tempRow = new row;
		halvedRL[i] = *tempRow;
		tempRow->r_capacity = rowList[i].r_capacity;
		tempRow->numStitchesInRow = rowList[i].numStitchesInRow;
		rowList[i].copyRow(tempRow->stitchList);
	}
	for (; i < p_capacity / 2; i++) {
		row *tempRow = new row;
		halvedRL[i] = *tempRow;
		tempRow->r_capacity = INITIAL_CAPACITY;
		tempRow->numStitchesInRow = 0;
		for (int j = 0; j < tempRow->r_capacity; j++) {
			stitch *tempStitch = new stitch;
			tempStitch->stitchHeight = -1;
			tempStitch->stitchLen = -1;
			tempStitch->stitchWidth = -1;
			tempStitch->typeOfStitch = "un-utilized";
			tempRow->stitchList[j] = *tempStitch;
		}
	}
	//Deallocate old pattern memory
	for (int i = 0; i < p_capacity; i++) {
		delete[] rowList[i].stitchList;
		rowList[i].stitchList = NULL;
	}
	delete[] rowList;
	rowList = halvedRL;
	p_capacity = numRows / 2;
	numRows = numRows / 2;
}
void row::addSegementOfRow() {
	string sName = "";
	string numBuff = "";
	int numStitchesToAdd = 0;
	cout << "Enter TYPE of stitch: ";
	cin >> sName;
	while (!isalpha(sName[0])) {
		cout << "Enter a valid type of stitch: ";
		cin >> sName;
	}
	cout << "Enter NUMBER of " << sName << " stitches: ";
	cin >> numBuff;
	while (isalpha(numBuff[0])) {
		cout << "Invalid Input - please enter the number of stitches:";
		cin >> numBuff;
	}
	numStitchesToAdd = stoi(numBuff);
	availableStitchHolesForNextRow = numStitchesToAdd;
	for (int i = numStitchesInRow; i < numStitchesInRow + numStitchesToAdd; i++) {
		if (i >= r_capacity) {
			increaseSLCap(numStitchesToAdd);
		}
		stitchList[i].typeOfStitch = sName;
		if (sName == "INC" || sName == "inc" || sName == "Inc") {	//An inc represents 2 stitches being made in one opening, increasing total stitch amount by 2.
			availableStitchHolesForNextRow++;
		}
		else if (sName == "DEC" || sName == "Dec" || sName == "dec") {	//A dec represents one opening being skipped, reducing total stitch amount by 1.
			availableStitchHolesForNextRow--;
		}
	}
	//Available holes from the last row must correlate with number of stitches made in next row.
	availableStitchHolesForNextRow += numStitchesInRow;
	numStitchesInRow += numStitchesToAdd;
}
void row::editSegmentOfRow(int index) {
	int startIndex;
	int endIndex;
	string nA = "";
	int stitchAmount = 0;
	string sType;
	printRowDetails(index);
	//Get the range of stitches to be edited
	cout << "Starting index of the range of stitches to be edited: ";
	cin >> startIndex;
	while (startIndex < 0 || startIndex > numStitchesInRow) {
		cout << "Select a starting index from the possible indexes: ";
		cin >> startIndex;
	}
	cout << "Ending index of the range of the stitches to be edited: ";
	cin >> endIndex;
	while (endIndex < 0 || endIndex > numStitchesInRow) {
		cout << "Select a starting index from the possible indexes: ";
		cin >> endIndex;
	}
	//If range is selected backwards, swap start and end
	if (endIndex < startIndex) {
		int temp = startIndex;
		startIndex = endIndex;
		endIndex = temp;
	}
	cout << "You have selected to replace stitches " << startIndex << " to " << endIndex << endl;
	cout << "What would you like to replace that with? \n Type: ";
	cin >> sType;
	cout << "\nNumer of " << sType << ": ";
	cin >> nA;
	while (isalpha(nA[0])) {
		cout << "Enter a numerical value for the number of " << sType << " you'd like to add: ";
		cin >> nA;
	}
	stitchAmount = stoi(nA);
	replaceIntoRow(sType, stitchAmount, startIndex, endIndex);

}
void row::replaceIntoRow(string sType, int stitchAmount, int begRep, int endRep) {
	const int range = abs(endRep - begRep);
	//Make sure array is large enough for the replacement segment
	while ((numStitchesInRow - range + stitchAmount) > numStitchesInRow) {
		increaseSLCap(stitchAmount - range);
	}
	//Save all the stitches after the range to be replaced
	vector<stitch> tempStitchContainer;
	int i;
	for (i = endRep; i <= numStitchesInRow; i++) {
		tempStitchContainer.push_back(stitchList[i]);
	}
	//Add the new stitches in
	for (i = begRep; i < stitchAmount; i++) {
		stitchList[i].typeOfStitch = sType;
		//Refresh dimensions ***
	}
	//Add back the stitches after the range that was replaced
	numStitchesInRow = numStitchesInRow - range + stitchAmount;
	for (; i < numStitchesInRow; i++) {
		stitchList[i] = tempStitchContainer.at(i);
	}
}
//Deletes a portion of a row. Differs from replaceIntoRow in that no stitches are provided
//to replace what gets deleted. Segment to the right of the deleted portion will be shifted
//to meet the left side.
void row::deleteSegementOfRow(stitch *segToDel) {
	//***
}