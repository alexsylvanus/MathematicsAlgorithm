/*

File: evaluate.cpp

Author: Alex Sylvanus

Description: Functions that evaluate mathematical operations in string format

Date: 7/27/2018

*/

// Includes
#include "evaluate.h"

// Functions
void evaluateSingleLOE(string &s) {
	// Get structure from input string
	line_operation_extraction_t loe;
	lineOperationStructExtraction(s, loe);

	// Declare indexing and storage variables
	int sz = loe.operators.size();
	int index = 0;
	vector<int> priorityIndex;
	float temp;

	// Identify indexes of operations to perform first
	for (int i = 0; i < sz; i++) {
		if (loe.operators[i] == '*' || loe.operators[i] == '/') {
			priorityIndex.push_back(i);
		}
	}

	// Check if there are any priority operations
	sz = priorityIndex.size();
	if (sz > 0) {
		// If there are, loop through them, and calculate their values, replacing and removing correct indexes
		for (int j = 0; j < sz; j++) {
			/* Assuming that an operation is performed on each iteration, the index of the current operation will shift down each time,
			because the operation reduces the size of the operations vector, as noted later.*/
			index = priorityIndex[j] - j;

			// Check whether to multiply or divide
			if (loe.operators[index] == '*') { // Multiply
				temp = loe.numbers[index] * loe.numbers[index + 1];
				loe.numbers[index] = temp;

				// Reduce LOE structs
				floatVectorRemoveElement(loe.numbers, index + 1);
				charVectorRemoveElement(loe.operators, index); // Reduces where next operator index will be
			}
			else if (loe.operators[index] == '/') { // Divide
				temp = loe.numbers[index] / loe.numbers[index + 1];
				loe.numbers[index] = temp;

				// Reduce LOE structs
				floatVectorRemoveElement(loe.numbers, index + 1);
				charVectorRemoveElement(loe.operators, index); // Reduces where the next operator index will be
			}
		}
	}

	// Finish up adding and subtracting remaining operations
	sz = loe.operators.size();
	for (int k = 0; k < sz; k++) {
		// Check whether to add or subtract
		if (loe.operators[0] == '+') { // Add
			temp = loe.numbers[0] + loe.numbers[1]; // Always perform calculation between first two numbers
			loe.numbers[0] = temp; // Replace first number with result

			// Reduce LOE structs
			floatVectorRemoveElement(loe.numbers, 1);
			charVectorRemoveElement(loe.operators, 0);
		}
		else if (loe.operators[0] == '-') { // Subtract
			temp = loe.numbers[0] - loe.numbers[1]; // Always perform calculation between first two numbers
			loe.numbers[0] = temp; // Replace first number with result

			// Reduce LOE structs
			floatVectorRemoveElement(loe.numbers, 1);
			charVectorRemoveElement(loe.operators, 0);
		}
	}

	// Clear original string and replace with converted float result
	s.clear();
	s = to_string(loe.numbers[0]);
}

void evaluateInnerLOEs(string &s) {
	int sz = s.size();
	string temp;
	string ret;
	vector<string> vecS;

	// Declare inside parentheses operator signifier
	bool insideSig = false;

	// Loop through string
	for (int i = 0; i < sz; i++) {
		if (insideSig) {
			temp.push_back(s[i]);
		}
		else {
			ret.push_back(s[i]); // Only record return string while not inside parentheses
		}

		if (s[i] == '(') {
			insideSig = true;
			ret = ret + temp; // This ensures that what got recorded by the temp variable gets copied onto return string
			temp.clear();
		}
		else if (s[i] == ')') {
			insideSig = false;
			if (temp.size() > 0) {
				temp.pop_back(); // Don't put the ) in the temporary string
				if (checkValidSingleOperationStr(temp)) { // If it's a proper line operation, evaluate it, and place it in the return string
					evaluateSingleLOE(temp);
					ret.pop_back();
					ret = ret + temp;
				}
				temp.clear(); // Clear the temporary string for new calculation
			}
		}
	}
	// Replace input string with return string
	s.clear();
	s = ret;
}

void evaluateExpression(string &s) {
	if (!checkValidSingleOperationStr(s)) { // Keep reducing the expression until it is a single line operation
		while (!checkValidSingleOperationStr(s)) {
			evaluateInnerLOEs(s);
		}
	}
	// Evaluate the resulting single line operation
	evaluateSingleLOE(s);
}