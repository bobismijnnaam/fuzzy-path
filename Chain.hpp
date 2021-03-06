// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 24/12/2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef CHAIN_HPP
#define CHAIN_HPP

// Includes I didn't make myself
#include "SFML/Graphics.hpp"

 // Includes I did make myself

enum class QueueMessage {
	Success,
	Rewind,
	Violation,
	Failure
} ;

class Chain : public sf::Drawable {
public:
	Chain();
	~Chain();

	void push(sf::Vector2f point, sf::Color pointColor);
	void push(sf::Vertex point);
	void pop();
	QueueMessage queue(sf::Vector2f point, sf::Color pointColor);
	void commit();

	void logic();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getChainLength();
	std::vector<sf::Vector2i> getChain();
	int getArrayLength();

	bool containsPoint(sf::Vector2i testPoint);

private:
	std::vector<sf::Vertex> points;
	std::vector<sf::Vector2i> pointChain;
};

#endif
