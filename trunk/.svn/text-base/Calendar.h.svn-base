/*
 *  Calendar.h
 *  run_log
 *
 *  Created by Murder on 6/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CALENDAR_H
#define CALENDAR_H

#include "FileWriter.h"
#include <ctime>

class Date{

public:
	
	Date();
	Date( tm* p_tm );

	void setDate( const int& month, const int& day, const int& year );
	int getWdayOfMonth( const int& month, const int& year ) const;
	void setToday();
	
	inline void updateYear(){ current_day->tm_year += 1900; }
	inline void updateDayOfWeek() { if( --current_day->tm_wday == -1 ) current_day->tm_wday = 6; }

	friend ostream& operator<<( ostream&  os, const Date& date );
	friend bool operator==( const Date& date1, const Date& date2  );
		
	virtual Date& operator++();		
	virtual Date& operator--();
	virtual Date& operator--(int){ return operator--(); }  //postfix just use prefix
	virtual Date& operator++(int){ return operator++(); }

	inline void setModeM() { p_mode = c_mode; c_mode = MONTH; }
	inline void setModeD() { p_mode = c_mode; c_mode = DAY;   }
	void setModeW();
	inline void revertMode() { mode temp = c_mode; c_mode = p_mode; p_mode = temp; }
	int getMode() const { return c_mode; }

	inline int getYear() const { return current_day->tm_year; }
	inline int getMonth() const { return current_day->tm_mon; }
	inline int getDay() const { return current_day->tm_mday; }
	void setDay(const int& mday, const int& wday, const int& mon = 0);
	inline int getDayOfWeek() const { return current_day->tm_wday; }
	inline int getDaysinCurrentMonth() const { return days_months[current_day->tm_mon]; }
	int getFirstDayOfMonth();
	int getDaysinMode();
	vector<string> getDayNumbersInMode();
	int getDaysInPreviousMonth();
	int getDaysinMonth( const int& month )const { return days_months[ month ]; }

	const static string Days[];
	const static string Days_s[];
	const static string Months_s[];
	const static string Months[];
	const static int days_months[];
	const static int wday_months[];

	string getDateString()const;
	string getDate()const;
	string getDateDB()const;
	vector<string> getDates();	
	string toShortString();
	string getYearString() const { return IntToStr( current_day->tm_year); }
	vector<string> getWeekDayStrings();
	string getMonthString();
	string getCurrentWeekString();
	vector<string> getWeekStrings();
	string getWeekString();
	vector<string> getMonthStrings();

	bool hasMonthChanged() const { return monthChanged; }
	bool isTodayInCurrentMonth();
	int getTodayDaym();
	static bool lessThan( const string& date1, const string& date2 );
	
	enum mode
	{	
		DAY, 
		WEEK, 
		MONTH
	};

	virtual ~Date(){}
	
private:
	
	struct tm* current_day;
	
	mode c_mode, p_mode;

	inline bool isLeap( const int& year )const{

		return  !(year%400) || (!(year%4) && (year%100) );
	}

	bool monthChanged;
};

#endif //CALENDAR_H