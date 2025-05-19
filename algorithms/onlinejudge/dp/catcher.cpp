/*
    Longest Decreasing Subsequence (LDS) - Bottom-Up DP Approach

    Overview:
    ----------
    - We treat each element as the potential end of a decreasing subsequence.
    - For each element a[i], we check all previous elements a[j] (j < i).
    - If a[j] > a[i], we can extend the decreasing subsequence ending at a[j] to include a[i].
    - We keep track of the maximum such extension to compute LDS(i), the length of the longest decreasing subsequence ending at i.

    State:
    -------
    - dp[i] = length of the longest decreasing subsequence ending at a[i]
    - parent[i] = index of the previous element in the LDS path ending at i (for reconstruction)

    Recurrence:
    -----------
    dp[i] = 1 + max(dp[j]) over all j < i such that a[j] > a[i]
           ^   ^
           |   |
           |   longest LDS ending at j that a[i] can follow
           |
           the element itself contributes at least length 1

    Initialization:
    ---------------
    - dp[i] = 1 for all i (every element can be a sequence of length 1)
    - parent[i] = -1 (initially no predecessors)

    Time Complexity:
    ----------------
    - O(n^2), due to nested loops comparing each pair (i, j)

    DAG Analogy:
    ------------
    - We can view this as a DAG where there's an edge j → i if a[j] > a[i].
    - dp[i] stores the longest path ending at node i.
    - This resembles doing DFS on a DAG, but implemented iteratively via DP.

    Path Reconstruction (optional):
    --------------------------------
    - Use the parent[] array to backtrack and retrieve the actual LDS path.
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




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::dp::catcher
{
    /** https://onlinejudge.org/external/2/231.pdf */
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

        int c = 1;
        bool is_first = true;
        while(true)
        {
            int t;
            vi targets;
            while(while_read(t) && t != -1)
              targets.push_back(t);
            if(targets.empty()) break;
             
            int s = (int)targets.size();
            vi dp = vi(s, 1);
            for(int i = 1; i < s; ++i)
              for(int j = i - 1; j >= 0; --j)
                if(targets[j] >= targets[i])
                  dp[i] = std::max(dp[i], 1 + dp[j]);
      
            if(!is_first) std::cout << std::endl;
            is_first = false;      
            int ans = *std::max_element(dp.begin(), dp.end());
            printf("Test #%d:\n  maximum possible interceptions: %d\n", c++, ans);
        }
    }
}