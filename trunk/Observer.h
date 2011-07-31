/*
 *  Observer.h
 *  run_log
 *
 *  Created by Murder on 7/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

using std::vector;

class Observer{
	
	Observer(){}
	
	virtual ~Observer(){}
	
public:
	
	virtual void update( void* data ) = 0;
};


class Observable{
	
public:
	
	Observable(){}
	
	void addObserver( Observer* observer){ Observers.push_back( observer); }
	
	void notifyObservers(void* data){  
		
		for( iter it = Observers.begin(); it != Observers.end(); it++){
		
			(*it)->update( data );
		}
	}
	
	virtual ~Observable(){}

private:
	
	vector<Observer*> Observers;
	
	typedef vector<Observer*>::iterator iter;

};

#endif