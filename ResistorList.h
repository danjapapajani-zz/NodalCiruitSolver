/* 
 * File:   ResistorList.h
 * Author: papajan6
 *
 * Created on November 6, 2017, 7:52 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H
#include <string>
#include "Resistor.h"


class ResistorList {
    
private:
    Resistor* head;
    
public:
    
    ResistorList();
    
    bool findResistorName(string ResistorName);
    
    void insertResistor(Resistor *newResPointer);
    
    bool modifyResistor(string nameRes, double newResistorValue);
    
    double returnResValue (string nameRes);
    
    bool printResistor (string nameRes);
    
    void printAllResistors ();
    
    int countResistors();
    
    void deleteResistor(string name);
    
    double addResistorsParallel();
    
    //solve function that finds if resistor is connected to node
     bool isResConnected(int);
     
     //solve function that finds resistance of node
     double resOfConnected(int); 

    ~ResistorList();
    
};
#endif	/* RESISTORLIST_H */

