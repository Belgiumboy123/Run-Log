/*
 *  RunLogController.h
 *  run_log
 *
 *
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "MainWin.h"  //includes "ObserverT.h", Buttons.h //VIEW
#include "RunLog.h"	  // MODEL 	

class RunLogController : public Observer<DataPair>{

public:

	RunLogController();
	
	~RunLogController()
	{  
		if( m_RunLog != 0 )
		{
			delete m_RunLog; 
			Trace( "RunLog deleted" );
		}
	}
	
	void update( DataPair& dp );	
	
private:

	MainWin* Win;
	RunLog* m_RunLog;
	
	void updateWinMode(const bool& updateMonth = false);
	void updateMiniPanels(const bool& updateMonth);
	void updateStats(const bool& months = false);
};

#endif
