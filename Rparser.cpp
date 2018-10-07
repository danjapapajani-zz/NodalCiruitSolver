#include <iostream>  
#include <fstream>
#include <string>

#include "Rparser.h"
#include "NodeList.h"
#include "Node.h"
#include "Resistor.h"

using namespace std;

/********************************************
 *************   EOF function   *************
 *******************************************/
bool endOfFile(stringstream &lineStream) {
   
    //check if end of file is reached
    
    bool error = false;
    if (lineStream.eof()) {
        cout << "Error: too few arguments" << endl;
        error = true; //sends back true if end of file was found
    }
    return (error);
}

/********************************************
 ************* insertR function *************
 *******************************************/
void insertR(stringstream &lineStream, NodeList* nodeList) {

    string nameRes, extraChar;
    double resValue;
    int nodeID1, nodeID2;

    if (endOfFile(lineStream))//checks if the stream is empty
        return;

    lineStream >> nameRes;

    if (nameRes == "all") { //resistor cannot be all
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return;
    }

    if (lineStream.fail()) { //resistorName failed
        if (endOfFile(lineStream)) //too few arguments
            return;
        else {
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    lineStream >> resValue; //type double

    if (lineStream.fail()) { //a double type was not inserted     
        if (endOfFile(lineStream))
            return;

        else { //if end was not reached, something invalid was inputted
            cout << "Error: invalid argument" << endl;
            return;
        }
    }
    if (resValue < 0) { //negative resistance isn't allowed
        cout << "Error: negative resistance" << endl;
        return;
    }

    /*
     * Check to see if nodeID1 and nodeID2 inputs are valid
     *
     */

    lineStream >> nodeID1;
    if (lineStream.fail()) { 
        if (endOfFile(lineStream))
            return;

        else {
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    lineStream >> nodeID2;
    if (lineStream.fail()) { 
        if (endOfFile(lineStream))
            return;
        else {
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    //cannot have same nodes!
    if (nodeID1 == nodeID2) { 
        cout << "Error: both terminals of resistor connect to node " << nodeID1 << endl;
        return;

    } else {
        
        //check to see if string has too many arguments
        lineStream >> extraChar;  
        if (extraChar.length() != 0) {
            cout << "Error: too many arguments" << endl;
            return;
        }

        //Check to see if a resistor with that name has already been inserted
        bool nameExists = false; //name does not exist

        if (nodeList->findResName(nameRes)) {
            //resistor with the same name was found
            nameExists = true;
            cout << "Error: node " << nameRes << " already exists" << endl;
            return;
        }

        Resistor *newResPointer;
        Resistor *newResPointer2;
        
        /*
         * If the resistor name was not found and res value is valid, 
         * make a new resistor with this info
         */

        if (!nameExists) {

            int nodeIDs[2] = {nodeID1, nodeID2};

            newResPointer = new Resistor(nameRes, resValue, nodeIDs);
            newResPointer2 = new Resistor(nameRes, resValue, nodeIDs);
        }

        /* 
         * congratulations! insertR was valid, we are going to create new resistor
         * 
         */

        nodeList->insertResistor(newResPointer, nodeID1);
        nodeList->insertResistor(newResPointer2, nodeID2);

        cout << fixed << setprecision(2) << "Inserted: resistor " << nameRes
             << " " << resValue << " Ohms " << nodeID1 << " -> " << nodeID2 << endl;
    }
}

/********************************************
 ************* modifyR function *************
 *******************************************/
void modifyR(stringstream &lineStream, NodeList* nodeList) {
    
    //modifies value of existing resistor 
    
    string nameRes = "", extraChar = "";
    double resValue;

    if (endOfFile(lineStream))//checks if string is empty
        return;

    lineStream >> nameRes;

    if (lineStream.fail()) { //resistorName failed
        if (endOfFile(lineStream)) //too few arguments
            return;
        else {
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    if (nameRes == "all") { //if user inputs all
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return;
    }

    lineStream >> resValue; //type double

    if (lineStream.fail()) { //a double type was not inserted 
        if (endOfFile(lineStream))
            return;
        else {
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    if (resValue < 0) { //resistance can't be negative
        cout << "Error: negative resistance" << endl;
        return;
    } else {

        lineStream >> extraChar; //looks for extra characters at end for too many arguments
        if (extraChar.length() != 0) {
            cout << "Error: too many arguments" << endl;
        } else {


            /*
             * 
             * valid input, change resistor now
             *
             * 
             */

            double oldResValue;

            if (nodeList->findResName(nameRes)) {
                //resistor with the same name was found
                oldResValue = nodeList->returnResValue(nameRes);
            }

            if (nodeList->changeResValue(nameRes, resValue)) {
                //resistance name was found and changed 

                cout << "Modified: resistor " << nameRes << " from " << fixed << setprecision(2) << oldResValue << " Ohms to " << resValue << " Ohms" << endl;
            } else {
                
                //no resistor with that name was found
                cout << "Error: resistor " << nameRes << " not found" << endl;
            }

            return;
        }
    }
}

/********************************************
 ************** printR function *************
 *******************************************/
void printR(stringstream &lineStream, NodeList* nodeList) {

    //print resistors (either all or a specific one)
    
    string nameRes = "", extraChar = "";

    if (endOfFile(lineStream))//checks if string is empty
        return;

    lineStream >> nameRes;

    if (lineStream.fail()) { //resistorName failed
        if (endOfFile(lineStream)) //too few arguments
            return;
        else {
            cout << "Error: invalid argument" << endl;
            return;
        }
    }

    lineStream >> extraChar; //looks for extra characters at the end
    if (extraChar.length() != 0) {
        cout << "Error: too many arguments" << endl;
        return;
    }

    //check if resistor exists 
    if (!nodeList->findResName(nameRes)) {
        cout << "Error: resistor " << nameRes << " not found" << endl;
        return;
    }

    /*
     * valid input, print the resistor now
     */

    nodeList->printResistor(nameRes);

    return;

}

/********************************************
 ************ printNode function ************
 *******************************************/
void printNode(stringstream &lineStream, NodeList* nodeList) {

    //prints all nodes 
    
    string nodeID1 = "", command = "", extraChar = "";

    if (endOfFile(lineStream))//checks if string is empty
        return;

    //checks if keyword All was entered
    lineStream >> command;

    if (command == "all") {
        //all nodes gotta be printed

        cout << "Print:" << endl;
        nodeList->printAllNodes();

        return;

    } else {

        stringstream change("");
        change << command;
        int nodeID;
        change >> nodeID;

        nodeList->printNode(nodeID);
    }

    lineStream >> extraChar; //checks for extra characters at the end
    if (extraChar.length() != 0) {
        cout << "Error: too many arguments" << endl;
        return;
    }
}

/********************************************
 ************ setV function *****************
 *******************************************/
void setV(stringstream &lineStream, NodeList* nodeList) {
    
    //user sets voltage at a node
    
    int nodeID;
    double voltage;

    lineStream >> nodeID;

    //if node exists already, function will return a pointer to it
    if (nodeList->findNode(nodeID) == NULL) {
        cout << "Error: node " << nodeID << " not found" << endl;
        return;
    }

    lineStream >> voltage;

    nodeList->setVoltage(nodeID, voltage);

    return;
}

/********************************************
 ************ unsetV function ***************
 *******************************************/
void unsetV(stringstream &lineStream, NodeList* nodeList) {
    
    //user unsets voltage at node 
    
    int nodeID;
    lineStream >> nodeID;

    //if node exists already, function will return a pointer to it
    if (nodeList->findNode(nodeID) == NULL) {
        cout << "Error: node " << nodeID << " not found" << endl;
        return;
    }

    nodeList->unsetVoltage(nodeID);

}

/********************************************
 ************** deleteR function ************
 *******************************************/
void deleteR(stringstream &lineStream, NodeList* nodeList) {

    //delete a resistor or all resistors

    string command = "", extraChar = "";

    if (endOfFile(lineStream)) //checks if string is empty
        return;

    lineStream >> command;

    if (lineStream.fail()) { //resostorName failed
        if (endOfFile(lineStream)) //too few arguments
            return;
        else {
            cout << "Error: invalid argument" << endl;
            return;
        }
    }
    
   /*
    * 
    * No errors, time to delete!
    * 
    */ 
   
    //check if resistor exists if you're not trying to delete all
    if (command != "all" && !(nodeList->findResName(command))){
        cout << "Error: resistor " <<command <<" not found" << endl;
        return;
    }

        //delete the resistor, or all
        nodeList->deleteResistors(command);
        return;
  
}

/********************************************
 ***************** Parser *******************
 *******************************************/
int parser() {

    //main function that takes user input and sends to correct function
    
    //input commands    
    string line, command = "", nameRes = "", extraChar = "";

    int nodeID1 = 0, nodeID2 = 0;

    NodeList* nodeList = new NodeList();

    cout << "> ";
    getline(cin, line); //get user input
    while (!cin.eof()) {
        while (!cin.eof()) {//while the string doesn't reach the end of the file

            command = "";
            stringstream lineStream(line);
            lineStream >> command;

            //check if the inputted command matches any valid commands & send to appropriate function

            if (command == "insertR") {
                insertR(lineStream, nodeList);
            } else if (command == "modifyR") {
                modifyR(lineStream, nodeList);
            } else if (command == "printR") {
                printR(lineStream, nodeList);
            } else if (command == "printNode") {
                printNode(lineStream, nodeList);
            } else if (command == "setV") {
                setV(lineStream, nodeList);
            } else if (command == "unsetV") {
                unsetV(lineStream, nodeList);
            } else if (command == "deleteR") {
                deleteR(lineStream, nodeList);
            } else if (command == "solve") {
                nodeList->solve();
            } else { //the command did not match any valid commands
                cout << "Error: invalid command" << endl;
            }

            cin.clear();
            cout << "> ";
            getline(cin, line); //get user input again to loop. if eof is inserted, while loop will break
        }
    }

    delete nodeList;
    return 0;
}