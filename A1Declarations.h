#ifndef _A1Declarations_H
#define _A1Declarations_H

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

void flish();
void pressEnter();
void runMenu();
void displayText(string filename);
void createLists(string filename,string savedCypto);
void generateCryptograms();
void saveData();
void writeDataToFile(string filename, string data);
void readAllFileLines(string filename, char newLineChar);
void displaySavedCryptograms();
bool dataLoadedCheck();
void convertFileToVector(string filename, vector<string> &collection, char newLine);


bool dataLoaded = false;
char command;
string cryptogram;
vector<string> quotes;
vector<string> cryptograms;
#endif