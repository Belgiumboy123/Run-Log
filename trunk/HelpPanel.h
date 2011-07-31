#ifndef HELPPANEL_H
#define HELPPANEL_H

#include "Panel.h"

class HelpPanel : public Panel
{	

	Scroll* scrollPane;
	Group* infoGroup;

public:
	
	HelpPanel( const int& width, const int& height );
	void buildPanel( const int& width, const int& height );
	void btn_cb_i(const int& btn);

	/* static call backs */
	static void btn0_cb( Widget* w, void* data );
	static void btn1_cb( Widget* w, void* data );
	static void btn2_cb( Widget* w, void* data );

	/** Un used */
	void setInfo( const vector<string>& info ){}
	void setSecondaryInfo( const vector<string>& info ) {}
	void updatePanel( const string& info ) {}
	void updatePanelSecondary( const string& info ) {}

};

#endif