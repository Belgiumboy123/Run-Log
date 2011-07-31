#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "StringManip.h"
#include "FL_Header.h"

using namespace FLTK;

/**
* Base class for a button, placed in the scrollPane, in a Menu
*/
class MenuButton : public Group {

public:

	MenuButton( const int& x, const int& y, const int& w, const int& h );
	virtual void setText( const string& info ) = 0;
	virtual string getText() = 0;
	virtual void setCallback( void (*fp)(Widget* w, void* data) ,void* data) = 0;
	
	virtual ~MenuButton(){}
};

#endif