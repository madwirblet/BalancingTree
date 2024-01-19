// COP3530 -- Project1: GatorAVL Tree
// "main.cpp" -- Created by: Madelyne Wirbel
#include "StudentTree.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool numCheck(string ID){
    // check that all characters are numbers
    for (char c : ID){
        if (!isdigit(c)){
            return false;
        }
    }

    return true;
}

string removeQuotes(string nameWQuotes){
    string newString;
    if (numCheck(nameWQuotes)){
        return nameWQuotes;
    }
    for (char c : nameWQuotes){
        if (!isalpha(c) && !isspace(c)){
            continue;
        }
        else{
            newString += c;
        }
    }
    return newString;
}

int main() {

    Tree tree;

// first line of the file will have the number of lines called
    string numLines;
    getline(cin, numLines);
    int numLoop = stoi(numLines);

    // define possible inputs within a line
    string completeLine;
    string command;
    string info1;
    string info2;

    for (int i = 0; i < numLoop; i++){
        getline(cin, completeLine);
        istringstream in(completeLine);

        in >> command;

        if (command == "insert"){
            // insert takes in both the name and the ID
            getline(in, info1, '"'); // need to ensure grab entire name even if there is a space
            getline(in, info1, '"');
            in >> info2;

            // int intInfo2 = stoi(info2); // convert info2 to a valid integer

            info1 = removeQuotes(info1);

            tree.insert(info1, info2);
        }

        else if (command == "remove"){
            in >> info1;

            if (numCheck(info1)){ // this statement will run if the information is a number
                // int GatorID = stoi(info1);
                tree.removeID(info1); // checks length within funct.
                continue;
            }
            else{
                cout << "unsuccessful\n";
            }

        }

        else if (command == "search"){
            // need inner if statements for if the command is to search name or search ID
           // some reason there is a gap of whitespace throwing this off
            getline(in, info1, '"'); // need to ensure grab entire name even if there is a space
            getline(in, info1, '"');

            info1 = removeQuotes(info1);

            if (numCheck(info1)){ // this statement will run if the information is a number
                tree.searchID(info1); // checks length within funct.
                continue;
            }
            else{
                tree.searchName(info1); // this will return unsuccessful if not a name
                continue;
            }

        }

        else if (command == "printInorder"){
            tree.printInorder();
        }

        else if (command == "printPreorder"){
            tree.printPreorder();
        }

        else if (command == "printPostorder"){
            tree.printPostorder();
        }

        else if (command == "printLevelCount"){
            tree.printLevelCount();
        }

        else if (command == "removeInorder"){
            in >> info1;

            if (numCheck(info1)){ // this statement will run if the information is a number
                int removeN = stoi(info1);
                tree.removeInorder(removeN); // checks length within funct.
                continue;
            }
            else{
                cout << "unsuccessful\n";
            }
        }

        else{
            cout << "unsuccessful\n";
        }

    }




    return 0;
}
