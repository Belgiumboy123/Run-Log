/*
 *  Sqlite3Wrapper.cp
 *  Sqlite3Wrapper
 *
 *  Created by Brecht Moulin on 6/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Database.h"
#include <sqlite3.h>

using std::cout;
using std::endl;

Database::Database(){}
Database::~Database(){}

/**
 * Returns true if database was opened successfully
 * false otherwise.
 */
bool Database::openDB(const char* databaseFile){
	
	return !sqlite3_open( databaseFile, &db );
}

void Database::closeDB(){
	
	sqlite3_close(db);
}

/**
 * sqlite3_exec  callback - called for every record
 * 
 * v - user parameter - vector<vector<string> >
 *     where each row is a vector
 * numCol - number of cols in result
 * resultCol - array holding result
 * resultColName - array holding corresponding table collumn names
 */
int Database::handleQ( void* v, int numCol, char** resultCol , char** resultColName ){
	
	vector<string> row;
	for( int i = 0; i<numCol; ++i ){
		
		row.push_back( resultCol[i] );
	}
	
	((vector<vector<string> >*)v)->push_back(row);
	return 0;
}

/**
 * Query the sqlite3 database with given query 
 * Store and return all results in matrix.
 *
 * Need to add error handling
 */
vector<vector<string> > Database::queryDB( const char* sqlCmd ){
	
	char* errorMsg[1024];
	vector<vector<string> > result; 
	sqlite3_exec( db, sqlCmd, &handleQ, &result, errorMsg );
	return result;
}


vector<vector<string> > Database::queryDB( const string& sqlCmd ){
	
	return queryDB( sqlCmd.c_str() );
}
