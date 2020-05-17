#include "stdafx.h"
#include "Errors.h"
using namespace std;

//intializing private static variables
vector<string> Errors::m_ErrorMsgs = { "Start of errors" };
bool Errors::m_error_display = false;

/*
NAME

	InitErrorReporting -  Initializes error reports

SYNOPSIS

	void Errors::InitErrorReporting()

DESCRIPTION

	this function is used once in the start of passII to initialize 
	error_display to false, which is a safety measure because this class
	has been activated during passI as well, so it has a fresh start that way.


*/
void Errors::InitErrorReporting() {

	m_error_display = false;
	//because errors were also recorded during PassI in Instruction.cpp, 
	//so it's neat i am clearing the errors it recorded at that time
	m_ErrorMsgs.clear();

}
/*void Errors::InitErrorReporting() */


/*
NAME

	RecordError -  Records an error message.

SYNOPSIS

	void Errors::RecordError(string &a_emsg)

	a_emsg -> unique message for an error

DESCRIPTION

	this function pushes an error message into a private member vector
	every time it is called. Any time in one iteration of PassII it catches
	an error, it sets a flag (!)

*/
void Errors::RecordError(string &a_emsg) {
	//set the flag when an error is found
	m_error_display = true;
	m_ErrorMsgs.push_back(a_emsg);
}
/*void Errors::RecordError(string &a_emsg)*/


/*
NAME

	DisplayErrors -  Displays an error message.

SYNOPSIS

	void Errors::DisplayErrors()

DESCRIPTION

	this function displays only the most recent messages, but it does
	so after each iteration in PassII, so it is guaranteed that it will 
	return the most recent mistake. It will only display an error if the 
	flag in void Errors::RecordError(string &a_emsg) has been set. 

*/
void Errors::DisplayErrors() {

	if (m_error_display == true) {
		cout << "===================================================" << endl;
		cout << m_ErrorMsgs.back() << endl;
		cout << "===================================================" << endl;
		//after displaying an error, set the flag to false to avoid printing old error messages in new lines
		m_error_display = false;
	}
}
/*void Errors::DisplayErrors()*/