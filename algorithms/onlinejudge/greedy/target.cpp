#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>







namespace algorithms::onlinejudge::greedy::target
{
    /**  from the book: https://jeffe.cs.illinois.edu/teaching/algorithms/book/Algorithms-JeffE.pdf
     *  Consider the following process. At all times you have a single positive
     * integer x, which is initially equal to 1. In each step, you can either
     * increment x or double x. Your goal is to produce a target value n. For
     * example, you can produce the integer 10 in four steps as follows:
     * 1 -> 2  (+1), 2 -> 4 (* 2), 4 -> 5 (+1), 5 -> 10 (*2)
     * Obviously you can produce any integer n using exactly n - 1 increments, but
     * for almost all values of n, this is horribly inefficient. Describe and analyze
     * an algorithm to compute the minimum number of steps required to produce
     * any given integer n. */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
          
        int n;
        while(while_read(n))
        {
            int steps = 0;
            while(n > 1)
            {
                 n = !(n % 2) ? n /= 2 : --n;
                 ++steps;
            }
            std::cout << steps << std::endl;
        }
    }
}