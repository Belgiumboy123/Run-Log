/*
*  MainWin.cpp
*  run_log
*
*  Created by Murder on 6/19/10.
*  Copyright 2010 __MyCompanyName__. All rights reserved.
*
*/

#include "MainWin.h"

/*
* Static call back functions followed by their inline versions
*/

void MainWin::next_cb( Widget* w, void * data )
{	
	MainWin* mw = (MainWin*) data;
	mw->next_cb_i();
}

void MainWin::next_cb_i()
{	
	if( m_Mode != LOOPMENU && m_Mode != GOTO && m_Mode != HELP )
	{
		DataPair next( NEXT, "" );
		notifyObservers( next );
	}
}

void MainWin::prev_cb( Widget* w, void* data )
{
	MainWin* mw = (MainWin*) data;
	mw->prev_cb_i();
}

void MainWin::prev_cb_i()
{	
	if( m_Mode != LOOPMENU && m_Mode != GOTO && m_Mode != HELP )
	{
		DataPair prev( PREVIOUS, "");
		notifyObservers(prev);
	}
}

void MainWin::daym_cb( Widget* w, void*data)
{
	MainWin* mw = (MainWin*) data;
	mw->daym_cb_i();
}

void MainWin::daym_cb_i()
{
	if( m_Mode != DAY )
	{
		DataPair daym( DAYM, "");
		notifyObservers(daym);
	}
}

void MainWin::weekm_cb( Widget*w, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->weekm_cb_i();
}

void MainWin::weekm_cb_i()
{
	if( m_Mode != WEEK )
	{
		DataPair weekm( WEEKM, "" );
		notifyObservers(weekm);
	}
}

void MainWin::monthm_cb( Widget* w,  void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->monthm_cb_i();	
}

void MainWin::monthm_cb_i()
{
	if( m_Mode != MONTH )
	{
		DataPair monthm( MONTHM, "" );
		notifyObservers( monthm );
	}
}

void MainWin::new_cb( Widget*, void* data )
{
	MainWin* mw = (MainWin*) data;
	mw->new_cb_i();
}

void MainWin::new_cb_i()
{
	DataPair dp ( NEW, "" );
	notifyObservers(dp);
}

void MainWin::open_cb( Widget* w, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->open_cb_i();
}

void MainWin::open_cb_i()
{
	DataPair dp( OPEN, "");
	notifyObservers(dp);
}

void MainWin::save_cb( Widget* w, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->save_cb_i();
}

void MainWin::save_cb_i()
{
	DataPair dp( SAVE, "");
	notifyObservers(dp);
}

void MainWin::close_cb( Widget* w, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->close_cb_i();
}

void MainWin::close_cb_i()
{
	DataPair dp( MAINWIN_CLOSE, "");
	notifyObservers(dp);
}

void MainWin::goto_cb( Widget* w, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->goto_cb_i();
}

void MainWin::goto_cb_i()
{
	if( m_Mode != GOTO )
	{
		this->setPanel( GOTO );
		this->setDate( "Go To a Day or Month" );
		DataPair dp( GOTO_OPEN, "" );
		notifyObservers( dp );
	}
}

void MainWin::help_cb( Widget* w, void* data )
{
	MainWin* mw = (MainWin*) data;
	mw->help_cb_i();
}

void MainWin::help_cb_i()
{
	if( m_Mode != HELP )
	{
		this->setPanel( HELP );
		this->setDate( "Instructions" );
	}
}

void MainWin::open_lm_cb( Widget* w, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->open_lm_cb_i();
}

void MainWin::open_lm_cb_i()
{
    if( m_Mode != LOOPMENU )
    {	
		setPanel( LOOPMENU );
		this->setDate( "Loop Menu" );
        DataPair dp( LOOP_OPEN, "");
        notifyObservers(dp);
    }	
}

void MainWin::today_cb(Widget*, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->today_cb_i();
}

void MainWin::today_cb_i()
{
	DataPair dp( MAINWIN_TODAY, "");
	notifyObservers(dp);
}

void MainWin::back_cb(Widget*, void* data)
{
	MainWin* mw = (MainWin*) data;
	mw->back_cb_i();
}

void MainWin::back_cb_i()
{
	DataPair dp( MAINWIN_BACK, "");
	notifyObservers(dp);
}

/**
* Windows callback to handle window-specific events
*/
void MainWin::window_cb( Widget*w, void* data){
	
	MainWin* mw;

	switch( Fl::event() )
	{
		case FL_CLOSE:
			
			mw = (MainWin*) data;
			mw->close_cb_i();
			break;

		case FL_SHORTCUT:
			
			if(  (Fl::event_key() == FL_Escape) ) break;
	
		default:
			//cout << Fl::event() << "< fl mainwin event" <<endl;
			break;
	}
}

const int MainWin::height = 700;     
const int MainWin::width = 1280; 

MainWin::MainWin(const int& firstday, const int& totaldays, const int& lastMonthDay) : 
					DWindow( 0,0,width,height, "Run Log"), 
					m_Mode( MONTH ), 
					//previousPanel(0),
					m_Goto(0),
					m_Help(0),
					m_LoopMenu(0)
{
	Trace( "MainWin construction START", true);
	this->callback( window_cb, this ); //-> handle all window events
	
	CurrentDateW = new Box(width*0.175,height*.15,width*.38, height*0.10 );
	CurrentDateW->labelsize( 20 );

	Previous= new Buttonf( width*0.025,height*.15,width*0.07,height*0.075, "@<-");
	Previous->callback( prev_cb, this );
	Previous->clear_visible_focus();
	
	Next = new Buttonf( 0.625*width,height*.15,width*0.07,height*0.075, "@->");
	Next->callback( next_cb, this );
	Next->clear_visible_focus();
	
	DayM = new Buttonf( 0.05*width, 35, width*0.15,height*0.0625   ,"DAY");
	DayM->callback( daym_cb, this );
	DayM->clear_visible_focus();
	WeekM = new Buttonf( 0.20*width,35,width*0.15,height*0.0625, "WEEK");
	WeekM->callback( weekm_cb, this );
	WeekM->clear_visible_focus();
	MonthM = new Buttonf( 0.35*width,35,width*0.15,height*0.0625, "MONTH");
	MonthM->callback( monthm_cb, this );
	MonthM->clear_visible_focus();
	
	Today = new Buttonf( 0.80*width, 35, width*0.1,height*0.0625, "Today");
	Today->callback( today_cb, this );
	Today->clear_visible_focus();
	Close = new Buttonf( 0.9*width, 35, width*0.1,height*0.0625, "Close");
	Close->callback( close_cb, this );
	Close->clear_visible_focus();
	
	Header = new MenuBar( 0,0, width, 30);
	Header->add( "File/New",0, new_cb, this, 0);
	Header->add( "File/Open",0, open_cb,this,0);
	Header->add( "File/Save",0, save_cb,this,0);
	Header->add( "File/Close",0, close_cb,this,0);
	Header->add( "Tools/Goto",0, goto_cb, this,0);
	Header->add( "Tools/Loop Menu", 0, open_lm_cb, this, 0);
	Header->add( "Help",0,help_cb, this, 0 );

	m_RunMenu = new RunMenu( width*.75,height*0.75  );
	m_RunMenu->position( 0, height*0.25 );
	m_RunMenu->hide();
	this->add( m_RunMenu );

	m_Table = new Table( firstday, totaldays, width*0.75,height*0.75);
	this->add( m_Table );
	m_Table->position( 0, height*0.25 );
	currentPanel = m_Table;
	m_Table->show();
	
	CurrentMonthW = new Box(width*0.75, height*0.20 ,width*0.25, height*0.05 );
	CurrentMonthW->labelsize( 15 );
	m_MiniTable = new MiniTable( firstday, totaldays, width*0.25,height*0.375,lastMonthDay );
	m_MiniTable->position( width*0.75, height*0.25 );
	m_MiniTable->show();
	
	m_Stats = new StatsPanel( width*0.25,height*0.375 );
	m_Stats->position( width*0.75, height*0.625 );
	m_Stats->show();

	end();
	Trace( "MainWin construction END");
}

void MainWin::setDate( const string& date )
{
	CurrentDateW->copy_label( date.c_str() );
}

void MainWin::setMonth( const string& month )
{
	CurrentMonthW->copy_label( month.c_str() );		
}

/**
* Functions dealing with displaying and updating the Main Menu
*/

void MainWin::setPanelInfo( const vector<string>& v )
{
    currentPanel->setInfo(v);
}

void MainWin::setPanelInfoSec( const vector<string>& v )
{
    currentPanel->setSecondaryInfo( v );
}

void MainWin::updatePanel( const string& info )
{
    currentPanel->updatePanel( info );
}

void MainWin::updatePanelSecondary( const string& info )
{
	currentPanel->updatePanelSecondary( info );
}

void MainWin::setPanel(const int& menu)
{
    previousPanel = currentPanel;
	currentPanel->hide();
	p_Mode = m_Mode;
	m_Mode = static_cast<MainWin::Mode>(menu);

    switch( menu )
    {
		case DAY:
			currentPanel = m_RunMenu;
			break;

		case LOOPMENU:
			if( m_LoopMenu == 0 )
			{
				m_LoopMenu = new LoopMenu( width*.75,height*0.75 );
				m_LoopMenu->position( 0, height*0.25 );
				m_LoopMenu->addObservers( this->getObservers() );
				this->add( m_LoopMenu );
			}
			currentPanel = m_LoopMenu;
			break;

		case WEEK:
		case MONTH:
			currentPanel = m_Table;
			break;

		case GOTO:
			if( m_Goto == 0 )
			{
				m_Goto = new GotoPanel( width*0.75, height*0.75 );
				m_Goto->addObservers( this->getObservers() );
				m_Goto->position( 0,height*0.25 );
				this->add( m_Goto ) ;
			}
			currentPanel = m_Goto;
			break;

		case HELP:
			if( m_Help == 0)
			{
				cout << "building help" << endl;
				m_Help = new HelpPanel( width*0.75, height*0.75 );
				m_Help->position( 0,height*0.25 );
				this->add( m_Help );
			}
			currentPanel = m_Help;
			break;
	}
	
	previousPanel->UpdateBeforeHide(); 
  
    currentPanel->show();
}

void MainWin::updatePanelMini1( const string& info )
{
	m_MiniTable->updatePanel(info);
}

void MainWin::updatePanelMini1Sec( const vector<string>& info )
{
	m_MiniTable->setInfo(info);
}

void MainWin::updatePanelMini1T3( const string& info )
{
	m_MiniTable->updatePanelSecondary( info );	
}

void MainWin::updatePanelMini2(  const vector<string>& info )
{
	m_Stats->setInfo(info);
}

void MainWin::updatePanelMini2Sec( const string&  info )
{
	m_Stats->updatePanel( info );
}


