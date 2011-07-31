/**
* RunLog.h 
*
* Class RunLog
*/

#ifndef RUNLOG_H
#define RUNLOG_H

#include "Calendar.h"
#include "Loop.h"
#include "FileWriter.h"
#include "Log.h"

#include <algorithm>

class RunLog : public Date
{

private:

	LoopVector* m_Loops;
	Log* m_Log;
	static const char* loopsFile;
	static const char* logFile;
	static const char* logFile_Stats;
	
	/** info is date \t time \t pace 
	*
	* "November 11 2010" delimited by " ";
	*/
	struct DateSorter 
	{
		bool operator() (string info1, string info2) 
		{ 
			info1 = info1.substr( 0,info1.find( "\t"))+" ";
			info2 = info2.substr( 0,info2.find( "\t"))+" ";
			return lessThan( info1, info2 );
		}
	} _dateSorter;
	
	/**
	* Time is "hours:XX:XX"
	*/
	struct TimeSorter
	{
		bool operator() (string info1, string info2)
		{

			vector<string> v1 = seperateByDelimit( seperateByTabs(info1,3)[1]+":", ":");
			vector<string> v2 = seperateByDelimit( seperateByTabs(info2,3)[1]+":", ":");
						
			int i1,i2;
			if( v1.size() == 3 )
				i1 = convertToSeconds( StrToDouble(v1[0]), StrToDouble(v1[1]), StrToDouble(v1[2]) );
			else
				i1 =  convertToSeconds( 0.0, StrToDouble(v1[0]), StrToDouble(v1[1]) );
 
			if( v2.size() == 3 )
				i2 = convertToSeconds( StrToDouble(v2[0]), StrToDouble(v2[1]), StrToDouble(v2[2]) );
			else
				i2 =  convertToSeconds( 0.0, StrToDouble(v2[0]), StrToDouble(v2[1]) );
 
			return i1<i2;
		}
	} _timeSorter;

public:

	RunLog();

	void New();
	void Load();
	void Save();

	/** Forwarding Loopvector calls */
	bool push_back( string& info );
	void erase( string& info );
	vector<string> getLoops();
	vector<string> getLoopNames();
	string getMilesInLoop( const string& loopName );

	/** Forwarding Log calls */
	void add( string& info );
	void remove( string& info );
	vector<string> getInfo( const vector<string>& dates, const bool& mainInfo);
	vector<string> getInfo( const string& date );
	vector<string> getStats(const bool& months = false);
	vector<string> get2ndItemStats( const string& item );
	vector<string> get2ndItemSorted( const string& item, const int& sortBy );
	
	/** Time calculation fuctions */
	static int convertToSeconds( const double& p_hours, const double& p_min, const double& p_sec );
	static void convertToMinSec( double* array, const double& p_seconds );
	string PaceCalculator(string& info);

	void print()
	{
		m_Loops->print();
		m_Log->print();
	}

	~RunLog() 
	{ 
		if( m_Loops != 0){
			delete m_Loops;
			Trace( " m_loops deleted" );
		}	
		if( m_Log != 0)
		{
			delete m_Log;
			Trace( "m_Log deleted" );
		}
	}
};

#endif