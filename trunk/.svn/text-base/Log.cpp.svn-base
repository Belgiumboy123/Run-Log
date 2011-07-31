#pragma warning(disable:4786)
#pragma warning(disable:4503)
#include "Log.h"

const string Log::DELIMIT = "\t";
const string Log::NEWLINE = "\n";

Log::Log() {}

void Log::buildLog( const string& dataC )
{
	string& data = const_cast<string&>( dataC );
	while( data != "" )
	{
		size_t found = data.find( NEWLINE );

		if( found != string::npos)
		{
			string entry = data.substr( 0, found );
			data = data.substr( found+1);
				
			size_t d_found = entry.find( DELIMIT );
			if( d_found != string::npos)
			{
				m_Log.insert( pair<string,string>(entry.substr( 0, d_found ), entry.substr( d_found+1) ) );
			}
		}
		else 
			data = "";
	}
}

void Log::add( const string& date, string& info )
{
	m_Log.insert( pair<string,string>( date, info) );
}

void Log::remove( const string& date, string& info )
{	
	iterRange range = m_Log.equal_range( date );
	for( iter it = range.first; it != range.second; ++it)
	{
		if( (*it).second == info )
		{
			m_Log.erase( it );
			break;
		}	
	}//*/
}

vector<string> Log::getInfo( const string& date )
{
	vector<string> v;
	iterRange range = m_Log.equal_range( date ); 
	cout << "get infro from " << date << endl;
	for( iter it = range.first; it != range.second; ++it){
		
		cout << it->second << " run getinfo " <<endl;
		v.push_back( it->second );
	}
	print();
	return v;
}

string Log::extractMainInfoHelper( const string& info )
{
	size_t found = info.find( "\t" );
	if( found != string::npos )
	{
		return info.substr( 0, found );
	}

	return "0";
}

vector<string> Log::extractUpToNthItem(  const string& info, const int& N )
{	
	vector<string> v;
	string info2 = info;
	for( int i = 0; i<N; i++)
	{
		size_t found = info2.find( "\t" );
		if( found != string::npos )
		{
			v.push_back( info2.substr( 0, found ));	
			info2 = info2.substr( found+1);
		}
		else
			break;
	}
	return v;
}

/**
* Return "X miles" 
*/
string Log::extractMainInfo( const string& info )
{
	return extractMainInfoHelper(info) + " miles\n";	
}

/**
* Return "X miles\nLoop\nTT"
*/
string Log::extractMainExtraInfo( const string& info )
{
	const vector<string>& v = extractUpToNthItem( info, 5);
	
	if( v.size() != 5 ) cout << " trouble " << endl;

	string s = v[0] + " miles\n";
	
	if( v[1] != "" )
		s += v[1] + "\n";
	
	if( v[2] != "" || v[3] != "" )
		s += "in " + v[2] + ":" + v[3] + ":" + v[4] + "\n";
	
	return s + "\n\n";
}

string Log::getSecondItem( const string& info )
{
	return extractUpToNthItem( info, 2 )[1];
}

/**
* 
*/
vector< string > Log::getInfo( const vector<string>& dates, const bool& mainInfo )
{
	vector<string> v;
	string s = "";
	int count = 0;
	for( vector<string>::const_iterator it = dates.begin(); it != dates.end(); it++)
	{
		iterRange range = m_Log.equal_range( (*it) );
		for( iter it2 = range.first; it2 != range.second; ++it2,count++)
		{
			if( mainInfo )
				s += extractMainInfo( it2->second );
			else
				s += extractMainExtraInfo( it2->second );
				
			if ( count == 2 ) break;
		}
		v.push_back( s );
		s = "";
	}

	return v;
}

/////////////////////////
// Statistic Functions //
/////////////////////////

void Log::getStatInfo( string* outVector, const vector<string>& info )
{
	for( int i = 0; i<info.size(); i++)
	{
		outVector[i] = info[i] + ": ";
		if( m_Log_Stats.find( info[i] ) == m_Log_Stats.end() )
			outVector[i] += "0 miles";
		else
			outVector[i] += m_Log_Stats[info[i]] + " miles";
	}
}

void Log::addStats( const string& date1, const string& date2, const string& info )
{
	Trace(" Adding stats for " + date1 + "  and " + date2 + " info is " + extractMainInfoHelper( info ));
	addStats( date1, extractMainInfoHelper( info ) );
	addStats( date2, extractMainInfoHelper( info ) );
}

void Log::removeStats( const string& date1, const string& date2, const string& info )
{
	removeStats( date1, extractMainInfoHelper( info ) );
	removeStats( date2, extractMainInfoHelper( info ) );
}

void Log::addStats( const string& date, const string& mainInfo )
{
	Trace( "adding stats " + date + " " +mainInfo);
	if( m_Log_Stats.find( date ) == m_Log_Stats.end() )
	{
		m_Log_Stats.insert( pair<string,string>( date, mainInfo ) );
		Trace( "Stat is now " + date + " " + m_Log_Stats[ date ] );
	}
	else
	{
		Trace( "before adding " + date + " " + m_Log_Stats[ date ] );
		string currentStat = m_Log_Stats[ date ];
		m_Log_Stats[ date ] = IntToStr( StrToInt( currentStat ) + StrToInt( mainInfo ));
		Trace( "after adding " + date + " " + m_Log_Stats[ date ] );
	}
	
}

void Log::removeStats( const string& date, const string& mainInfo )
{
	if( m_Log_Stats.find( date ) != m_Log_Stats.end() )
	{
		string currentStat = m_Log_Stats[ date ];
		int newStat =  StrToInt( currentStat ) - StrToInt( mainInfo );
		if( newStat < 1) 
			m_Log_Stats.erase( m_Log_Stats.find( date ) );
		else
			m_Log_Stats[ date ] = IntToStr( StrToInt( currentStat ) - StrToInt( mainInfo ));
	}
}

void Log::print()
{
	for( iter it = m_Log.begin(); it != m_Log.end(); it++)
	{
		cout << (it->first) << "<\t>" << (it->second) << endl;
	}
}

string Log::getStringForFile()
{
	string s = "";
	for( iter it = m_Log.begin(); it != m_Log.end(); it++)
	{
		s += it->first + DELIMIT + it->second + "\n";	
	}
	
	return s;
}

void Log::buildLogStats( const string& dataC )
{
	string& data = const_cast<string&>(dataC);
	while( data != "" )
	{
		size_t found = data.find( NEWLINE );

		if( found != string::npos)
		{
			string entry = data.substr( 0, found );
			data = data.substr( found+1);
				
			size_t d_found = entry.find( DELIMIT );
			if( d_found != string::npos)
			{
				m_Log_Stats.insert( pair<string,string>(entry.substr( 0, d_found ), entry.substr( d_found+1) ) );
			}
		}
		else 
			data = "";
	}
}

string Log::getStringStatsForFile()
{
	string s = "";
	for( iterStats it = m_Log_Stats.begin(); it != m_Log_Stats.end(); it++)
	{
		s += it->first + "\t" + it->second + "\n";	
	}
	
	return s;
}

////////////////////
/// 2nd Item Logs //
////////////////////

bool Log::contains2Item( const string& item )
{
	return m_Log_2ndItem.find( item ) != m_Log_2ndItem.end();
}

vector<string> Log::get2ndItemStatsInfo( const string& item )
{
	return build2ndItem( item );
}

vector<string>& Log::build2ndItem( const string& item )
{
	if( contains2Item( item ) ) return m_Log_2ndItem[ item ];
	vector<string> v;
	 
	string data = ReadFromFile( (item+".txt.").c_str() );

	while( data.size() > 0 )
	{
		size_t found = data.find( NEWLINE );
		if( found != string::npos )
		{
			v.push_back( data.substr( 0,found ));
			data = data.substr( found+1 );
		}
		else
			data = "";
	}
	
	m_Log_2ndItem.insert( pair<string, vector<string> >(item, v));
	return m_Log_2ndItem[ item ];
}

void Log::add2ndItemStats( const string& date, const string& allInfo )
{
	this->add2ndItemStats_i( getSecondItem( allInfo ), date+"\t"+stripInfo2ndItem( allInfo ) );
}

void Log::remove2ndItemStats( const string& date, const string& allInfo )
{
	this->remove2ndItemStats_i( getSecondItem( allInfo ), date+"\t"+stripInfo2ndItem( allInfo ) );
}

void Log::add2ndItemStats_i( const string& item, const string& info )
{
	Trace( "adding item " + item + " stats " + info );
	build2ndItem( item );
	m_Log_2ndItem[ item ].push_back( info );
}

void Log::remove2ndItemStats_i( const string& item, const string& info )
{
	build2ndItem( item );
	m_Log_2ndItem[ item ].erase( findInVec( m_Log_2ndItem[ item ],info) );
}

string Log::writeVector2File( const vector<string>& v )
{
	string data = "";

	vector<string>::const_iterator iter1 = v.begin();
	for( ; iter1 != v.end(); iter1++)
	{
		data += *iter1 + NEWLINE;
	}
	return data;
}

void Log::write2ndItemStatsToFile()
{
	mapStrToVec::iterator iter2 = m_Log_2ndItem.begin();

	for( ; iter2 != m_Log_2ndItem.end(); iter2++)
	{
		WriteToFile( (iter2->first + ".txt" ).c_str(), writeVector2File( iter2->second ) );
	}
}

/** Just need to extract the time info, total and pace ->totaltime \t pace */
string Log::stripInfo2ndItem( const string& info )
{
	const vector<string>& v = extractUpToNthItem( info, 7);
	string strippedInfo = "";

	if( v[2] != "" ) strippedInfo = v[2] + ":";
	strippedInfo  += v[3] + ":" + v[4] + "\t";
	strippedInfo += v[5] + ":" + v[6] + "\t";
	
	return strippedInfo;
}

/** just have to load log before this call */
void Log::buildAll2ndItemFiles()
{
	m_Log_2ndItem.clear();
	iter it = m_Log.begin();
	for( ;it != m_Log.end(); it++)
	{
		string date = it->first;
		string info = it->second;
		this->add2ndItemStats( getSecondItem( info ), date+"\t"+stripInfo2ndItem( info ) );
	}

	this->write2ndItemStatsToFile();
}

