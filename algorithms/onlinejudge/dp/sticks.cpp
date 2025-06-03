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





typedef std::vector<int> vi;
typedef std::vector<vi> vvi;



namespace algorithms::onlinejudge::dp::sticks
{
    /** https://onlinejudge.org/external/100/10003.pdf */
    int length, n;
    // f(l, i, j) = sum of k from i to j l + min(f(cut[k], i, k), f(l - cut[k], k + 1, j))
    int min_cut(const vi& cuts, int l, int r, vvi& memo)
    {
        if(r - l <= 1) return 0;
        
        int& best = memo[l][r];
        if(~best) return best;

        int cost = cuts[r] - cuts[l];
        best = INT32_MAX;
        for(int k = l + 1; k < r; ++k)
          best = std::min(best, cost + min_cut(cuts, l, k, memo) + min_cut(cuts, k, r, memo));
        return best;
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
        
        while(while_read(length) && length)
        {
            while_read(n);
            vi cuts(n);
            loop(n, [&cuts](int i) { while_read(cuts[i]); });
            cuts.emplace(cuts.begin(), 0);
            cuts.push_back(length);
            int s = (int)cuts.size();
            vvi memo(s, vi(s, -1));
            printf("The minimum cutting is %d.\n", min_cut(cuts, 0, s - 1, memo));
        }
    }
}