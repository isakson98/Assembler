#include "stdafx.h"
#include "Emulator.h"


/*
NAME

	insertMemory -  Run emulator on the translation..

SYNOPSIS

	bool emulator::insertMemory(int a_location, int a_contents);

DESCRIPTION

	insert a line unless there is nothing in it or the size does not permit


RETURNS

	returns bool depending whether the insertion was succsefful or not

*/
bool emulator::insertMemory(int a_location, int a_contents) {

	// if current location is empty, it's ok to put contents in it and size does not overflow
	if (m_memory[a_location] == 0 && a_location < MEMSZ) {
		m_memory[a_location] = a_contents;
		return true;
	}
	else {
		return false;
	}
	
}
/*bool emulator::insertMemory(int a_location, int a_contents) */


/*
NAME

	runProgram -  executes a line of the machine language

SYNOPSIS

	bool emulator::runProgram()

DESCRIPTION

	iterates through every line stored in memory and executes its instruction

RETURNS

	returns true when executed

*/
bool emulator::runProgram() {


	// we start at address 100
	int loc = 100;

	while (loc < MEMSZ) {

		//for ease of manipulation, convert the line to a string
		string content  = to_string(m_memory[loc]);
		string opCode ="00";
		string reg_s = "0";
		string address ="00000";

		//for converting string to int 
		int opCode_int;
		int reg_int;
		int addres_int;


		//if content has 8 digits = opcode is between 10 and 13
		if (content.length() == 8){
			//opcode 2 digits
			opCode = content.at(0);
			opCode.push_back(content.at(1));
			// reg 1 digit
			reg_s = content.at(2);
			// address 5 digits
			address = content.substr(3, 8);
		}
		// executes if opcode is one digit
		else if (content.length() == 7) {
			//opcode 1 digits
			opCode = content.at(0);
			// reg 1 digit
			reg_s = content.at(1);
			// address 5 digits
			address = content.substr(2, 7);
		}


		//converting string to int 
		opCode_int = stoi(opCode);
		reg_int = stoi(reg_s);
		addres_int = stoi(address);

		// a decision switch -> a case per opcode
		switch (opCode_int) {
		//add
		case 1: 
			reg[reg_int] = reg[reg_int] + m_memory[addres_int];
			break;
		//sub
		case 2:
			reg[reg_int] = reg[reg_int] - m_memory[addres_int];
			break;
		//mult
		case 3:
			reg[reg_int] = reg[reg_int] * m_memory[addres_int];
			break;
		//div
		case 4:
			reg[reg_int] = reg[reg_int] / m_memory[addres_int];
			break;
		//load
		case 5:
			reg[reg_int] = m_memory[addres_int];
			break;
		//store
		case 6:
			m_memory[addres_int] = reg[reg_int];
			break;
		// read
		case 7:
			m_memory[addres_int] = PromptUser();
			break;
		//write
		case 8:
			cout << m_memory[addres_int] << endl;
			break;
		// branch
		case 9:
			loc = addres_int;
			break;
		// branch minus
		case 10:
			if (reg[reg_int] < 0) {
				loc = addres_int;
			}
			break;
		//branch zero 
		case 11:
			if (reg[reg_int] == 0) {
				loc = addres_int;
			}
			break;
		case 12:
			if (reg[reg_int] > 0) {
				loc = addres_int;
			}
			break;
		//halt 
		case 13:
			return true;
		}

		//
		loc++;
	}


	return true;
}
/*bool emulator::runProgram()*/



/*
NAME

	PromptUser -  asks for input

SYNOPSIS

	int emulator::PromptUser();

DESCRIPTION

	prompts the user when the opcode is "read" in bool emulator::runProgram();

RETURNS

	returns input number

*/
int emulator::PromptUser() {

	int input;
	cout << "? ";
	cin >> input;
	return input;

}
/*int emulator::PromptUser() */