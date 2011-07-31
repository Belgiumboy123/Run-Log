#ifndef MINITABLE_H
#define MINITABLE_H

#include "MenuButton.h"
#include "Panel.h"

/**
* One cell in the table
*/
class MiniTableCell : public MenuButton
{
	Buttonf* day;
	
public:
	
	MiniTableCell
	(	const int& x, const int& y, const int& w, const int& h, 
		const string& info, const bool& inactive = false
	 );
	void setText( const string& info );
	string getText();
	void setCallback( void (*fp)(Widget* w, void* data) ,void* data);
	void highLight( Fl_Color p_Color );
	bool isInactive();
};

/**
 * Class for a Table that only has a month view but shows days visible from previous and next month
 */
class MiniTable : public Panel
{
	static const string days[];
	Fl_Color normalColor;
	Fl_Color highLightColor;
	Fl_Color highLightColorIN;
	Fl_Color highLightToday;
	
public:
	
	MiniTable( const int& firstDay, const int& totalDays, const int& width, const int& height, const int& lastMonthDay );
	void BuildMenu( const int& firstDay, const int& totalDays, const int& width, const int& height, const int& lastMonthDay );
	
	/** Contains cells that need to be highlighted */
	void setInfo( const vector<string>& info );
	
	/** Updates Table with new month setup 
	 * Info contains 3 info pieces seperated by tabs
	 */
	void updatePanel( const string& info );
	
	/** Highlight the given cell - info */
	void updatePanelSecondary( const string& info );
	
	/** unused */
	void setSecondaryInfo( const vector<string>& info ){}
	
	/** call back for each cell */
	static void cell_cb( Widget* w, void* data );
	
	/** inline function makes call to observers */
	void cell_cb_i(const string& day);

	/** Return widget pointer to first cell that is active */
	Widget* getFirstActive();

	/** Convert index into array()[num] into MiniTableCell */
	MiniTableCell* convertToMTC( const int& num );
	
	/**Highlight given MTC depending wheter its active or not */
	void colorMTC( MiniTableCell* mtc );
	
};




#endif 