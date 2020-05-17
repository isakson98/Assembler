//
// This class will allow its clients to record the errors encountered and to display them. 
// The members of this class must be accessible everywhere in the code so that we can read and write everywhere.
//
#ifndef _ERRORS_H
#define _ERRORS_H

using namespace std;

class Errors {

public:
    
    // Initializes error reports.
    static void InitErrorReporting( );

    // Records an error message.
    static void RecordError( string &a_emsg );

    // Displays the collected error message.
    static void DisplayErrors( );

private:

	// bool to set flags after each record of an error
	static bool m_error_display;
	//vector for storing all messages
	static vector<string> m_ErrorMsgs;
};
#endif