//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/*
NAME

	FileAccess - constructor, opens the file .

SYNOPSIS

	FileAccess::FileAccess( int argc, char *argv[] )

	char *argv[] -> file itself

DESCRIPTION

	opens the file, checks if it exists

*/
FileAccess::FileAccess( int argc, char *argv[] ) {
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
		cerr << argc << endl;
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }

	cout << "Opened file successfully" << endl;
}
/*FileAccess::FileAccess( int argc, char *argv[] )*/


/*
NAME

	GetNextLine  - gets the next line.

SYNOPSIS

	bool FileAccess::GetNextLine( string &a_buff )

	 string &a_buff -> passed by reference line from PassI function

DESCRIPTION

	gets the next line

*/
bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
        return false;
    }
    getline( m_sfile, a_buff );
    
    // Return indicating success.
    return true;
}
/*bool FileAccess::GetNextLine( string &a_buff )*/


/*
NAME

	rewind  - sets the reader pointer to the first line of the file

SYNOPSIS

	void FileAccess::rewind( )

DESCRIPTION

	 sets the reader pointer to the first line of the file

*/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}
/*void FileAccess::rewind( )*/
    

FileAccess::~FileAccess()
{
	// Not that necessary in that the file will be closed when the program terminates, but good form.
	m_sfile.close();
}
