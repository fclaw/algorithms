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





typedef std::vector<int> vi;
typedef std::vector<std::pair<int, int>> vpii;


namespace algorithms::onlinejudge::dp::Jill_rides_again
{
    /** https://onlinejudge.org/external/5/507.pdf */
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
            int n;
            std::cin >> n;
            vi stops(n - 1);
            loop(n - 1, [&stops](int i) { std::cin >> stops[i]; });
            
        }
    }
}