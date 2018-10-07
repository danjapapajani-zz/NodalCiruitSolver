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
#include "NodeList.h" 
#include <cmath>

#define MIN_ITERATION_CHANGE 0.0001 

using namespace std;

/********************************************
 ************** Constructor  ****************
 *******************************************/
NodeList::NodeList() {
    head=NULL;
}

/********************************************
 ***************  findNode ******************
 *******************************************/
Node * NodeList::findNode(int nodeID) {

    //finds a node with the same ID and returns pointer to it or NULL
    
    Node* tmpResPointer = head;

    //if the list empty the node doesn't exist
    if (head == NULL)
        return (NULL);

    //traverse through the list and check if nodeID exists
    while (tmpResPointer != NULL) {
        if (tmpResPointer->getNodeID() == nodeID)
            return (tmpResPointer);
        else
            tmpResPointer = tmpResPointer->getNext();
    }

    //no node with that ID was found 
    return (NULL);
}

/********************************************
 ************** insertNode   ****************
 *******************************************/
void NodeList::insertNode(Node *newNodePointer) {

    //insert node
    
    //empty list case
    if (head == NULL) {
        head = newNodePointer;
        newNodePointer->setNext(NULL);
        return;
    } else {

        //creatE temp pointer 
        Node* prev = NULL;

        //create second temp pointer that looks ahead to sort
        Node* current = head;

        //only one node in list
        if (current->getNext() == NULL) {
            if(current->getNodeID() < newNodePointer->getNodeID()){

            current->setNext(newNodePointer);
            newNodePointer = NULL;
            return;
          }
            else{
                head = newNodePointer;
                newNodePointer->setNext(current);
                return;
            }

        }


        while (current != NULL) {

            // when current moves from head assign prev to new head
           
            if (current->getNodeID() < newNodePointer->getNodeID()) {

                //advance the pointers
                if (current == head)
                    prev = head;
                else
                    prev = prev->getNext();

                current = current->getNext();
            } else {

                if (prev == NULL) {
                    head = newNodePointer;
                    newNodePointer->setNext(current);
                    return;
                }
                
                //beep beep I want to insert!
                else {
                    prev->setNext(newNodePointer);
                    newNodePointer->setNext(current);
                    return;
                }
            }
        }

        //second ptr reached NULL which means we reached the end of the list 
        prev->setNext(newNodePointer);
        newNodePointer = NULL;
        return;
    }
}

/********************************************
 *********** insertResistor  ****************
 *******************************************/
void NodeList::insertResistor(Resistor *newResPointer, int newNodeID) {

    //inserts resistor into node of give ID
    
    if (findNode(newNodeID) == NULL) { //there is no node with this ID.

        //create a new pointer to a node
        Node *newNodePointer = new Node(newNodeID);

        //new resistor was added to this new node
        newNodePointer->addResistor(newResPointer);

        //insert newNode into node linked list, "NodeList"
        this->insertNode(newNodePointer);

    } else {
        //assign the pointer that findNode returns to the node that already has this ID
        Node* existingNode = (this->findNode(newNodeID));

        existingNode->addResistor(newResPointer);
    }
}

/********************************************
 ***********  changeResValue ****************
 *******************************************/
bool NodeList::changeResValue(string nameRes, double resistorValue) {

    //find a resistor name and return a pointer to it
    
    int countRes = 0;
    //empty list case
    Node* nodeListPointer = head;
    if (head == NULL)
        return (0);

    //while loop that traverses though all nodes
    while (nodeListPointer != NULL & countRes < 2) {

        //create new pointer to resistor list
        ResistorList *resListPointer = (nodeListPointer->accessResistorList());

        //while loop that traverses through all resistorlist (all resistors within a node)
        if (resListPointer != NULL) {

            if (resListPointer->modifyResistor(nameRes, resistorValue)) {
                countRes++;
            }
        }
        nodeListPointer = nodeListPointer->getNext();
    }

    return countRes;
}

/********************************************
 ************* findResName ******************
 *******************************************/
bool NodeList::findResName(string nameRes) {
    //for ModifyR when old resistance value is needed     
        
    //empty list case
    Node* nodeListPointer = head;
    if (head == NULL)
        return false;

    //while loop that traverses though all nodes
    while (nodeListPointer != NULL) {

        if (nodeListPointer->returnResValue(nameRes) != 0) {
            return true;
        }

        nodeListPointer = nodeListPointer->getNext();
    }
    return false;
}

/********************************************
 ************* returnResValue ***************
 *******************************************/
double NodeList::returnResValue(string nameRes) {

    //return the resistance value of given resistor name
    
    //empty list case
    Node* nodeListPointer = head;
    if (head == NULL)
        return (0);

    //while loop that traverses though all nodes
    while (nodeListPointer != NULL) {

        if (nodeListPointer->returnResValue(nameRes) != 0) {
            return (nodeListPointer->returnResValue(nameRes));

        }

        nodeListPointer = nodeListPointer->getNext();
    }
    return 0;
}

/********************************************
 ************* printResistor  ***************
 *******************************************/
void NodeList::printResistor(string nameRes) {

    //print resistor with specific name 
    
    //empty list case
    Node* nodeListPointer = head;
    if (head == NULL)
        return;

    //while loop that traverses though all nodes
    while (nodeListPointer != NULL) {

        //create new pointer to resistor list
        ResistorList *resListPointer = (nodeListPointer->accessResistorList());

        //while loop that traverses through all resistorlist (all resistors within a node)
        if (resListPointer != NULL) {

            if (resListPointer->printResistor(nameRes)) {
                return;
            }
        }
        nodeListPointer = nodeListPointer->getNext();
    }
    return;
}

/********************************************
 *************** printNode  *****************
 *******************************************/
void NodeList::printNode(int nodeID) {

    //print an entire node
    
    cout << "Print:" << endl;

    //empty list case
    if (head == NULL) {
        return;
    } else {

        bool nodeFound = false;

        //create one temporary pointer 
        Node* tmp = head;

        while (tmp != NULL && !nodeFound) {

            if ((tmp->getNodeID()) == nodeID) {
                nodeFound = true;

                cout << setprecision(2) << "Connections at node " <<
                        tmp->getNodeID() << ": " <<
                        tmp->connectedResistors() << " resistor(s)"
                        << endl;

                //print all resistors at that node
                tmp->printAllResistors();
            }
            //advance the pointer
            tmp = tmp->getNext();

        }
    }

    return;
}

/********************************************
 *************  printAllNodes ***************
 *******************************************/
void NodeList::printAllNodes() {

    //print all of the nodes that exist

    //empty list case
    if (head == NULL) {
        //node list is empty
        return;
    } else {
        //create one temporary pointer 
        Node* tmp = head;

        if (tmp->connectedResistors() == 0) {
            return;
        }

        while (tmp != NULL) {
            if (tmp->accessResistorList() != NULL) {

                cout << "Connections at node " << tmp->getNodeID() << ": " << tmp->connectedResistors() << " resistor(s)" << endl;
                //print all resistors at that node
                tmp->printAllResistors();

                //advance the pointer
                tmp = tmp->getNext();
            }
        }
    }
    return;
}

/********************************************
 **************** setVoltage ****************
 *******************************************/
void NodeList::setVoltage(int nodeID, double voltage) {

    //set a voltage of given node with given value

    Node* changeVNode = (this->findNode(nodeID));

    changeVNode->setVoltage(voltage);

}

/********************************************
 ************* unsetVoltage *****************
 *******************************************/
void NodeList::unsetVoltage(int nodeID) {

    //unset voltage of given node
    
    Node* changeVNode = (this->findNode(nodeID));

    changeVNode->unsetVoltage();

}

/********************************************
 ************* deleteResistors **************
 *******************************************/
void NodeList::deleteResistors(string command) {

    //delete either all resistors or given resistor
    
    //empty list case
    if (head == NULL) {
        //node list is empty
        return;
    }

    Node* tmp = head;

    //go through all of the nodes and delete the resistor or all of them
    while (tmp != NULL) {

        //delete all resistors at that node
        tmp->deleteResistor(command);

        //advance the pointer
        tmp = tmp->getNext();
    }

    if (command != "all") {
        cout << "Deleted: resistor " << command << endl;
    } else {
        cout << "Deleted: all resistors" << endl;
    }
    return;
}

/********************************************
 **************** Solve *********************
 *******************************************/
void NodeList::solve() {

    Node* currentNode = head;
    double denominator1 = 0, term1 = 0, term2 = 0, finalValue = 0;

    /*
     * 
     * set all unassigned voltages to 0
     * 
     */

    bool userSetVoltage = false;
    while (currentNode != NULL) {
        if (!currentNode->isVoltageSet())
            currentNode->setSolveVoltage(0);
        else {
            //there is at least one node with a user-set voltage
            userSetVoltage = true;
        }
        currentNode = currentNode->getNext();
    }

    /*
     * 
     * Error Check & message
     * 
     */

    if (!userSetVoltage) {
        cout << "Error: no nodes have their voltage set" << endl;
        return;
    }

    /*
     * 
     * SOLVE:
     * 
     */


    double maxChange = 0;
    currentNode = head;

    do { //while the change is greater than max

        maxChange = 0;
        currentNode = head;

        // loops through every node
        while (currentNode != NULL) {
            
            term2 = 0;
            finalValue = 0;
            
            if (!currentNode->isVoltageSet()) {

                double initialVoltageValue = currentNode->getVoltage();

                if (!currentNode->isVoltageSet() && currentNode != NULL) {

                    denominator1 = currentNode->addResistorsParallel(); //add all resistors in parallel
                    term1 = 1 / denominator1;

                    Node* otherNode = head;

                    while (otherNode != NULL) {

                        if (
                                otherNode != currentNode &&
                                otherNode->isResConnected(currentNode->getNodeID())
                            ) {
                            term2 = term2 + (otherNode->getVoltage() / otherNode->resOfConnected(currentNode->getNodeID()));
                        }

                        otherNode = otherNode->getNext();
                    }
                }

                finalValue = term1 * term2;

                currentNode->setSolveVoltage(finalValue);

                if (abs(finalValue - initialVoltageValue) > maxChange) {
                    maxChange = abs(finalValue - initialVoltageValue);
                }
            }
            currentNode = currentNode->getNext();
        }

    } while (maxChange > MIN_ITERATION_CHANGE);

    //print out final values
    Node* nodePointer = head;

    cout << "Solve:" << endl;

    while (nodePointer != NULL) {

        cout << "  Node " << nodePointer->getNodeID() << ": " << nodePointer->getVoltage() << " V" << endl;

        nodePointer = nodePointer->getNext();
    }
}

/********************************************
 *************** Destructor *****************
 *******************************************/
NodeList::~NodeList() {
    /*
     * We want to delete all the contents of the nodelist
     */

    //delete all the resistors in this node
    Node* currentNode = head;

    while (currentNode != NULL){
        
        delete currentNode -> accessResistorList();
        currentNode= currentNode -> getNext();
        delete head;
        
        head= currentNode;
    }
    
    head = NULL;
}