/*

File: verificationFunctions.cpp

Author: Alex Sylvanus

Description: Compilation of functions that verify if calculator input string
is in proper format

Date: 7/23/2018

*/

// Includes
#include "verificationFunctions.h"

bool checkCharacterMatchList(char c, const string char_list) {
	int sz = char_list.size();
	bool ret = false;
	for (int i = 0; i < sz; i++) {
		if (c == char_list[i]) {
			ret = true;
		}
	}
	return ret;
}

bool checkSingleOperationValidCharacter(char c) {
	return checkCharacterMatchList(c, single_operation_valid_chars);
}

bool isCharacterOperator(char c) {
	return checkCharacterMatchList(c, operator_valid_chars);
}

bool isCharacterDigit(char c) {
	return checkCharacterMatchList(c, digit_valid_chars);
}

bool checkValidSingleOperationStr(string s) {
	// Declare return variable
	bool ret = true;
	// loop over string
	int sz = s.size();
	int op_cnt = 0;

	// Check if first or last character is an operator, first not being a negative indicator, fail if true
	if (isCharacterOperator(s[0]) && (s[0] != '-')) {
		return false;
	}
	else if (isCharacterOperator(s[sz - 1])) {
		return false;
	}

	for (int i = 0; i < sz; i++) {
		// If an invalid character is detected
		if (!checkSingleOperationValidCharacter(s[i])) {
			return false;
		}

		// Check that when an operator is detected, prior to the operator is a digit, and after the operator is either a '-' or a digit
		if (isCharacterOperator(s[i])) {
			if (i > 0) {
				if (!isCharacterDigit(s[i - 1]) && s[i] != '-') {
					return false;
				}
				else if (!isCharacterDigit(s[i+1]) && s[i+1] != '-') {
					return false;
				}
			}
		}
	}
	return ret;
}
