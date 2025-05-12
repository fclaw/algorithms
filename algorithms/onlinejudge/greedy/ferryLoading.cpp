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
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;


namespace algorithms::onlinejudge::greedy::ferry_loading
{
    /** https://onlinejudge.org/external/104/10440.pdf */
    int cap, t, n;
    int backtrack(const vi& cars, int i, int curr_t, int load, vvvi& memo)
    {
         int trip = curr_t / (2 * t);
         if (trip >= (int)memo[0][0].size())
           return INT32_MAX;

         int& res = memo[i][load][trip];
         if (~res) return res;

         if(i == (int)cars.size())
         {  return curr_t + t; }

         if(cars[i] > curr_t) return backtrack(cars, i, cars[i], load, memo);
         if(load == cap) return backtrack(cars, i, curr_t + 2 * t, 0, memo);
         res = backtrack(cars, i + 1, curr_t, load + 1, memo);
         if(load > 0) res = std::min(res, backtrack(cars, i + 1, curr_t + 2 * t, 0, memo));
         return res;
    }
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
            while_read(cap, t, n);
            vi cars(n);
            int max_trips = 2 * n + 1; // conservative upper bound
            loop(n, [&cars](int i) { std::cin >> cars[i]; } );
            vvvi memo(n + 1, vvi(cap + 1, vi(max_trips, -1)));
            std::cout << backtrack(cars, 0, 0, 0, memo) << std::endl;
        }
    }
}