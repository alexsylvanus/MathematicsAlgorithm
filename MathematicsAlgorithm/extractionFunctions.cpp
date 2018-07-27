/*

File: extractionFunctions.cpp

Author: Alex Sylvanus

Description: Compilation of declarations of functions that extract information from
valid operation strings

Date: 7/23/2018

*/

// Include
#include "extractionFunctions.h"

void numberExtraction(string s, vector<float> &ret) {
	float temp = 0;
	string num;

	// Loop through string
	int siz = s.size();
	for (int i = 0; i < siz; i++) {
		if (isCharacterDigit(s[i]) || s[i] == '.') {
			// Begin Copying Digits
			num.push_back(s[i]);
		}
		else if (s[i] == '-') {
			// Depending on if the - is following a digit or an operator, either add it to the string or terminate and convert current string
			if (num.size() > 0) {
				temp = stof(num, 0);
				ret.push_back(temp);
				num.clear();
			}
			else {
				num.push_back(s[i]);
			}
		}
		else {
			// Convert and store number in vector
			temp = stof(num, 0);
			ret.push_back(temp);
			// Clear temporary number string
			num.clear();

		}
	}
	// Convert remaining number data into vector
	temp = stof(num, 0);
	num.clear();
	ret.push_back(temp);
}

void operatorExtraction(string s, vector<char> &ret) {
	int sz = s.size();
	for (int i = 0; i < sz; i++) {
		if (isCharacterOperator(s[i])) {
			if (s[i] == '-') {
				if (i > 0 && !isCharacterOperator(s[i - 1])) {
					ret.push_back(s[i]);
				}
			}
			else {
				ret.push_back(s[i]);
			}
		}
	}
}

void lineOperationStructExtraction(string s, line_operation_extraction_t &soe) {
	numberExtraction(s, soe.numbers);
	operatorExtraction(s, soe.operators);
}


void floatVectorRemoveElement(vector<float> &vecF, int element) {
	if (vecF.size() > 0) {
		vecF.erase(vecF.begin() + element);
	}
	else {
		cout << "Vector Empty" << endl;
	}
}

void charVectorRemoveElement(vector<char> &vecC, int element) {
	if (vecC.size() > 0) {
		vecC.erase(vecC.begin() + element);
	}
	else {
		cout << "Vector Empty" << endl;
	}
}

void insertValueInOperation(float val, string &oper) {
	int sz = oper.size();
	string flt_val = to_string(val);
	string temp;
	for (int i = 0; i < sz; i++) {
		if (oper[i] != 'x') {
			temp.push_back(oper[i]);
		}
		else {
			temp = temp + flt_val;
		}
	}
	oper = temp;
}

void clearLOE(line_operation_extraction_t &loe) {
	loe.numbers.clear();
	loe.operators.clear();
}