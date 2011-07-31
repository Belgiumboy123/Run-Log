#ifndef PANEL_H
#define PANEL_H

#include "FileWriter.h"
#include "FL_Header.h"
#include "Buttons.h"
#include "ObserverT.h"

using namespace FLTK;
using namespace GlobalButtons;

class Panel : public Group, public Observable<DataPair>
{

public:

	Panel( const int& xSize, const int& ySize );
	
	virtual void setInfo( const vector<string>& info ) = 0;
	virtual void setSecondaryInfo( const vector<string>& info ) = 0;
	virtual void updatePanel( const string& info ) = 0;
	virtual void updatePanelSecondary( const string& info ) = 0;
	virtual void UpdateBeforeHide(){}
	
	virtual ~Panel(){}
};


#endif