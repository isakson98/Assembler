//
//		Emulator class - Contains functionality to record a machine language program and to execute it 
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

class emulator {

public:

	const static int MEMSZ = 100'000;	// The size of the memory of the Quack3200. 
    emulator() {

        memset( m_memory, 0, MEMSZ * sizeof(int) );
    }
    // Records instructions and data into Quack3200 memory.
    bool insertMemory( int a_location, int a_contents );
    
    // Runs the Quack3200 program recorded in memory.
    bool runProgram( );

private:

	int PromptUser(); //activated when asked to "read"

	int m_memory[MEMSZ];       // The memory of the Quack3200.
    int reg[10];					// The accumulator for the Quack3200
};

#endif

