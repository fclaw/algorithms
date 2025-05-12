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
typedef std::vector<std::pair<int, int>> vpii;
typedef std::vector<vpii> vvpii;
typedef std::vector<vvpii> vvvpii;
typedef std::pair<int, int> pii;


namespace algorithms::onlinejudge::greedy::ferry_loading
{
    /** https://onlinejudge.org/external/104/10440.pdf */
    int cap, t, n;
    pii backtrack(const vi& cars, int i, int curr_t, int load, vvvpii& memo)
    {
         int trip = curr_t / (2 * t);
         if (trip >= (int)memo[0][0].size())
           return { INT32_MAX, INT32_MAX };

          pii& res = memo[i][load][trip];
         if (res.first != INT32_MAX && 
             res.second != INT32_MAX) 
           return res;

         if(i == (int)cars.size())
         {  return { curr_t + t, 1}; }

         if(cars[i] > curr_t) 
           return backtrack(cars, i, cars[i], load, memo);

         if(load == cap) {
           pii local_res = backtrack(cars, i, curr_t + 2 * t, 0, memo);
           if(local_res.second != INT32_MAX) 
             local_res.second += 1; // Count this trip
           return res = local_res;
         }

         
         pii take = backtrack(cars, i + 1, curr_t, load + 1, memo);
         pii depart = {INT32_MAX, INT32_MAX};
         if(load > 0) {
           depart = backtrack(cars, i + 1, curr_t + 2 * t, 0, memo);
           if(depart.second != INT32_MAX) 
             depart.second += 1;
         }

         // Choose the better (min total time), breaking ties by fewer trips
         if (depart.first < take.first || 
             (depart.first == take.first && 
              depart.second < take.second))
           res = depart;
         else res = take;
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
            vvvpii memo(n + 1, vvpii(cap + 1, vpii(max_trips, {INT32_MAX, INT32_MAX})));
            pii ans = backtrack(cars, 0, 0, 0, memo);
            std::cout << ans.first << " " <<  ans.second << std::endl;
        }
    }
}