#ifndef STRINGMANIP_H
#define STRINGMANIP_H
#pragma warning(disable:4786)
/**
* StringManip.h
*
* Header for global functions dealing with string manipulation
*/

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

static char const* WHITESPACE = " \t\r\n";
static char const* DIGITS = "0123456789";
static char const* TIMEDIGITS = "012345";
static char const* OTHERINPUT = "e-+";

bool isNotWhiteSpace( const char* label );

string BoolToStr( const bool& pBool );

bool StrToBool( const string& s );

string DoubleToStr( double& n );

double StrToDouble( const string& s );

string IntToStr( const int& n);

int StrToInt( const string& s );

string& killLeadingWhiteSpace( string& s );

string& killTrailingWhiteSpace( string& str );

bool containsNumbers( const string& value );

string removeOtherInput( const string& info );

string correctTimeInput( const string& time );

vector<string> seperateByTabs( const string& info, const int& num );

vector<string> seperateByDelimit( const string& info, const string& delimit );

void printv( const vector<string>& v );

string correct2DTimeInput( const string& info );

vector<string>::iterator findInVec( vector<string>& v, const string& info );

int getIndexInArray( const string* _array, const int& len, const string& val );

#endif