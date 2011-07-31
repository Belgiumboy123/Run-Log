/*
 *  Day_Log.h
 *  run_log
 *
 *  Class MainWin
 *  Class LoopMenu
 *	
 */

#ifndef DAY_LOG_H
#define DAY_LOG_H

#include "Table.h"
#include "RunMenu.h"
#include "LoopMenu.h"
#include "MiniTable.h"
#include "StatsPanel.h"
#include "GotoPanel.h"
#include "HelpPanel.h"
#include "FileWriter.h"

/**
* Main window from which all other windows will be spawned
*/
class MainWin : public DWindow, public Observable<DataPair>{

private:
	
	Box* CurrentDateW;
	Box* CurrentMonthW;
	Buttonf* Previous;
	Buttonf* Next;
	Buttonf* DayM;
	Buttonf* WeekM;
	Buttonf* MonthM;
	MenuBar* Header;
	Buttonf* Close;
	Buttonf* Back;
	Buttonf* Today;
	
	Panel* m_LoopMenu;
	Panel* m_RunMenu;
	Panel* currentPanel;
	Panel* previousPanel;
	Panel* m_Table;
	Panel* m_MiniTable;
	Panel* m_Stats;
	Panel* m_Goto;
	Panel* m_Help;
	
	static const int width;
	static const int height;
	
public:

	enum Mode
	{
		DAY,
		LOOPMENU,
		WEEK,
		MONTH,
		GOTO,
		HELP
	} m_Mode,p_Mode;

	MainWin(const int& firstday, const int& totaldays, const int& lastMonthDay );
	
	~MainWin()
	{		
		if( m_LoopMenu != 0 )
		{ 
			delete m_LoopMenu; 
			Trace( "deleting loop menu"); 
		} 
		if( m_RunMenu != 0 )
		{
			delete m_RunMenu;
			Trace( "deleting runmenu" );
		}
		if( m_Table != 0 )
		{
			delete m_Table;
			Trace("deleting table");
		}
		if( m_MiniTable != 0 )
		{
			delete m_MiniTable;
			Trace( "delete miniTable" );
		}
		if( m_Stats != 0 )
		{
			delete m_Stats;
			Trace("deleting stats");
		}
		if( m_Goto != 0 )
		{	
			delete m_Goto;
			Trace( "deleting goto");
		}
		if( m_Help != 0 )
		{
			delete m_Help;
			Trace( "deleting help");
		}
	}
	
	void setDate( const string& date );
	void setMonth( const string& month );
	
	/** Inline functions that handle specific events */ 
	inline void next_cb_i();
	inline void prev_cb_i();
	inline void daym_cb_i();
	inline void weekm_cb_i();
	inline void monthm_cb_i();
	inline void new_cb_i();
	inline void open_cb_i();
	inline void close_cb_i();
	inline void save_cb_i();
	inline void goto_cb_i();
	inline void open_lm_cb_i();
	inline void today_cb_i();
	inline void back_cb_i();
	inline void help_cb_i();
	
	/** static functions that forward to inline */
	static void today_cb(Widget*, void* data);
	static void back_cb(Widget*, void* data);
	static void next_cb( Widget* w, void * data );
	static void prev_cb( Widget* w, void * data );
	static void daym_cb( Widget* w, void * data );
	static void weekm_cb( Widget* w, void * data );
	static void monthm_cb( Widget* w, void * data );
	static void new_cb( Widget* w, void * data );
	static void open_cb( Widget* w, void * data );
	static void save_cb( Widget* w, void * data );
	static void close_cb( Widget* w, void * data );
	static void goto_cb( Widget* w, void * data );
	static void open_lm_cb( Widget*w, void* data );
	static void help_cb( Widget*w, void* data );
	
	/** functions dealing with Panel */
	void setPanelInfo( const vector<string>& v );
	void setPanelInfoSec( const vector<string>& v );
	void updatePanel( const string& info );
	void updatePanelSecondary( const string& info );
	void setPanel(const int& panel);
	
	/** functions dealing with the two miniPanels */
	void updatePanelMini1( const string& info );
	void updatePanelMini1Sec( const vector<string>& info );
	void updatePanelMini1T3( const string& info );
	void updatePanelMini2(  const vector<string>& info );
	void updatePanelMini2Sec( const string&  info );
		
	/**
	* Override of addObserver so that it adds its observers to
	* its child members
	*/
	void addObserver( Observer<DataPair>* observer)
	{
		Observable<DataPair>::addObserver( observer );
		m_RunMenu->addObserver( observer );
		m_Table->addObserver( observer );
		m_MiniTable->addObserver( observer );
		m_Stats->addObserver( observer );
	}
	
	static void window_cb( Widget*w, void*data );
};

#endif