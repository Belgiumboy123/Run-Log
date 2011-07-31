#pragma warning(disable:4786)
#pragma warning(disable:4503)
#include "RunLog.h"

const char* RunLog::loopsFile = "Loops.txt";
const char* RunLog::logFile = "RunLog.txt";
const char* RunLog::logFile_Stats = "RunLog_Stats.txt";

RunLog::RunLog()
{
	m_Loops = new LoopVector();
	m_Log = new Log();
}

void RunLog::New()
{
	if( m_Loops != 0 ) delete m_Loops;
	if( m_Log != 0 ) delete m_Log;
	
	m_Loops = new LoopVector();
	m_Log = new Log();
}

void RunLog::Load()
{
	const string& data1 = ReadFromFile( loopsFile );
	const string& data2 = ReadFromFile( logFile );
	const string& data3 = ReadFromFile( logFile_Stats );
	m_Loops->buildVector( data1 );
	m_Log->buildLog( data2 );
	m_Log->buildLogStats( data3 );
}

void RunLog::Save()
{
	WriteToFile( loopsFile, m_Loops->GetStringForFile() );
	WriteToFile( logFile, m_Log->getStringForFile() );
	WriteToFile( logFile_Stats, m_Log->getStringStatsForFile() );
	m_Log->write2ndItemStatsToFile();
	Trace( "saving files" );
}

bool RunLog::push_back( string& info )
{
	return m_Loops->push_back( info );
}

void RunLog::erase( string& info )
{
	m_Loops->erase( info );
}

vector<string> RunLog::getLoops()
{
	return m_Loops->getLoops();
}

vector<string> RunLog::getLoopNames()
{
	return m_Loops->getLoopNames();
}

string RunLog::getMilesInLoop( const string& loopName )
{
	return m_Loops->getMilesInLoop(loopName);
}

////////////////////
// m_Log functins //
////////////////////

void RunLog::add(  string& info )
{
	m_Log->add( getDateDB() , info );
	m_Log->addStats( getCurrentWeekString(), getMonthString(), info );
	if( m_Loops->contains( m_Log->getSecondItem( info ) ) )
		m_Log->add2ndItemStats( getDateDB(), info );
}

void RunLog::remove( string& info )
{
	m_Log->remove( getDateDB(), info );
	m_Log->removeStats( getCurrentWeekString(),getMonthString(), info );
	if( m_Loops->contains( m_Log->getSecondItem( info ) ) )
		m_Log->remove2ndItemStats( getDateDB(), info );
}

vector<string> RunLog::getInfo( const string& date )
{
	return m_Log->getInfo( date );
}

vector< string > RunLog::getInfo( const vector<string>& dates, const bool& mainInfo )
{
	return m_Log->getInfo( dates,mainInfo );
}

vector<string> RunLog::getStats(const bool& months)
{
	if( months )
	{
		vector<string> v(13);
		v[0] = "Yearly Totals for\n" + getYearString();
		m_Log->getStatInfo( &v[1], getMonthStrings() );
		return v;
	}
	else
	{
		const vector<string>& weeks = getWeekStrings();
		vector<string> v(weeks.size() + 1);
		v[0] =  "Weekly Totals for\n" + this->getMonthString();
		m_Log->getStatInfo( &v[1], weeks );
		return v;
	}
}

vector<string> RunLog::get2ndItemStats( const string& item )
{
	return m_Log->get2ndItemStatsInfo( item );
}

vector<string> RunLog::get2ndItemSorted( const string& item, const int& sortBy )
{
	vector<string> v = m_Log->get2ndItemStatsInfo( item );
	
	switch( sortBy )
	{
	case 0:
		std::sort( v.begin(), v.end(), _dateSorter);
		break;

	case 1:
		std::sort( v.begin(), v.end(), _timeSorter);
		break;
	}

	return v;
}

/**
* Return given hours, minutes, seconds as total seconds
*/
int RunLog::convertToSeconds( const double& p_hours, const double& p_min, const double& p_sec )
{
	return p_hours*3600 + p_min*60 + p_sec;
}

/**
*Place the minutes and seconds of given total seconds into given array
*/
void RunLog::convertToMinSec( double* array, const double& p_seconds )
{
	array[0] = ((int)p_seconds / 60);
	array[1] = ((int)p_seconds % 60);
}

/**
 *@param info - "miles \t p_min \t p_sec \t tt_hour \t tt_min \t tt_sec"
 *    one of three sections will be all " ";
 *@return  the missing part of the equation
 */
string RunLog::PaceCalculator( string& p_Info )
{
	double numbers[6];
	int calcCase;
	string retval = "";
	for( int i = 0; i<6; i++)
	{
		size_t found = p_Info.find( "\t" );
		if( found != string::npos )
		{
			string num = p_Info.substr( 0, found );
			if( num == " " )
				calcCase = i;
			else
			{
				numbers[i] = atof( num.c_str() );
			}
			p_Info = p_Info.substr( found +1 );
		}
		else
		{
			return "";
		} 
	}
	
	double pace,tt,temp, zero = 0.0;
	switch( calcCase )
	{
		case 0:
			//convert pace and tt to seconds		
			pace = convertToSeconds( zero, numbers[1], numbers[2] );
			tt = convertToSeconds( numbers[3], numbers[4], numbers[5] );
			temp = tt / pace;//divide
			retval = DoubleToStr( temp );
			break;
			
		case 1:
		case 2:
		
			//convert tt to seconds 
			tt = convertToSeconds( numbers[3], numbers[4], numbers[5] );
			temp = tt / numbers[0];
			
			//divide by miles
			convertToMinSec( &numbers[1], temp );
			//convert to min and seconds
			retval = DoubleToStr( numbers[2] );
			if( retval.size() == 1 ) retval = "0" + retval;
			retval = DoubleToStr( numbers[1] ) + " " +  retval;
			break;
		case 4:
		case 3:
		case 5:
			
			double tempM;
			//multiply miles by pace min adn sec
			temp = numbers[0] * numbers[1];
			if( temp > 59 )
			{
				numbers[3] =  (int)temp / 60;
				tempM =  (int)temp % 60;
			}
			
			temp = numbers[0] * numbers[2];
			if( temp > 60 )
			{
				tempM += (int)temp / 60;
				
				
				if (tempM > 59){
					numbers[3]++;
				tempM -= 60;}
				numbers[5] = (int)temp %60;
			}
			
			retval = DoubleToStr( numbers[3] ) + " " 
			+ DoubleToStr( numbers[4] )+ " " + DoubleToStr( numbers[5] );
			break;
	}
	return retval;
}