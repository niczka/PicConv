#include "picture.h"

using namespace std;

Picture::Picture( BITMAP* p )
	: picture( p )
{ }

Picture::Picture( string p )
	: path( p )
{
	picture = load_bmp( path.c_str( ), default_palette );
}

inline double pi(int i, int m, int n){
	return 1.0+abs((double)i-1.0)*((double)m-1.0)/((double)n-1.0);
}

inline int spline3(double p, double* diff, int x, int y){
    double fp = floor(p), cp = ceil(p);
    double rp = p - fp, pr = cp - p;
    
    return (int)round(diff[(int)fp]*pow(pr, 3.0)/6.0 + diff[(int)cp]*pow(rp, 3.0)/6.0 + ((double)x - diff[(int)fp]/6.0)*pr + 				((double)y - diff[(int)cp]/6.0)*rp);
}

BITMAP* resize_vertical_spline3(int n, BITMAP* bmp){
    BITMAP* result = create_bitmap(bmp->w, n);

    double diffr[bmp->h], diffg[bmp->h], diffb[bmp->h];
    for(int j = 0;j < bmp->w;j++)
    {
        //oblicz ilorazy różnicowe
        for ( int i = 0; i < bmp->h; i++ )	// wypełnij tablicę
	{
		int pix = getpixel(bmp, j, i);
		diffr[i] = getr(pix);
		diffg[i] = getg(pix);
		diffb[i] = getb(pix);
	}
        for ( int i = 0; i < bmp->h - 1; i++ )	// pierwsza iteracja
        {
		diffr[i] = diffr[i+1] - diffr[i];
		diffg[i] = diffg[i+1] - diffg[i];
		diffb[i] = diffb[i+1] - diffb[i];
	}
        for( int i = 1; i < bmp->h - 1; i++ )	// druga iteracja
        {
		diffr[i] = (diffr[i] - diffr[i-1]) / 2.0;
		diffg[i] = (diffg[i] - diffg[i-1]) / 2.0;
		diffb[i] = (diffb[i] - diffb[i-1]) / 2.0;
	}
		
        diffr[0] = diffr[bmp->h - 1] = diffg[0] = diffg[bmp->h - 1] = diffb[0] = diffb[bmp->h - 1] = 0;
	
	//rozwiąż układ równań
        double M[bmp->h - 2];	// wystarczy jedna tablica (bo macierz trójprzekątniowa)
        M[0] = 2.0;
        for(int i = 0;i < bmp->h - 3;i++)	// i jedna pętla for dla redukcji
        {
                double e = 1.0/(2.0 * M[i]);
                M[i+1] = 2.0 - e/2.0;
                diffr[i+2] -= e*diffr[i+1];
		diffg[i+2] -= e*diffg[i+1];
		diffb[i+2] -= e*diffb[i+1];
        }
        
        // wylicz wartości M_k
        for(int i = bmp->h - 2;i > 0;i--)
        {
                diffr[i] -= diffr[i+1]/2.0;
                diffr[i] /= M[i-1];
		diffg[i] -= diffg[i+1]/2.0;
                diffg[i] /= M[i-1];
		diffb[i] -= diffb[i+1]/2.0;
                diffb[i] /= M[i-1];
        }
        
        // wylicz wartości pixeli
        for(int i = 0;i < n;i++)
        {
		double p = pi(i, bmp->h, n);
		
		int pix1 = getpixel(bmp, j, (int)floor(p)), pix2 = getpixel(bmp, j, (int)ceil(p));
		
		int red = spline3(p, diffr, getr(pix1), getr(pix2));
		int green = spline3(p, diffg, getg(pix1), getg(pix2));
		int blue = spline3(p, diffb, getb(pix1), getb(pix2));
		
                if(red < 0) red = 0; if(red > 255) red = 255;
		if(green < 0) green = 0; if(green > 255) green = 255;
		if(blue < 0) blue = 0; if(blue > 255) blue = 255;

                putpixel(result, j, i, makecol(red, green, blue));
        }
    }
    
    return result;
} 

BITMAP* resize_horizontal_spline3(int n, BITMAP* bmp){
    BITMAP* result = create_bitmap(n, bmp->h);

    double diffr[bmp->w], diffg[bmp->w], diffb[bmp->w];
    for(int j = 0;j < bmp->h;j++)
    {
        //oblicz ilorazy różnicowe
        for ( int i = 0; i < bmp->w; i++ )	// wypełnij tablicę
	{
		int pix = getpixel(bmp, i, j);
		diffr[i] = getr(pix);
		diffg[i] = getg(pix);
		diffb[i] = getb(pix);
	}
        for ( int i = 0; i < bmp->w - 1; i++ )	// pierwsza iteracja
        {
		diffr[i] = diffr[i+1] - diffr[i];
		diffg[i] = diffg[i+1] - diffg[i];
		diffb[i] = diffb[i+1] - diffb[i];
	}
        for( int i = 1; i < bmp->w - 1; i++ )	// druga iteracja
        {
		diffr[i] = (diffr[i] - diffr[i-1]) / 2.0;
		diffg[i] = (diffg[i] - diffg[i-1]) / 2.0;
		diffb[i] = (diffb[i] - diffb[i-1]) / 2.0;
	}
		
        diffr[0] = diffr[bmp->w - 1] = diffg[0] = diffg[bmp->w - 1] = diffb[0] = diffb[bmp->w - 1] = 0;
	
	//rozwiąż układ równań
        double M[bmp->w - 2];	// wystarczy jedna tablica (bo macierz trójprzekątniowa)
        M[0] = 2.0;
        for(int i = 0;i < bmp->w - 3;i++)	// i jedna pętla for dla redukcji
        {
                double e = 1.0/(2.0 * M[i]);
                M[i+1] = 2.0 - e/2.0;
                diffr[i+2] -= e*diffr[i+1];
		diffg[i+2] -= e*diffg[i+1];
		diffb[i+2] -= e*diffb[i+1];
        }
        
        // wylicz wartości M_k
        for(int i = bmp->w - 2;i > 0;i--)
        {
                diffr[i] -= diffr[i+1]/2.0;
                diffr[i] /= M[i-1];
		diffg[i] -= diffg[i+1]/2.0;
                diffg[i] /= M[i-1];
		diffb[i] -= diffb[i+1]/2.0;
                diffb[i] /= M[i-1];
        }
        
        // wylicz wartości pixeli
        for(int i = 0;i < n;i++)
        {
		double p = pi(i, bmp->w, n);
		
		int pix1 = getpixel(bmp, (int)floor(p), j), pix2 = getpixel(bmp, (int)ceil(p), j);
		
		int red = ((p!=floor(p)) ? spline3(p, diffr, getr(pix1), getr(pix2)) : getr(pix1));
		int green = ((p!=floor(p)) ? spline3(p, diffg, getg(pix1), getg(pix2)) : getg(pix1));
		int blue = ((p!=floor(p)) ? spline3(p, diffb, getb(pix1), getb(pix2)) : getb(pix1));
		
        if(red < 0) red = 0; if(red > 255) red = 255;
		if(green < 0) green = 0; if(green > 255) green = 255;
		if(blue < 0) blue = 0; if(blue > 255) blue = 255;

        putpixel(result, i, j, makecol(red, green, blue));
        }
    }
    
    return result;
} 
BITMAP* resize_vertical(int n, BITMAP* bmp){
	BITMAP* result = create_bitmap(bmp->w, n);
	int i,j;
	for( i=0; i<n ; i++ ){
		for( j=0; j<bmp->w; j++ ){
			putpixel( result, j, i, getpixel( bmp, j, round(pi(i, bmp->h, n))));
		}
	}
	return result;
}

BITMAP* resize_horizontal(int n, BITMAP* bmp){
	BITMAP* result = create_bitmap(n, bmp->h);
	int i,j;
	for( i=0; i<bmp->h ; i++ ){
		for( j=0; j<n; j++ ){
			putpixel( result, j, i, getpixel( bmp, round(pi(j, bmp->w, n)), i));
		}
	}
	return result;
}

inline int spline1(int x, int y, double p){
  double f = floor(p), c = ceil(p);
  if(p == f)
    return x;
  else
    return (p - f)*x + (c - p)*y;
}

BITMAP* resize_vertical_spline1(int n, BITMAP* bmp){
	BITMAP* result = create_bitmap(bmp->w, n);
	int i,j;
	double p;
	for( i=0; i<n ; i++ ){
		for( j=0; j<bmp->w; j++ ){
			p = pi(i, bmp->h, n);
			int pix1 = getpixel(bmp, j, round(p)), pix2 = getpixel(bmp, j, round(p+1));
			int pixr = spline1(getr(pix1), getr(pix2), p);
			int pixg = spline1(getg(pix1), getg(pix2), p);
			int pixb = spline1(getb(pix1), getb(pix2), p);
			putpixel(result, j, i, makecol(pixr, pixg, pixb));
		}
	}
	
	return result;
} 

BITMAP* resize_horizontal_spline1(int n, BITMAP* bmp){
	BITMAP* result = create_bitmap(n, bmp->h);
	int i,j;
	double p;
	for( i=0; i<bmp->h ; i++ ){
		for( j=0; j<n; j++ ){
			p = pi(j, bmp->w, n);
			int pix1 = getpixel(bmp, round(p), i), pix2 = getpixel(bmp, round(p+1), i);
			int pixr = spline1(getr(pix1), getr(pix2), p);
			int pixg = spline1(getg(pix1), getg(pix2), p);
			int pixb = spline1(getb(pix1), getb(pix2), p);
			putpixel(result, j, i, makecol(pixr, pixg, pixb));
		}
	}
	
	return result;
} 


BITMAP* Picture::resize( int x, int y )
{
	return resize_horizontal( x, resize_vertical( y, this -> picture ) );
}

Picture::~Picture( )
{
	delete picture;
}


