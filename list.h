/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 122, Fall  2016; Lab Section 5                                               *
* Programming Assignment: Programming Assignment 5					                       *
* Date: February 21, 2016                                                                  *
* Description: Writing a program that will manage student data                     		   *
*******************************************************************************************/

//gaurd code
#pragma once

//error handler for ctime
#define _CRT_SECURE_NO_WARNINGS

//Include standard libraries
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>


//Include local libararies
#include "node.h"

//include easier use for following
using namespace std;
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

class List {
//public functions
public:
	//construct and destructor
		List() { this->mphead = nullptr; }
		~List(){ deleteDataStructure(this->mphead); }
		
	//main logic 
		void runApp(void);

	//data structure caller
		void printList(void);
		void printListRecInOrder(void) { printListRecInOrder(this->mphead); }

//private functions
private:
	//private vars
		Node *mphead; //pointer to start of the list
		Node *& returnHead(void) { return this->mphead; } //getter for var

	//main functions
		void printMainMenu(void); //prints menu
		int mainMenu(void); //logic for main menu
		void exitProgram(void); //exit for main menu
		void checkCsvFile(void); //call readInscvfile
		void readInCsvFile(void); //load from csv file
		void storeMasterList(void); //store master list to file
		void writetoFile(ofstream &inpuFileStream, Node* inputNode);//write to file
		void markAbsences(void); //makr absences
		void loadMasterListFromFile(void); //load from master.txt
		void genReports(void); //generate Reports
		void printReportmenu(void); //prints menu for report
		int mainSelectorReport(void); //return 1-3
		void printAllStudents(void); //prints everything
		void fileprintAllStudents(ofstream &filehandler, Node* inputNode); //write report to file
		void printWithSpecificAbs(void); //print with a specific absences
		void recursivelySpecificsAbs(ofstream &filehandler,Node * head, int compare); //rec to print things
		void specificDateAbs(void); //will handle specific date
		void recSpecificDateAbs(ofstream &filehandler, Node* head, string compare); //rec to print things to file
		void editAbs(void); //edit absences

	//data structure functions
		void insertatFront(Node *& head, Data inputData); //insert in order
		void deleteDataStructure(Node *head); //free memeory
		void printListRecInOrder(Node *head); //print in order 
		int isEmpty(void) {return !this->mphead;}//check for empty

};