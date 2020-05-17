//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{	//file access class is needed
    // Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler( )
{
}


/*
NAME

	PassI - establish the locations of the symbols .

SYNOPSIS

	void Assembler::PassI( );

DESCRIPTION

	Get Next Line.
	Read the next line from the source file.
	Detect comments and blanks lines.
	Parse the statement into label, operation code, and operand.
	Add Label to Symbol Table - adds a label and its address to the symbol table.
	Get Location of Next Instruction - get the address of the next instruction.	
	

*/
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string line = ""; 
		
        if( ! m_facc.GetNextLine( line ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( line ); 

		
        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) {
			return;
		}
        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {	
			//skipping the code below (adding Symbols), and going onto another iteration in loop
        	continue;
		}
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc);
        }
		// Compute the location of the next instruction.
		// previously last line, but "continue" will be screwing up and missing which is the next location
		loc = m_inst.LocationNextInstruction(loc, st);

    }
}
/*void Assembler::PassI( );*/


/*
NAME

	PassII - generate a translation .

SYNOPSIS

	void Assembler::PassII();

DESCRIPTION

	Rewind Source File - prepare to reread the source file.
	Get Next Line.
	Generate Instruction - display the original assembler instruction and its machine language equivalent.
	Get Location of Next Instruction. Report error if we have exceeded to maximum memory size.

*/
void Assembler::PassII() {

	//sets up the error class to start safely
	Errors::InitErrorReporting();

	//rewind file to begin readind the file from start
	m_facc.rewind();

	int loc = 0;        // Tracks the location of the instructions to be generated.
	cout << " " << endl;
	cout << "Translation of Program :" << endl;
	cout << "Location" << setw(10) << " Contents" << setw(30) << " Original Statement     " << endl;

	for ( ; ; ) {
		
		string line = "";

		//this is triggered if exiting improperly
		if (!m_facc.GetNextLine(line)) {
			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			string msg = "Missing an end statement";
			Errors::RecordError(msg);

			//displaying errors at every line
			Errors::DisplayErrors();

			return;
		}

		// Parse the line and get the instruction type.
		string copy_line = line;
		Instruction::InstructionType st = m_inst.ParseInstruction(line);


		//get the values for opcode and register
		int op_num = m_inst.GetOpCode();
		int reg_num = m_inst.GetRegister();

		//lines with no labels will be zero
		int addr_num = 0;


		//making a difference between parsing a single integer and a label
		if (m_inst.isOperand() == true) {
			string operand = m_inst.GetOperand();
			//if operand starts with letter -> its a label or variable
			if (isalpha(operand[0]) != 0) {
				//using getlabel from instruction class as a parameter for look up in symtable private map
				addr_num = m_symtab.GetLabelAddress(operand);
			}
			//if operand is a number just convert to int
			else {
				addr_num = stoi(operand);
				//if address is bigger than 5 digits, it cannot fit in memory
				if ((addr_num / 1'000'000) > 0) {
					string msg = "Operand is too large for Quack3200 memory";
					Errors::RecordError(msg);
				}	
			}
		}


		//exiting the proper way, this would be triggered
		if (st == Instruction::ST_End) {
			cout << "                            " << copy_line << endl;
			return;
		}

		else if (st == Instruction::ST_Comment) {
			cout << "                            " << copy_line << endl;
			continue;
		}

		//string used to display instruction, 
		//string because it can display blank screen if certain assembly instructions are in place
		// 8 spaces to emulate a full content
		string machine_line_string = "        ";
		int machine_lang_line = 0 ;

		//if op num is zero, its an assembly instruction which deals with memory -> not relevant to show contents
		if (op_num > 0 || op_num < -2) {
			//below -2 is the assembly code dc
			if (op_num < -2) {
				op_num = 0;
			}

			machine_lang_line = op_num * 1'000'000 + reg_num * 100'000 + addr_num;
			machine_line_string = to_string(machine_lang_line);
		}

		//inserting for emulator to use later
		m_em_memory.insert(pair<int, int>(loc, machine_lang_line));
		
		//printing location 
		cout  << loc << "      ";

		//printing either full content or blank line
		if (op_num >= 0) {
			cout << setw(8) << setfill('0') << machine_line_string;
		}
		else {
			cout << setw(8) << machine_line_string ;
		}
		
		//printing content of the original statement
		cout << "      " << copy_line << endl;

		//get location for the next iteration
		loc = m_inst.LocationNextInstruction(loc, st);

		//issue an error if the location is over the limit
		if (loc >= 100'000) {
			string msg = "Insufficient memory for the translation.";
			Errors::RecordError(msg);
		}

		//displaying errors at every line
		Errors::DisplayErrors();

	}
}
/*void Assembler::Pass2( );*/


/*
NAME

	RunProgramInEmulator -  Run emulator on the translation..

SYNOPSIS

	void Assembler::RunProgramInEmulator();

DESCRIPTION

	insert every line into memory
	run the program

*/
void Assembler::RunProgramInEmulator() {

	//make some space after passII
	cout << endl;
	cout << endl;

	//get the iterator for the unordered map in order to iterate
	unordered_map<int, int>::iterator itr;
	for (itr = m_em_memory.begin(); itr != m_em_memory.end(); ++itr) {

		if ((itr->first) > 100'000) {
			return;
		}

		//inserting from unordred map which was used in PassII in every iteration
		m_emul.insertMemory(itr->first, itr->second);
	}

	m_emul.runProgram();

}
/*void Assembler::RunProgramInEmulator()*/
