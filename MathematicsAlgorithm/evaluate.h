/*

File: evaluate.h

Author: Alex Sylvanus

Description: Declarations of functions that evaluate mathematical expressions in string form

Date: 7/27/2018

*/

#pragma once


#ifndef EVALUATE_H
#define EVALUATE_H

// Includes
#include "extractionFunctions.h"

// Functions
void evaluateSingleLOE(string &s); // This function takes a string in the LOE format and reduces the operation to a single value
void evaluateInnerLOEs(string &s); // This function takes a string in standard format and reduces the inner LOEs
void evaluateExpression(string &s);


#endif // !EVALUATE_H
