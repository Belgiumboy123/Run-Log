#include "Menu.h"
#pragma warning(disable:4786)

Menu::Menu( const int& xsize, const int& ysize): Panel( xsize, ysize ), buttons(0),lastClicked(0),currentlyLoaded("") {}

void Menu::setInfo( const vector<string>& info )
{
	Trace( "menu setinfo " );
	clearInfo();
    vector<string>::const_iterator it;
    for( it = info.begin(); it != info.end(); it++)
    {
		Trace( "adding " + (*it) );
		addInfo( (*it) );
    }
}

void Menu::addInfo()
{
	addInfo(  grabInfo() );
}

void Menu::addInfo( const string& info )
{
	pack->begin();
		addButton( 0, (ySizeButton*buttons)+y()+0, xSizeButton, ySizeButton, const_cast<string&>(info) );
	pack->end();
	scrollPane->redraw();
	clearFields();
	buttons++;
}

void Menu::clearInfo()
{
    pack->clear();
    scrollPane->redraw();
}

void Menu::handleEvent_i( const int& btn, const string& info )
{
    DataPair dp( btn, info );
    if( info == "" ) dp.second = grabInfo();
    notifyObservers(dp);
}

void Menu::deleteInfo(const bool& clear)
{
    if( lastClicked != 0 )
	{
		pack->remove( lastClicked );
		Fl::delete_widget( lastClicked );
        if( clear ) clearFields();
		lastClicked = 0;
		scrollPane->redraw();
		buttons--;
	}
}