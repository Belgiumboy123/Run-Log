#ifndef GOTOPANEL_H
#define GOTOPANEL_H

#include "Panel.h"

class GotoPanel : public Panel
{

	/** FLTK widgets */
	Choice* MonthC;
	Choice* DayC;
	Choice* YearC;
	Buttonf* Dayb;
	Buttonf* Monthb;
	static const string months[];

public:
	
	GotoPanel( const int& width, const int& height );
	void buildPanel( const int& width, const int& height );

	void updatePanel( const string& info ) ;
	void updatePanelSecondary( const string& info ) ;

	static void goto_month_cb( Widget* w, void* data );
	static void goto_day_cb( Widget* w, void* data );
	static void monthC_cb( Widget* w, void* data );

	void goto_cb_i(const int& but);
	void monthC_cb_i();

	/** Un used */
	void setInfo( const vector<string>& info ){}
	void setSecondaryInfo( const vector<string>& info ) {}
};

#endif