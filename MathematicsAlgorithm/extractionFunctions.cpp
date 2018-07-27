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
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
			// Begin Copying Digits
			num.push_back(s[i]);
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
			ret.push_back(s[i]);
		}
	}
}

void lineOperationStructExtraction(string s, line_operation_extraction_t &soe) {
	float temp = 0;
	string num;
	// Loop through string
	int siz = s.size();
	for (int i = 0; i < siz; i++) {
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
			// Begin Copying Digits
			num.push_back(s[i]);
		}
		else {
			// Convert and store number in vector
			temp = stof(num, 0);
			soe.numbers.push_back(temp);
			soe.operators.push_back(s[i]);
			// Clear temporary number string
			num.clear();

		}
	}
	// Convert remaining number data into vector
	temp = stof(num, 0);
	num.clear();
	soe.numbers.push_back(temp);
}

void evaluateSingleLineOperationExtraction(line_operation_extraction_t loe, string &ret) {
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
	// cout << endl << "Priority Index Size: " << sz << endl;
	if (sz > 0) {
		// If there are, loop through them, and calculate their values, replacing and removing correct indexes
		for (int j = 0; j < sz; j++) {
			index = priorityIndex[j] - j;
			// cout << "Index: " << index << endl;
			if (loe.operators[index] == '*') {
				temp = loe.numbers[index] * loe.numbers[index + 1];
				loe.numbers[index] = temp;
				floatVectorRemoveElement(loe.numbers, index + 1);
				charVectorRemoveElement(loe.operators, index);
			}
			else if (loe.operators[index] == '/') {
				temp = loe.numbers[index] / loe.numbers[index + 1];
				loe.numbers[index] = temp;
				floatVectorRemoveElement(loe.numbers, index + 1);
				charVectorRemoveElement(loe.operators, index);
			}
		}
	}

	// Finish up adding and subtracting
	sz = loe.operators.size();
	for (int k = 0; k < sz; k++) {
		if (loe.operators[0] == '+') {
			temp = loe.numbers[0] + loe.numbers[1];
			loe.numbers[0] = temp;
			floatVectorRemoveElement(loe.numbers, 1);
			charVectorRemoveElement(loe.operators, 0);
		}
		else if (loe.operators[0] == '-') {
			temp = loe.numbers[0] - loe.numbers[1];
			loe.numbers[0] = temp;
			floatVectorRemoveElement(loe.numbers, 1);
			charVectorRemoveElement(loe.operators, 0);
		}
	}
	ret.clear();
	// sz = loe.operators.size();
	/*for (int n = 0; n < sz; n++) {
		// cout << loe.numbers[n] << loe.operators[n];
		ret = ret + to_string(loe.numbers[n]);
		ret = ret + loe.operators[n];
	}*/
	ret = to_string(loe.numbers[0]);
	//cout << "Resulting String: " << ret << endl;
	// 3.5+5.6*1.2/0.578-3.5/9.5
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

void computeSingleOperation(string oper, string &ret) {
	vector<float> nums;
	numberExtraction(oper, nums);
	float res = 0;
	vector<char> op;  
	operatorExtraction(oper, op);

	/*
	switch (op) {
	case '+':
		res = nums[0] + nums[1];
		break;
	case '-':
		res = nums[0] - nums[1];
		break;
	case '*':
		res = nums[0] * nums[1];
		break;
	case '/':
		res = nums[0] / nums[1];
		break;
	default :
		res = 0;
		break;
	}
	*/
	ret = to_string(res);
}

void extractDeepestSingleOperation(string s, vector<line_operation_extraction_t> &loes, vector<int> &LOE_location) {
	int sz = s.size();
	string temp;
	string ret;
	vector<string> vecS;
	line_operation_extraction_t loe_temp;

	// Declare inside parentheses operator signifier
	bool insideSig = false;

	for (int i = 0; i < sz; i++) {
		//ret.push_back(s[i]);
		if (insideSig) {
			temp.push_back(s[i]);
			// cout << s[i];
		}
		else {
			ret.push_back(s[i]);
		}

		if (s[i] == '(') {
			if (!insideSig) {
				insideSig = true;
				
				// cout << "Current total string: " << ret << endl;


			}
			ret = ret + temp;
			temp.clear();
		}
		else if (s[i] == ')') {
			insideSig = false;
			if (temp.size() > 0) {
				temp.pop_back();
				// cout << "Testing String: \"" << temp << "\" " << endl;
				// Get temporary line operation extraction and store it in input vector
				if (checkValidSingleOperationStr(temp)) {
					// cout << "adding to Vector" << endl;
					lineOperationStructExtraction(temp, loe_temp);
					evaluateSingleLineOperationExtraction(loe_temp, temp);
					// cout << "Resulting String: " << temp << endl;
					ret.pop_back();
					ret = ret + temp;
					// cout << "Current total String: " << ret << endl;
					loes.push_back(loe_temp);
					clearLOE(loe_temp);
					//cout << "adding location: " << i - temp.size() << endl;
					//LOE_location.push_back(i - temp.size());
				}
				
				temp.clear();
			}
			// cout << temp << endl;
		}

	}
	cout << endl;
	cout << "Final String Result" << ret << endl;

}

void clearLOE(line_operation_extraction_t &loe) {
	loe.numbers.clear();
	loe.operators.clear();
}

void evaluateLineOperationExtractions(string &s) {
	// Declare temporary storage vectors for SingleOperations extraction
	vector<line_operation_extraction_t> vecLOE;
	vector<int> vecI;

	// Declare string manipulation variables
	int sz = s.size();
	int sz2 = 0;
	string flt_val;
	string temp;
	int extraction_index = 0;

	// Extract Single Operations
	extractDeepestSingleOperation(s, vecLOE, vecI);
	cout << s << endl;
	//sz2 = vecLOE.size();
	// Loop through string
	for (int i = 0; i < sz; i++) {
		// Check if index is a value which needs to be calculated
		//cout << endl;
		if (i != vecI[extraction_index]) {
			temp.push_back(s[i]);
			cout << s[i];
		}
		// If it is an extraction point:
		else {
			if (temp.size() > 0) {
				// temp.pop_back();
				vecI[extraction_index] =- extraction_index;
			}
			evaluateSingleLineOperationExtraction(vecLOE[extraction_index], flt_val);
			// computeSingleOperation(vecS[extraction_index], flt_val);

			// i += vecS[extraction_index].size();
			if (extraction_index < (vecI.size() - 1)) {

				extraction_index++;
				
			}
			
			temp = temp + flt_val;
			flt_val.clear();
		}
	}
	s = temp;
}