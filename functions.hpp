// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 24/12/2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

// Includes I didn't make myself
#include "SFML/Graphics.hpp"
#include <string>
#include <sstream>

 // Includes I did make myself

// Checks for range [min, max)
template <typename T>
bool inRange(T v, T min, T max) {
	return v >= min && v < max;
}

// Inverts color
sf::Color invertColor(sf::Color i);

// Centers sf::Text instance
void centerAlignText(sf::Text& t);

std::string itos(int i);

#endif