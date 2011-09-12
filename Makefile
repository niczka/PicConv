main : main.cpp picture.o bigpicture.o thumbnail.o collection.o
	g++ -o main main.cpp picture.o bigpicture.o thumbnail.o collection.o `allegro-config --libs`

picture.o : picture.cpp picture.h
	g++ -c -o picture.o picture.cpp `allegro-config --libs`

thumbnail.o : thumbnail.cpp thumbnail.h picture.o
	g++ -c -o thumbnail.o thumbnail.cpp picture.o `allegro-config --libs`

collection.o : collection.cpp collection.h thumbnail.o
	g++ -c -o collection.o collection.cpp thumbnail.o `allegro-config --libs`

bigpicture.o : bigpicture.cpp bigpicture.h picture.o collection.o
	g++ -c -o bigpicture.o bigpicture.cpp picture.o collection.o


