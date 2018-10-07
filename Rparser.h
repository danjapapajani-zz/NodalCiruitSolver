/* 
 * File:   Rparser.h
 * Author: papajan6
 *
 * Created on November 6, 2017, 8:37 PM
 */

#ifndef RPARSER_H
#define	RPARSER_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <cstddef>
#include <iomanip>
#include <stdio.h>
#include <cctype>
#include "Node.h"
#include "Resistor.h"

//Defining all of the functions from Rparser.cpp

/********************************************
 *************   EOF function   *************
 *******************************************/
bool endOfFile(stringstream &lineStream); 

/********************************************
 ************* insertR function *************
 *******************************************/
int insertR(stringstream &lineStream);

/********************************************
 ************* modifyR function *************
 *******************************************/
int modifyR(stringstream &lineStream);

/********************************************
 ************** printR function *************
 *******************************************/
int printR(stringstream &lineStream);

/********************************************
 ************ printNode function ************
 *******************************************/
int printNode(stringstream &lineStream);

/********************************************
 ************* deleteR function *************
 *******************************************/
int deleteR(stringstream &lineStream);

/********************************************
 ***************   Parser   *****************
 *******************************************/
int parser();

#endif	/* RPARSER_H */

