/*

File: extractionFunctions.h

Author: Alex Sylvanus

Description: Compilation of declarations of functions that extract information from
valid operation strings

Date: 7/23/2018

*/

#pragma once

#ifndef EXTRACTION_FUNCTIONS_H
#define EXTRACTION_FUNCTIONS_H

// Includes
#include "verificationFunctions.h"

// Namespace
using namespace std;

// Defines

// Structs
typedef struct {
	vector<float> numbers;
	vector<char> operators;
}line_operation_extraction_t;

// Global Variables

// Functions
// Extractions from Line Operation
void numberExtraction(string s, vector<float> &ret);
void operatorExtraction(string s, vector<char> &ret);
void lineOperationStructExtraction(string s, line_operation_extraction_t &soe);

// 
void floatVectorRemoveElement(vector<float> &vecF, int element);
void charVectorRemoveElement(vector<char> &vecF, int element);
void insertValueInOperation(float val, string &oper);
void clearLOE(line_operation_extraction_t &loe);


#endif // !EXTRACTION_FUNCTIONS_H
