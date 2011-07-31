/*
 *  Calendar.cpp
 *  run_log
 *
 *  Created by Murder on 6/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#pragma warning(disable:4786)
#include "Calendar.h"

const int		Date::days_months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const string	Date::Days[] = { "Monday", "Tuesday", "Wednesday" , "Thursday", "Friday", "Saturday" , "Sunday" };
const string	Date::Months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const string	Date::Days_s[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"  };
const string	Date::Months_s[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
const int	 	Date::wday_months[] = {0,3,3,6,1,4,6,2,5,0,3,5};

Date::Date(): c_mode( MONTH ),current_day(0)
{
	setToday();
}

void Date::setToday()
{
	int monOld = -1;
	if( current_day != 0 )
		monOld = current_day->tm_mon;
	time_t rawtime;
    time( &rawtime );
    current_day = localtime( &rawtime);
    current_day->tm_year += 1900;

	// monday is first day in week
	if( --current_day->tm_wday == -1 ) current_day->tm_wday = 6;
	
	monOld == current_day->tm_mon ? monthChanged = false : monthChanged = true;
}

Date::Date( tm* p_tm ){

	current_day = p_tm;
}

/**
 * Set the day based upon given day of the month and day of the week.
 *
 * currently ignores leap year
 */
void Date::setDay(const int& mday, const int& wday, const int& mon)
{
	current_day->tm_wday = wday;
	monthChanged = false;
	
	if( mday > days_months[ current_day->tm_mon ] )
	{
		current_day->tm_mday = mday - days_months[ current_day->tm_mon ];
		current_day->tm_mon++;	
		goto changeMonth;
	}
	else
	{
		current_day->tm_mday = mday;
	}
	
	if( mon != 0 )
	{	
		current_day->tm_mon += mon; 
changeMonth:	
		if( current_day->tm_mon == 12 )
		{
			current_day->tm_year++;
			current_day->tm_mon = 0;
		}
		monthChanged = true;
	}
}

int Date::getWdayOfMonth( const int& month, const int& year ) const
{
	if( (month == 0 || month == 1) && isLeap( year ) )
	{
		return month == 0 ? 6 : 2;
	}
	else
	{
		return wday_months[month];
	}
}

void Date::setDate( const int& month, const int& day, const int& year ) 
{	
	int monthOld = current_day->tm_mday;

	current_day->tm_year = year;			
	current_day->tm_mon = month; 
	current_day->tm_mday = day;

	int c = 2*( 3- ((year/100)%4));
	int y2d = year%100;
	int y = (y2d)/4;
	
	int totaldays = c + y2d + y + getWdayOfMonth( month, year ) + day;
	int nwday = totaldays%7;
	current_day->tm_wday = nwday;
	
	if( --current_day->tm_wday == -1 ) current_day->tm_wday = 6;
	monthOld == month ? monthChanged = false : monthChanged = true;
}

ostream& operator<<( ostream& os, const Date& date ){
        
        os << "It is " << date.current_day->tm_mon+1  << "/"
                                                        <<((date.current_day->tm_mday))  << "/" 
                                                                        << date.current_day->tm_year << "/" << date.current_day->tm_wday;

        return os;
}

bool operator==( const Date& date1, const Date& date2) {

        return date1.getDay() == date2.getDay() && date1.getMonth() == date2.getMonth() && date1.getYear() == date2.getYear();
}

void Date::setModeW()
{
	p_mode = c_mode;
	c_mode = DAY;
	int mon = current_day->tm_mday;
	while( current_day->tm_wday != 0 )
	{
		operator--();
	}
	if( mon != current_day->tm_mday ) monthChanged = true;
	else monthChanged = false;
	
	c_mode = WEEK;
}

Date& Date::operator++(){                                    

        int& c_day = current_day->tm_mday;
		int mono;
        switch( c_mode ){
        
                case DAY:
                        if( ++current_day->tm_wday == 7) current_day->tm_wday = 0; // update day of week 
                
                        if( ++c_day > days_months[current_day->tm_mon] )
						{          
                                if( c_day == 29 && current_day->tm_mon == 1  &&  isLeap( current_day->tm_year ) )  break;

                                c_day = 1;
                                
                                if( ++(current_day->tm_mon) == 12 )
								{
                                        current_day->tm_mon = 0;
                                        current_day->tm_year++;
                                }
								monthChanged = true;
                        }
						else
							monthChanged = false;

						current_day->tm_mday = c_day; 
                        break;

                case WEEK:                      
						
						mono = current_day->tm_mon;
						setModeD();
						do{
							operator++();
				
						}while( current_day->tm_wday != 0 );
						
						c_mode = WEEK;
						monthChanged = ( mono != current_day->tm_mon ? true : false );
                        break;

                case MONTH:             //go to first day of next month

                        current_day->tm_wday = (current_day->tm_wday + ( days_months[ current_day->tm_mon ] - current_day->tm_mday +1)%7)%7;
                        
                        ///add another day if leap feb
                        if( current_day->tm_mon == 1 && isLeap( current_day->tm_year ) )
                        {
                                if( ++current_day->tm_wday == 7 ) current_day->tm_wday = 0;
                        }
                                
                        if( ++current_day->tm_mon == 12)   // new year
                        {       
                                current_day->tm_mon = 0;
                                current_day->tm_year++; 
                        }
                        
                        current_day->tm_mday = 1;
                        monthChanged = true;
                        break;
        }     
        return *this;   
}

Date& Date::operator--(){ 

        int& c_day = current_day->tm_mday, mono;
        switch( c_mode ){
        
                case DAY:

                        if( --current_day->tm_wday == -1) current_day->tm_wday = 6; // update day of week  
                
                        if( --c_day == 0 ){ // switch months

                                if( --(current_day->tm_mon) < 0 ){  // jan 1 to dec 31

                                        current_day->tm_year--;
                                        current_day->tm_mon = 11;                       
                                }

                                if( current_day->tm_mon == 1  &&  isLeap( current_day->tm_year ) ){

                                        c_day = 29;
                                        break;
                                }
                                
                                c_day = days_months[ current_day->tm_mon ];
								monthChanged = true;
                        }
						else
							monthChanged = false;
                        
                        current_day->tm_mday = c_day; 
                        break;

                case WEEK:
                        
						mono = current_day->tm_mon;
						setModeD();
						do{
							operator--();
				
						}while( current_day->tm_wday != 0 );
						
						c_mode = WEEK;
                        monthChanged = ( mono != current_day->tm_mon ? true : false );
                        break;

                case MONTH:
                        
                        if( --current_day->tm_mon == -1 ) 
                        {       
                                current_day->tm_year--;
                                current_day->tm_mon = 11;
                        }       
                        

						 //weekday
                        //int totaldays to subtract    % 7  
                        int td = (current_day->tm_mday-1 + days_months[ current_day->tm_mon ])%7;
                        //current - answer^   
						int neww = current_day->tm_wday - td;
						if( current_day->tm_mon == 1 &&  isLeap( current_day->tm_year ) ) neww--;

						if( neww < 0 ) neww += 7;
						
						current_day->tm_wday = neww;
                        //equate for when that is negative
					
                        current_day->tm_mday = 1;
						monthChanged = true;
                        break;              
        }               
        return *this;
}

string Date::getDateString() const
{ 
        switch( c_mode ){
                case DAY:
                
                        return Days[ current_day->tm_wday] + " " +
                                                Months[ current_day->tm_mon ] + " " + 
                                                        IntToStr(current_day->tm_mday) + " " + 
                                                                IntToStr( current_day->tm_year);
                case WEEK:
                        
                        return "Week of " + Months[ current_day->tm_mon ] + " " + 
                                                                        IntToStr(current_day->tm_mday) + " " + 
                                                                                IntToStr( current_day->tm_year);
                
                case MONTH:
                
                        return Months[ current_day->tm_mon ] + " " +
                                                IntToStr( current_day->tm_year);
        }
        
        return "fail";
}

string Date::getDate() const
{
        return
                        IntToStr(current_day->tm_mon)  + "\t" + 
                                IntToStr(current_day->tm_mday) + "\t" + 
                                        IntToStr( current_day->tm_year) + "\t";
}

string Date::getDateDB()const 
{
	  return
                        Months[ current_day->tm_mon ] + " " + 
                                IntToStr(current_day->tm_mday) + " " + 
                                        IntToStr( current_day->tm_year);
}

vector<string> Date::getDates()
{  //used as the keys to get info from database
                                 
        vector<string> v;
        tm old = *current_day;
		bool old2 = monthChanged;
		int i = 0;
			
        switch( c_mode ){
                
                case DAY:
                
                        v.push_back( getDateDB() );                
                        break;

                case WEEK:
						setModeD();
						
						v.push_back( getDateDB() );
						do{
							operator++();
							v.push_back( getDateDB() ); 
							i++;
						}while( i < 6 );

						c_mode = WEEK;

						break;
                case MONTH:
						
						string d1 = Months[ current_day->tm_mon ] + " ";
						string d2 = " " + IntToStr( current_day->tm_year );
						
						for(  i = 1; i<=days_months[ current_day->tm_mon ]; i++)
						{
							v.push_back( d1 + IntToStr( i ) + d2 );
						}
						if( current_day->tm_mon == 1 && isLeap( current_day->tm_year ) )
								v.push_back( "February 29" + d2 );
                       
        }
        
        *current_day = old;
		monthChanged = old2;
        return v;
}

/**
 * Get weekday of first day of the month
 */
int Date::getFirstDayOfMonth()
{
	int neww = (current_day->tm_wday - (current_day->tm_mday%7))+1;
	return ( neww < 0 ? neww+=7 : neww );
}

int Date::getDaysinMode()
{
	switch( c_mode )
	{
	case WEEK:

		return 7;
		break;

	case MONTH:
		
		return days_months[current_day->tm_mon]; 
		break;

	default:

		return 1;
	}
}

/** Return "Mon Aug 1" */
string Date::toShortString()
{
	return Days_s[ current_day->tm_wday ] + " " 
				+ Months_s[ current_day->tm_mon ] + " " 
						+ IntToStr( current_day->tm_mday ); 
}

vector<string> Date::getWeekDayStrings()
{
	vector<string> v;

	tm old = *current_day;
	bool old2 = monthChanged;
	int i = 0;

	setModeD();
						
	v.push_back( toShortString() );
	do{
		operator++();
		v.push_back( toShortString() ); 
		i++;
	}while( i < 6 );

	c_mode = WEEK;
	monthChanged = old2;
	*current_day = old;
	return v;
}

/**
* Get days of the month that are currently representing in the mode
*
* Month returns "" others return days of month - 0 based
*/
vector<string> Date::getDayNumbersInMode()
{
	vector<string> v;
	switch( c_mode )
	{
		case DAY:
			
			v.push_back( IntToStr( current_day->tm_mday ) );
			break;
		case WEEK:
			
			tm old = *current_day;
			bool old2 = monthChanged;
			c_mode = DAY;
			int i = 0;
			v.push_back( IntToStr( current_day->tm_mday ) );
			do{
				operator++();
				v.push_back( IntToStr( current_day->tm_mday ) ); 
				i++;
			}while( i < 6 );	
				
			c_mode = WEEK;
			*current_day = old;
			monthChanged = old2;
			break;
	}
	return v;
}

int Date::getDaysInPreviousMonth()
{
	return current_day->tm_mon == 0 ? days_months[11] : days_months[ current_day->tm_mon-1 ];
}

string Date::getMonthString()
{
	return Months_s[current_day->tm_mon] + " " + IntToStr(current_day->tm_year);
}

bool Date::isTodayInCurrentMonth()
{
	tm old = *current_day;
	bool old2 = monthChanged;
	
	setToday();
	int todayMon = current_day->tm_mon;
	int todayYear = current_day->tm_year;

	monthChanged = old2;
	*current_day = old;
	return todayYear == current_day->tm_year && todayMon == current_day->tm_mon;
}

int Date::getTodayDaym()
{
	tm old = *current_day;
	bool old2 = monthChanged;
	
	setToday();

	int todayMday = current_day->tm_mday;
	monthChanged = old2;
	*current_day = old;
	return todayMday;
}

string Date::getWeekString()
{
	return "Week of " +	Months_s[ current_day->tm_mon ]
					  + " " + IntToStr(current_day->tm_mday);
}

string Date::getCurrentWeekString()
{
	tm old = *current_day;
	bool old2 = monthChanged;
	mode previous = c_mode;
	string s;
	
	setModeW();
	s = getWeekString();
	
	c_mode = previous;
	monthChanged = old2;
	*current_day = old;
	return s;
}

/**
 * Get strings representing each week in current month
 *
 * Include all weeks neccasary so all days within month are included
 */
vector<string> Date::getWeekStrings()
{
	vector<string> v;
	tm old = *current_day;
	bool old2 = monthChanged;
	mode previous = c_mode;
	
	setDay( 1, getFirstDayOfMonth() );
	setModeW();
	v.push_back( getWeekString() );
	
	do
	{
		operator++();
		v.push_back( getWeekString() );
	}	//add 7 days until monday is no longer in same month
	while( current_day->tm_mday+7 <= days_months[ current_day->tm_mon ] );
	c_mode = previous;
	monthChanged = old2;
	*current_day = old;
	return v;
}//*/

vector<string> Date::getMonthStrings()
{
	vector<string> v;
	for( int i = 0; i<12; i++)
	{
		v.push_back( Months_s[i] + " " + IntToStr(current_day->tm_year));
	}
	return v;
}

/**
* "november 11 2010" delimit - " ";
*
* Return true is date1 occurs before date2, false otherwise
*/
bool Date::lessThan( const string& date1, const string& date2 )
{
	vector<string> v1 = seperateByDelimit( date1, " ");
	vector<string> v2 = seperateByDelimit( date2, " ");

	int year1 = StrToInt( v1[2] );
	int year2 = StrToInt( v2[2] );

	if( year1 < year2 ) 
		return true;
	else if( year1 > year2 )
		return false;
	else //same year
	{
		int mon1 = getIndexInArray( Months, 12, v1[0] );
		int mon2 = getIndexInArray( Months, 12, v2[0] );
		if( mon1 < mon2 )
			return true;
		else if( mon1 > mon2 )
			return false;
		else // same month
		{
			int day1 = StrToInt( v1[1] );
			int day2 = StrToInt( v2[1] );
			if( day1 < day2 )
				return true;
			else
				return false;
		}
	}
}