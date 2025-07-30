 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 12379 Central Post Office, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>


namespace tree = algorithms::onlinejudge::graph::tools::tree;


namespace algorithms::onlinejudge::graph::central_post_office
{
    /** https://onlinejudge.org/external/123/12379.pdf */
    int t_cases, cities;
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
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(cities);
          tree::vvi roads(cities);
          for (int city = 0; city < cities; ++city) {
            int n;
            while_read(n);
            for(int i = 0; i < n; ++i) {
              int neigh;
              while_read(neigh);
              --neigh;
              roads[city].push_back(neigh);
            }
          }

          tree::Point point = tree::find_first_point(0, -1, roads);
          tree::Diameter diameter = tree::detect_diameter(point.idx, -1, roads);
          // The total time to traverse every road is derived from a key tree property.
          // To visit every edge in a tree and return to the start, each of the
          // (N-1) edges must be traversed twice (once down, once back up).
          // The total cost for such a full traversal would be 2 * (N-1).
          //
          // However, the mail truck does not need to return to its starting point.
          // It can start at one end of a path and finish at the other. To minimize
          // the total travel time, we want this one-way path to be as long as
          // possible, saving us the maximum number of return trips.
          // The longest possible one-way path in a tree is its diameter.
          //
          // Therefore, the optimal route is to traverse the diameter once, and
          // every other "side branch" edge twice. This is equivalent to taking the
          // full traversal cost (2 * (N-1)) and subtracting the saved return trips
          // along the diameter (diameter.length).
          int delivery_time = 2 * (cities - 1) - diameter.length;
          std::cout << delivery_time << std::endl;
        }  
    }
}