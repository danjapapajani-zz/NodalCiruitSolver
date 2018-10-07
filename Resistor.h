/* 
 * File:   Resistor.h
 * Author: papajan6
 *
 * Created on November 6, 2017, 7:49 PM
 */
#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>


using namespace std;

class Resistor {
private:

    Resistor* next;
    double resistance; // resistance (in Ohms)
    string name; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to

public:
    //CONSTRUCTOR:
    Resistor(string name_, double resistance_, int endpoints_[2]);
    
    // returns the resistance
    double getResistance() const; 
    
    //sets resistance 
    void setResistance(double resistance_);

    //prints resistors
    void print();

    //clears resistors
    void clear();

    Resistor* getNext();

    void assignNext(Resistor*);

    string getName();

    void assignName(string);

    //return one nodeID endpoint
    int getEndpointNode0();

    //return one nodeID endpoint
    int getEndpointNode1();
    
    //Destructor:
    ~Resistor();
};

#endif	/* RESISTOR_H */

