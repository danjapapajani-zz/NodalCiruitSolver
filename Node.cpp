
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
#include "ResistorList.h"

using namespace std;


/********************************************
 ************** Constructor  ****************
 *******************************************/
Node::Node(int nodeIDinput) {

    head = new ResistorList();
    nodeID = nodeIDinput;
    next = NULL;
    voltage = 0;
    voltageSet = false;

}

/********************************************
 ************   addResistor  ****************
 *******************************************/
void Node::addResistor(Resistor *newResPointer) {
    
    //add resistors
    head->insertResistor(newResPointer);

}

/********************************************
 ************ accessResistorList  ***********
 *******************************************/
ResistorList * Node::accessResistorList() {
    
    //retirn access pointer to resistor list
    
    return (head); 
    
}

/********************************************
 *********** printAllResistors  *************
 *******************************************/
void Node::printAllResistors() {
    
    head->printAllResistors();
    
}

/********************************************
 ************** getNodeID *******************
 *******************************************/
int Node::getNodeID() {
    
    return(nodeID);
    
}

/********************************************
 **************** getNext *******************
 *******************************************/
Node * Node::getNext() {
    
    return(next);
    
}

/********************************************
 **************** setNext *******************
 *******************************************/
void Node::setNext(Node* newNext) {
    
    next = newNext;
   
}

/********************************************
 ************* connectedResistors ***********
 *******************************************/
int Node::connectedResistors(){
    
    //count the number of resistors connected
    
    return(head->countResistors());
    
}

/********************************************
 ************* setVoltage *******************
 *******************************************/
void Node::setVoltage (double newVoltage){
    
    //set the voltage of a node from the user
    
    voltage = newVoltage;
    voltageSet = true;
    
    cout << "Set: node " << nodeID <<" to " << voltage << " Volts" << endl;

}

/********************************************
 ************* unsetVoltage *****************
 *******************************************/
void Node::unsetVoltage() {
    
    //unset voltage given by user
    
    voltage = 0;
    voltageSet = false;
    
  cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
    
}

/********************************************
 *************** deletResistor **************
 *******************************************/
void Node::deleteResistor(string command) {
    
    //delete either all resistors or the resistor name passed 
    
    head->deleteResistor(command);
    
} 

/********************************************
 ************* isVoltageSet *****************
 *******************************************/
bool Node::isVoltageSet() {
    
    //if the voltage is set, it is not 0 so true is returned
    
    return(voltageSet);
    
}

/********************************************
 *********** setSolveVoltage ****************
 *******************************************/
void Node::setSolveVoltage(double newVoltage) {
    
    //solve sets voltages that should not be remembered outside of solve
    
    voltage = newVoltage;
    
}    

/********************************************
 ********** addResistorsParallel ************
 *******************************************/
double Node::addResistorsParallel() {
      
      //solve function that adds resistors in parallel
      
    return(head->addResistorsParallel());
      
  }
 
/********************************************
 ************ isResConnected ****************
 *******************************************/
bool Node::isResConnected(int nodeID) {
      
      //is the resistor connected to given nodeID
      
      return(head->isResConnected(nodeID));
      
  }
  
/********************************************
 **************** getVoltage ****************
 *******************************************/
double Node::getVoltage() {
      
      return (voltage);
  }
  
/********************************************
 *********** resOfConnected *****************
 *******************************************/  
double Node::resOfConnected(int nodeID) {
      
      //find resistance of connected node to nodeID
      
      return(head->resOfConnected(nodeID));
      
  }
  
/********************************************
 ************* returnResValue ***************
 *******************************************/
double Node::returnResValue (string nameRes) {
      
       //find & return resistance value of given resistor 
       
       return(head->returnResValue(nameRes));
   }
  
/********************************************
 **************  Destructor  ****************
 *******************************************/
Node::~Node() {

}