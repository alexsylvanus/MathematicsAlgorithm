/*

File: verificationFunctions.h

Author: Alex Sylvanus

Description: Compilation of declarations of functions that verify if calculator input 
string is in proper format

Date: 7/23/2018

*/

#pragma once

#ifndef VERIFICATION_FUNCTIONS_H
#define VERIFICATION_FUNCTIONS_H

// Includes
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// Namespace
using namespace std;

// Defines

// Structs
typedef struct {
	float x;				// Operation being evaluated at value of this variable
	string operation_Str;	// String to convert to mathematical operation
} operation_t;

// Global Variables
const string single_operation_valid_chars = "0123456789.+-*/";
const string operator_valid_chars = "+-*/";
const string digit_valid_chars = "0123456789";

// Functions

/*Check if the input string is in the format (digits | variable)(operator)(digits | variable)
Examples of valid strings
	10+1.6
	3*45
	x-29
	8/x

Examples of invalid strings
	g5-7
	36*
	3+2+9
	+8
*/


bool checkCharacterMatchList(char c, const string char_list);
bool checkSingleOperationValidCharacter(char c);
bool isCharacterOperator(char c);
bool isCharacterDigit(char c);
bool checkValidSingleOperationStr(string s);


#endif // !VERIFICATION_FUNCTIONS_H


