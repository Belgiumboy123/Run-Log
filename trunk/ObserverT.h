/*
 *  ObserverT.h
 *  run_log
 *
 * Observer and Observable classes needed for Observer Pattern
*/

#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <vector>

using std::vector;

template <typename T>
class Observer{
	
public:
	
	virtual void update( T& data ) = 0;
	
	virtual ~Observer(){}
};

template <typename T>
class Observable{
	
public:
		
	int getNum(){  return Observers.size(); } 
	
	virtual void addObserver( Observer<T>* observer){ Observers.push_back( observer); }
	
	void addObservers( vector<Observer<T>*> p_Observers )
	{ 
		for( iter it = p_Observers.begin(); it != p_Observers.end(); it++)
		{
			Observers.push_back( (*it) );
		}
	}
	
	vector<Observer<T>*> getObservers() { return Observers; }
	
	void notifyObservers(T& data)
	{  
		Trace("notifying all observers" );
		
		for( iter it = Observers.begin(); it != Observers.end(); it++){
			
			Trace("calling update" );
			(*it)->update( data );
		}
	}
	
	virtual ~Observable(){}
	
private:
	
	vector<Observer<T>*> Observers;	
	typedef typename vector<Observer<T>*>::iterator iter;
};


/**
*  Very simple smart pointer used for previousPanel in MainWin
*
* Instead of using delete keyword, set previousPanel to 0.
*/
template<typename T>
class ref_ptr
{
	T* _mainptr;
	vector<T**> _refs;

public:	
	ref_ptr<T>()
	{
		_mainptr = 0;
	}

	T* operator->(){ return _mainptr; }

	void operator=( T** newobject)
	{
		if ( newobject == 0 )
		{
			delete _mainptr;
			_mainptr = 0;
			for( int i =0; i<_refs.size(); i++)
			{
				(*_refs[i]) = 0;
			}
			_refs.clear();
		}
		else	   ///take care of case that newobject points to same object as mainptr
		{			//so now its just saving two pointers
			_refs.clear();
			_mainptr = *newobject;
			_refs.push_back( newobject );
		}
	}

	void operator=( const ref_ptr<T>& other )  //should check for self assignment
	{
		_mainptr = other.getMainPtr();
		_refs.clear();
		vector<T**> f = other.getRefs();
		for( int i = 0; i<f.size(); i++)
		{
			_refs.push_back( f[i] );
		}
	}	

	vector<T**> getRefs() const { return _refs; }
	T* getMainPtr() const { return _mainptr; }
};

#endif