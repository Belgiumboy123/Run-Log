/*
 *  Sqlite3Wrapper.h
 *  Sqlite3Wrapper
 *
 *  Created by Brecht Moulin on 6/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef Sqlite3Wrapper_H
#define Sqlite3Wrapper_H

#include <iostream>
#include <vector>

using std::vector;
using std::string;

class sqlite3;

/**
 * Very simple wrapper around sqlite3 that hides the callback functions
 */
class Database{
	
private: 
	
	sqlite3* db;
	
	static int handleQ( void* v, int numCol, char** resultCol , char** resultColName );
	
public:
	
	Database();
	~Database();
	
	bool openDB(const char* databaseFile);
	vector<vector<string> > queryDB( const string& sqlCmd );
	vector<vector<string> > queryDB( const char* sqlCmd );
	void closeDB();
	
};


#endif
