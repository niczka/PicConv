#ifndef BIGPICTURE_INCLUDED
#define BIGPICTURE_INCLUDED  1

#include <stdio.h>
#include <allegro.h>
#include "picture.h"
#include "collection.h"
#include <math.h>
#include <string>

using namespace std;


class BigPicture: public Picture
{
private:
	BITMAP* picture_replaced;
	char* path_replaced;
	Collection* picture_colletion;
	
	BigPicture( )	{ }
	
public:
	BigPicture( BITMAP* p );
	BigPicture( string p );
	const string get_path( )			{ return Picture::get_path(); }
	const BITMAP* get_picture( )		{ return Picture::get_picture(); }
	BITMAP* resize( int x, int y )	{ return Picture::resize( x, y ); }
	string get_path_replaced( )		{ return path_replaced; }
	BITMAP* get_picture_replaced( )	{ return picture_replaced; }
	void replace( int t, Collection col );
	void save( string filename );
	~BigPicture( );
};


#endif 
