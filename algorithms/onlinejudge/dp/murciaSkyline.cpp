/*
 * DP Solution for UVa 11790 - Murcia’s Skyline
 *
 * Problem:
 * Given n buildings, each with a height h[i] and weight w[i],
 * find the maximum total weight for:
 *   - an increasing sequence of building heights (strictly increasing),
 *   - a decreasing sequence of building heights (strictly decreasing).
 *
 * Approach:
 * Dynamic Programming (similar to Weighted LIS):
 *
 * 1. For each building `i`, initialize:
 *    - dp_incr[i] = w[i]: the max weight of an increasing subsequence ending at i.
 *    - dp_decr[i] = w[i]: the max weight of a decreasing subsequence ending at i.
 *
 * 2. For each building `i`, look back at all buildings `j` before `i`:
 *    - If h[j] < h[i]: we can extend an increasing sequence.
 *         dp_incr[i] = max(dp_incr[i], dp_incr[j] + w[i])
 *
 *    - If h[j] > h[i]: we can extend a decreasing sequence.
 *         dp_decr[i] = max(dp_decr[i], dp_decr[j] + w[i])
 *
 * 3. After processing all buildings:
 *    - max_incr = maximum value in dp_incr → weight of best increasing skyline.
 *    - max_decr = maximum value in dp_decr → weight of best decreasing skyline.
 *
 * 4. Report the result by comparing both:
 *    - If max_incr >= max_decr: output "Increasing (max_incr). Decreasing (max_decr)."
 *    - Else: output "Decreasing (max_decr). Increasing (max_incr)."
 *
 * Complexity: O(n^2), where n is the number of buildings (acceptable for n ≤ 1000).
 */

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




struct Building
{
    int h;
    int w;
};


std::ostream& operator << 
  (std::ostream& out, const Building& b) 
  { return out << "{" << b.h << ", " << b.w << "}"; }

typedef std::vector<int> vi;
typedef std::vector<Building> vb;


namespace algorithms::onlinejudge::dp::skyline
{
    /** https://onlinejudge.org/external/117/11790.pdf */
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

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            int n;
            std::cin >> n;
            vb buildings(n);
            loop(n, [&buildings](int i) { std::cin >> buildings[i].h; });
            loop(n, [&buildings](int i) { std::cin >> buildings[i].w; });

            vi dp_incr(n);
            vi dp_decr(n);
            for(int i = 0; i < n; ++i) {
              dp_decr[i] = buildings[i].w;
              dp_incr[i] = buildings[i].w;
            }

            for(int i = 0; i < n; ++i)
              for(int j = i - 1; j >= 0; --j)
                if(buildings[j].h < buildings[i].h)
                  dp_incr[i] = std::max(dp_incr[i], buildings[i].w + dp_incr[j]);
                else if(buildings[j].h > buildings[i].h)
                  dp_decr[i] = std::max(dp_decr[i], buildings[i].w + dp_decr[j]);
            
            int max_incr = *std::max_element(dp_incr.begin(), dp_incr.end()); 
            int max_decr = *std::max_element(dp_decr.begin(), dp_decr.end());
            printf("Case %d. ", c++);
            max_incr >= max_decr ?
              printf("Increasing (%d). Decreasing (%d).\n", max_incr, max_decr) : 
              printf("Decreasing (%d). Increasing (%d).\n", max_decr, max_incr);
        }
    }
}