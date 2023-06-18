#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <cstddef> //for size_t
#include "./LCS/inc/LCS.hpp"
#include "./util/inc/meters.hpp"
#include "./util/inc/sequenceGen.hpp"

int main()
{
    /*
    TESTS - small size sequences
    -------------------------------------------------------------------------------------
    */
    std::cout << LCS("ABCBDAB", "BDCABA", true);
    std::cout << LCS("ababbbaaabb", "abaabddasba", true) << "\n";
    std::cout << "Number of comparisons: " << numberOfComparisons(true) << "\n";

    std::string A {randomSequence(10)};
    std::string B {randomSequence(10)};
    std::cout << LCS(A, B, true) << "\n";
    std::cout << "Number of comparisons: " << numberOfComparisons(true) << "\n";


    std::string C {randomSequence(15)};
    std::string D {randomSequence(25)};
    std::cout << LCS(C, D, true) << "\n";
    std::cout << "Number of comparisons: " << numberOfComparisons(true) << "\n";

    /*
    -------------------------------------------------------------------------------------   
    */



    /*
    TEST - sequences of length = [1000, 2000, 3000, 4000, 5000]
    -------------------------------------------------------------------------------------   
    */
    std::ofstream outputFile("../output.csv");

    if (!outputFile) {
        std::cerr << "Failed to open the file." << "\n";
        return 1;
    }


    for (size_t length {1000}; length < 5001; length += 1000)
    {
        std::string A {randomSequence(length)};
        std::string B {randomSequence(length)};
        std::cout << LCS(A, B, false) << "\n";
        size_t noOfComparisons {numberOfComparisons(true)};
        outputFile << noOfComparisons << "," << "\n";
        std::cout << "Number of comparisons: " << noOfComparisons << "\n";
    }
    
    outputFile.close();

    std::cout << "Data saved successfully." << "\n";

    /*
    -------------------------------------------------------------------------------------   
    */

    return 0;
}