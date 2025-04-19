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
    vi geTowers(int tower)
    {
        vi towers;
        for (int d = 0; d < N; d++)
          if(tower & (1 << d))
            towers.push_back(d + 1);
        return towers;
    }
    int getCoverage(int towers, int customers, const std::unordered_map<int, int>& areas)
    {
        int coverage = customers;
        for (auto& a : areas)
        {
            // Apply inclusion-exclusion to avoid double-counting shared customers.
            // Each entry in `areas` represents a group of customers covered by multiple towers.
            // If more than one tower from such a group is selected, we would be counting those
            // customers multiple times — once per tower.
            //
            // We calculate the overlap as the number of selected towers in the group.
            //
            // For every extra tower selected in the group (i.e., overlap - 1),
            // we subtract that many times the group's customer count from the total coverage.
            //
            // This ensures each group of shared customers is only counted once.
            int overlap = __builtin_popcount(towers & a.first);
            if (overlap >= 2) coverage -= a.second * (overlap - 1);
        }
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
            std::unordered_map<int, int> overlapped;
            std::cin >> C;
            for (int i = 0; i < C; i++) 
            {
                int t;  // Number of towers in this service area
                std::cin >> t;
                int mask = 0;  // Initialize the bitmask for the towers
                int tower;
                while(t--)
                  std::cin >> tower,
                  mask |= (1 << (tower - 1));
                int shared_customer;
                std::cin >> shared_customer;
                overlapped[mask] += shared_customer;
            }

            int towers = (1 << N);
            vi customers_sum(towers);
            for(int t = 1; t < towers; ++t)
            {
                int last_bit = __builtin_ctz(t); // rightmost set bit
                int prev_towers = t ^ (1 << last_bit);
                customers_sum[t] = customers_sum[prev_towers] + customers[last_bit];
            }

            int max_coverage = INT32_MIN;
            vi max_towers;
            for(int t = 0; t < towers; t++)
              if(__builtin_popcount(t) == K)
              {
                  vi curr_towers = geTowers(t);
                  int curr_coverage = getCoverage(t, customers_sum[t], overlapped);
                  if(max_coverage < curr_coverage)
                  {
                      max_towers = curr_towers;
                      max_coverage = curr_coverage;
                  }else if(max_coverage == curr_coverage)
                    max_towers = std::min(max_towers, curr_towers);
              }

            std::string s;
            for(int t : max_towers) s += std::to_string(t) + " ";
            s.pop_back();
            printf("Case Number  %d\nNumber of Customers: %d\nLocations recommended: %s\n\n", c++, max_coverage, s.c_str());
        }
    }
}