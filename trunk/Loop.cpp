#include "Loop.h"

bool operator==( Loop loop1, Loop loop2 )
{
	return loop1.m_Name == loop2.m_Name;
}

const string LoopVector::DELIMIT = "\t";
const string LoopVector::NEWLINE = "\n";

LoopVector::LoopVector():  vector<Loop*>() {}

LoopVector::LoopVector( string& listOfLoops ) : vector<Loop*>()
{
	buildVector( listOfLoops );
}

void LoopVector::buildVector( const string& listOfLoops )
{
	string& data = const_cast<string&>( listOfLoops );
	size_t found;
	while( data != "" && data.size() > 2 )
	{
		found = data.find( NEWLINE );

		if( found != string::npos ) //should always enter
		{
			string loop = data.substr( 0,found );
			push_back( loop );
			data = data.substr( found+1 );
		}
		else
		{
			data = "";
		}
	}
}


string LoopVector::GetStringForFile()
{
	string s;
	for( iter it = begin(); it != end(); it++)
	{
		s += (*it)->m_Name + DELIMIT +  (*it)->m_Miles + NEWLINE;
	}
	return s;
}

vector<string> LoopVector::getLoops()
{
	vector<string> v;
	
	for( iter it = begin(); it != end(); it++)
	{
		v.push_back(  (*it)->m_Name + DELIMIT +  (*it)->m_Miles );	
	}
	return v;
}

vector<string> LoopVector::getLoopNames()
{
	vector<string> v;
	
	for( iter it = begin(); it != end(); it++)
	{
		v.push_back(  (*it)->m_Name );	
	}
	
	return v;
}

string LoopVector::getMilesInLoop( const string& loopName )
{
	string retVal = "";
	for( iter it = begin(); it != end(); it++)
	{
		if( (*it)->m_Name == loopName )
		{
			retVal = (*it)->m_Miles;
			break;
		}
	}
	return retVal;
}

bool LoopVector::push_back( string& p_Loop )
{	
	if( find( p_Loop ) != end() )
	{
		return false;
	}
	else
	{
		vector<Loop*>::push_back( convert( p_Loop ) );
		return true;
	}		
}

void LoopVector::erase( string& pLoopName )
{
	vector<Loop*>::iterator it = find(pLoopName+DELIMIT);
    if( it != end() )
        vector<Loop*>::erase( it );
}

void LoopVector::print()
{
	for( iter it = begin(); it != end(); it++)
	{
		cout << (*it)->m_Name << DELIMIT <<  (*it)->m_Miles << endl;
	}
}

Loop* LoopVector::convert( string& p_Loop )
{
	Loop* loop = new Loop;
	size_t found = p_Loop.find( DELIMIT );
	if( found != string::npos )
	{
		loop->m_Name = p_Loop.substr( 0, found );
		loop->m_Miles = p_Loop.substr( found+1 );
	}

	return loop;
}

vector<Loop*>::iterator LoopVector::find( const string& p_Loop )
{
	string s = "";
	size_t found = p_Loop.find( DELIMIT );
	if( found != string::npos )
	{
		s = p_Loop.substr( 0, found );
	}

	for( iter it = begin(); it != end(); it++)
	{
		if( (*it)->m_Name == s )
			return it;
	}
	return end();
}

bool LoopVector::contains( const string& p_Loop )
{
	string s = p_Loop;
	size_t found = p_Loop.find( DELIMIT );
	if( found != string::npos )
	{
		s = p_Loop.substr( 0, found );
	}

	for( iter it = begin(); it != end(); it++)
	{
		if( (*it)->m_Name == s )
			return true;
	}

	return false;
}