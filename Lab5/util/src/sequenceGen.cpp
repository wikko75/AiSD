#include "../inc/sequenceGen.hpp"
#include <random>
#include <string>

std::string randomSequence(size_t length)
{
    std::mt19937 mt { std::random_device{}() };              // Instantiate a 32-bit Mersenne Twister
    std::uniform_int_distribution<size_t> number {0, 2*length - 1};
    std::string sequence {};
	
	for (int count {0}; count < length; ++count)
	{
		sequence += std::to_string(number(mt));               // generate a random number and convert to std::string and stores
    }

    return sequence;
}