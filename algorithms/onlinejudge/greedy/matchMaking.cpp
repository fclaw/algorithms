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
typedef std::vector<std::pair<size_t, bool>> vpib;

namespace algorithms::onlinejudge::greedy::match_making
{
    /** https://onlinejudge.org/external/122/12210.pdf */
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

        size_t B, S, c = 1;
        while(scanf("%zu %zu\n", &B, &S) && B && S)
        {
            vi bachelors(B);
            vpib spinster(S, {0, false});
            for(size_t i = 0; i < B; i++)
              std::cin >> bachelors[i];
            for(size_t j = 0; j < S; j++)
              std::cin >> spinster[j].first;
            
            std::sort(bachelors.begin(), bachelors.end(), std::greater<size_t>());
            std::sort(spinster.begin(), spinster.end(), std::greater<std::pair<size_t, bool>>());

            vi left;
            for(size_t i = 0; i < B; i++)
            {
                size_t min_diff = INT32_MAX;
                size_t best_j = -1;
                int b_age = (int)bachelors[i];
                for(size_t j = 0; j < S; j++)
                {
                     bool is_claimed = spinster[j].second;
                     if(is_claimed) continue;
                     int s_age = (int)spinster[j].first;
                     size_t diff = std::abs(b_age - s_age);
                     if(diff < min_diff)
                     { min_diff = diff; best_j = j; }
                }
                if((int)best_j == -1) left.push_back(bachelors[i]);
                else spinster[best_j].second = true;
            }

            printf("Case %zu: ", c++);
            left.size() ? std::cout << left.size() << " " << *std::min_element(left.begin(), left.end()) << std::endl : std::cout << 0 << std::endl;
        }  
    }
}