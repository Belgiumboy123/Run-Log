/**
* StringManip.cpp
*/
#pragma warning(disable:4786)
#include "StringManip.h"

/**
* Returns true if label contains just whitespace
*/
bool isNotWhiteSpace( const char* label )
{
	string str = (string) label;
	size_t found = str.find_first_not_of( WHITESPACE );
	str.erase( 0,found );
	return str != "";
}

/**
* Return given bool as string, "yes" or "no"
*/
string BoolToStr( const bool& pBool )
{
	return pBool ? "yes" : "no";
}

/**
* Return given string as bool
*/
bool StrToBool( const string& s )
{
	return s == "yes" ? true : false;
}

/**
* Return given string as double
*/
double StrToDouble( const string& s )
{
	return atof( s.c_str() );
}

/**
* Return given double as string
*/
string DoubleToStr( double& n )
{
        std::ostringstream result;
        result << n;   
        return result.str();
}

/**
* Return given int as string
*/
string IntToStr( const int& n )
{
        std::ostringstream result;
        result << n;   
        return result.str();
}

/**
* Return given string as int
*/
int StrToInt( const string& s )
{
	return atoi( s.c_str() );
}

/**
* Return string without leading whitespace
*/
string& killLeadingWhiteSpace(  string& str )
{
	return str.erase( 0, str.find_first_not_of( WHITESPACE ) );
}

/**
* Return string without trailing whitespace
*/
string& killTrailingWhiteSpace(  string& str )
{
	return str.erase(  str.find_last_not_of( WHITESPACE )+1 );
}

/**
* Returns true if string contains any digits.
*/
bool containsNumbers( const string& value )
{
	return value.find_first_of( DIGITS ) != string::npos;
}

/**
 * Return string removing OTHERINPUT from string
 */
 string removeOtherInput( const string& info )
{
	if( info.find_first_of( OTHERINPUT ) != string::npos )
		return info.substr( 0,info.size()-1);
		
	return info;
}


/**
* Return string correcting the input string x, 0x-59 is allowed
*/
string correctTimeInput( const string& time )
{
	if( time.size() == 1 )
	{
		if( time.find_first_of( OTHERINPUT ) != string::npos )
			return "";
	}
	else if( time.size() == 2 )
	{
		if( time.find_first_of( TIMEDIGITS ) != 0 ) 
			return time.substr(0,1);
	}
	else //> 2
		return time.substr( 0,2 );
	
	return time;
}

/**
* Returns a string pointer to array of strings that was seperated in paramter by tabs
*
* Must have a tab after the last char in info
*/
vector<string> seperateByTabs( const string& info, const int& num )
{
	vector<string> v;
	string temp = info;
	
	int count = 0;
	while ( temp != "" )
	{
		size_t found = temp.find( "\t" );
		if( found != string::npos )
		{
			v.push_back( temp.substr( 0,found ) );
			temp = temp.substr( found+1);
			count++;
		}
		else
		{
			temp = "";
			break;
		}
	}
	return v;
}

/**
* Returns a string pointer to array of strings that was seperated in paramter by tabs
*
* Must have a tab after the last char in info
*/
vector<string> seperateByDelimit( const string& info, const string& delimit )
{
	vector<string> v;
	string temp = info;
	
	int count = 0;
	while ( temp != "" )
	{
		size_t found = temp.find( delimit );
		if( found != string::npos )
		{
			v.push_back( temp.substr( 0,found ) );
			temp = temp.substr( found+delimit.size());
			count++;
		}
		else
		{
			temp = "";
			break;
		}
	}
	return v;
}

/** Print each string in vector */
void printv( const vector<string>& v )
{
	cout << "printing vector" << endl;
	for( int i = 0;  i<v.size(); i++)
	{
		cout << v[i] << endl;
	}	
}

/**Return given string as a Correct 2 digit time input
 * I.E. '07', '59', '00'
 */
string correct2DTimeInput( const string& info )
{
	if( info.size() == 0 )
		return "00";
	else if ( info.size() == 1 )
		return "0" + info;
	
	return info;
}

vector<string>::iterator findInVec(  vector<string>& v, const string& info )
{
	vector<string>::iterator it = v.begin();
	while( it != v.end() )
	{
		if( (*it) == info ) return it;
		it++;
	}

	return it;
}

int getIndexInArray( const string* _array, const int& len, const string& val )
{	
	for( int i = 0; i<len; i++)
	{
		if (_array[i] == val )
			return i;
	}

	return -1;
}