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
#include "Resistor.h" 
#include "Node.h"

using namespace std;

/********************************************
 ************** Constructor  ****************
 *******************************************/
Resistor::Resistor(string name_, double resistance_, int endpoints_[2]) {

    resistance = resistance_;
    name = name_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    next = NULL;
}

/********************************************
 ************** getResistance  **************
 *******************************************/
double Resistor::getResistance() const {

    //returns resistance value
    
    return (resistance);
}

/********************************************
 ************** setResistance  **************
 *******************************************/
void Resistor::setResistance(double resistance_) {

    //sets new resistance
    
    resistance = resistance_;

}

/********************************************
 **************    print    *****************
 *******************************************/
void Resistor::print() {

    //Prints resistors
    
    cout.width(20);
    cout << left << name;
    cout.width(8);
    cout << right << fixed << setprecision(2) << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}

/********************************************
 ************** clearResistors **************
 *******************************************/
void Resistor::clear() {

    //clears resistors
    
    resistance = 0;
    name = "";
    endpointNodeIDs[0] = 0;
    endpointNodeIDs[1] = 0;
    
}
/********************************************
 **************** getNext  ******************
 *******************************************/
Resistor* Resistor::getNext() {

    return(next);

}

/********************************************
 ************** clearResistors **************
 *******************************************/
void Resistor::assignNext(Resistor* newNext) {

    next=newNext;

}

/********************************************
 **************** getName  ******************
 *******************************************/
string Resistor::getName() {

    return (name);

}

/********************************************
 ************** assignName ******************
 *******************************************/
void Resistor::assignName(string newName){

    name=newName;

}

/********************************************
 ************* getEndPointNode0 *************
 *******************************************/
int Resistor::getEndpointNode0(){

    //return first node that the resistor is connected to
    
    return(endpointNodeIDs[0]);

}

/********************************************
 ************* getEndPointNode1 *************
 *******************************************/
int Resistor::getEndpointNode1(){

    //return the second node that the resistor is connected to
    
    return(endpointNodeIDs[1]);

}

/********************************************
 **************  Destructor  ****************
 *******************************************/
Resistor::~Resistor() {
 
}