/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 122, Fall  2016; Lab Section 5                                               *
* Programming Assignment: Programming Assignment 5					                       *
* Date: February 21, 2016                                                                  *
* Description: Writing a program that will manage student data                     		   *
*******************************************************************************************/

//Include local class libararies
#include "list.h"

/*************************************************************
* Function: runApp(void)                                     *
* Date Created: 02/21/2015                                   *
* Date Last Modified: 02/21/2015                             *
* Description: contains all logic                            *
* Input parameters: none                                     *
* Returns: nothin                                            *
* Preconditions: Nothing                                     *
* Postconditions: end of the program                         *
*************************************************************/
void List::runApp(void)
{
	while(true)
		//start main menu
		switch (mainMenu())
		{
		//import course list
		case 1:
			checkCsvFile();
			break;
		//load master list
		case 2:
			loadMasterListFromFile();
			break;
		//store master list
		case 3:
			storeMasterList();
			break;
		//mark absences
		case 4:
			markAbsences();
			break;
		//edit absences
		case 5:
			editAbs();
			break;
		//generate report
		case 6:
			genReports();
			break;
		//exit
		case 7:
			exitProgram();
			break;
		//error handler
		default:
			exitProgram();
			break;
		}
}

//only prints main menu
void List::printMainMenu(void)
{
	cout << "===========================================================" << endl <<
		endl << "\t\tStudent Record Keeper" << endl <<
		endl << "\t(To use insert 1-7 and than enter)" <<
		endl << "===========================================================" << endl << endl
		<< "\t1. Import Course List"
		<< "\t2. Load Master List" << endl << endl 
		<< "\t3. Store Master List"
		<< "\t4. Mark Absences" << endl << endl
		<< "\t5. Edit Absences"
		<< "\t6. Generate Report" << endl << endl
		<< "\t7. Exit" << endl << endl << "==========================================================="
		<< endl << endl << "\t\tSelection: ";
}

//logic handler for main mendu
int List::mainMenu(void)
{
	//local var for input
	int userChoice = 0;

	//get user input
	do {
		//print menu get user choice
		printMainMenu();
		cin >> userChoice;
		
		//show user error
		if ((userChoice <= 0) || (userChoice >= 8))
		{
			cout << endl << "You accidently entered " << userChoice
				<< " please make a choice between 1 - 7." << endl;
			system("pause");
		}

		//clear buffer for cin
		cin.clear();
		cin.ignore(INT_MAX,'\n');

		//clear screen
		system("cls");
	} while ((userChoice <= 0) || (userChoice >= 8));

	//return choice
	return userChoice;
}

//basic exit handler
void List::exitProgram(void)
{
	//exit program 
	system("cls");
	cout << "\tExiting Program. Have a good day!" << endl;
	system("pause");
	exit(1);
}

//read from csv file
void List::readInCsvFile(void)
{//is get data from file put into a Data struct than call insertatFront
	int inputFileDataSize = 0;
	Data curFileData = { 0,0,"","" ,"" ,"" ,"" ,0," "}; //init data struct
	ifstream inputFile; //set ifstream object
	string inputFileData = "", emptyString = "", lastName = "";
	

	inputFile.open("classList.csv"); //open desired file

	if (inputFile.is_open())
	{//check is stream open
		while (getline(inputFile, inputFileData))
		{
			inputFileData += ','; //dirty hack to fix last input from file
			if (inputFileData.find(",Level") == std::string::npos)
			{//read from file but ignore fist line
				
				inputFileDataSize = inputFileData.length(); //get length of input from file
				curFileData = { 0,0,"","" ,"" ,"" ,"" ,0," " }; //init data struct
				lastName = ""; //init last name

				for (std::string::iterator curString = inputFileData.begin(); curString != inputFileData.end(); ++curString)
				{//from cplusplus to itterate string (http://www.cplusplus.com/reference/string/string/begin/)
					if (*curString != ',') emptyString += *curString; //put string in emptystring till comma
					else
					{
						if (curFileData.recordNumber == 0) curFileData.recordNumber = atoi(emptyString.c_str());
						else if (curFileData.studentId == 0) curFileData.studentId = atoi(emptyString.c_str());
						else if (curFileData.name == "") curFileData.name = emptyString;
						else if (lastName == "")
						{
							lastName = emptyString;
							curFileData.name += ',' + lastName;
							curFileData.name.erase(0, 1);
							curFileData.name.erase(curFileData.name.size() - 1);
						}
						else if (curFileData.email == "") curFileData.email = emptyString;
						else if (curFileData.units == "") curFileData.units = emptyString;
						else if (curFileData.program == "") curFileData.program = emptyString;
						else if (curFileData.level == "") curFileData.level = emptyString;

						emptyString = ""; // init empty string
					}
				}
				insertatFront(this->mphead, curFileData);
			}
		}
	}
	else this->exitProgram(); //error handler
		
	inputFile.close(); //close file
	
	cout << "Done Loading from file to master list." << endl;
	system("pause");
	system("cls");
	
}

//call readincsvfile
void List::checkCsvFile(void)
{
	if (this->mphead == nullptr) readInCsvFile();
	else {
		deleteDataStructure(this->mphead);
		this->mphead = nullptr;
		readInCsvFile();
	}
}

//write master list to file
void List::storeMasterList(void)
{
	//create file object
	ofstream outfile;
	outfile.open("master.txt");

	if (outfile.good() && (this->mphead != nullptr))
	{//check to make sure it opeened
		writetoFile(outfile, this->mphead);
		cout << "Done storing master list to file to (master.txt)." << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "Erorr: either couldn't open file or master list is empty. Sorry." << endl;
		system("pause");
		system("cls");
	}
}

//simple writing to file
void List::writetoFile(ofstream &inpuFileStream, Node* inputNode)
{
		Node* pCur = inputNode;

		if (pCur->getpNext() != nullptr) writetoFile(inpuFileStream, pCur->getpNext());

		Data temp(pCur->getData());

		inpuFileStream << temp.recordNumber << ','
			<< temp.studentId << ','
			<< '\"' << temp.name << '\"' << ','
			<< temp.email << ','
			<< temp.units << ','
			<< temp.program << ','
			<< temp.level << ',' << temp.numberofAbsences << ',' << temp.dateofAbsences << endl;
}

//mark absences
void List::markAbsences(void)
{
	// retrieved from stackoverflow - http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	Node* pCur = this->mphead;
	int userChoice = 0;

	while (pCur != nullptr)
	{
		userChoice = 0;

		cout << "================================" << endl << endl;
		cout << pCur << endl;
		cout << "================================" << endl << endl;

		cout << "Was this student Absencent(Type 1 for yes 0 or for no)?: ";
		cin >> userChoice;

		if (userChoice)
		{
			Data marked(pCur->getData()); //while replace pCur
			marked.numberofAbsences++; //itterate number of absence
			marked.dateofAbsences += to_string(now->tm_mon + 1) + '/' + to_string(now->tm_mday) + '/' + to_string(now->tm_year + 1900) + '-';
			pCur->setData(marked); //change node
		}
		
		system("cls");
		pCur = pCur->getpNext();
	}
}

//load master.txt
void List::loadMasterListFromFile(void)
{
	if (!this->isEmpty())
	{//this->head to make sure it is null if not free all memory
		//and set it to nullptr
		deleteDataStructure(this->mphead);
		this->mphead = nullptr;
	}
	
	//local vars
	int inputFileDataSize = 0;
	string inputFileData = "", lastName = "", emptyString = "";
	Data curFileData = { 0,0,"","" ,"" ,"" ,"" ,0," " };

	//open master file 
	ifstream masterFileIn;
	masterFileIn.open("master.txt");
	if (masterFileIn.good())
	{//make sure stream is open
		while (getline(masterFileIn, inputFileData))
		{//while I can getline also itterates lines
			inputFileData += ','; //dirty hack to fix last input from file

			inputFileDataSize = inputFileData.size(); //size of getline buffer
			curFileData = { 0,0,"","" ,"" ,"" ,"" ,0," " }; //init data struct
			lastName = ""; //init last name


			for (std::string::iterator curString = inputFileData.begin(); curString != inputFileData.end(); ++curString)
			{
				if(*curString != ',')  emptyString += *curString;
				else {//so we hit a comma need to empty empty string and put data in palce
					if (curFileData.recordNumber == 0) curFileData.recordNumber = atoi(emptyString.c_str());
					else if (curFileData.studentId == 0) curFileData.studentId = atoi(emptyString.c_str());
					else if (curFileData.name == "") curFileData.name = emptyString;
					else if (lastName == "")
					{
						lastName = emptyString;
						curFileData.name += ',' + lastName;
						curFileData.name.erase(0, 1);
						curFileData.name.erase(curFileData.name.size() - 1);
					}
					else if (curFileData.email == "") curFileData.email = emptyString;
					else if (curFileData.units == "") curFileData.units = emptyString;
					else if (curFileData.program == "") curFileData.program = emptyString;
					else if (curFileData.level == "") curFileData.level = emptyString;
					else if (curFileData.numberofAbsences == 0) curFileData.numberofAbsences = atoi(emptyString.c_str());
					else if (curFileData.dateofAbsences == " ") curFileData.dateofAbsences = emptyString;

					emptyString = ""; //init for every line
					}
			}
			insertatFront(this->mphead, curFileData);
		}
	}
	else this->exitProgram();

	masterFileIn.close(); //close file

	//brief message for user
	cout << "Done Loading from master.txt to master list." << endl;
	system("pause");
	system("cls");
}

//gene Reports
void List::genReports(void)
{
	int thisVar = 1;
	if (!isEmpty())
	{
			switch (mainSelectorReport())
			{
			case 1://generate report for all students
				printAllStudents();
				break;
			case 2://generate reports students with specific absences
				printWithSpecificAbs();
				break;
			case 3://generate report students with date report
				specificDateAbs();
				break;
			case 4:
				thisVar = 0;
				cout << "Returning to main menu." << endl;
				system("pause");
				system("cls");
				break;
			default:
				exitProgram();
				break;
			}
		
	}else{
		cout << "Erorr: Master list is empty please load record from file or masterfile. Sorry." << endl;
		system("pause");
		system("cls");
	}
}

//menu for reports
void List::printReportmenu(void)
{
	cout << "===========================================================" << endl <<
		endl << "\t\tGenerate Reports" << endl <<
		endl << "\t(To use insert 1-4 and than enter)" <<
		endl << "===========================================================" << endl << endl
		<< "\t1. Generate report for all students." << endl << endl
		<< "\t2. Generate report for students with absences." << endl << endl
		<< "\t3. Generate date Report." << endl << endl
		<< "\t4. Return to main menu." << endl << endl <<
		"==========================================================="
		<< endl << endl << "\t\tSelection: ";
}

//main selector for reports return ins
int List::mainSelectorReport(void)
{
	//local var for input
	int userChoice = 0;

	//get user input
	do {
		//print menu get user choice
		printReportmenu();
		cin >> userChoice;

		//show user error
		if ((userChoice <= 0) || (userChoice >= 5))
		{
			cout << endl << "You accidently entered " << userChoice
				<< " please make a choice between 1 - 4." << endl;
			system("pause");
		}

		//clear buffer for cin
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		//clear screen
		system("cls");
	} while ((userChoice <= 0) || (userChoice >= 5));

	//return choice
	return userChoice;
}

//print all students 
void List::printAllStudents(void)
{
	ofstream outfile;
	outfile.open("report_all_students.csv");

	outfile << "name,email,numberofabsences,datesofabsences" << endl;

	fileprintAllStudents(outfile, this->mphead);

	outfile.close();

	cout << "Done generating all student reports.\nPlease check report_all_students.csv in current directory." << endl;
	system("pause");
	system("cls");
}

//file for all studentds
void List::fileprintAllStudents(ofstream &filehandler, Node* inputNode)
{
	if (inputNode->getpNext() != nullptr) fileprintAllStudents(filehandler, inputNode->getpNext());
	
	Data temp(inputNode->getData());
	filehandler << '\"' << temp.name << '\"' << ',' << temp.email << ',' << temp.numberofAbsences << ',' << temp.dateofAbsences << endl;
}

//will print abscence with specific days
void List::printWithSpecificAbs(void)
{
	//local vars
	int userChoice = 0;

	//prompt user
	cout << "What ammount of absences do you want to serch for?"
		 <<"\nResult will also inlcude greater than the number given.\nPlease give a number: ";
	cin >> userChoice;

	if (userChoice >= 0)
	{//vaild input
		ofstream outfile;
		outfile.open("students_with_specific_absences.csv");
		outfile << "name,email,numberofabsences,datesofabsences" << endl;
		recursivelySpecificsAbs(outfile, this->mphead, userChoice);
		system("cls");
		cout << "Done printing specific absences to students_with_specific_absences.csv." << endl;
		system("pause");
	}
	else {
		cout << "Error: You either entered a number less than 0 or 0. I hate you." << endl;
		system("pause");
		system("cls");

		cout << "JK. I love you you are beautiful you!" << endl;
		system("pause");
		system("cls");
	}
	system("cls");
}

//recursively print specific absences
void List::recursivelySpecificsAbs(ofstream &filehandler, Node * head, int compare)
{
	if (head->getpNext() != nullptr) recursivelySpecificsAbs(filehandler, head->getpNext(), compare);

	Data temp(head->getData());

	if (temp.numberofAbsences >= compare)
		filehandler << '\"' << temp.name << '\"' << ',' << temp.email << ',' << temp.numberofAbsences << ',' << temp.dateofAbsences << endl;

		
}

//specific date
void List::specificDateAbs(void)
{
	string userChoice = "";

	cout << "Please enter a date to search for(example 1/1/2016): ";
	cin >> userChoice;

	ofstream outfile;
	outfile.open("students_with_absense_on_specific_date.csv");

	outfile << "name,email,numberofabsences,datesofabsences" << endl;

	recSpecificDateAbs(outfile, this->mphead, userChoice);

	outfile.close();

	cout << "Done generating all student reports.\nPlease check students_with_absense_on_specific_date.csv in current directory." << endl;
	system("pause");
	system("cls");

}

//recusive way to search the linked list for abs dates
void List::recSpecificDateAbs(ofstream &filehandler, Node* head, string compare)
{
	if (head->getpNext() != nullptr) recSpecificDateAbs(filehandler, head->getpNext(), compare);
	
	Data temp(head->getData());

	if (temp.dateofAbsences.find(compare) != std::string::npos)
	{
		filehandler << '\"' << temp.name << '\"' << ',' << temp.email << ',' << temp.numberofAbsences << ',' << temp.dateofAbsences << endl;
	}
}

//edit Abs
void List::editAbs(void)
{
	if (this->mphead != nullptr)
	{
		int userChoice = 0, startofdate = 0, endofdate = 0, searchId = 0;
		string nameStudent = "", dateToEdit = "";
		Node *pCur = this->mphead;

		cout << "Would you like to search by name or student ID?\n"
			<< "Please enter 1 for name and 2 for student ID: ";
		cin >> userChoice;

		switch (userChoice)
		{
		case 1:
			cout << "Enter Name(Example LastName,FirstName = Doe,John): ";
			cin >> nameStudent;
			

			while (pCur->getpNext() != nullptr)
			{
				Data temp(pCur->getData());

				if (temp.name.find(nameStudent) != std::string::npos)
				{
					cout << "Enter date present(Example: 1/2/2016): ";
					cin >> dateToEdit;

					startofdate =  temp.dateofAbsences.find(dateToEdit);
					endofdate = startofdate + dateToEdit.size() + 1;

					temp.dateofAbsences.erase(startofdate, endofdate);
					temp.numberofAbsences--;

					pCur->setData(temp);

					cout << "Marked " << temp.name << " as present for " << dateToEdit << "." << endl;
					system("pause");
					system("cls");
				}

				pCur = pCur->getpNext();
			}


			break;
		case 2:
			cout << "Enter Student Id: ";
			cin >> searchId;

			while (pCur->getpNext() != nullptr)
			{
				Data temp(pCur->getData());

				if (temp.studentId == searchId)
				{
					cout << "Enter date present(Example: 1/2/2016): ";
					cin >> dateToEdit;

					startofdate = temp.dateofAbsences.find(dateToEdit);
					endofdate = startofdate + dateToEdit.size() + 1;

					temp.dateofAbsences.erase(startofdate, endofdate);
					temp.numberofAbsences--;

					pCur->setData(temp);

					cout << "Marked " << temp.studentId << " as present for " << dateToEdit << "." << endl;
					system("pause");
					system("cls");
				}
				pCur = pCur->getpNext();
			}
			break;
		default:
			system("cls");
			break;
		}
	}
	else {
		cout << "Master List is empty. Pleae load from a file" << endl;
		system("pause");
		system("cls");
	}
}

/*************************************************************
* Functions: Data Strucutre functions                        *
* Date Created: 02/21/2015                                   *
* Date Last Modified: 02/21/2015                             *
* Description: contains all logic                            *
* Input parameters: none                                     *
* Returns: nothin                                            *
* Preconditions: Nothing                                     *
* Postconditions: end of the program                         *
*************************************************************/

//data structure functions
void List::insertatFront(Node *& head, Data inputData)
{
	//make memory in heap and set input data to it
	Node *pmem = nullptr;
	pmem = new Node(inputData);

	if (pmem != nullptr)
	{//memory allocated successfully
		if (head == nullptr)
		{//if mphead is null
			head = pmem;
		}
		else
		{//mphead has a node
			//set pmem pnext to head and set head to pmem
			pmem->setpNext(this->mphead);
			head = pmem;
		}
	}
	else this->exitProgram(); //error handler
}

//print data structure
void List::printList(void)
{
	Node *pCur = this->mphead; //set pCur to head

	while (pCur != nullptr) //while pCur is not null
	{
		cout << pCur << endl;
		pCur = pCur->getpNext();
	}
}

//delete data strucutre
void List::deleteDataStructure(Node *head)
{
	Node *pCur = head; //set pCur to head

	if (pCur != nullptr)//base case
		deleteDataStructure(pCur->getpNext()); //call delete struct

	delete pCur; //delete pCur (delete can handle nullptr)
}

//print data recursively
void List::printListRecInOrder(Node* head)
{
	if (this->mphead != nullptr)
	{
		Node *pCur = head;

		if (pCur->getpNext() != nullptr)
			printListRecInOrder(head->getpNext());

		cout << pCur << endl;
	}
}

