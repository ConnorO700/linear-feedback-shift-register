all: PhotoMagic.o LFSR.o 
	g++ PhotoMagic.o LFSR.o -o PhotoMagic -lsfml-graphics -lsfml-window -lsfml-system  #-o to end then name of exe then lib flags;

pixels.o: PhotoMagic.cpp 
	g++ -c PhotoMagic.cpp -Wall -Werror -ansi -pedantic 

LFSR.o: LFSR.cpp LFSR.hpp
	g++ -c LFSR.cpp -Wall -Werror -ansi -pedantic 

clean: 
	rm *.o PhotoMagic
