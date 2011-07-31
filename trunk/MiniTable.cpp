#include "MiniTable.h"

const string MiniTable::days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

MiniTable::MiniTable( const int& firstDay, const int& totalDays, const int& width, const int& height, const int& lastMonthDay )
: Panel( width,height)
{
	highLightColor = FL_RED;
    normalColor = FL_GRAY;
	highLightColorIN = fl_rgb_color(207, 144, 144);
	highLightToday = FL_YELLOW;
	BuildMenu(firstDay, totalDays, width, height, lastMonthDay);
	this->end();
}

void MiniTable::BuildMenu( const int& firstDay, const int& totalDays, const int& width, const int& height, const int& lastMonthDay )
{
	this->begin();
	int cellWidth = width/7 + (width%7)/7;
	int header_w = height*0.1;
	
	for( int i = 0; i<7; i++ )
	{
		Box* day = new Box( cellWidth*i,0,cellWidth, header_w , days[i].c_str() );
		day->box( FL_DOWN_BOX );
	}
	
	int cellHeight = height*0.15;  // 0.15 =  ( (1-(0.1)) / 6 )
	int row1 = header_w;
	for( int b =0; b<firstDay;b++)
	{
		int x2 = b*cellWidth;
		MenuButton* tb = new MiniTableCell( x2,row1,cellWidth, cellHeight, IntToStr(lastMonthDay-firstDay+b+1), true);
		tb->setCallback( cell_cb, this );
	}//*/
	
	int x,y,k=0;
	for( ; k<totalDays; k++)
	{
		x = ((firstDay+k)%7)*cellWidth;
		y = ((firstDay+k)/7)*cellHeight + header_w;
		
		MenuButton* tb = new MiniTableCell( x,y,cellWidth, cellHeight, IntToStr(k+1));
		tb->setCallback( cell_cb, this );
	}
	
	//from last cell to end of row
	int lstart = (firstDay+totalDays) %7;
	int a = 1;
	if( lstart != 0 )
	{
		for (int z = lstart; z<7; z++,a++)
		{
			int x3 = z*cellWidth;
			MenuButton* tb = new MiniTableCell( x3,y,cellWidth, cellHeight, IntToStr(a), true);
			tb->setCallback( cell_cb, this );
		}
	}//*/
	end();
}

/**
 * Highlight the given cell
 */
void MiniTable::setInfo( const vector<string>& info )
{
	//save pointer to first child thats highlighted
	//for 7 from that child highlight back to normal instead of all children
	for( int i = 7;i<this->children(); i++)
	{
		MiniTableCell* tb = (MiniTableCell*) this->child( i );
		tb->highLight( normalColor );
    }//*/
	
	if (info.size()  == 1 )
	{
		Widget* first = getFirstActive();
		int cell = this->find( first ) + StrToInt( info[0] )-1;
		convertToMTC( cell )->highLight( highLightColor );
	}
	else if( info.size() == 7 )
	{
		for( int i = 7; i<this->children(); i+=7 ) //for each monday
		{
			if
			( 
				convertToMTC( i )->getText() == info[0] &&
				convertToMTC( i+6)->getText() == info[6]
			) 
			{
				for( int j = i; j<(i+7);j++)
				{
					this->colorMTC( this->convertToMTC(j) );
				}
				break;
			}
		}
	}
}

Widget* MiniTable::getFirstActive()
{
	for( int i = 7; i<this->children(); i++ )
	{
		if( ! convertToMTC( i )->isInactive() )
		{
			return this->child( i );
		}
	}
	return 0;
}

MiniTableCell* MiniTable::convertToMTC( const int& num )
{
	return (MiniTableCell*) this->child( num );
}

void MiniTable::colorMTC( MiniTableCell* mtc )
{	
	mtc->isInactive() ? mtc->highLight(highLightColorIN) : mtc->highLight(highLightColor);
}

/** Updates table with the new setup / new starting position and new total # of cells */
void MiniTable::updatePanel( const string& info )
{
	int xpos = x(), ypos = y();
	this->clear();
	position(0,0);
	vector<string> v2 = seperateByTabs( info, 3 );
	int firstDay = StrToInt(v2[0]);  
	int totalDays = StrToInt(v2[1]);
	int lastmonthDay = StrToInt(v2[2]);
	BuildMenu( firstDay, totalDays, w(), h(), lastmonthDay );
	position(xpos,ypos);
	this->redraw();
}

void MiniTable::cell_cb( Widget* w, void* data )
{
	MiniTable* table = (MiniTable*) data;
    MiniTableCell* mb = (MiniTableCell*) w->parent();
	string d = mb->getText();
	int day = StrToInt( d );
    int x = mb->x() - mb->parent()->x();
    int pX = mb->parent()->w();
    int wday = (x / (pX/7));  //->col
	string mon = "0";
	if( mb->isInactive() )
	{
		if( day > 7 )
			mon = "-1";
		else 
			mon = "1";
	}
	table->cell_cb_i( d + "\t" + IntToStr(wday) + "\t" + mon + "\t" );
}

void MiniTable::cell_cb_i(const string& day)
{
	DataPair dp( MINI_TABLE_CELL_CLICKED, day );
	notifyObservers( dp );
}

void MiniTable::updatePanelSecondary( const string& info )
{
	int cell = this->find( getFirstActive() ) + StrToInt( info )-1;
	convertToMTC( cell )->highLight( highLightToday );
}

/**
 * Mini Table Cell
 */
MiniTableCell::MiniTableCell( const int& x, const int& y, const int& w, const int& h, const string& info, const bool& inactive )
: MenuButton( x,y,w,h)
{
	day = new Buttonf( x,y,w,h );
    day->clear_visible_focus();
    day->copy_label( info.c_str() );        
    day->align( FL_ALIGN_INSIDE | FL_ALIGN_CENTER );
    day->labelsize( 15 );
	if( inactive )
	{
		day->box( FL_FLAT_BOX ); 
	}
	end();
}

void MiniTableCell::setText( const string& info ){}

/**
 * Return the day of month 
 */
string MiniTableCell::getText()
{
	return (string) day->label();
}

void MiniTableCell::setCallback( void (*fp)(Widget* w, void* data) ,void* data)
{
	day->callback( fp, data );
}

void MiniTableCell::highLight( Fl_Color p_Color )
{
	if( day->color() != p_Color )
		day->color( p_Color );
}

bool MiniTableCell::isInactive()
{
	return day->box() == FL_FLAT_BOX;
}

