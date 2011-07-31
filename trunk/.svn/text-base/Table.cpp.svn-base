/*
 *  Table.cpp
 *  run_log
*/

#include "Table.h"

const string Table::days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

Table::Table(const int& firstDay, const int& totalDays, const int& width, const int& height) : Panel( width,height )
{
	this->end();
} 

void Table::BuildMenu( const int& firstDay, const int& totalDays, const int& width, const int& height  ) 				
{
	current( this );
	this->begin();
	int col = width/7 + (width%7)/7;
	int header_w = height*0.1;

	for( int i = 0; i<7; i++ )
	{
		Box* day = new Box( col*i,0,col, header_w , days[i].c_str() );
		day->box( FL_DOWN_BOX );
	}
	
	if( totalDays == 7 ) // build week view
	{
		int cellHeight = 0.9*height; // 0.9 = 1 - 0.1
		int cellWidth = col;
		int y = header_w;

		for( int i = 0; i<7; i++ )
		{
			int x = i*cellWidth;
			MenuButton* mb = new TableWeekCell( x,header_w, cellWidth, cellHeight, "" );
			mb->setCallback( cell_cb_week, this );  
		}
	}
	else
	{
		int cellHeight = height*0.15;  // 0.15 =  ( (1-(0.1)) / 6 )
		int cellWidth = col;

#ifndef _WIN32
		//firstDay++;
#endif	
		
		int x,y;
		for( int k =0; k<totalDays; k++)
		{
			x = ((firstDay+k)%7)*cellWidth;
			y = ((firstDay+k)/7)*cellHeight + header_w;

			MenuButton* tb = new TableMonthCell( x,y,cellWidth, cellHeight, IntToStr(k+1));
			tb->setCallback( cell_cb_month, this );
		}
	}
	end();
}

void Table::cell_cb_month( Widget* w, void* data )
{
	Table* table = (Table*) data;
	MenuButton* mb = (MenuButton*) w->parent();
	string d = mb->getText();	 
	int x = mb->x() - mb->parent()->x();
	int pX = mb->parent()->w();
	int wday = (x / (pX/7));	
	table->cell_cb_i( d + "\t" + IntToStr(wday) );
}

void Table::cell_cb_week( Widget* w, void* data )
{
	Table* table = (Table*) data;
	MenuButton* mb = (MenuButton*) w->parent();
	int x = mb->x() - mb->parent()->x();
	int pX = mb->parent()->w();
	int wday = (x / (pX/7));

	string firstday  = (string)table->child( 0 )->label(); //"mon oct 3"
	string day = firstday.substr( firstday.find_last_of( " " )+1 );
	int dayn = StrToInt(day) + wday;
	table->cell_cb_i( IntToStr(dayn) + "\t" + IntToStr(wday) );
}

/**
* Grab date info and notifyObservers with this date.
*/
void Table::cell_cb_i(const string& day)
{
	DataPair dp( TABLE_DAY_CLICKED, day );
	notifyObservers( dp );
}

/** Vector containing info to be placed on each cell, "" if to remain empty ( unchanged ) */
void Table::setInfo( const vector<string>& info )
{
	int j=0;
	for( int i = 7; i<children(); i++,j++)
	{
		Widget* child = this->child( i ); 
		MenuButton* mb = (MenuButton*) child;
		mb->setText( info[j] );
	}
}

/** Vector containing additional info ( days for week table ) to be placed in each cell */
void Table::setSecondaryInfo( const vector<string>& info )
{
	for( int i = 0; i<7; i++)
	{
		Widget* child = this->child( i );
		child->copy_label( info[i].c_str() );
	}
}

/** Updates table with the new setup / new starting position and new total # of cells */
void Table::updatePanel( const string& info )
{
	int xpos = x(), ypos = y();
	this->clear();
	position(0,0);
	int firstDay = StrToInt( info.substr( 0, info.find( "\t" ) ) );
	int totalDays = StrToInt( info.substr(  info.find( "\t" )+1 ) );
	BuildMenu( firstDay, totalDays, w(), h() );
	position(xpos,ypos);
	this->redraw();
}


void Table::updatePanelSecondary( const string& info ){}

/**
* Table Month Cell 
*
* Info will be the day number 
*/
TableMonthCell::TableMonthCell
( 
	const int& x, 
	const int& y, 
	const int& w, 
	const int& h, 
	const string& info
)
: MenuButton( x,y,w,h)
{
	//cout << info << endl; 
	
	box = new Buttonf( x,y,w,h );
	box->clear_visible_focus();
	
	day = new Buttonf( x+5,y+5,w/4, h/3, "");
	day->box( FL_NO_BOX);
	day->clear_visible_focus();
	day->copy_label(info.c_str());
	
	text = new Buttonf( x+5+w/4, y+5+h/3, w*0.75, h*0.64 );
	text->clear_visible_focus();
	text->box( FL_NO_BOX);
	end();
}

/**
 * Set main info in this cell
 *
 */
void TableMonthCell::setText( const string& info )
{
	text->copy_label(info.c_str());
}

/**
* Return the day of month 
*/
string TableMonthCell::getText()
{
	return (string) day->label();
}

void TableMonthCell::setCallback( void (*fp)(Widget* w, void* data) ,void* data)
{
	box->callback( fp, data );
	day->callback( fp, data );
	text->callback( fp, data );
}

/**
* Table Week Cell
*/
TableWeekCell::TableWeekCell( const int& x, const int& y, const int& w, const int& h, const string& info )
: MenuButton( x,y,w,h)
{
	wday = new Buttonf( x,y,w,h,"" );
	wday->clear_visible_focus();
	wday->labelsize(18);
	end();
}

void TableWeekCell::setText( const string& info )
{
	wday->copy_label( info.c_str() );
}

/**
* Function is not used
*/
string TableWeekCell::getText()
{
	return "";
}

void TableWeekCell::setCallback( void (*fp)(Widget* w, void* data) ,void* data)
{
	wday->callback( fp, data );
}