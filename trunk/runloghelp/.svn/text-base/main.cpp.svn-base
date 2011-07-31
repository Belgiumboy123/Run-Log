#include "../Log.h"
#include "../Loop.h"

#include <iostream>

int main (int argc, char * const argv[]) {
	
	Log log;
	LoopVector m_Loops;
	const string& data2 = ReadFromFile( "RunLog.txt" );
	const string& data1 = ReadFromFile( "Loops.txt" );
	m_Loops.buildVector( data1 );
	log.buildLog( data2 );
	
	//
	multimap<string,string,stringCompare> m = log.getMap();
	multimap<string,string,stringCompare>::iterator it = m.begin();
	for( ; it!= m.end(); it++)
	{
		if( m_Loops.contains( log.getSecondItem( it->second ) ) )
			log.add2ndItemStats( it->first, it->second ); 
	}
	log.write2ndItemStatsToFile();
}
