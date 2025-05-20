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
#include <unordered_map>
#include <unordered_set>
#include <cctype>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::dp::strategic_defense_initiative
{
    /** https://onlinejudge.org/external/4/481.pdf */
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
        
        std::string in;
        std::getline(std::cin, in);       // Read number of test cases
        int tc = std::stoi(in);
        std::getline(std::cin, in);       // Read the blank line after T
        while(tc--)
        {
            vi targets;
            while (std::getline(std::cin, in) && !in.empty())
              targets.push_back(std::stoi(in));

            int s = (int)targets.size();
            vi dp(s, 1);
            vi sol(s);
            sol[0] = -1;

            for(int i = 1; i < s; ++i)
            {
                int child = -1;
                for(int j = i - 1; j >= 0; --j)
                  if(targets[j] < targets[i] && 
                     dp[i] < 1 + dp[j]) {
                     child = j;
                     dp[i] = 1 + dp[j];
                  }
                sol[i] = child;
            }
 
            int idx = std::distance(dp.begin(), std::max_element(dp.begin(), dp.end()));
            vi path;
            while(idx != -1) {
              path.push_back(targets[idx]);
              idx = sol[idx];
            }
            printf("Max hits: %d\n", (int)path.size());
            for(auto it = path.rbegin(); it != path.rend(); ++it) std::cout << *it << std::endl;
            if(tc) std::cout << std::endl;  
        }
    }
}