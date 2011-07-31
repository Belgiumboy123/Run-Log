#pragma warning(disable:4786)
#pragma warning(disable:4503)
#ifndef LOG_H
#define	LOG_H

#include "FileWriter.h"
#include <map>
#include <list>

using namespace std;

/**
* String compare funtion object
*/
struct stringCompare
{
	//might need to change to order based on number
	bool operator() ( const string& s1, const string& s2 ) const
	{
		return (s1 < s2);
	}
};

/**
* Wrapper for map specialization <string, string>
*/
class Log
{

private:

	typedef multimap<string,string, stringCompare> mapType;
	typedef mapType::iterator iter;
	typedef pair<iter,iter> iterRange;
	typedef map<string,string> mapStatsType;
	typedef mapStatsType::iterator iterStats;
	typedef map< string, vector<string> > mapStrToVec;

	mapType m_Log;
	mapStatsType m_Log_Stats;
	mapStrToVec m_Log_2ndItem;

	static const string DELIMIT;
	static const string NEWLINE;

public:

	Log();
	void buildLog( const string& data );

	void add( const string& date, string& info );
	void remove( const string& date, string& info );

	/** Returns map, only to be used for stats creation */
	mapType getMap() const { return m_Log; }

	/** Return vector containing info for all entries for this date */
	vector<string> getInfo( const string& date ); 

	/** Return vector containing MainInfo or MainExtraInfo depending on bool for all entries for all given dates */
	vector< string > getInfo( const vector<string>& dates, const bool& mainInfo );

	/** Return just the main info of given Log entry */
	string extractMainInfo( const string& info );

	/** Return main and other extras of given Log entry */
	string extractMainExtraInfo( const string& info );

	/** return vector of strings up to N size seperating info by "\t" */
	vector<string> extractUpToNthItem( const string& info, const int& N );

	/** Return second item in info string */
	string getSecondItem( const string& info );

	/** Extracts first item from info delimited by a tab */
	string extractMainInfoHelper( const string& info );

	/** Return entire Log as one string that can be written to a file */
	string getStringForFile();

	//////////////////
	//Stat Functions//
	//////////////////

	/** Retrieve stat info for each string in info and place in outVector */
	void getStatInfo( string* outVector, const vector<string>& info );

	/** Extract main info from info and add to Stats Log for both dates */
	void addStats( const string& date1, const string& date2, const string& info );

	/** Extract main info from info and remove to Stats Log for both dates */
	void removeStats( const string& date1, const string& date2, const string& info );

	/** add maininfo to date */
	void addStats( const string& date, const string& mainInfo );
	
	/** remove maininfo to date */
	void removeStats( const string& date, const string& mainInfo );

	/** build Log stats from given string which is in correct format
	* date \t statistic \n 
	*/
	void buildLogStats( const string& data );

	/** Return entire stats log as one string that can be written to a file */
	string getStringStatsForFile();

	///////////////////////////
	//2nd Item Stat Functions//
	///////////////////////////

	/** Write m_Log_2ndItem to files  */
	void write2ndItemStatsToFile();

	/** Read the item file and store in m_Log_2ndItem 
	* If no file place in an empty vector
	*/
	vector<string>& build2ndItem( const string& item );
	
	/** add given info to item calls _i() */
	void add2ndItemStats( const string& date, const string& allInfo );

	/** remove given info from item, calls _i() */
	void remove2ndItemStats( const string& date, const string& allInfo );

	/** add given info to item / internal */
	void add2ndItemStats_i( const string& item, const string& info );

	/** remove given info from item / internal */
	void remove2ndItemStats_i( const string& item, const string& info );

	/** get vector holding all info corresponding to given item */
	vector<string> get2ndItemStatsInfo( const string& item );

	/** Returns true if given item has been loaded */
	bool contains2Item( const string& item );

	/** Return string of vector content seperated by NEWLINE */
	string writeVector2File( const vector<string>& v );

	/** Return string containing just needed info */
	string stripInfo2ndItem( const string& item );

	/** Build all txt files for 2ndItemLog */
	void buildAll2ndItemFiles();

	/** Print contents of m_Log */
	void print();

	virtual ~Log(){}
};

#endif