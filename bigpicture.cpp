#include "bigpicture.h"

BigPicture::BigPicture( BITMAP* p )
	:Picture::Picture( p )
{ }

BigPicture::BigPicture( string p )
	:Picture::Picture( p )
{ }

void BigPicture::replace( int t, Collection col ) //arg: resolution of thumbs
{
	this -> picture_replaced = this -> resize( (int)round( ( ( this -> picture
		) -> w ) / t) * t, (int)round( ( ( this -> picture ) -> h ) / t ) * t );
		
	printf( "%d %d\n", this -> picture_replaced -> h, this -> picture_replaced -> w);
		
	const BITMAP* thumb;
	
	for ( int ii = 0; ii < this -> picture_replaced -> w; ii += t )
	{
		for ( int jj = 0; jj < this -> picture_replaced -> h; jj += t )
		{
			thumb = col. get_best( this -> picture_replaced, ii, jj, t );
			for ( int iii = 0; iii < t; iii++ )
			{
				for ( int jjj = 0; jjj < t; jjj++ )
				{
					putpixel( this -> picture_replaced, ii+iii, jj+jjj, 
					getpixel((BITMAP*)thumb, iii, jjj));
				}
			}
		}
	}
}

void BigPicture::save( string filename )
{
	save_bmp( filename.c_str(), this -> picture_replaced, default_palette);	
}

BigPicture::~BigPicture( )
{
	//Picture::~Picture();
	delete picture_replaced;
	delete path_replaced;
	delete picture_colletion;
}
