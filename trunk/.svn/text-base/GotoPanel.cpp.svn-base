#include "GotoPanel.h"

const string GotoPanel::months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

GotoPanel::GotoPanel( const int& width, const int& height ) : Panel( width, height )
{
	buildPanel( width, height );
	end();
}

void GotoPanel::buildPanel( const int& width, const int& height )
{
	Box* monthL = new Box( 5,height*0.1, width*0.2,height*0.15 , "Month:");
	monthL->labelsize( 17 );
	MonthC = new Choice( 5+width*0.2, height*0.1, width*0.2,height*0.15);
	MonthC->when( FL_WHEN_CHANGED );
	MonthC->clear_visible_focus();
	for( int i = 0; i<12; i++)
	{
		MonthC->add( months[i].c_str(),0,monthC_cb,this,0);
	}

	Box* dayL = new Box( 5, height*0.35, width*0.2, height*0.15, "Day:"	);
	dayL->labelsize( 17 );
	DayC = new Choice( 	5+width*0.2	, height*0.35, width*0.2,height*0.15 );
	DayC->clear_visible_focus();
	
	Box* YearL = new Box( 5, height*0.6, width*0.2, height*0.15, "Year:"	);
	YearL->labelsize( 17 );
	YearC = new Choice( 5+width*0.2	, height*0.6, width*0.2,height*0.15 );
	YearC->clear_visible_focus();
	for( int j = 1970; j<2020; j++)
	{
		YearC->add( IntToStr(j).c_str(), 0,0,0,0);
	}

	Dayb = new Buttonf( width* 0.7, height* 0.25, width*0.2, height*0.1, "Goto Day" );
	Dayb->callback( goto_day_cb, this );
	Dayb->clear_visible_focus();
	Monthb = new Buttonf( width* 0.7, height* 0.5, width*0.2, height*0.1, "Goto Month" );
	Monthb->callback( goto_month_cb, this );
	Monthb->clear_visible_focus();
}

/** Set current day info */
void GotoPanel::updatePanel( const string& info )
{
	const vector<string>& v = seperateByTabs( info, 3 );
	MonthC->value( StrToInt( v[0] ) );
	this->monthC_cb_i();
	DayC->value( StrToInt( v[1] )-1 );
	YearC->value( StrToInt(v[2] )-1970 );
}

/** Info is largest day allowed for month*/
void GotoPanel::updatePanelSecondary( const string& info ) 
{
	int val = DayC->value();
	const int& totaldays = StrToInt( info );
	DayC->clear();
	for( int k = 1; k<totaldays+1; k++)
	{
		DayC->add( IntToStr(k).c_str(), 0,0,0,0);
	}
		
	if( val >= totaldays )	val = totaldays-1;

	DayC->value( val );
	DayC->redraw();
}

void GotoPanel::goto_month_cb( Widget* w, void* data )
{
	GotoPanel* gp = (GotoPanel*) data;
	gp->goto_cb_i(GOTO_MONTH);
}

void GotoPanel::goto_day_cb( Widget* w, void* data )
{
	GotoPanel* gp = (GotoPanel*) data;
	gp->goto_cb_i(GOTO_DAY);
}

void GotoPanel::goto_cb_i(const int& but)
{
	cout << "day " << DayC->value() << "+1" << endl;
	cout << "year " << YearC->value() << "+1970" << endl;
	DataPair dp( but, IntToStr(MonthC->value()) + "\t" +  IntToStr(DayC->value()+1) +"\t" + IntToStr( YearC->value()+1970)+"\t" );
	notifyObservers( dp );
}

/** Callback for month selected */
void GotoPanel::monthC_cb( Widget* w, void* data )
{
	GotoPanel* gp = (GotoPanel*) data;
	gp->monthC_cb_i();	
}

void GotoPanel::monthC_cb_i()
{
	DataPair dp( GOTO_MONTH_SELECTED ,IntToStr( MonthC->value()));
	notifyObservers( dp );
}
