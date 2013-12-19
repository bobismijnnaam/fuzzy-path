// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: di 17-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 
#include <time.h>

 // Includes I did make myself 
#include "Randomizer.hpp" 

Randomizer::Randomizer() {

}

Randomizer::~Randomizer() {

}

void Randomizer::seed(uint32_t inputSeed) {
	Randomizer::rng->seed(inputSeed);
	Randomizer::generatorSeed = inputSeed;
}

void Randomizer::selfSeed() {
	// Code seems to crash on my machine
	/*std::random_device trng;
	std::uniform_int_distribution<uint32_t> uint_dist;
	Randomizer::generatorSeed = uint_dist(trng);*/
	
	// Seeded with time
	Randomizer::generatorSeed = time(NULL);
	Randomizer::rng->seed(Randomizer::generatorSeed);
}

uint32_t Randomizer::getSeed() {
	return Randomizer::generatorSeed;
}

uint32_t Randomizer::getRange(int start, int end) {
	std::uniform_int_distribution<uint32_t> uint_dist(start,end);
	return uint_dist(*Randomizer::rng);
}

uint32_t Randomizer::generatorSeed = 0;
std::mt19937* Randomizer::rng = new std::mt19937();