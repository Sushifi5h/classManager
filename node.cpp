/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 122, Fall  2016; Lab Section 5                                               *
* Programming Assignment: Programming Assignment 5					                       *
* Date: February 21, 2016                                                                  *
* Description: Writing a program that will manage student data                     		   *
*******************************************************************************************/

//include local libararies
#include "node.h"

//default construct
Node::Node()
{
	this->maindata.recordNumber = 0;
	this->maindata.studentId = 0;
	this->maindata.name = "";
	this->maindata.email = "";
	this->maindata.units = "";
	this->maindata.program = "";
	this->maindata.level = "";
	this->maindata.numberofAbsences = 0;
	this->maindata.dateofAbsences = " ";
}

//construct
Node::Node(Data input)
{
	//set values
	maindata.recordNumber = input.recordNumber;
	maindata.studentId = input.studentId;
	maindata.name = input.name;
	maindata.email = input.email;
	maindata.units = input.units;
	maindata.program = input.program;
	maindata.level = input.level;
	maindata.numberofAbsences = input.numberofAbsences;
	maindata.dateofAbsences = input.dateofAbsences;

	//set pNext
	this->pNext = nullptr;
}

//copy constructor
Node::Node(Node &inputNode)
{
	//set values
	maindata.recordNumber = inputNode.maindata.recordNumber;
	maindata.studentId = inputNode.maindata.studentId;
	maindata.name = inputNode.maindata.name;
	maindata.email = inputNode.maindata.email;
	maindata.units = inputNode.maindata.units;
	maindata.program = inputNode.maindata.program;
	maindata.level = inputNode.maindata.level;
	maindata.numberofAbsences = inputNode.maindata.numberofAbsences;
	maindata.dateofAbsences = inputNode.maindata.dateofAbsences;

	//set pNext
	this->pNext = inputNode.pNext;
}

//setters
void Node::setData(Data setData)
{
	maindata.recordNumber = setData.recordNumber;
	maindata.studentId = setData.studentId;
	maindata.name = setData.name;
	maindata.email = setData.email;
	maindata.units = setData.units;
	maindata.program = setData.program;
	maindata.level = setData.level;
	maindata.numberofAbsences = setData.numberofAbsences;
	maindata.dateofAbsences = setData.dateofAbsences;
}

//set pointer
void Node::setpNext(Node *setptr)
{
	this->pNext = setptr;
}

//none member overloaded cout
ostream & operator<<(ostream &lhs, Node *& rhs)
{
	//get data from rhs
	Data temp = rhs->getData();

	//long print statement that is why i made an overloaded operator
	//because I want to type this onces
	cout << "Record Number: " << temp.recordNumber << endl
		<< "Student Id: " << temp.studentId << endl
		<< "Name: " << temp.name << endl
		<< "Email: " << temp.email << endl
		<< "Units: " << temp.units << endl
		<< "Program: " << temp.program << endl
		<< "Level: " << temp.level << endl
		<< "Number of times Absences: " << temp.numberofAbsences << endl
		<< "Dates Absences: " << temp.dateofAbsences;

	return lhs;
}

ostream & operator<<(ostream &lhs, Data &rhs)
{
	//set data to temp because copied last overloaded operator
	Data temp = rhs;

	//long print statement that is why i made an overloaded operator
	//because I want to type this onces
	cout << "Record Number: " << temp.recordNumber << endl
		<< "Student Id: " << temp.studentId << endl
		<< "Name: " << temp.name << endl
		<< "Email: " << temp.email << endl
		<< "Units: " << temp.units << endl
		<< "Program: " << temp.program << endl
		<< "Level: " << temp.level << endl
		<< "Number of times Absences: " << temp.numberofAbsences << endl
		<< "Dates Absences: " << temp.dateofAbsences;

	return lhs;
}
