/*
* Loop.h
*
* struct Loop
*
* class LoopVector
*/

#pragma warning(disable:4786)

#ifndef LOOP_H
#define LOOP_H

#include "StringManip.h"
#include <set>


/**
* struct that holds name and number of miles in loop
*
* has a global operator== that differentiates on name
*/
struct Loop{

	string m_Name;
	string m_Miles;

	friend bool operator==( Loop loop1, Loop loop2 );
};

/**
* class that holds stores Loops
*/
class LoopVector : public vector<Loop*> {

private:
	
	typedef vector<Loop*>::iterator iter;

	static const string DELIMIT;
	static const string NEWLINE;

public:

	/** default constructor */
	LoopVector();

	/** constructor from given list of loop */
	LoopVector( string& listOfLoops );

	/** fill loop vector from list of loop  */
	void buildVector( const string& listOfLoops );

	/** Return a string representing the loop vector 
	* that can be written to a file 
	*/
	string GetStringForFile();

	/** Get list of loops in string format */
	vector<string> getLoops();

	/** get list of loop names */
	vector<string> getLoopNames();

	/** get miles in given loop */
	string getMilesInLoop( const string& loopName );
 
	bool push_back( string& p_Loop );
	void erase( string& pLoopName );

	void print();

	/** Return an iterator to given Loop in vector */
	vector<Loop*>::iterator find( const string& p_Loop );

	/** Return true if it contains this loop */
	bool contains( const string& p_Loop );

	/** convert given string to a Loop struct object */
	Loop* convert( string& p_Loop);

	virtual ~LoopVector()
	{
		for( iter it = begin(); it != end(); it++)
		{
			delete (*it);
		}
	}
};

#endif
