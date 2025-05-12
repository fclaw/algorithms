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
typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;
typedef std::vector<vpii> vvpii;
typedef std::vector<vvpii> vvvpii;

const pii def = {INT32_MAX, INT32_MAX};


namespace algorithms::onlinejudge::greedy::ferry_loading
{
    /** https://onlinejudge.org/external/104/10440.pdf */
    int cap, t, n;
    pii backtrack(const vi& cars, int i, int curr_t, int load, vvvpii& memo)
    {
         if(i == n) { return {curr_t + t, 1}; }

         pii& res = memo[i][load][curr_t];
         if (res != def) return res;

         // cars haven't arrived yet, the ferry have to wait for the first to be available
         if(cars[i] > curr_t && !load) return backtrack(cars, i, cars[i], load, memo);

         pii best = def;
         // take on one car and wait for others
         if(load < cap) best = backtrack(cars, i + 1, std::max(curr_t, cars[i]), load + 1, memo);

         // cross with a partial load
         if(load > 0 && load <= cap) {
            pii ferry = backtrack(cars, i, i == n ? curr_t + t : curr_t + 2 * t, 0, memo); 
            ++ferry.second;
            best = std::min(best, ferry);
         }

         return res = best;
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
            int max_time = 10000 * 100 + 100; // max cars × max latest arrival + return
            loop(n, [&cars](int i) { std::cin >> cars[i]; } );
            vvvpii memo(n + 1, vvpii(cap + 1, vpii(max_time, def)));
            pii ans = backtrack(cars, 0, 0, 0, memo);
            std::cout << ans.first << " " << ans.second << std::endl;
        }
    }
}