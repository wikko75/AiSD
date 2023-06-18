#include <iostream>
#include <vector>
#include "LCS.hpp"
#include "meters.hpp"


void LCS_print(const std::vector<std::vector<char>> &routes, const std::string &A, int i, int j, std::vector<char> LCS)
{
    if (i < 0 || j < 0)
    {
        for (char character : LCS)
        {
            std::cout << character;
        }

        std::cout << "\n";
    
        return;
    }

    if (routes[i][j] == '\\')
    {
        LCS.insert(LCS.begin(), A[i]);
        return LCS_print(routes, A, i - 1, j - 1, LCS);
    }
    else if (routes[i][j] == '^')
    {
        return LCS_print(routes, A, i - 1, j, LCS);

    }
    else
    {
        return LCS_print(routes, A, i, j - 1, LCS);
    }
}

size_t LCS(const std::string &A, const std::string &B, bool print /*= true*/)
{
    if (A.empty() || B.empty())
    {
        return -1;
    }
    
    //matrix of symbols in A and B
    std::vector<std::vector<int>> tab {
        A.length() + 1,
        std::vector<int>(B.length() + 1)
    };

    //matrix of routes
    std::vector<std::vector<char>> route {
        A.length(),
        std::vector<char>(B.length())
    };

    for(size_t i {0}; i < A.length(); ++i)
    {
        std::cout << "";
        for (size_t j {0}; j < B.length(); ++j)
        {
            numberOfComparisons();
            if (A[i] == B[j])
            {
                tab[i+1][j+1] = 1 + tab[i][j];
                route[i][j] = '\\';

            }
            else
            {   numberOfComparisons();
                if (tab[i][j+1] >= tab[i+1][j])
                {
                    tab[i+1][j+1] = tab[i][j+1];
                    route[i][j] = '^';

                }
                else
                {
                    tab[i+1][j+1] = tab[i+1][j];
                    route[i][j] = '<';
                }
            }           
        }    
    }

    if (print)
    {
        //vector that will hold LCS
        std::vector<char> LCS {};
        std::cout << "Longest Common Subsequence of\n" << A << "\nend\n" << B << "\nis\n";
        LCS_print(route, A, A.length() - 1, B.length() - 1, LCS);
    }
    

    //bottom left corner of tab matrix
    return tab[A.length()][B.length()];
}



//ten uczuć kiedy pomylisz wiersz z kolumną / wpiszesz z palca błędną daną :d