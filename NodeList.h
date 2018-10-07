/* 
 * File:   NodeList.h
 * Author: papajan6
 *
 * Created on November 6, 2017, 7:53 PM
 */

#ifndef NODELIST_H
#define	NODELIST_H
#include <string>
#include "Node.h"
#include "Resistor.h"

class NodeList {
    
private:
    Node* head;

   
public:
    
    //constructor ?
    NodeList();
    
    //find a node and return pointer to it or return NULL
    Node* findNode(int nodeID);
    
    bool changeResValue(string nameRes, double resistorValue);
    
    void insertNode(Node* newNode);
    
    void insertResistor(Resistor *, int);
    
    bool findResName (string nameRes);
    
    double returnResValue (string nameRes);
    
    void printResistor(string nameRes);
    
    void printNode(int nodeID);
    
    void printAllNodes();
    
    void setVoltage(int nodeID, double voltage);
    
    void unsetVoltage(int nodeID);
    
    void deleteResistors(string command);
    
    void solve();
    
    
    
    //destructor ?
    ~NodeList(); 


};

#endif	/* NODELIST_H */

