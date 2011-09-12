#include "collection.h"

using namespace std;

Collection::Collection( std::string dir_path, int t_size )
	:dir_path( dir_path )
{
	thumb_list = std::list< Thumbnail >();
	DIR *dp;
    struct dirent *dirp;
    std::string name;
    
    dp  = opendir(dir_path.c_str());

    while ((dirp = readdir(dp)) != NULL) {
		name = string( dirp -> d_name );
        if ( ( name != "." ) && ( name != ".." ) )
        {
			Thumbnail* t = new Thumbnail( dir_path + "/" + name, t_size );
			thumb_list.push_back( *t );
		}
    }
    closedir(dp);
}

const BITMAP* Collection::get_best( BITMAP* big_p, int x, int y, int t)
{
	double min_value = 100000000.0;
	double temp;
	const BITMAP* result;
	for( std::list< Thumbnail > :: const_iterator
			p = thumb_list. begin( );
			p != thumb_list. end( );
			++ p )
	{
		temp = (*p). compare( big_p, x, y, t );
		if ( temp <= min_value )
		{
			min_value = temp;
			result = (*p). get_picture();
		}
	}
	return result;
}

Collection::~Collection( )
{
//	delete thumb_list;
}
