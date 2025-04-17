#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>





typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::zones
{
    /**  https://onlinejudge.org/external/10/1047.pdf, 
     * LA 3278, WorldFinals Shanghai 05, notice that
     * n ≤ 20 so that we can try all possible subsets of towers to be taken; then
     * apply inclusion-exclusion principle to avoid overcounting  */
    // N stands for planned towers. K - for actually built
    int N, K, c = 1;
    std::string geTowers(int tower)
    {
        std::string s;
        for (int d = 0; d < N; d++)
          if(tower & (1 << d))
          {
              s += ('0' + (d + 1));
              s += " ";
          }
        s.pop_back();
        return s;
    }
    int getCoverage(int towers, int customers, const std::unordered_map<int, int>& areas)
    {
        int coverage = customers;
        for(auto a : areas)
          if((a.first & towers) == a.first)
            coverage -= a.second;
        return coverage;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
       
        while(std::cin >> N >> K && N && K)
        {
            vi customers(N);
            for(int i = 0; i < N; i++)
              std::cin >> customers[i];

            int C;
            // common service areas
            std::unordered_map<int, int> cs_areas;
            std::cin >> C;
            for (int i = 0; i < C; i++) 
            {
                int t;  // Number of towers in this service area
                std::cin >> t;
                int mask = 0;  // Initialize the bitmask for the towers
                for (int j = 0; j < t; j++) 
                {
                    int tower;
                    std::cin >> tower;
                    // Set the corresponding bit in the bitmask
                    mask |= (1 << (tower - 1));  // Adjusting for 1-indexed tower IDs
                }
                std::cin >> cs_areas[mask];
            }

            int total_towers = (1 << N);
            vi customers_sum(total_towers);
            for(int towers = 1; towers < total_towers; ++towers)
            {
                int last_bit = __builtin_ctz(towers); // rightmost set bit
                int prev_towers = towers ^ (1 << last_bit);
                customers_sum[towers] = customers_sum[prev_towers] + customers[last_bit];
            }

            int max_coverage = INT32_MIN;
            int towers = 0;
            for(int t = 0; t < total_towers; t++)
              if(__builtin_popcount(t) == K);

            printf("Case Number %d\nNumber of Customers: %d\nLocations recommended: %s\n", c++, max_coverage, geTowers(towers).c_str());
        }
    }
}