/**
* FileWriter.h
*
* Contains global functions for file I/O
*/

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "stdio.h"
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#include "StringManip.h"

#ifdef _WIN32
	#include <direct.h>  //mkdir( PATH_W )
#else
	
#endif

//is completely erasing and rewriting the file every time 
//with large files this could be noticeably slow

using namespace std;

static const char* PATH_A = "/Library/Application Support/Run Log/";
static const char* PATH_W = "C:\\Program Files\\Run Log\\" ;

/**
* Create directory folder Run Log
*/
void makeRunLogDir();

/**
* Write given string to given file
*/
void WriteToFile( const char* filename, const string& input );

/**
* Return entire given file as one string
*/
string ReadFromFile( const char* filename );

/**
 * Trace file function
 */
void Trace( const string& output, const bool& addTab = false );
void endCurrentTrace();
void resetTrace();

#endif


