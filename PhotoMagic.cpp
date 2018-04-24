// pixels.cpp: 
// using SFML to load a file, manipulate its pixels, write it to disk
// Fred Martin, fredm@cs.uml.edu, Sun Mar  2 15:57:08 2014

// g++ -o pixels pixels.cpp -lsfml-graphics -lsfml-window

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream> 
#include <iostream> 
#include "LFSR.hpp"
using namespace std; 

sf::Image transform(sf::Image pic, LFSR& meh);

int main(int argc,char *argv[]){
	string infile = argv[1];
	string outfile = argv[2];
	string bitString = argv[3];
	int tap = atoi(argv[4]);
	
	
	sf::Image image;
	if (!image.loadFromFile(infile))
		return -1;
	// create photographic negative image of upper-left 200 px square
	LFSR num(bitString, tap);
	sf::Image newCat = transform(image,num); 
	/*
		// p is a pixel
	sf::Color p;
	for (int x = 0; x<200; x++) {
		for (int y = 0; y< 200; y++) {
			p = image.getPixel(x, y);
			p.r = num.generate(8)^p.r;
			p.g = num.generate(8)^p.g;
			p.b = num.generate(8)^p.b;
			//p.r = 255 - p.r;
			//p.g = 255 - p.g;
			//p.b = 255 - p.b;
			image.setPixel(x, y, p);
		}
	}
	*/

	sf::Vector2u size1 = image.getSize();
	sf::RenderWindow window1(sf::VideoMode(size1.x, size1.y), "Meow");

	sf::Texture texture1;
	texture1.loadFromImage(image);

	sf::Sprite sprite1;
	sprite1.setTexture(texture1);	


	sf::Vector2u size2 = newCat.getSize();
	sf::RenderWindow window2(sf::VideoMode(size2.x, size2.y), "Meow");

	sf::Texture texture2;
	texture2.loadFromImage(newCat);

	sf::Sprite sprite2;
	sprite2.setTexture(texture2);

	while (window1.isOpen() && window2.isOpen()) {                         
	    sf::Event event;
	    while (window1.pollEvent(event)) {
	      if (event.type == sf::Event::Closed)
		window1.close();
	    }
	    while (window2.pollEvent(event)) {
	      if (event.type == sf::Event::Closed)
		window2.close();
	    }
	    window1.clear();
	    window1.draw(sprite1);
	    window1.display();
	    window2.clear();
	    window2.draw(sprite2);
	    window2.display();
  }

	// fredm: saving a PNG segfaults for me, though it does properly
	//   write the file
	if (!newCat.saveToFile(outfile))
		return -1;

	return 0;
}

sf::Image transform(sf::Image pic, LFSR& num){
	sf::Color p;
	sf::Vector2u WH = pic.getSize();
	int xmax = WH.x; 
	int ymax = WH.y; 
	for (int x = 0; x<xmax; x++) {
		for (int y = 0; y< ymax; y++) {
			p = pic.getPixel(x, y);
			p.r = num.generate(8)^p.r;
			p.g = num.generate(8)^p.g;
			p.b = num.generate(8)^p.b;
			pic.setPixel(x, y, p);
		}
	}

return pic; 
	
}
