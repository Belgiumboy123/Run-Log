#include "RunMenu.h"

void RunMenu::add_cb( Widget* W, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	if( rm->validEntry() )
	{
		rm->handleEvent_i( ADD_RUN );
		rm->addInfo( rm->grabInfo() );
		rm->resetLastClicked();
	}
}

void RunMenu::delete_cb( Widget* W, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	rm->handleEvent_i( DELETE_RUN );
	rm->deleteInfo();
}

void RunMenu::edit_cb( Widget*w, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	rm->edit_cb_i();
}

void RunMenu::done_cb( Widget* W, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	rm->handleEvent_i( RUN_DONE );
	rm->resetLastClicked();
}

void RunMenu::reset_cb( Widget* w, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	rm->clearFields();
	rm->resetLastClicked();
}

void RunMenu::loop_cb( Widget* w, void* data )
{
    RunMenu* rm = (RunMenu*) data;
    rm->loop_cb_i();
}

/** Callback when user clicks a choice in loop */
void RunMenu::loop_cb_i()
{
	const char* s = Loop->menubutton()->text();
	Loop->value( s );
	handleEvent_i( LOOP_RUN_MENU, s  );
	MilesI->deactivate();
}

void RunMenu::input_cb_seconds( Widget* w, void* data )
{
	InputI* in = (InputI*) w;
	string s = correctTimeInput( in->value() );
	in->value( s.c_str() );
	RunMenu* rm = (RunMenu*) data;
	rm->CalcPace();
}

void RunMenu::input_cb_other( Widget* w, void* data )
{
	InputF* in = (InputF*) w;
	string s  = removeOtherInput(in->value() );
	in->value( s.c_str() );
	RunMenu* rm = (RunMenu*) data;
	rm->CalcPace();
}

void RunMenu::input_cb_miles( Widget*w, void* data )
{
	InputF* in = (InputF*) w;
	string s  = removeOtherInput(in->value() );
	in->value( s.c_str() );
	RunMenu* rm = (RunMenu*) data;
	rm->addLoopVisibilityCheck();
}

void RunMenu::loopChoice_cb( Widget* w, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	rm->loopChoice_cb_i();
}

/** callback when user enters text into loop input */
void RunMenu::loopChoice_cb_i()
{
	addLoopVisibilityCheck();
	if( NotContainLoop() ) MilesI->activate();
	else
	{
		handleEvent_i( LOOP_RUN_MENU, Loop->value()  );
		MilesI->deactivate();
	}
}

RunMenu::RunMenu(const int& xsize, const int& ysize ) : Menu( xsize,ysize )
{
	Menu::xSizeButton = xsize*0.466667-20;
	Menu::ySizeButton = ysize*0.25;
	current( this );
	BuildMenu( xsize, ysize);
	end();
}

void RunMenu::BuildMenu( const int& xsize, const int& ysize )
{
	scrollPane = new Scroll( 0, 0 , xsize*0.466667, ysize );
	scrollPane->type( Fl_Scroll::VERTICAL );
    scrollPane->align( FL_ALIGN_RIGHT );
	scrollPane->box( FL_FLAT_BOX );
	scrollPane->scrollbar.linesize(ySizeButton);
	pack = new Pack( 0,0,xsize*0.466667, ysize );
    scrollPane->end();
	Box* box1 = new Box( xsize * 0.471875, 0, xsize-xsize * 0.471875, ysize);
	box1->box( FL_FLAT_BOX );
	Box* LoopL = new Box( xsize * 0.471875, ysize* 0.0361905 , xsize* 0.0697917, ysize * 0.0761905, "Loop:");
	Box* Miles = new Box( xsize * 0.471875, ysize* 0.165714 , xsize* 0.0697917, ysize * 0.0761905, "Miles:");
	Box* TT = new Box( xsize * 0.471875, ysize* 0.304762 , xsize* 0.0697917, ysize * 0.0761905, "Time:");
	Box* PaceL = new Box( xsize * 0.471875, ysize* 0.419048 , xsize* 0.0697917, ysize * 0.0761905, "Pace:");
	Box* NotesL = new Box( xsize * 0.471875, ysize* 0.533333 , xsize* 0.0697917, ysize * 0.0761905, "Notes:");
	Loop = new Input_Choice( xsize * 0.666667, ysize* 0.0361905 , xsize* 0.234375, ysize * 0.0761905, "");
	Loop->callback( loopChoice_cb, this  );
	Loop->when( FL_WHEN_CHANGED );
	MilesI = new InputF( xsize * 0.666667, ysize* 0.165714 , xsize* 0.234375, ysize * 0.0761905, "");
	MilesI->callback( input_cb_miles, this );
	MilesI->when( FL_WHEN_CHANGED );
	Box* TTHL = new Box( xsize * 0.545833, ysize* 0.304762 , xsize* 0.0479167, ysize * 0.0666667, "Hours:");
	Box* TTML = new Box( xsize * 0.692708, ysize* 0.304762 , xsize* 0.0479167, ysize * 0.0666667, "Min:");
	Box* TTSL = new Box( xsize * 0.838542, ysize* 0.304762 , xsize* 0.0479167, ysize * 0.0666667, "Sec:");
	TT_H = new InputI( xsize * 0.59375, ysize* 0.304762 , xsize* 0.0729167, ysize * 0.0666667, "");
	TT_H->callback( input_cb_other, this );
	TT_H->when( FL_WHEN_CHANGED );
	TT_M = new InputI( xsize * 0.757292, ysize* 0.304762 , xsize* 0.0729167, ysize * 0.0666667, "");
	TT_M->callback( input_cb_other, this );
	TT_M->when( FL_WHEN_CHANGED );
	TT_S = new InputI( xsize * 0.888542, ysize* 0.304762 , xsize* 0.0729167, ysize * 0.0666667, "");
	TT_S->callback( input_cb_seconds, this );
	TT_S->when( FL_WHEN_CHANGED );
	Box* PML = new Box( xsize * 0.59375, ysize* 0.420952 , xsize* 0.0572917, ysize * 0.0666667, "Min:");
	Box* PSL = new Box( xsize * 0.757292, ysize* 0.420952 , xsize* 0.0572917, ysize * 0.0666667, "Sec:");
	P_M = new InputI( xsize * 0.66875, ysize* 0.420952 , xsize* 0.0729167, ysize * 0.0666667, "");
	//P_M->callback( input_cb, this );
	//P_M->when( FL_WHEN_CHANGED );
	P_M->deactivate();
	P_S = new InputI( xsize * 0.827083, ysize* 0.420952 , xsize* 0.0729167, ysize * 0.0666667, "");
	//P_S->callback( input_cb, this );
	//P_S->when( FL_WHEN_CHANGED );
	P_S->deactivate();
	NotesI = new InputM( xsize * 0.545833, ysize* 0.546667 , xsize* 0.416667, ysize * 0.171429, "");
	Delete = new Buttonf( xsize * 0.470833, ysize* 0.742857 , xsize* 0.173611333, ysize * 0.12381, "Delete");
	Delete->callback( delete_cb, this );
	Delete->clear_visible_focus();
	Edit = new Buttonf( xsize*0.64444,ysize* 0.742857,xsize* 0.173611333,ysize * 0.12381, "Edit" );
	Edit->callback( edit_cb, this );
	Edit->clear_visible_focus();
	Add = new Buttonf( xsize * 0.818055663, ysize* 0.742857 , xsize*0.173611333, ysize * 0.12381, "Add");
	Add->callback( add_cb, this );
	Add->clear_visible_focus();
	Close = new Buttonf( xsize * 0.73125, ysize* 0.866667 ,  xsize* 0.260417, ysize * 0.12381, "Back");
	Close->callback( done_cb, this );
	Close->clear_visible_focus();
	Reset = new Buttonf( xsize * 0.470833, ysize* 0.866667  , xsize* 0.260417, ysize * 0.12381, "Reset Fields");
	Reset->callback( reset_cb, this );
	Reset->clear_visible_focus();
	AddLoop = new Buttonf( xsize * 0.90625, ysize* 0.0952381 , xsize* 0.0791667, ysize * 0.0914286, "Add \n This Loop");
	AddLoop->callback( AddLoop_cb, this );
	AddLoop->clear_visible_focus();
	AddLoop->hide();
	end();
}

void RunMenu::closeRB_cb( Widget* w, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	RunButton* rb = ( RunButton*) w->parent();
	rm->closeRB_cb_i( rb->getText().c_str(), w->parent() );
}

void RunMenu::closeRB_cb_i(const char* info, Widget* w)
{
   lastClicked = w;
   deleteInfo(false);
   handleEvent_i( DELETE_RUN,(string) info );
}

void RunMenu::fillRun_cb( Widget* w, void* data )
{
	RunMenu* rm = (RunMenu*) data;
	RunButton* rb = ( RunButton*) w->parent();
	rm->fillInfo_cb_i( rb->getText().c_str(), w->parent() );
}

void RunMenu::fillInfo_cb_i( const char* info, Widget* w ) 
{
	lastClicked = w;
	string str = (string) info;
	currentlyLoaded = info;
	string values[8];
	
	for( int i =0; i<8;i++)
	{
		size_t found = str.find( "\t" );
		if( found != string::npos )
		{
			values[i] = str.substr(0,found);
			str = str.substr( found+1);
		}
	}
	//load values into input widgets
	MilesI->value( values[0].c_str() );
	Loop->value( values[1].c_str() );
	TT_H->value( values[2].c_str() );
	TT_M->value( values[3].c_str() );
	TT_S->value( values[4].c_str() );
	P_M->value( values[5].c_str() );
	P_S->value( values[6].c_str() );
	NotesI->value( values[7].c_str() );

	if( !NotContainLoop() ) MilesI->deactivate();
}

void RunMenu::AddLoop_cb( Widget*w, void* data )
{
    RunMenu* rm = (RunMenu*) data;
    rm->AddLoop_cb_i();
}

void RunMenu::AddLoop_cb_i()
{
    //safety check
    if( isNotWhiteSpace( Loop->value() ) && isNotWhiteSpace( MilesI->value()) && NotContainLoop() )
    { 
        string s =  (string) Loop->value()  + "\t" +(string) MilesI->value();
        handleEvent_i( LOOP_ADD, s );
        Loop->menubutton()->add( Loop->value(), 0, loop_cb, this, 0); 
        Loop->redraw(); 
	}
}

void RunMenu::edit_cb_i()
{
	if( validEntry() && currentlyLoaded != "" )
	{	
		deleteInfo( false );
		handleEvent_i( DELETE_RUN,currentlyLoaded );
		add_cb( 0, this );
	}
}

void RunMenu::setCallBack( Buttonf* btn )
{
	btn->callback( fillRun_cb, this);
}

bool RunMenu::validEntry()
{
    return containsNumbers( MilesI->value() );
}

string RunMenu::grabInfo()
{   
    return
	(string) MilesI->value() +	"\t" +
	(string) Loop->value()	+	"\t" +
	(string) TT_H->value()	+	"\t" +
	(string) TT_M->value()	+	"\t" +
	correct2DTimeInput( TT_S->value() )	+	"\t" +
	(string) P_M->value()	+	"\t" +
	correct2DTimeInput( P_S->value() )	+	"\t" +
	(string) NotesI->value()+   "\t"; 
}

void RunMenu::clearFields()
{
	Loop->value("");
	TT_H->value(0);
	TT_M->value(0);
	TT_S->value(0);
	P_M->value(0);
	P_S->value(0);
	MilesI->value(0);
	MilesI->activate();
	NotesI->value(0);
	AddLoop->hide();
}

const string RunMenu::labels[] = 
{	
	"Miles:\t", 
	"\tLoop:\t",
	"\nTotal Time:\t",
	"\t",
	"\t", 
	"\nPace:\t", 
	"\t", 
	"\nNotes:\t"  
};

string RunMenu::format( string& info, const string* labels )
{	
	if( info == "" )
		return "";
	else
	{
		size_t found = info.find_first_of( "\t" );	
		if( found != string::npos )
		{
			string created = labels[0] + info.substr( 0, found );
			info = info.substr( found+1);
			return created + format( info, ++labels);
		}
		else
			return "fail";
	}
}

string RunMenu::format( string& info )
{
    return format( info, &labels[0] );
}

/**
* Adds the given strings ( loops ) to Loop's Fl_Menu
*/
void RunMenu::setSecondaryInfo( const vector<string>& info )
{
    Loop->clear();
    vector<string>::const_iterator it;
    for( it = info.begin(); it != info.end(); it++)
    {
        Loop->menubutton()->add( (*it).c_str(), 0, loop_cb, this, 0);  
    }

    Loop->redraw();
}

/**
* Updates miles field when a loop has been selected
*
*/
void RunMenu::updatePanel( const string& info )
{
    MilesI->value( info.c_str() );
}

/**
* Returns true if Loop does not already contain the value entered in its textfield.
*/
bool RunMenu::NotContainLoop()
{
	const Menu_Item* mi = Loop->menubutton()->find_item(  Loop->value() );
	return ( mi != NULL ? false : true );
}

/**
* Loads up the newly calculated pace
*/
void RunMenu::updatePanelSecondary( const string& info )
{
	loadPace( info );
}

void RunMenu::loadPace( const string& pace )
{
	size_t found = pace.find( " " ); //the delimiter is hardcoded 
	string s1 = pace.substr( 0,found );
	string s2 = pace.substr( found+1 );
	P_M->value( s1.c_str() );
	P_S->value( s2.c_str() );
	P_M->redraw();
	P_S->redraw();
}

/** Return info needed to calculate pace*/
string RunMenu::grabPaceInfo()
{
	return 
		(string) MilesI->value()+	"\t" +
		" "						+	"\t" +
		" "						+	"\t" +
		(string) TT_H->value()	+	"\t" +
		(string) TT_M->value()	+	"\t" +
		(string) TT_S->value()	+	"\t";
}

/** if correct data has been entered notify observers to calculate pace */
void RunMenu::CalcPace()
{
	if //miles have been entered or one of the 3 total times fields
	( 
		containsNumbers( MilesI->value() ) &&
			( 											
				containsNumbers( TT_M->value() )	||											
				containsNumbers( TT_S->value() )	||												
				containsNumbers( TT_H->value() )	
			)										 
	)
	{
		DataPair dp( RUN_LOAD_PACE, grabPaceInfo() );
		notifyObservers( dp );
	}
}

void RunMenu::addButton( const int& x, const int& y, const int& w, const int& h, const string& info )
{
	RunButton* rb = new RunButton( x,y,w,h,info);
	rb->setCallback( fillRun_cb, this );
	rb->setCallback2(closeRB_cb, this);
}

void RunMenu::addLoopVisibilityCheck()
{
	if( isNotWhiteSpace( MilesI->value() ) && isNotWhiteSpace( Loop->value() ) )
		AddLoop->show();
	else
		AddLoop->hide();
}

////////////////
// RunButton ///
////////////////

RunButton::RunButton( const int& x, const int& y, const int& w, const int& h, const string& info ) 
	: MenuButton(x,y,w,h)
{
	//build group
	int half = w/2;
	int quarterH = h/4;
	box = new Box( x,y,w,h);
	box->box( FL_BORDER_BOX );

	loop = new Buttonf(x,y,half,h/4, "" );
	loop->box( FL_NO_BOX );
	loop->align( FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
	loop->clear_visible_focus();

	miles = new Buttonf(x+half, y, half*.75, h/4 , "");
	miles->box( FL_NO_BOX );
	miles->align( FL_ALIGN_LEFT | FL_ALIGN_INSIDE );
	miles->clear_visible_focus();

	close = new Buttonf( x+half+half*0.75, y+1, half*0.25-1, h/4, "X" );
	close->labelfont( FL_TIMES_BOLD );
	close->labelsize( 20);
	close->clear_visible_focus();

	box1 = new Buttonf( x,y+h/4, half, h/4, "Total Time:" );
	box1->align( FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
	box1->box( FL_NO_BOX );
	box1->clear_visible_focus();
	tt = new Buttonf( x+half, y+h/4, half, h/4, "");
	tt->align( FL_ALIGN_LEFT | FL_ALIGN_INSIDE );
	tt->box( FL_NO_BOX );
	tt->clear_visible_focus();
	
	box2 = new Buttonf( x, y+h/2, half, h/4, "Pace: " );
	box2->align( FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
	box2->box(FL_NO_BOX );
	box2->clear_visible_focus();
	pace = new Buttonf( x+half, y+h/2, half, h/4, "" );
	pace->align( FL_ALIGN_LEFT | FL_ALIGN_INSIDE );
	pace->box(FL_NO_BOX );
	pace->clear_visible_focus();

	box3 = new Buttonf( x, y+ h*0.75, half,h/4, "Notes: ");
	box3->align( FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
	box3->box(FL_NO_BOX );
	box3->clear_visible_focus();
	notes = new Buttonf( x+half, y+h*0.75, half, h/4, "" );
	notes->align( FL_ALIGN_LEFT | FL_ALIGN_INSIDE );
	notes->box(FL_NO_BOX );
	notes->clear_visible_focus();

	setText( info );
	end();
}

/**
* info is tab divided -> the return value of grabInfo()
*/
void RunButton::setText( const string& info )
{
	string values[8];
	for( int i = 0; i<8; i++)
	{
		size_t found = info.find( "\t" );
		if( found != string::npos )
		{
			values[i] = info.substr( 0, found );
			const_cast<string&>(info) = info.substr( found+1);
		}
	}
	
	miles->copy_label( (values[0]+ " miles").c_str() );
	loop->copy_label( values[1].c_str() );
	if( values[2] == "" ) tt->copy_label( (values[3] + ":" + values[4]).c_str() );
	else tt->copy_label( (values[2] + ":" + values[3] + ":" + values[4]).c_str() );
	pace->copy_label( (values[5] + ":" + values[6] ).c_str() ) ;
	notes->copy_label( values[7].c_str() );
}

/**
* Delimited by tabs
*/
string RunButton::getText()
{
	string m = (string)miles->label();	
	string text = m.substr( 0, m.find( " " ) ) + "\t"; 
	text += (string) loop->label() + "\t";
	string paceS = (string)pace->label();
	string ttS = (string)tt->label();
	if( ttS.find_first_of( ":") == ttS.find_last_of( ":") )
	{
		text += "\t";
		text += ttS.substr( 0, ttS.find( ":" ) ) + "\t";
		text += ttS.substr( ttS.find( ":" )+1 ) + "\t";
	}
	else
	{
		size_t found = ttS.find( ":" );
		text += ttS.substr( 0,found ) + "\t";
		size_t f = ttS.find_last_of( ":") - found-1;
		text += ttS.substr( found+1,f ) + "\t";
		text += ttS.substr( ttS.find( ":", found+1 )+1 ) + "\t";
	}
	text += paceS.substr( 0, paceS.find( ":" ) ) + "\t";
	text += paceS.substr( paceS.find( ":" )+1 ) + "\t";
	text += (string)notes->label() + "\t";  
	return text;
}

/**
* set callback to all buttons
*/
void RunButton::setCallback( void (*fp)(Widget* w, void* data) ,void* data)
{
	box1->callback(fp, data);
	box2->callback(fp, data);
	box3->callback(fp, data);
	loop->callback(fp, data);
	pace->callback(fp, data);
	notes->callback(fp, data);
	tt->callback(fp, data);
	miles->callback(fp, data);
}

void RunButton::setCallback2( void (*fp)(Widget* w, void* data) ,void* data)
{
	close->callback( fp, data );
}
