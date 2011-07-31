/*
 *  RunLogController.cpp
 *  run_log
 *
 *  Created by Murder on 7/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#include "RunLogController.h"

RunLogController::RunLogController()
{
	makeRunLogDir();
	
	m_RunLog = new RunLog();

	Win = new MainWin(m_RunLog->getFirstDayOfMonth(), m_RunLog->getDaysinMode(), m_RunLog->getDaysInPreviousMonth());
	Win->addObserver(this);
	Win->show();
	m_RunLog->Load();
	m_RunLog->print();

#ifndef _WIN32
	//m_RunLog->updateYear(); // year resets to 110 so update
	//m_RunLog->updateDayOfWeek(); //update day of week
	//Trace("Mac stuff updated" );
#endif
	
	updateWinMode(true);
	updateStats();
}

void RunLogController::update( DataPair& dp ) 
{
	cout << "Update Called" << endl;
	switch( dp.first )
	{
		case NEXT:
			Trace( "NEXT Start" );		
			(*m_RunLog)++;
			updateWinMode( true );
			Trace( "NEXT Done");
			break;
			
		case PREVIOUS:
			
			Trace( "Previous Start");
			(*m_RunLog)--;
			updateWinMode(true );
			Trace( "Previous End");
			break;
			
		case DAYM:
			
			Trace( "Day mode" );
			m_RunLog->setModeD();
			updateWinMode();
			Trace( "Day mode End" );
			break;

		case WEEKM:
			
			Trace( "Week mode");
			m_RunLog->setModeW();
			updateWinMode();
			Trace( "Week mode End");
			break;
			
		case MONTHM:
			
			Trace("MONTH MODE start" );
			m_RunLog->setModeM();
			updateWinMode(true);
			Trace( "Month mode end");
			break;

		case SAVE:
			
			m_RunLog->Save();
			break;

		case MAINWIN_CLOSE:
			
			Trace( "Closing mainwin " );
			m_RunLog->Save();
			Win->hide();		
			break;	

		case LOOP_ADD:
			
			Trace( "Loop added " + dp.second );
			m_RunLog->push_back( dp.second );
			Trace( "Loop added End" );
			break;

		case LOOP_DELETE:
			
			Trace( "Loop deleted " + dp.second  );
			m_RunLog->erase( dp.second );
			Trace( "Loop deleted End" );
			break;
			
		case LOOP_OPEN:
			
			Trace( "Open LoopMenu" );
			Win->setPanelInfo( m_RunLog->getLoops() );	
			break;
			
		case LOOP_CLOSE:
			
			Trace("loop close in rlc so show main win");
			m_RunLog->setModeM();
			updateWinMode(); // closing loop goes to month mode
			break;

		case LOOP_STATS_OPEN:

			Trace("LOOP_STATS_OPEN");
			//dp.second will be just the loop
			Win->setPanelInfoSec( m_RunLog->get2ndItemStats(dp.second) );			
			break;

		case LOOP_STATS_SORT_0:

			Trace("LOOP_STATS_SORT_0");
			Win->setPanelInfoSec( m_RunLog->get2ndItemSorted( dp.second, 0 ) );
			break;

		case LOOP_STATS_SORT_1:

			Trace("LOOP_STATS_SORT_1");
			Win->setPanelInfoSec( m_RunLog->get2ndItemSorted( dp.second, 1 ) );
			break;

		case GOTO_OPEN: 
			
			Trace( "goto open");
			Win->updatePanel( m_RunLog->getDate() );
			break;

		case GOTO_MONTH_SELECTED:

			Trace( "GOTO month selected" );
			Win->updatePanelSecondary( IntToStr( m_RunLog->getDaysinMonth(StrToInt( dp.second ))));
			break;

		case GOTO_MONTH:
		{	
			Trace( "Goto month" );
			const vector<string>& v = seperateByTabs( dp.second,3 );
			m_RunLog->setDate
			(
				StrToInt(v[0]),
				StrToInt(v[1]),
				StrToInt(v[2])
			); 
			m_RunLog->setModeM();
			updateWinMode( true );		
			break;
		}
		case GOTO_DAY:
		{
			Trace( "Goto day"  );		
			const vector<string>& v = seperateByTabs( dp.second,3 );
			m_RunLog->setDate
			(
				StrToInt(v[0]),
				StrToInt(v[1]),
				StrToInt(v[2])
			);
			m_RunLog->setModeD();
			updateWinMode( true );
			break;
		}	
		case ADD_RUN:
			
			Trace( "ADDING A RUN " + dp.second, true );
			m_RunLog->add( dp.second );
			updateStats();
			Trace( "Done added run" );
			break;
			
		case DELETE_RUN:

			Trace( "Deleting A RUN " + dp.second, true );
			m_RunLog->remove( dp.second );
			updateStats();
			Trace( "deleting run done" );
			break;

		case LOOP_RUN_MENU:

			Trace( "LOOP_RUN_MENU" );
			Win->updatePanel( m_RunLog->getMilesInLoop( dp.second ) );
			break;

		case RUN_DONE:
			Trace( "done button in runmenu" );  
			m_RunLog->revertMode();
			Win->setDate( m_RunLog->getDateString() );
			this->updateWinMode();
			break;

		case RUN_LOAD_PACE:
			
			Trace( " load pace ");
			Win->updatePanelSecondary( m_RunLog->PaceCalculator( dp.second ) );
			break;
		
		case TABLE_DAY_CLICKED:
		
			Trace( "cell clicked in table " + dp.second );
			
			m_RunLog->setDay
			(	
				StrToInt( dp.second.substr( 0, dp.second.find( "\t")) ),
				StrToInt( dp.second.substr( dp.second.find( "\t") +1 )) 
			); 
			m_RunLog->setModeD();
			this->updateWinMode( true ); 
			break;
			
		case MAINWIN_TODAY:
			
			Trace( "Today clicked" );
			m_RunLog->setToday();
			m_RunLog->setModeD();
			this->updateWinMode(  true );
			break;

		case MINI_TABLE_CELL_CLICKED:
		{
			Trace( "MINI_TABLE_CELL_CLICKED " + dp.second );;
			
			const vector<string>& v = seperateByTabs( dp.second,3 );
			m_RunLog->setDay
			(
				StrToInt(v[0]),
				StrToInt(v[1]),
				StrToInt(v[2])
			);
			m_RunLog->setModeD();
			this->updateWinMode(true);
			break;
		}
		case STATS_CHANGE:

			Trace( "STATS_CHANGE Start");
			Win->updatePanelMini2Sec( "" );
			dp.second == "true" ? updateStats( true ) : updateStats( false );		
			break;

		default:

			Trace( "action does not exist");
	}
}

void RunLogController::updateWinMode( const bool& updateMonth)
{
	Trace( "UpdateWinMode Start", true );
	Win->setDate( m_RunLog->getDateString() ); 	
	this->updateMiniPanels(updateMonth); // update lil table	
	Win->updatePanelMini1Sec( m_RunLog->getDayNumbersInMode()  ); //highlight mode
	if( m_RunLog->isTodayInCurrentMonth() )
	{
		Win->updatePanelMini1T3(  IntToStr( m_RunLog->getTodayDaym() ) );
	}
	switch( m_RunLog->getMode() )
	{
		case 0: 
			Win->setPanel( 0 );  
			Win->setPanelInfo( m_RunLog->getInfo( m_RunLog->getDateDB() ));
			Win->setPanelInfoSec( m_RunLog->getLoopNames() );  
			break;

		case 1:
			Win->setPanel( 2 );
			Win->updatePanel(IntToStr( m_RunLog->getFirstDayOfMonth()) + "\t" + IntToStr(m_RunLog->getDaysinMode()));
			Win->setPanelInfoSec( m_RunLog->getWeekDayStrings()  );
			Win->setPanelInfo( m_RunLog->getInfo( m_RunLog->getDates(),false) );
			break;

		case 2:		
			Win->setPanel( 3 );
			Win->updatePanel(IntToStr( m_RunLog->getFirstDayOfMonth()) + "\t" + IntToStr(m_RunLog->getDaysinMode()));
			Win->setPanelInfo( m_RunLog->getInfo( m_RunLog->getDates(),true) );
			break;
	}
	Trace( "UpdateWinMode Start" );
}

void RunLogController::updateMiniPanels(const bool& updateMonth)
{
	if( updateMonth && m_RunLog->hasMonthChanged() )
	{
		Trace( "updating minipanels" );
		Win->updatePanelMini1
		(	
			IntToStr( m_RunLog->getFirstDayOfMonth()) + "\t" + 
			IntToStr( m_RunLog->getDaysinCurrentMonth()) + "\t" +
			IntToStr( m_RunLog->getDaysInPreviousMonth()) + "\t"
		);
		Win->setMonth( m_RunLog->getMonthString() );
		this->updateStats();
	}
}

void RunLogController::updateStats( const bool& months )
{
	Trace( "updating stats" );
	Win->updatePanelMini2( m_RunLog->getStats(months) );
}
 