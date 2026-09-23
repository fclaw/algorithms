/*
───────────────────────────────────────────────────────────────
🧳 UVa 1231 ACORN, https://onlinejudge.org/external/12/1231.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


struct Tree
{
    int idx;
    vi acorns;

   friend std::ostream& operator<<(std::ostream& os, const Tree& t) {
        os << "Tree #" << t.idx << " (" << t.acorns.size() << " acorns): [";
        for (size_t i = 0; i < t.acorns.size(); ++i) {
            os << t.acorns[i] << (i + 1 < t.acorns.size() ? ", " : "");
        }
        os << "]";
        return os;
    }

};



int dp(int height, const std::vector<Tree>& trees, int flight_drop) {
  return 0;
}


// When the size of naive DP states are too large that causes the overall DP time complexity
// to be not-doable, think of another more efficient (but usually not obvious) way to represent
// the possible states. Using a good state representation is a potential major speed up for a
// DP solution. Remember that no programming contest problem is unsolvable, the problem
// author must have known a trick!!!
int get_maximum_acorns(const std::vector<Tree>& trees, int height, int flight_drop) {
   return dp(height, trees, flight_drop);
}

namespace algorithms::onlinejudge::advanced_topics::ACORN
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

        int t_cases, terminus;
        std::cin >> t_cases;
        while(t_cases--) {
          int trees_n, height, flight_drop;
          while_read(trees_n, height, flight_drop);
          std::vector<Tree> tress(trees_n);
          for(int t = 0; t < trees_n; ++t) {
            int acorns_n, h;
            Tree tree;
            tree.idx = t;
            tree.acorns = vi(height + 1);
            std::cin >> acorns_n;
            for(int a = 0; a < acorns_n; ++a) {
              std::cin >> h;
              tree.acorns[h]++;
            }
            tress[t] = tree;
          }
          printf("%d\n", get_maximum_acorns(tress, height, flight_drop));
        }
        std::cin >> terminus;
    }
}