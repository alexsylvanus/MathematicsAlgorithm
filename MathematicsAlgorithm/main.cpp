// File: main.cpp
/*

Author: Alex Sylvanus

Description: main function for calculator program

Date: 7/23/2018

*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "evaluate.h"

const string inpt = "-2.5+(1.05+((x-4.7*4)/(x-6)+1.9)*2.19)*5.8";
const string inpt2 = "19.5-x+4.2*4.8/x+x*2.5+1.4";
const string inpt3 = "4.58-6.7/-3.7*x+5.58";

using namespace std;

int main() {

	string s;
	string s1;
	vector<int> t;
	vector<string> vecS;
	vector<line_operation_extraction_t> vecLOE;
	// cout << "Enter a string with a number: ";
	// cin >> s;
	s = inpt;
	float f = 2.17;
	insertValueInOperation(f, s);
	line_operation_extraction_t loe;
	cout << s << endl;
	if (checkValidSingleOperationStr(s)) {
		cout << "Valid Operation" << endl;
		// lineOperationStructExtraction(s, loe);
		// evaluateSingleLineOperationExtraction(loe, s1);
		evaluateSingleLOE(s);
		cout << s << endl;
	}
	else {
		cout << "Invalid Operation" << endl;
		evaluateExpression(s);
		cout << s << endl;
	}
	// numberExtraction(s, t);
	//int sz = t.size();
	//for (int i = 0; i < sz; i++) {
	//	cout << t[i] << endl;
	//}
	cout << "Enter integer to exit: ";
	int j;
	cin >> j;
}