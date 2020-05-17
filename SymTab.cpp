//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/
void SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );

	//searching for duplicates
    if( st != m_symbolTable.end() ) {
        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}
/*void SymbolTable::AddSymbol( string &a_symbol, int a_loc )*/


/*
NAME

	DisplaySymbolTable - shows entire the symbol table.

SYNOPSIS

	void SymbolTable::DisplaySymbolTable();

DESCRIPTION

	This function will iterate through the private member map "m_symbolTable" to
	illustrate both the location and the name of the variable
*/
void SymbolTable::DisplaySymbolTable() {

	cout << "Symbol Table:" << endl;
	cout << "Symbol#    Symbol     Location " << endl;

	int i = 0;
	for (auto it = m_symbolTable.cbegin(); it != m_symbolTable.cend(); ++it) {
		cout << i <<"           " << (*it).first << "          " << (*it).second << endl;
		i++;
	}
}
/*void SymbolTable::DisplaySymbolTable() */


/*
NAME

	GetLabelAddress - find label address in map .

SYNOPSIS

	int SymbolTable::GetLabelAddress(string &a_symbol);

DESCRIPTION
	
	iterated through each element in the our symbol table
	to fetch the symbol address

RETURNS

	returns int that represents the location of the label 
	in our program
	
*/
int SymbolTable::GetLabelAddress(string &a_symbol) {

	//finds an address by a specified letter as first 
	int it = 0;
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {
		it = m_symbolTable.find(a_symbol)->second;
		return it;
	}
	return it;
}
/*int SymbolTable::GetLabelAddress(string &a_symbol)*/