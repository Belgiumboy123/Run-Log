#ifndef MENU_H
#define MENU_H

#include "Panel.h"

/**
* Base class for all main menu modes.
* Acts as an interface with necassary and optional functions to override( pure virtual vs virtual ).
*/
class Menu : public Panel 
{
	
protected:
	
	Scroll*	scrollPane;
	Pack*	pack;

	int		xSizeButton, 
			ySizeButton,
			buttons;

	Widget* lastClicked;
	string	currentlyLoaded;

public:
	
	virtual void	BuildMenu( const int& xSize, const int& ySize ) = 0; 
	virtual string	grabInfo() = 0;
	virtual void	clearFields() = 0;
	virtual string	format( string& info) =0;
	virtual void	fillInfo_cb_i(const char* info, Widget* w) = 0;
	virtual bool	validEntry() = 0;
	virtual void	setCallBack( Buttonf* btn ) = 0;
	virtual void	addButton( const int& x, const int& y, const int& w, const int& h, const string& info ) =0;

	/** empty function calls for derived Menus that don't need these functions */
	virtual void	setSecondaryInfo( const vector<string>& info ){}
	virtual void	updatePanel( const string& info ){}
	virtual void	updatePanelSecondary( const string& info ){}

	/** Menu functions */
	Menu( const int& xsize, const int& ysize);
	void			setInfo( const vector<string>& info ); 
	void			addInfo();
	void			addInfo( const string& info );
	inline void		clearInfo();
	void			handleEvent_i( const int& btn, const string& info = "" );
	void			deleteInfo(const bool& clear = true);
	void			resetLastClicked() 
	{ 
		lastClicked = 0;
		currentlyLoaded = "";
	}
	
	virtual ~Menu(){}
};

#endif