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
#include <sstream>
#include <string>
#include <unordered_map>




struct Boulder
{
    uint32_t d;
    bool is_one_time;
};


std::ostream& operator << 
  (std::ostream& out, const Boulder& b) 
  { return out << "{" << b.d << ", "  << b.is_one_time << "}"; }

typedef std::vector<Boulder> vb;
typedef std::vector<int> vi;



namespace algorithms::onlinejudge::greedy::dynamic_frog
{
    /** https://onlinejudge.org/external/111/11157.pdf */
    int tc, c = 1;
    uint32_t n, d;
    uint32_t backtrack(const vb& boulders, int i, uint32_t jump, vi& memo)
    {
        int s = boulders.size();
        if(i == s - 1)
        { return jump; }

        if(~memo[i]) 
          return memo[i];

        uint32_t min_jump = UINT32_MAX;
        for(int j = i + 1; j < s; ++j) {
          uint32_t curr_jump = boulders[j].d - boulders[i].d;
          if(boulders[j].is_one_time && j + 1 < s)
            jump = std::max(jump, boulders[j + 1].d - boulders[i].d);
          else jump = std::max(jump, curr_jump);
          min_jump = std::min(min_jump, backtrack(boulders, j, jump, memo));
        }
        return memo[i] = min_jump;
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

        std::cin >> tc;
        while(tc-- && while_read(n, d))
        {
            uint32_t s = n + 2;
            vb boulders(s);
            std::string token;
            boulders[n + 1] = {d, 0};
            // boulders[s - 1] = {2 * d, 0};
            for(uint32_t i = 1; i <= n; i++) {
              std::cin >> token;
              char type = token[0]; // 'B' or 'S'
              uint32_t bd = std::stoi(token.substr(2)); // Get the number after '-'
              boulders[i] = {bd, type == 'S'};
            }

            // dbg(boulders);
            vi memo(101, -1);
            printf("Case %d: %u\n", c++, backtrack(boulders, 0, 0, memo));
        }
    }
}