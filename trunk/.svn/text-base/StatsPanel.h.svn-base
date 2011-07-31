#ifndef STATSPANEL_H
#define STATSPANEL_H

#include "Panel.h"

class StatsPanel : public Panel
{
	/** FLTK widgets */
	Box* header;
	Buttonf* switchType;

	bool monthPanel;
	
public:

	StatsPanel( const int& width, const int& height );
	void buildPanel( const int& width, const int& height );
	void setInfo( const vector<string>& info );
	void updatePanel( const string& info );
	static void switchLook_cb( Widget* w, void* data );
	void switchLook_cb_i();

	/** Un-used */
	void setSecondaryInfo( const vector<string>& info ){}
	void updatePanelSecondary( const string& info ){}

	~StatsPanel(){}
};

#endif

