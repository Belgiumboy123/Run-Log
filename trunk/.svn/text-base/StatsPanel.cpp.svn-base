#include "StatsPanel.h"

StatsPanel::StatsPanel( const int& width, const int& height ) : Panel( width,height ), monthPanel( false )
{
	buildPanel( width, height );
	end();
}

void StatsPanel::buildPanel( const int& width, const int& height )
{
	begin();
	
	Box* b2 = new Box(0,0,width,height);
	b2->box( FL_BORDER_BOX );
	header = new Box( 0,5, width/2, height*0.2, "");
	header->align( FL_ALIGN_INSIDE | FL_ALIGN_CENTER );
	header->labelsize( 13 );
	switchType = new Buttonf( width/2, 5, width/2, height*0.2, "" );
	switchType->labelsize(13);
	switchType->align( FL_ALIGN_INSIDE | FL_ALIGN_CENTER );
	switchType->callback( switchLook_cb, this );
	switchType->clear_visible_focus();
	
	if( !monthPanel )
	{
		switchType->copy_label( "View Monthly Statistics" );
		int rowHeight = 0.8*height / 6,
			rowStart = 0.2*height;
		for( int i = 1; i<7; i++)
		{
			Box* b = new Box( 0, rowStart+rowHeight*(i-1), width, rowHeight);
			b->align( FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
		}
	}
	else
	{
		switchType->copy_label( "View Weekly Statistics" );	
		int rowHeight = 0.8*height / 6,
			rowStart = 0.2*height;
		for( int i = 0; i<6; i++)
		{
			Box* b = new Box( 0, rowStart+rowHeight*(i), width/2, rowHeight);
			b->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
		}
		for( int j = 0; j<6; j++)
		{
			Box* b = new Box( width/2, rowStart+rowHeight*(j), width/2, rowHeight);
			b->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
		} 
	}
	end();
}

void StatsPanel::setInfo( const vector<string>& info )
{
	if( info.size() != 13 && monthPanel )
	{
		monthPanel = false;
		updatePanel( "" );
	}

	header->copy_label( info[0].c_str() );
	for( int i = 1; i<info.size(); i++)
	{
		child(i+2)->copy_label( info[i].c_str() );
	}
	if( info.size() == 6 ) child( 8 )->copy_label( "" );
}

void StatsPanel::updatePanel( const string& info )
{
	int xpos = x(), ypos = y();
	this->clear();
	position(0,0);
	
	buildPanel( w(), h() );
	
	position( xpos, ypos );
	this->redraw();
}

void StatsPanel::switchLook_cb( Widget* w, void* data )
{
	StatsPanel* sp = (StatsPanel*) data;
	sp->switchLook_cb_i();
}

void StatsPanel::switchLook_cb_i()
{
	monthPanel = !monthPanel;
	
	DataPair dp( STATS_CHANGE,(monthPanel ? "true" : "false") );
	notifyObservers( dp );
}
