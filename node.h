/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 122, Fall  2016; Lab Section 5                                               *
* Programming Assignment: Programming Assignment 5					                       *
* Date: February 21, 2016                                                                  *
* Description: Writing a program that will manage student data                     		   *
*******************************************************************************************/

//gaurd code
#pragma once

//Include standard libraries
#include <iostream>
#include <string>

//include easier use for following
using std::cout;
using std::endl;
using std::string;
using std::ostream;

typedef struct {
	int recordNumber;
	int studentId;
	string name;
	string email;
	string units;
	string program;
	string level;
	int numberofAbsences;
	string dateofAbsences;
} Data;


class Node{
//public functions
public:
	//constructor and copy constructor
		Node(); //default
		Node(Data input); //copy 
		Node(Node &inputNode); //copy

	//getter
		Data getData(void) { return (this->maindata); }
		Node *& getpNext(void) { return this->pNext; }

	//setters
		void setData(Data setData);
		void setpNext(Node *setptr);

//private vars and functions
private:
	Data maindata;
	Node *pNext;
};

//member print function
ostream & operator<<(ostream &lhs, Node *& rhs);
ostream & operator<<(ostream &lhs, Data &rhs);