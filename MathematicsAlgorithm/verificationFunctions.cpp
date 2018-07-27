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
	bool ret = true;
	// loop over string
	int sz = s.size();
	int op_cnt = 0;
	// Check if first or last character is an operator, fail if true
	if (isCharacterOperator(s[0]) || isCharacterOperator(s[sz - 1])) {
		return false;
	}

	for (int i = 0; i < sz; i++) {
		if (!checkSingleOperationValidCharacter(s[i])) {
			return false;
		}
		if (isCharacterOperator(s[i])) {
			if (!isCharacterDigit(s[i - 1]) || !isCharacterDigit(s[i + 1])) {
				return false;
			}
			op_cnt++;
		}

	}
	//if (op_cnt > 1) {
	//	ret = false;
	//}
	return ret;
}
