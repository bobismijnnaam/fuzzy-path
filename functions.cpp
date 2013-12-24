// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 24/12/2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

// Includes I didn't make myself
#include "SFML/Graphics.hpp"

 // Includes I did make myself
#include "functions.hpp"

sf::Color invertColor(sf::Color i) {
	return sf::Color(255 - i.r, 255 - i.g, 255 - i.b);
}