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

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Block> vblock;


namespace algorithms::onlinejudge::dp::tower_of_babylon
{
    /** https://onlinejudge.org/external/1/111.pdf, can be modeled as LIS */
    int backtrack(const vblock& blocks, int w, int l, std::unordered_set<int>& used, std::unordered_map<int, std::unordered_map<int, int>>& memo)
    {
         // base case
         if(used.size() == blocks.size())
           return 0;
        
         if(memo.count(w) && memo[w].count(l))
           return memo[w][l];

         int max_height = 0;
         for(int i = 0; i < (int)blocks.size(); ++i)
           if(!used.count(i) && 
              blocks[i].w < w &&
              blocks[i].l < l) {
             used.insert(i);
             int local_max_height = backtrack(blocks, blocks[i].w, blocks[i].l, used, memo);
             max_height = std::max(max_height, blocks[i].h + local_max_height);
             used.erase(i);
           }
         return memo[w][l] = max_height; 
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

            std::unordered_set<int> used;
            std::unordered_map<int, std::unordered_map<int, int>> memo;
            printf("Case %d: maximum height = %d\n", c++, backtrack(blocks, INT32_MAX, INT32_MAX, used, memo));
        }
    }
}