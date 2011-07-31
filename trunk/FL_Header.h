#ifndef FL_HEADER_H
#define FL_HEADER_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_FLoat_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Double_Window.H>

/**
 * Namespace to avoid typing Fl_ in front of all Fl types.
 */

namespace FLTK
{
	typedef Fl_Box Box;
	typedef Fl_Window Window;
	typedef Fl_Button Buttonf;		//Buttonf is there because there is name ambiguity
	typedef Fl_Int_Input InputI;
	typedef Fl_Input Input;
	typedef Fl_Float_Input InputF;
	typedef Fl_Widget Widget;
	typedef Fl_Choice Choice;
	typedef Fl_Scroll Scroll;
	typedef Fl_Menu_Bar MenuBar;
	typedef Fl_Group Group;
	typedef Fl_Input_Choice Input_Choice;
	typedef Fl_Menu_Item Menu_Item;
	typedef Fl_Multiline_Input InputM;
	typedef Fl_Pack Pack;
	typedef Fl_Double_Window DWindow;
}

#endif