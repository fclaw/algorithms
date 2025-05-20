/*
 * UVa 437 - The Tower of Babylon
 *
 * Problem Summary:
 *   Given N blocks, each with 3 dimensions (w, l, h), and the ability to rotate
 *   each block into 3 different orientations, find the tallest possible tower that
 *   can be built by stacking blocks. A block can be placed on top of another only if
 *   both its width and length are strictly smaller.
 *
 * Approach (LIS-style DP on 3D blocks):
 *   1. For each block, generate all 3 orientations (w < l assumed for stacking).
 *      We generate all 3! = 6 permutations to cover all orientations.
 *
 *   2. Sort all block orientations in ascending order of (width, then length).
 *      This allows us to apply the Longest Increasing Subsequence (LIS) technique
 *      with height accumulation based on width and length constraints.
 *
 *   3. Use DP where:
 *        - dp[i] = maximum tower height ending with block i on top
 *        - dp[i] = max(dp[j] + h[i]) for all j < i where block[j] fits below block[i]
 *
 *   4. The result is the maximum value in the dp array.
 *
 * Time Complexity: O(N²) where N is the number of generated orientations (≈ 3 × input blocks)
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
#include <string>
#include <sstream>





struct Block
{
    int w;
    int l;
    int h;
};

std::ostream& operator << 
  (std::ostream& out, const Block& b) 
  { return out << "{" << b.w << ", "  << b.l << ", " << b.h << "}"; }

bool operator < (const Block& bl, const Block& br) { return bl.w > br.w || (bl.w == br.w && bl.l > br.l); }

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Block> vblock;


namespace algorithms::onlinejudge::dp::tower_of_babylon
{
    /** https://onlinejudge.org/external/1/111.pdf, can be modeled as LIS */
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
        
        int n, c = 1;
        while(while_read(n) && n)
        {
            vblock blocks;
            int w, l, h;
            loop(n, [&blocks, &w, &l, &h](int i) 
                    { std::cin >> w >> l >> h;
                      vi block = {w, l, h};
                      std::sort(block.begin(), block.end());
                      do { blocks.push_back({block[0], block[1], block[2]}); }
                      while(std::next_permutation(block.begin(), block.end())); }
            );

            std::sort(blocks.begin(), blocks.end());

            int s = (int)blocks.size();
            vi dp(s);
            for(int i = 0; i < s; ++i)
              dp[i] = blocks[i].h; 

            int max_height = INT32_MIN;
            for(int i = 1; i < s; ++i)
            {
                for(int j = i - 1; j >= 0; --j)
                  if(blocks[j].w > blocks[i].w && 
                    blocks[j].l > blocks[i].l)
                    dp[i] = std::max(dp[i], blocks[i].h + dp[j]);
                max_height = std::max(max_height, dp[i]);
            }
            printf("Case %d: maximum height = %d\n", c++, max_height);
        }
    }
}