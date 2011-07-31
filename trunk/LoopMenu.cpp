/**
* LoopMenu.cpp
*/

#include "LoopMenu.h"

const string LoopMenu::DELIMIT = "\t\t\t";

void LoopMenu::add_cb( Widget* w, void* data)
{
    LoopMenu* lm = (LoopMenu*) data;
	if( lm->validEntry() )
	{
		lm->handleEvent_i( LOOP_ADD );
		lm->addInfo();
		lm->resetLastClicked();
		lm->displayError(false);
	}
	else
	{
		lm->displayError(true);
	}
}

void LoopMenu::displayError(const bool& display)
{
	display ? Error->show() : Error->hide();
}

void LoopMenu::delete_cb( Widget* w, void* data)
{
	LoopMenu* lm = (LoopMenu*) data;
	lm->delete_cb_i();
}

void LoopMenu::delete_cb_i()
{
    handleEvent_i( LOOP_DELETE, (string) name->value() );
    deleteInfo();
}

void LoopMenu::close_lm_cb( Widget* w, void* data )
{
	LoopMenu* lm = (LoopMenu*) data;
	lm->handleEvent_i( LOOP_CLOSE );
	lm->resetLastClicked();
}

void LoopMenu::fillLoop_cb( Widget *w, void* data )
{
	LoopMenu* lm = (LoopMenu*) data;
	LoopButton* lb = (LoopButton*) w->parent();
	lm->fillInfo_cb_i( lb->getText().c_str(), w->parent() );
}

void LoopMenu::fillInfo_cb_i(const char* info, Widget* w)
{
	string lab = (string) info;
	size_t found = lab.find(DELIMIT);
	if( found != string::npos )
	{
		string s_name = lab.substr( 0, found );
		string s_miles = lab.substr( found +DELIMIT.size() );
		
		name->value( s_name.c_str() );
		miles->value( s_miles.c_str() );
		lastClicked = w;
		Error->hide();
	}
}

void LoopMenu::ViewStats_cb( Widget* w, void* data )
{
	LoopMenu* lm = (LoopMenu*) data;
	LoopButton* lb = (LoopButton*) w->parent();
	
	lm->ViewStats_cb_i( lb->getText() );
}

void LoopMenu::ViewStats_cb_i(const string& info)
{
	buildLoopStatsMenu(info);
	
	DataPair dp( LOOP_STATS_OPEN, info.substr( 0,info.find( DELIMIT)));
	this->notifyObservers( dp );
}

void LoopMenu::backAllLoops_cb( Widget* w, void* data )
{
	LoopMenu* lm = (LoopMenu*) data;
	lm->backAllLoops_cb_i();
}

void LoopMenu::backAllLoops_cb_i()
{
	containerStat->hide();

	containerMain->show();

	DataPair dp( LOOP_OPEN, "");
	notifyObservers(dp);
}

void LoopMenu::sort0_cb( Widget*w, void* data )
{
	LoopMenu* lm = (LoopMenu*) data;
	lm->sort0_cb_i();
}

void LoopMenu::sort0_cb_i()
{
	DataPair dp( LOOP_STATS_SORT_0, (string)LoopName->label() );
	notifyObservers( dp );
}

void LoopMenu::sort1_cb( Widget*w, void* data )
{
	LoopMenu* lm = (LoopMenu*) data;
	lm->sort1_cb_i();
}

void LoopMenu::sort1_cb_i()
{
	DataPair dp( LOOP_STATS_SORT_1, (string)LoopName->label() );
	notifyObservers( dp );
}

LoopMenu::LoopMenu( const int& xsize, const int& ysize ) :	Menu( xsize, ysize )
{
	Menu::xSizeButton = xsize*0.448-20;
	Menu::ySizeButton = ysize*0.1;
	current( this );
    BuildMenu( xsize, ysize);
    end();
}

void LoopMenu::BuildMenu( const int& xsize, const int& ysize )
{
	containerMain = new Group( 0,0,xsize,ysize);	
		scrollPane = new Fl_Scroll( 0,0,xSizeButton,ysize);
		scrollPane->type( Fl_Scroll::VERTICAL );
		scrollPane->align( FL_ALIGN_RIGHT );
		pack = new Pack( 0,0,xSizeButton, ysize );
		scrollPane->end();  
	
		int	xentry = 0.25*xsize,
			yentry = 0.125*ysize,
			ybutton = 0.1875 * ysize;

		name = new Input( 0.625*xsize ,yentry,xentry,yentry ,"Name: ");
		miles = new InputI( 0.625*xsize,0.3125*ysize,xentry,yentry,"Miles: " );

		Add = new Buttonf( 0.73*xsize,0.625*400,xentry,ybutton,"ADD");
		Add->callback( add_cb, this);
		Add->clear_visible_focus();
		Delete = new Buttonf( 0.483*xsize,0.625*400,xentry,ybutton,"Delete");
		Delete->callback( delete_cb, this );
		Delete->clear_visible_focus();
		Close = new Buttonf( 0.483*xsize,0.8125*ysize,xentry*2,ybutton,"Back");
		Close->callback( close_lm_cb, this );
		Close->clear_visible_focus();
		Error = new Box( 0.483*xsize,0.625*400+ybutton,xentry*2,ybutton, "Each Loop must have a unique name" );
		Error->box( FL_NO_BOX );
		Error->align( FL_ALIGN_INSIDE | FL_ALIGN_CENTER );
		Error->labelsize( 16 );
		Error->hide();
	containerMain->end();
	containerStat = 0;
}

void LoopMenu::buildLoopStatsMenu(const string& info)
{
	containerMain->hide();
	string s_name, s_miles;
	size_t found = info.find(DELIMIT);
	if( found != string::npos )
	{
		s_name = info.substr( 0, found );
		s_miles = info.substr( found +DELIMIT.size() ) + " miles";
	}

	if( containerStat == 0 )
	{
		Trace( "ContainerStat is being built" );
		containerStat = new Group( x(), y(), w(), h() );
		int xs = x(), ys = y(), width = w(), height = h();
		containerStat->begin();
			
			LoopName = new Box( xs+5, ys+5, width*0.2, height*0.1  );
			LoopName->box( FL_BORDER_BOX );
			LoopName->labelsize( 20 );
			LoopMiles = new Box( xs+width*0.35, ys+5, width*0.2, height*0.1);
			LoopMiles->box( FL_BORDER_BOX );
			LoopMiles->labelsize( 20 );

			Box* l1 = new Box( xs+5, ys+height*0.15, width*0.2, height*0.05, "Date");
			l1->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT );
			Box* l2 = new Box( xs+5+width*0.2, ys+height*0.15, width*0.2, height*0.05, "Time");
			l2->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT );
			Box* l3 = new Box( xs+width*0.4, ys+height*0.15, width*0.2, height*0.05, "Pace");
			l3->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT );

			LoopSPane = new Scroll( xs+5, ys+height*0.2, width*0.6, height*0.7 );
			LoopSPane->type( Fl_Scroll::VERTICAL );
			LoopSPane->align( FL_ALIGN_RIGHT );
				LoopsPack = new Pack( xs+5, ys+height*0.2, width*0.6, height*0.7 );
				LoopsPack->end();
			LoopSPane->end();
			
			Buttonf* b1 = new Buttonf( xs+width*0.7, ys+height*0.3, width*0.2, height*0.1, "Sort by Date" );
			b1->clear_visible_focus();
			b1->callback( sort0_cb, this );
			Buttonf* b2 = new Buttonf( xs+width*0.7, ys+height*0.5, width*0.2, height*0.1, "Sort by Time" );
			b2->clear_visible_focus();
			b2->callback( sort1_cb, this );

			Buttonf* b = new Buttonf( xs+ width*0.7, ys+5, width*0.2, height*0.1, "Back to All Loops");
			b->clear_visible_focus();
			b->callback( backAllLoops_cb, this );
		containerStat->end();

		this->add( containerStat );
	}
	
	LoopName->copy_label( s_name.c_str() );
	LoopMiles->copy_label( s_miles.c_str() );

	containerStat->show();
}


void LoopMenu::setCallBack( Buttonf* btn )
{
	btn->callback( fillLoop_cb,this );
}

bool LoopMenu::validEntry()
{
	for( int i = 0; i<pack->children(); i++)
	{
		Widget* w = pack->child( i );
		LoopButton* lb = (LoopButton*) w;
		string text = lb->getText();
		string s_name = text.substr( 0, text.find( DELIMIT) );
		if( (string)name->value() == s_name  )
			return false;
    }
	return isNotWhiteSpace( name->value() ) && isNotWhiteSpace( miles->value() );
}

string LoopMenu::grabInfo()
{
	return (string) name->value() + "\t" + (string) miles->value();
}

void LoopMenu::clearFields()
{
	name->value("");
    miles->value("");
	Error->hide();
}

/**
 * No longer needed
 */
string LoopMenu::format( string& info )
{
	size_t found = info.find( "\t" );
	return info.substr( 0, found ) + DELIMIT +  info.substr( found + 1);
}

void LoopMenu::addButton( const int& x, const int& y, const int& w, const int& h, const string& info )
{
	LoopButton* lp = new LoopButton( x,y,w,h, info);
	lp->setCallback( fillLoop_cb, this );
	lp->setCallback2( ViewStats_cb, this );
}

/** Info contains loop specific entries */
void LoopMenu::setSecondaryInfo( const vector<string>& info )
{
	cout << "loading entries for the currently loaded loop" << endl;
	LoopsPack->clear();
	
	int i = 0, width = LoopSPane->w(), height = LoopSPane->h()*0.1;

	vector<string>::const_iterator it;
	for( it = info.begin(); it != info.end(); it++)
	{
		vector<string> v = seperateByTabs( (*it) , 3 );
		
		LoopsPack->begin();
			Group* group = new Group( 0,i*height+y(),width,height);
			group->box( FL_BORDER_BOX );
				Box* b1 = new Box( 0, group->y(), width/3, height );
				b1->copy_label( v[0].c_str() );
				b1->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT );
				Box* b2 = new Box( width/3, group->y(), width/3, height );
				b2->copy_label( v[1].c_str() );
				b2->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT );
				Box* b3 = new Box( width*0.66, group->y(), width/3, height, v[2].c_str() );
				b3->copy_label( v[2].c_str() );
				b3->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT );
			group->end();
		LoopsPack->end();
		i++;
	}
	LoopSPane->redraw();
}

/**
* Hide has been called on this Panel, need to revert back to All Loops screen if neccassary
*/
void LoopMenu::UpdateBeforeHide()
{
	if( !containerMain->visible() )
	{
		containerStat->hide();
		containerMain->show();
	}	
}

////////////////////// LoopButton class //////////////////////////////////////////

LoopButton::LoopButton( const int& x, const int& y, const int& w, const int& h, const string& info ) : MenuButton( x,y,w,h )
{
	Box* frame = new Box( x,y,w,h );
	frame->box( FL_BORDER_BOX );
	LoopL = new Buttonf( x+10, y,w/3-10, h );
	LoopL->box( FL_NO_BOX );
	LoopL->align( FL_ALIGN_LEFT | FL_ALIGN_INSIDE );
	LoopL->clear_visible_focus();
	MilesL = new Buttonf( x+5+(w/3), y, w/3-5, h );
	MilesL->align( FL_ALIGN_LEFT | FL_ALIGN_INSIDE  );
	MilesL->box( FL_NO_BOX );
	MilesL->clear_visible_focus();
	setText( info );

	ShowStats = new Buttonf( x+5+w*0.66, y+5, w/3-5, h-10, "Show all Entries");
	ShowStats->clear_visible_focus();
	end();
}

void LoopButton::setText(const string& info )
{
	string Loop = info.substr( 0, info.find( "\t" ) );
	string Miles = info.substr( info.find( "\t" )+1 );
	LoopL->copy_label( Loop.c_str() );
	MilesL->copy_label( Miles.c_str() );
}

string LoopButton::getText() //uses LoopMenu::DELIMIT
{
	return (string)LoopL->label() + "\t\t\t" + (string) MilesL->label();
}

void LoopButton::setCallback( void (*fp)(Widget* w, void* data) ,void* data)
{
	LoopL->callback( fp, data );
	MilesL->callback( fp, data );
}

void LoopButton::setCallback2( void (*fp)(Widget* w, void* data) ,void* data)
{
	ShowStats->callback( fp, data );
}