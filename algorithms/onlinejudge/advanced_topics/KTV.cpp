/*
───────────────────────────────────────────────────────────────
🧳 UVa 11218 KTV, https://onlinejudge.org/external/112/11218.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vii = std::vector<ii>;



namespace algorithms::onlinejudge::advanced_topics::ktv
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        int n, t_case = 1;
        while(std::cin >> n && n) {
          int a, b, c, s;
          vii groups(n);
          for(int i = 0; i < n; ++i) {
            std::cin >> a >> b >> c >> s;
            int mask = (1 << a) | (1 << b) | (1 << c);
            groups[i] = {mask, s};
          }

          int max_score = -1;
          for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
              for(int k = 0; k < n; ++k) {
                if(i != j && j != k && i != k) {
                  ii i_group = groups[i];
                  ii j_group = groups[j];
                  ii k_group = groups[k];
                  int all_9_mask = i_group.first | j_group.first | k_group.first;
                  int total_score = i_group.second + j_group.second + k_group.second;
                  if(__builtin_popcount(all_9_mask) == 9) {
                    max_score = std::max(max_score, total_score);
                  }
                }
              }
            }
          }

          printf("Case %d: %d\n", t_case++, max_score);
        }
    }
}