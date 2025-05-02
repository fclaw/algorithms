#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>






typedef std::vector<size_t> vi;


namespace algorithms::onlinejudge::greedy::coins
{
    /** https://onlinejudge.org/external/112/11264.pdf */
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
        
         int tc;
         std::cin >> tc;
         while(tc--)
         {
             size_t N;
             std::cin >> N;
             vi coins(N);
             for(size_t i = 0; i < N; i++)
               std::cin >> coins[i];
            
             size_t sum = 0;
             size_t denom = 1; // coin of 1 denomination
             for(size_t i = 1; i < N; i++)
              if(sum + coins[i - 1] < coins[i])
              { sum += coins[i - 1]; ++denom; }
             std::cout << denom << std::endl;
         }
    }
}