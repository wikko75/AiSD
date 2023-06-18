#ifndef SEQ_GEN_13_HPP
#define SEQ_GEN_13_HPP
#include <string>

/// @brief Returns randomly generated sequence of numbers (range [0, 2*length - 1]), converted to std::string
/// @param length length of sequence you want to generate
/// @return string representation of generated sequence
std::string randomSequence(size_t length);

#endif