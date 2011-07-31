#include "HelpPanel.h"

const char* nmw = "Day/Week/Month Views:\n"
"\t\t\tEach of the three buttons will change which days are being displayed.\n"
"\t\t\tClicking on a day in week or month mode will display the day that was clicked.\n\n"
"Next/Previous:\n"
"\t\t\tClicking on the arrows next to the current day will take you to the next or previous\n"
"\t\t\tday/week/month.\n\n"
"Today:\n\t\t\tThis button brings you the day view of today's day.\n\n"
"Close:\n\t\t\tCloses down the program.  Note: All runs entered this session will automatically be saved.\n\n"
"Stastics:\n\t\t\tButton right corner shows the total amount of miles run in a specific period.\n"
"\t\t\tClicking the button there will display different periods, miles per week for the month\n"
"\t\t\tyou are currently viewing and miles per month for the current year.\n\n"
"Mini-Month:\tTop right hand corner will always display the current month you are viewing. If you are viewing\n"
"\t\t\ta week or day these day(s) will be highlighted with a red color.\n"
"\t\t\tThe current day will be colored yellow. Clicking on the days will bring the user to the 'day' view\n"
"\t\t\tof that day.  Note: You can click on days not currently in the current month.";


const char* runs = "Adding a Run:\n"
"\t\t\tIn order for a run to be added the 'Miles' field must not be empty.\n\n"
"Editing a Run:\n"
"\t\t\tSelect the run you wish to edit from the list on the right, make your changes\n"
"\t\t\tand then press 'Edit'.  Note: If you press add after making some changes it will\n"
"\t\t\tadd a new run rather than editing the old one.\n\n"
"Deleting a Run:\n"
"\t\t\tTo delete a run press either the 'X' button in top right hand corner of the run on\n"
"\t\t\tthe right or selected it from the list and press the 'Delete' button.\n\n"
"Back:\n"
"\t\t\tThis will take the user back to the month or week view that was displayed before\n"
"\t\t\tthis day.";


const char* tools = "LoopMenu:\n"
"\t\t\tThis will display all your entered loops, and similar to adding/deleting runs, the user can\n"
"\t\t\tdelete and add loops.\n"
"\t\t\tThe 'Done' button will bring user back to 'Month' view.\n\n"
"Goto:\n"
"\t\t\tThis will allow user to go to a specific day or month\n." 
"\t\t\tThe currently viewed day is loaded up by default.\n"
"\t\t\tThe 'Goto Day' button will bring user to the chosen day view. 'Goto Month' will bring user to the\n"
"\t\t\tselected month view.";


HelpPanel::HelpPanel( const int& width, const int& height ) : Panel( width, height )
{
	buildPanel( width, height );
	end();
}

void HelpPanel::buildPanel( const int& width, const int& height )
{
	
	//buttons on left side that will fill in info on right side

	scrollPane = new Scroll( 0,0,width*0.25,height );
	scrollPane->type( Fl_Scroll::VERTICAL );
    scrollPane->align( FL_ALIGN_RIGHT );
	scrollPane->box( FL_FLAT_BOX );

		Buttonf* b1 = new Buttonf( 0,0,width*0.25, height*0.1 , "Navigating Main Window" );
		b1->callback( btn0_cb, this );
		b1->clear_visible_focus();
		b1->labelsize( 15 );

		Buttonf* b2 = new Buttonf( 0,height*0.1, width*0.25, height*0.1, "Logging a Run" );
		b2->clear_visible_focus();
		b2->labelsize( 15 );
		b2->callback( btn1_cb, this );

		Buttonf* b3 = new Buttonf( 0,height*0.2, width*0.25, height*0.1, "Tools" );
		b3->clear_visible_focus();
		b3->labelsize( 15 );
		b3->callback( btn2_cb, this );

	scrollPane->end();

	infoGroup = new Group( width*0.25, 0, width*0.75, height );
			
	infoGroup->end();
	this->end();
}

void HelpPanel::btn_cb_i(const int& btn)
{
	int xpos = x(), ypos = y();
	infoGroup->clear();
	infoGroup->position(0,0);
	infoGroup->hide();

	Box* b3 = new Box( w()*0.25 + 20, 10, w()*0.75-20, h()-10 );
	b3->align( FL_ALIGN_INSIDE | FL_ALIGN_LEFT | FL_ALIGN_TOP );

	switch( btn )
	{
		case 0:
			b3->copy_label( nmw );
			break;
		case 1:		
			b3->copy_label( runs );										
			break;
		case 2:	
			b3->copy_label( tools );			
	}
	infoGroup->add( b3 );
	infoGroup->position(xpos,ypos);
	infoGroup->redraw();
	infoGroup->show();
}

void HelpPanel::btn0_cb( Widget* w, void* data )
{
	HelpPanel* hp = (HelpPanel*) data;
	hp->btn_cb_i( 0 );
}

void HelpPanel::btn1_cb( Widget* w, void* data )
{
	HelpPanel* hp = (HelpPanel*) data;
	hp->btn_cb_i( 1 );
}

void HelpPanel::btn2_cb( Widget* w, void* data )
{
	HelpPanel* hp = (HelpPanel*) data;
	hp->btn_cb_i( 2 );
}