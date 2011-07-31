#include "Loops.h"
#include <iostream>

using std::pair;

Loops::Loops(){};

Loops::~Loops(){}

Loops::Loops( const string& databaseFile ){
	
	db.openDB( databaseFile.c_str() );
	vector<vector<string> > loops = db.queryDB( "SELECT name,miles FROM loops");
	
	for( int i = 0; i<loops.size(); ++i){
		const vector<string>& loop = loops[i];
		mLoops.insert ( pair<string,string>(loop[0],loop[1]));
	}
}

/**
 * Return vector contains strings of format
 "<name><\t><miles>"
 */
vector<string> Loops::getLoops(){
	
	vector<string> v;
	for( iter it = mLoops.begin(); it != mLoops.end(); ++it){
		
		v.push_back( it->first + "\t" + it->second);
	}
	
	return v;
}

vector<string> Loops::getLoopNames(){
	
	vector<string> v;
	for( iter it = mLoops.begin(); it != mLoops.end(); ++it){
		
		v.push_back( it->first);
	}
	
	return v;
}

string Loops::getMilesInLoop( const string& loopName ){
	
	iter it = mLoops.find( loopName );
	return it != mLoops.end() ? it->second : "";
}

bool Loops::push_back( string& loopInfo){
	
    size_t found = loopInfo.find( "\t" );
    if( found != string::npos )
    {
		std::cout << "push_back " << loopInfo << std::endl;
        string name = loopInfo.substr( 0, found );
		string miles = loopInfo.substr( found+1);
		std::cout << "name " << name << std::endl;
		std::cout << "miles " << miles << std::endl;
		db.queryDB( "INSERT INTO loops VALUES(\"NULL\",\"" + name + "\",\"" + miles + "\"  )");
		return mLoops.insert( pair<string,string>(name,miles)).second;	
    }
	
	return false;
}

void Loops::erase( string& loopName ){
	
	int num_items_deleted = mLoops.erase( loopName );
	std::cout << "erasing " << loopName << " " << num_items_deleted << std::endl;
	db.queryDB( "DELETE FROM loops WHERE name=\""+loopName+"\"");
}

void Loops::saveToDBandClose(){
	
	db.closeDB();
}

void Loops::print(){
	
	for( iter it = mLoops.begin(); it != mLoops.end(); ++it)
	{
		std::cout << it->first << "    " << it->second << std::endl;
	}
}


void Loops::convertToDB(const string& listOfLoops, const string& dbFile){
	
	Database db;
	db.openDB( dbFile.c_str());
	db.queryDB( "DROP TABLE loops" );
	db.queryDB( "CREATE TABLE loops(id INTEGER PRIMARY KEY, name TEXT UNIQUE NOT NULL, miles TEXT NOT NULL)");
	string& data = const_cast<string&>( listOfLoops );
	size_t found;
	while( data != "" && data.size() > 2 )
	{
		found = data.find( "\n" );
		
		if( found != string::npos ) //should always enter
		{
			string loop = data.substr( 0,found );				
			size_t found = loop.find( "\t" );
			if( found != string::npos )
			{
				std::cout << "push_back " << loop << std::endl;
				string name = loop.substr( 0, found );
				string miles = loop.substr( found+1);
				std::cout << "name " << name << std::endl;
				std::cout << "miles " << miles << std::endl;
				db.queryDB( "INSERT INTO loops VALUES(NULL,\"" + name + "\",\"" + miles + "\"  )");
			}
			
			data = data.substr( found+1 );
		}
		else
		{
			data = "";
		}
		
	}
	db.closeDB();
}