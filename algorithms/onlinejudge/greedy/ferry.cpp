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




typedef std::vector<int> vi;



namespace algorithms::onlinejudge::greedy::ferry
{
    /** https://onlinejudge.org/external/104/10440.pdf */
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
            int cap, t, n;
            while_read(cap, t, n);
            --cap;
            vi cars(n);
            loop(n, [&cars](int i) { std::cin >> cars[i]; } );
        }
    }
}