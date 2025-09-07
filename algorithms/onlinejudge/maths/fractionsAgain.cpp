/*
───────────────────────────────────────────────────────────────
🧳 UVa 10976 Fractions Again?!, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vii = std::vector<ii>;



namespace algorithms::onlinejudge::maths::fractions_again
{
    /** https://onlinejudge.org/external/109/10976.pdf */
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

        int k;
        while(scanf("%d", &k) == 1) {
          vii pairs;
          for(int x = 2 * k; x > k; --x) {
            if(x * k % (x - k) == 0) {
              pairs.push_back({x, x * k / (x - k)});
            }
          }
          printf("%d\n", (int)pairs.size());
          for(auto it = pairs.rbegin(); it != pairs.rend(); ++it) {
            printf("1/%d = 1/%d + 1/%d\n", k, it->second, it->first);
          }
        } 
    }
}