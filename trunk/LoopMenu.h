#ifndef LOOPMENU_H
#define LOOPMENU_H

#include "MenuButton.h"
#include "Menu.h"

/**
* Class for a Loop Menu
*/
class LoopMenu : public Menu{
	
public:
	
	LoopMenu( const int& xsize, const int& ysize);

	/** pure virtual Menu functions */
	void	BuildMenu( const int& xSize, const int& ySize ); 
	void	buildLoopStatsMenu(const string& info);
	string	grabInfo();
	void	clearFields();
	string	format(string& info);
	void	fillInfo_cb_i(const char * info, Widget* w);
	bool	validEntry();
	void	setCallBack( Buttonf* btn );
	void	addButton( const int& x, const int& y, const int& w, const int& h, const string& info );
	void	displayError(const bool& display);
	void	setSecondaryInfo( const vector<string>& info );
	void	UpdateBeforeHide();

	static void add_cb( Widget* W, void* data );
	static void delete_cb( Widget*W, void* data);
	void delete_cb_i();
	static void fillLoop_cb( Widget* w, void* data );
	static void close_lm_cb( Widget* w, void* data );
	static void ViewStats_cb( Widget* w, void* data );
	static void backAllLoops_cb( Widget* w, void* data );
	void ViewStats_cb_i(const string& info);
	void backAllLoops_cb_i();
	static void sort0_cb( Widget*w, void* data );
	static void sort1_cb( Widget*w, void* data );
	void sort0_cb_i();
	void sort1_cb_i();

private:
	
	InputI*		miles;
	Input*		name;
	Buttonf*	Add;
	Buttonf*	Delete;
	Buttonf*	Close;
	Box*		Error;
	Group*		containerMain;

	Group*		containerStat;
	Box*		LoopName;
	Box*		LoopMiles;
	Scroll*		LoopSPane;
	Pack*		LoopsPack;
	
	static const string DELIMIT;
};

/**
* Class that displays Loops insde the scrollPane
*/
class LoopButton : public MenuButton
{
	Buttonf*	LoopL;
	Buttonf*	MilesL;
	Buttonf*	ShowStats;

public:
	LoopButton( const int& x, const int& y, const int& w, const int& h, const string& info );
	void	setText( const string& info );
	string	getText();
	void	setCallback( void (*fp)(Widget* w, void* data) ,void* data);
	void	setCallback2( void (*fp)(Widget* w, void* data) ,void* data);
	
	~LoopButton(){}
};

#endif 