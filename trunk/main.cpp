#pragma warning(disable:4786)
#pragma warning(disable:4503)
#include "RunLogController.h"
#include "Loops.h";

/*
void buildLoopDatabaseFromLoopVector()
{
	const string& data1 = ReadFromFile( "Loops.txt" );
	FILE * pFile;
	pFile = fopen ("RunLog.db","a");
	fclose(pFile);
	Loops::convertToDB( data1, "RunLog.db" );
}
*/
 
 
/** 
 *
 * Run once on versions that have not yet generated 2nditem stats files.
 */
void build2ndItemsFromScratch()
{
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

int main(int argc, char **argv)
{	
#if 1
	//buildLoopDatabaseFromLoopVector();
#endif
	
	resetTrace();
	RunLogController rlc;
	Fl::scheme( "plastic" );
	Fl::visual(FL_DOUBLE|FL_INDEX);
	return Fl::run();
}