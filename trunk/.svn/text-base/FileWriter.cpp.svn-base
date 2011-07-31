/**
* FileWriter.cpp
*
* Contains global functions for file I/O
*/
#include "FileWriter.h"
#include <time.h>

/**
* Create directory folder Run Log
*/
void makeRunLogDir()
{			
#ifdef _WIN32
	cout << "windows" << endl;
	mkdir( PATH_W );
#else
	cout << "not windows" << endl;
	mkdir( PATH_A, 0777); 
#endif
}

/**
* Write given string to given file
*/
void WriteToFile( const char* filename, const string& input )
{
	string path;
#ifdef _WIN32
	path = PATH_W + (string) filename;
#else
	path = PATH_A + (string) filename;
#endif

	ofstream out;
	out.open( path.c_str() );
	if( out.is_open() )
	{
		out << input;	
		out.close();
	}
	else 
		Trace( "file not found " + (string)filename );
}

/**
* Return entire given file as one string
*/
string ReadFromFile( const char* filename ){
	
	string path;
#ifdef _WIN32
	path = PATH_W + (string) filename;
#else
	path = PATH_A + (string) filename;
#endif

	string s = "";
	ifstream in( path.c_str() );
	ostringstream out;

	if( in.is_open() )
	{	
		out << in.rdbuf();
		s = out.str();
		in.close();
	}else
		Trace( "file not found " + (string)filename );

	return s;
}

#define WRITETOFILE 1  
static string currentTab = "";

void Trace( const string& output, const bool& addTab )
{
	string filename2 = "trace.txt";
	string path;

#ifdef _WIN32
	path = PATH_W + (string) filename2;
#else
	path = PATH_A + (string) filename2;
#endif
	
	if( !addTab )
	{
		if( currentTab != "" )
			currentTab = currentTab.substr( 0,currentTab.size()-1);
	}
	
	ofstream out;
	out.open( path.c_str(), fstream::app );
	if( out.is_open() )
	{		
		
		cout << output << endl;
#if WRITETOFILE
		out << output << endl;
#endif		
		out.close();
	}
	else
	{
		
	}
	
	if( addTab)
		currentTab += "\t";
}

void resetTrace()
{
	string filename2 = "trace.txt";
	string path;
#ifdef _WIN32
	path = PATH_W + (string) filename2;
#else
	path = PATH_A + (string) filename2;
#endif
	
	ofstream out;
	out.open( path.c_str() );
	if( out.is_open() )
	{
		out << "";
		out.close();
	}
}

void endCurrentTrace()
{
	if( currentTab != "" )
		currentTab = currentTab.substr( 0,currentTab.size()-1);	
}

