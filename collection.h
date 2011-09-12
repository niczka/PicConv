#ifndef COLLECTION_INCLUDED
#define COLLECTION_INCLUDED  1

#include <stdio.h>
#include <allegro.h>
#include <math.h>
#include <list>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include "thumbnail.h"


class Collection
{
private:
	std::list< Thumbnail > thumb_list;
	std::string dir_path;
public:
	Collection( std::string dir_path, int size );
	const BITMAP* get_best( BITMAP* big_p, int x, int y, int t);
	~Collection( );
};


#endif 
