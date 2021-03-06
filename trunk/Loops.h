#include "Database.h"
#include <vector>
#include <string>
#include <map>

using std::map;
using std::vector;
using std::string;

class Loops{
	
private:
	
	map<string,string> mLoops;
	typedef map<string,string>::iterator iter;
	Database db;
	
public:
	
	Loops();
	
	Loops( const string& databaseFile );
	
	~Loops();
	
	/** Get list of loops in string format */
    vector<string> getLoops();
	
    /** get list of loop names */
    vector<string> getLoopNames();
	
    /** get miles in given loop */
    string getMilesInLoop( const string& loopName );
	
	/** add loop */
    bool push_back( string& loopInfo);
	
	/** erase loop */
    void erase( string& loopName );
	
	/** updates database and closes connection. */
	void saveToDBandClose();
	
	/** print map of loops to std */
	void print();
	
	/** Create table from scratch to be used when converting to database version */
	static void convertToDB(const string& listOfLoops, const string& dbFile);
};


