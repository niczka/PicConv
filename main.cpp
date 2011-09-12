#include "picture.h"
#include "bigpicture.h"
#include "thumbnail.h"
#include "collection.h"

using namespace std;


int main()
{
// INIT ALLEGRO
       int depth;

       allegro_init();
       depth = desktop_color_depth();
       if (depth == 0) depth = 32;

       set_color_depth(depth);


// END OF INIT
	string filename1, filename2, dir;
	int thumbnail_size;

	std::cout << "Hi!\n";
	std::cout << "Type name of file you want to modify(it should be placed in current directory).\n";
	std::cin >> filename1;
	BigPicture* pic = new BigPicture( filename1 );
	//std::cout << "BigPicture created\n";
	std::cout << "Type name of directory where you store pictures you want to use.\n";
	std::cin >> dir;
	std::cout << "Type one number - size of thumbnail.\n";
	std::cin >> thumbnail_size;
	Collection* coll = new Collection( dir, thumbnail_size );
	//std::cout << "Collection created\n";
	(*pic). replace( thumbnail_size, (*coll) );
	//std::cout << "BigPicture replaced\n";
	std::cout << "Type name of file where you want to save modified picture\n";
	std::cin >> filename2;
	(*pic). save( filename2 );
    return 0;
}
