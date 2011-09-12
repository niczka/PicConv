#ifndef THUMBNAIL_INCLUDED
#define THUMBNAIL_INCLUDED  1

#include <stdio.h>
#include <allegro.h>
#include <math.h>
#include <string>
#include "picture.h"

using namespace std;

class Thumbnail: public Picture
{
public:
	Thumbnail( BITMAP* p, int size );
	Thumbnail( string p, int size );
	const string get_path( )	{ return Picture::get_path(); }
	const BITMAP* get_picture( ) const			{ return picture; }
	BITMAP* resize( int x, int y )				{ return Picture::resize( x, y ); }
	double compare( BITMAP* big_p, int x, int y, int t ) const;
	~Thumbnail( );
};


#endif 
