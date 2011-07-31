#ifndef RUNMENU_H
#define RUNMENU_H
/**
* RunMenu.h
*
* Header for Menu allowing user to enter in a run
*/

#include "MenuButton.h"
#include "Menu.h"

class RunMenu : public Menu  {

	/** FLTK input components*/    
	Input_Choice* Loop;
	InputF* MilesI;
	InputI* TT_H;
	InputI* TT_M;
	InputI* TT_S;
	InputI* P_M;
	InputI* P_S;
	InputM* NotesI;
	Buttonf* Delete;
	Buttonf* Add;
	Buttonf* Close;
	Buttonf* AddLoop;
	Buttonf* Reset;
	Buttonf* Edit; 

public:
	
	RunMenu(  const int& xsize, const int& ysize );
	
	void BuildMenu(  const int& xSize, const int& ySize );
	string grabInfo();
	inline void clearFields();
	string format( string& info, const string* labels );
	string format( string& info);
	void fillInfo_cb_i(const char* info, Widget* w);
	bool validEntry();
	void setCallBack( Buttonf* btn );
	void setSecondaryInfo( const vector<string>& info );
	void updatePanel( const string& info );
	bool NotContainLoop();
	void loadPace( const string& pace );
	void updatePanelSecondary( const string& info ) ;
	void addButton( const int& x, const int& y, const int& w, const int& h, const string& info );	
	
	const static string labels[];

	static void add_cb( Widget* W, void* data );
	static void delete_cb( Widget* W, void* data );
	static void done_cb( Widget* W, void* data );
	static void fillRun_cb( Widget* w, void* data );
	static void loop_cb( Widget* w, void* data );
	static void reset_cb( Widget* w, void* data );
	static void AddLoop_cb( Widget*w, void* data );
	static void input_cb_seconds( Widget*w, void* data );
	static void input_cb_other( Widget* w, void* data );
	static void input_cb_miles( Widget*w, void* data );
	static void loopChoice_cb( Widget* w, void* data );
	static void edit_cb( Widget*w, void* data );
	static void closeRB_cb( Widget* w, void* data );

	void AddLoop_cb_i();
	void loop_cb_i();
	void edit_cb_i();
	void closeRB_cb_i(const char* info, Widget* w);
	void loopChoice_cb_i();
	inline string grabPaceInfo();
	void CalcPace();
	void addLoopVisibilityCheck();
};


class RunButton : public MenuButton {

	Box* box;
	Buttonf* box1;
	Buttonf* box2;
	Buttonf* box3;
	Buttonf* loop;
	Buttonf* pace;
	Buttonf* notes;
	Buttonf* tt;
	Buttonf* miles;
	Buttonf* close;
	
public:
	RunButton( const int& x, const int& y, const int& w, const int& h, const string& info );
	void setText( const string& info );
	string getText();
	void setCallback( void (*fp)(Widget* w, void* data) ,void* data);
	void setCallback2( void (*fp)(Widget* w, void* data) ,void* data);
};

#endif