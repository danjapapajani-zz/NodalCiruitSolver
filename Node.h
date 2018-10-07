/* 
 * File:   Node.h
 * Author: papajan6
 *
 * Created on November 6, 2017, 7:51 PM
 */

#ifndef NODE_H
#define NODE_H
#include <string>

#include "Resistor.h"
#include "ResistorList.h"

class Node
{
private:
    
   Node* next;
   int nodeID; 
   ResistorList* head; 
   bool voltageSet;
   double voltage;

public:
    
   //CONSTRUCTOR:
   Node(int nodeIDinput); 
   
   //DESTRUCTOR:
   ~Node();

   void addResistor(Resistor *newResPointer);  
   
   ResistorList* accessResistorList();
   
   void printAllResistors();
   
   int getNodeID(); 
   
   Node* getNext();
   
   void setNext(Node*);
   
   Node* getHead();
   
   int connectedResistors();
   
   void setVoltage (double voltage);
   
   void unsetVoltage();
   
   void deleteResistor(string);
   
   bool isVoltageSet();
   
   void setSolveVoltage(double);
   
   double addResistorsParallel();
   
   //solve function: is a resistor connected to a specific node
   bool isResConnected(int); 
   
   double getVoltage();
   
   //solve function: return resistance of connected node
   double resOfConnected (int nodeID);
   
   double returnResValue (string nameRes);
};

#endif	/* NODE_H */

