#ifndef LCS_13_HPP
#define LCS_13_HPP
#include <vector>

/// @brief Gets length of the Longest Common Subsequence of sequence A and sequence B, optionaly prints LCS via std::cout
/// @param A first sequence
/// @param B second sequence
/// @param print whether should print LCS to the console via std::cout, true by default
/// @return length of the LCS (size_t) 
size_t LCS(const std::string &A, const std::string &B, bool print = true);

/// @brief Prints LCS in console
/// @param routes matrix of routes
/// @param A first of sequences LCS was calculated of
/// @param i current row index in routes matrix, initialy max row idx (A.length())
/// @param j current column index in routes matrix, initialy max columnn idx (length of a second sequence LCS was calculated of)
/// @param LCS vector holding LCS
void LCS_print(const std::vector<std::vector<char>> &routes, const std::string &A, int i, int j, std::vector<char> LCS);

#endif