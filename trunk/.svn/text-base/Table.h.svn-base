#ifndef TABLE_H
#define TABLE_H

#include "MenuButton.h"
#include "Panel.h"

/**
 * Class Table for a calendar, week or month view.
 */
class Table : public Panel  {

public:
	
	/**Constructor*/
	Table(const int& firstDay, const int& totalDays, const int& width, const int& height );
	
	/** Build table */
	void BuildMenu( const int& firstDay, const int& totalDays, const int& width, const int& height );

	/** Vector containing info to be placed on each cell, "" if to remain empty ( unchanged ) */
	void setInfo( const vector<string>& info );

	/** Vector containing additional info ( days for week table ) to be placed in each cell */
	void setSecondaryInfo( const vector<string>& info );
	
	/** Updates Table with new setup */
	void updatePanel( const string& info );

	/** Un used */
	void updatePanelSecondary( const string& info );

	/** Call back for each individual cell */
	static void cell_cb_month( Widget* w, void* data );
	static void cell_cb_week( Widget* w, void* data );

	/** inline call back for each individual cell */
	void cell_cb_i(const string& day);

private:
	
	static const string days[];
};

/**
* Class for info on a Month cell
*/
class TableMonthCell : public MenuButton
{
	Buttonf* box;
	Buttonf* day;
	Buttonf* text;

public:
	TableMonthCell
	(	const int& x, const int& y, const int& w, const int& h, 
		const string& info
	);
	void setText( const string& info );
	string getText();
	void setCallback( void (*fp)(Widget* w, void* data) ,void* data);
};


/**
* Class for info on a week cell
*/
class TableWeekCell : public MenuButton
{
	
	Buttonf* wday;

public:
	TableWeekCell( const int& x, const int& y, const int& w, const int& h, const string& info );
	void setText( const string& info );
	string getText();
	void setCallback( void (*fp)(Widget* w, void* data) ,void* data);
};

#endif