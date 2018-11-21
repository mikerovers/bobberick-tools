#include "RandomGenerator.h"
#include <random>
#include <iostream>

int RandomGenerator::getRandomNumber(int const first, int const second) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(first, second);
	return dist(rng);
}

double RandomGenerator::getRandomDouble(double const first, double const second) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_real_distribution<double> dist(first, second);
	return dist(rng);
}