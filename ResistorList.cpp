#include "ResistorList.h"
#include "Resistor.h"
#include "Node.h"
#include "NodeList.h"
#include <iomanip> 
#include <string>

using namespace std;

/********************************************
 ************** Constructor  ****************
 *******************************************/
ResistorList::ResistorList() {
    
    head = NULL;

}

/********************************************
 *********** insertResistor  ****************
 *******************************************/
void ResistorList::insertResistor(Resistor* newResPointer) {

    //insert a resistor into the resistor list (of a specific node that sent it)

    if (head == NULL) {
        head = newResPointer;
        newResPointer->assignNext(NULL);
    } else {

        Resistor *tmp = head;

        while (tmp->getNext() != NULL) {
            tmp = tmp->getNext();
        }

        tmp->assignNext(newResPointer);
        newResPointer->assignNext(NULL);
    }
}

/********************************************
 *********** findResistorName ***************
 *******************************************/
bool ResistorList::findResistorName(string nameRes) {

    //check if resistor list contains resistor with inputted name

    Resistor* tmpResPointer = head;

    while (tmpResPointer != NULL) {
        if (tmpResPointer->getName() == nameRes)
            return (1); //found a resistor with this name
        else
            tmpResPointer = tmpResPointer->getNext();
    }
    return (0); //nothing was found    
}

/********************************************
 ************ modifyResistor ****************
 *******************************************/
bool ResistorList::modifyResistor(string nameRes, double newResistorValue) {

    //change a resistor of inputted name to inputted resistance value

    Resistor* tmpResPointer = head;
    if (head == NULL)
        return (0); 
    
    while (tmpResPointer != NULL) {
        
        if (tmpResPointer->getName() == nameRes) {

            //if name was found, change resistance
            tmpResPointer->setResistance(newResistorValue);
            
            //found a resistor with this name
            return (1); 
            
        } else
            tmpResPointer = tmpResPointer->getNext();
    }
    //nothing found  
    return (0);    

}

/********************************************
 ************ returnResValue  ***************
 *******************************************/
double ResistorList::returnResValue(string nameRes) {

    //return the value of resistor with inputted name

    Resistor* tmpResPointer = head;
    if (head == NULL)
        return (0); 


    while (tmpResPointer != NULL) {

        if (tmpResPointer->getName() == nameRes)
                
            //found resistor with this name, return res value
            return (tmpResPointer->getResistance());
        else
            tmpResPointer = tmpResPointer->getNext();
    }

    //nothing was found    
    return (0);
}

/********************************************
 ************* printResistor ****************
 *******************************************/
bool ResistorList::printResistor(string nameRes) {

    //print resistor with inputted name

    Resistor* tmpResPointer = head;
    if (head == NULL) {
        return (0); 

    }
    while (tmpResPointer != NULL) {

        if (tmpResPointer->getName() == nameRes) {

            //found resistor with this name
            cout << "Print:" << endl;
            cout.width(20);
            cout << left << nameRes;
            cout.width(8);
            cout << right << fixed << setprecision(2) << tmpResPointer->getResistance()
                 << " Ohms " << tmpResPointer->getEndpointNode0() << " -> " 
                 << tmpResPointer->getEndpointNode1() << endl;
            return true;
        } else
            tmpResPointer = tmpResPointer->getNext();
    }
    //nothing was found  
    return (0); 
}

/********************************************
 *********** printAllResistors **************
 *******************************************/
void ResistorList::printAllResistors() {

    //print all of the resistors

    Resistor* tmpResPointer = head;
    if (head == NULL) {
        
        // the list is empty
        return; 
    }

    while (tmpResPointer != NULL) {


        //found resistor with this name

        cout.width(20);
        cout << left << tmpResPointer->getName();
        cout.width(8);
        cout << right << fixed << setprecision(2) << tmpResPointer->getResistance() 
             << " Ohms " << tmpResPointer->getEndpointNode0() << " -> " 
             << tmpResPointer->getEndpointNode1() << endl;

        //increment temp pointer
        tmpResPointer = tmpResPointer->getNext();
    }
    return;
}

/********************************************
 ************** countResistors **************
 *******************************************/
int ResistorList::countResistors() {

    //count the number of resistors connected to a node

    Resistor* tmpResPointer = head;
    int countRes = 0;

    //traverse through all the resistors and count each time one exists
    while (tmpResPointer != NULL) {
        countRes++;
        tmpResPointer = tmpResPointer->getNext();
    }
    return (countRes);
}

/********************************************
 ************* deleteResistor ***************
 *******************************************/  
void ResistorList::deleteResistor(string command) {

    //delete all resistors or given resistor with inputted name

    Resistor* currentResistor = head;
    Resistor* tmpResPointerNext = head->getNext();
    Resistor* tmpResPointerPrev = NULL;

    if (command == "all") {
        Resistor* temp = head;
        while (temp != NULL) {
            head = head->getNext();
            delete (temp);
            temp = head;
        }
        
        //delete only the resistor inputted by user
        head = NULL;
    }        
    else {
        bool moveUp = false;

        //traverse through all the resistors
        while (currentResistor != NULL) {

            //if we found the resistor we want to delete
            if (currentResistor->getName() == command) {

                if (tmpResPointerPrev == NULL) {
                    head = currentResistor->getNext();
                    delete currentResistor;

                } else {
                    tmpResPointerPrev->assignNext(tmpResPointerNext);
                    delete currentResistor;
                }
            }

            //move current resistor to the next one
            currentResistor = tmpResPointerNext;

            if (tmpResPointerNext != NULL)
                tmpResPointerNext = tmpResPointerNext->getNext();

            /*
             * advance the prev pointer
             * if it points to null, make it point to current ptr
             */
            
            if (!moveUp) {
                tmpResPointerPrev = head;
            } 
            
            //if it has already moved up once, move up again
            else {
                tmpResPointerPrev = tmpResPointerPrev->getNext();
            }
            moveUp = true;
        }
        return;
    }
}

/********************************************
 ********** addResistorsParallel ************
 *******************************************/  
double ResistorList::addResistorsParallel() {

    //adds resistors in parallel 
    
    double resVal;
    double total = 0;

    Resistor* tmpResPointer = head;

    //traverse through all resistors 
    while (tmpResPointer != NULL) {

        resVal = tmpResPointer->getResistance();

        total = total + (1 / resVal);

        tmpResPointer = tmpResPointer->getNext();
    }
    return (total);

}

/********************************************
 ************* isResConnected ****************
 *******************************************/  
bool ResistorList::isResConnected(int nodeID) {

    //is a resistor connected to node??? lets find out
    
    Resistor* resList = head;

    while (resList != NULL) {

        if (resList->getEndpointNode0() == nodeID || resList->getEndpointNode1() == nodeID) {
            return true;
        }

        resList = resList->getNext();

    }

    return false;
}

/********************************************
 *********** resOfConnected *****************
 *******************************************/  
double ResistorList::resOfConnected(int nodeID) {

    //return the value of the resistor connected to node
    
    Resistor* resList = head;

    while (resList != NULL) {

        if (resList->getEndpointNode0() == nodeID || resList->getEndpointNode1() == nodeID) {
            return (resList->getResistance());
        }
        resList = resList->getNext();
    }
    return 0;
}

/********************************************
 **************  Destructor  ****************
 *******************************************/
ResistorList::~ResistorList() { 
     
     // delete all the resistors in the list
     
    Resistor* currentResistor = head;

    while (currentResistor != NULL) {
        head = head->getNext();
        delete currentResistor;
        currentResistor = head;
    }
    head = NULL;
}