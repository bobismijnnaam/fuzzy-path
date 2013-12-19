// Author: Bob Rubbens - Knights of the Compiler
// Creation date: di 17-12-2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef RANDOMIZER_HPP
#define RANDOMIZER_HPP

// Includes I didn't make myself
#include <random>

 // Includes I did make myself


class Randomizer {
public:
	Randomizer();
	~Randomizer();

	static void seed(uint32_t inputSeed);
	static void selfSeed();
	static uint32_t getSeed();
	static uint32_t getRange(int start, int end);

private:
	static uint32_t generatorSeed;
	static std::mt19937* rng;
};

#endif
