#include "stdafx.h"
#include "Instruction.h"


/*
NAME

	ParseInstruction - Parse the Instruction

SYNOPSIS

	Instruction::InstructionType Instruction::ParseInstruction(string&a_buff) 

	string&a_buff-> raw line from the file 

DESCRIPTION

	removes comments, parses the instruction 

RETURNS
	
	returns an element of enum InstructionType

*/
Instruction::InstructionType Instruction::ParseInstruction(string&a_buff) {
	
	// make copy of original instruction 
	m_instruction = a_buff;

	//get rid of the comment -> search the string for first ; 
	size_t isemi = a_buff.find(';');

	if (isemi != string::npos) {
		a_buff = a_buff.substr(0, isemi);
	}

	//parse instruction into basic elements
	GetLabelOpcodeEct(a_buff);
	
	//size equal to zero cause substr can become nonexists, not even " "
	if (a_buff.size() == 0) {
		return InstructionType::ST_Comment;
	}

	//if label is not empty that means it is MachineLanguage or Assembly which we want to extract later
	else if (m_Label != " " ){  
		return InstructionType::ST_MachineLanguage;
	}

	//if end, we have reached the last line of code in our text file
	else if (m_OpCode == "end") {
		return InstructionType::ST_End;
	}

	//anything without end, comment, or label is considered a T_AssemblerInstr;
	else {
		return InstructionType::ST_AssemblerInstr;
	}

}
/*Instruction::InstructionType Instruction::ParseInstruction(string&a_buff)*/


/*
NAME

	GetLabelOpcodeEct - Parse the Instruction

SYNOPSIS

	void Instruction::GetLabelOpcodeEct(const string &a_buff)

	const string &a_buff -> no-comment line from Instruction::ParseInstruction(string&a_buff)

DESCRIPTION

	assigns label, opcode, operand; parses the operand; record errors


*/
void Instruction::GetLabelOpcodeEct(const string &a_buff) {

	// The elemements of a instruction
	m_Label = m_OpCode = m_Register = m_Operand = " ";

	istringstream ins(a_buff);

	//using the last one for the error reporting
	//no spaces allowed between these
	string a1, a2, a3, a4;
	ins >> a1 >> a2 >> a3 >> a4;

	//if there is label in the line
	if (a_buff[0] != ' ' && a_buff[0] != '\t') {
		//setting the label
		m_Label = a1;
		m_OpCode = a2;
		m_Operand = a3;
		
	}
	//if there is no label in the line
	else {
		m_OpCode = a1;
		m_Operand = a2;
	}

	//translate op code string into numerical value
	m_NumOpCode = op_code_map[m_OpCode];
	if (m_NumOpCode == 0 && m_OpCode != "" ){

		string msg = "\"" + m_OpCode + "\" is an illegal operation code";
		Errors::RecordError(msg);
	}

	//parsing Operand if its a register
	size_t isemi = m_Operand.find(',');
	char l_register;
	m_NumRegister = 0; //initially zero

	//if there is a comma we are dealing with a register and label or varaible
	if (isemi != string::npos) {

		//if there is a register, we are converting first char to int only register 0-9, so char is enough
		l_register = m_Operand[0];
		m_NumRegister = int(l_register) - 48; //-48 because it's converting to ascii

		//operand will be after comma
		m_Operand = m_Operand.substr(isemi+1);
		//if first char of operand is a number, that's improper naming 
		if (isdigit(m_Operand[0])) {
			string msg = "\"" + m_Operand + "\" is an illegal operand for \"" + m_OpCode + "\"";
			Errors::RecordError(msg);
		}
	}

}
/*void Instruction::GetLabelOpcodeEct(const string &a_buff)*/


/*
NAME

	LocationNextInstruction - Parse the Instruction

SYNOPSIS

	int Instruction::LocationNextInstruction(int a_loc, InstructionType a_st)

	int a_loc -> location in file 

	InstructionType a_st -> type of instruction 

DESCRIPTION

	considers whether its a regular line, has ds, or has org

RETURNS

	returns int which is the next instruction (not line!!!)in the file.

*/
int Instruction::LocationNextInstruction(int a_loc, InstructionType a_st) {

	if (a_st != ST_Comment) {
		//org -> next instrcution starts at the operands value
		if (m_OpCode == "org") {
			// converting string to int using streamstream object  
			stringstream conversion(m_Operand);
			int convert_int = 0;
			conversion >> convert_int;

			//if not a number, its an error
			if (isdigit(m_Operand[0]) == false) {
				string msg = "\"" + m_OpCode + "\" must have a valid operand";
				Errors::RecordError(msg);
			}


			return a_loc = convert_int;
		}
		else if (m_OpCode == "ds") {
			// converting string to int using streamstream object  
			stringstream conversion(m_Operand);
			int convert_int = 0;
			conversion >> convert_int;

			//if not a number, its an error
			if (isdigit(m_Operand[0]) == false) {
				string msg = "\"" + m_OpCode + "\" must have a valid operand";
				Errors::RecordError(msg);
			}

			return a_loc = a_loc + convert_int;
		}

		//in the rest of cases, its just adding the next instrcution
		else {
			return a_loc + 1;
		}
	}

	//instruction remains the same because its a comment
	return a_loc;
}
/*int Instruction::LocationNextInstruction(int a_loc, InstructionType a_st)*/