//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:
	// initializing the opcode map for translation to int 
    Instruction( ) { 
		op_code_map["add"] = 1;
		op_code_map["sub"] = 2;
		op_code_map["mult"] = 3;
		op_code_map["div"] = 4;
		op_code_map["load"] = 5;
		op_code_map["store"] = 6;
		op_code_map["read"] = 7;
		op_code_map["write"] = 8;
		op_code_map["b"] = 9;
		op_code_map["bm"] = 10;
		op_code_map["bz"] = 11;
		op_code_map["bp"] = 12;
		op_code_map["halt"] = 13;
		// these are assembly instructions 
		op_code_map["org"] = -1;
		op_code_map["ds"] = -2;
		op_code_map["dc"] = -3;
	};
    ~Instruction( ) { };

	//public to allow easier to access by other classes
	unordered_map<string, int> op_code_map;

    // Codes to indicate the type of instruction we are processing.
    enum InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,  		// Assembler Language instruction.
        ST_Comment,          		// Comment or blank line
        ST_End                   		// end instruction.
    };

    // Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

    // Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc, InstructionType st);

	// ACCESS functions below

    // To access the label
    inline string &GetLabel( ) {

        return m_Label;
    };

	// To access the label
	inline string &GetOperand() {
		
		return m_Operand;
	};

	// To access the m_NumOpCode
	inline int &GetOpCode() {

		return m_NumOpCode;
	};

	// To access the m_NumRegister
	inline int &GetRegister() {

		return m_NumRegister;
	};

	// To determine if a label is blank.
	inline bool isOperand() {

		//spaces are not labels
		if (m_Operand == " ") {
			return false;
		}

		return !m_Operand.empty();
	};

    // To determine if a label is blank.
    inline bool isLabel( ) {

		//spaces are not labels
		if (m_Label == " ") {
			return false;
		}

        return ! m_Label.empty();
    };


private:

	// found in InstructionType ParseInstruction(string &a_buff)
	void GetLabelOpcodeEct(const string &a_buff);

	string m_instruction;    // The original instruction.

    // The elemements of a instruction
    string m_Label;            // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Register;       // The register value.
    string m_Operand;      // The operand.

    // Derived values.
    int m_NumOpCode;     // The numerical value of the op code.
    int m_NumRegister;	   // the numberic value for the register.
};


