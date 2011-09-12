#include "thumbnail.h"

using namespace std;

Thumbnail::Thumbnail( BITMAP* p, int size )
	:Picture::Picture( p )
{ 
	picture = Picture::resize( size, size );
}

Thumbnail::Thumbnail( string p, int size )
	:Picture::Picture( p )
{
	picture = Picture::resize( size, size );
}

double Thumbnail::compare( BITMAP* big_p, int x, int y, int t ) const //returns norm(2nd) : || pic1 - pic2 ||
{
	int sum, dif, difr, difg, difb;
	sum = 0;
	int pixel1, pixel2;
	for ( int ii = 0; ii < t; ii++ )
	{
		for ( int jj = 0; jj < t; jj++ )
		{
			pixel1 = getpixel( big_p, x+ii, y+jj );
			pixel2 = getpixel( this -> picture, ii, jj );
			difr = getr( pixel1 ) - getr( pixel2 );
			difg = getg( pixel1 ) - getg( pixel2 );
			difb = getb( pixel1 ) - getb( pixel2 );
			dif  = difr*difr + difg*difg + difb*difb;
			sum += dif;
		}
	}
	return sqrt((double)sum);
}

Thumbnail::~Thumbnail( )
{ }
