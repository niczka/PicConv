#ifndef PICTURE_INCLUDED
#define PICTURE_INCLUDED  1

#include <stdio.h>
#include <allegro.h>
#include <math.h>
#include <string>

using namespace std;

class Picture
{
private:
	double pi(int i, int m, int n);

protected:
	BITMAP* picture;
	string path;
	
	Picture( )	{ }
	
public:
	Picture( BITMAP* p );
	Picture( string p );
	virtual const string get_path( ) const	{ return path; }
	virtual const BITMAP* get_picture( ) const	{ return picture; }
	virtual BITMAP* resize( int x, int y );
	~Picture( );
};


#endif 
