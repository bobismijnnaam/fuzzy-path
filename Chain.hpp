// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 24/12/2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef CHAIN_HPP
#define CHAIN_HPP

// Includes I didn't make myself
#include "SFML/Graphics.hpp"

 // Includes I did make myself


class Chain : public sf::Drawable {
public:
	Chain();
	~Chain();

	void push(sf::Vector2f point, sf::Color pointColor);
	void pop();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getTrajectoryScore();

private:
	std::vector<sf::Vertex> points;

};

#endif
