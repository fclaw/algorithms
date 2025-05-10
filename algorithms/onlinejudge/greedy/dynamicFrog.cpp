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
    bool is_one_time_usage;
};


std::ostream& operator << 
  (std::ostream& out, const Boulder& b) 
  { return out << "{" << b.d << ", "  << b.is_one_time_usage << "}"; }

typedef std::vector<Boulder> vb;
typedef std::vector<uint32_t> vi;
typedef std::unordered_map<int, std::unordered_map<uint64_t, uint32_t>> mimii;



namespace algorithms::onlinejudge::greedy::dynamic_frog
{
    /** https://onlinejudge.org/external/111/11157.pdf */
    uint32_t backtrack(const vb& boulders, int i, vi& jumps, uint64_t used, mimii& memo)
    {
        int s = boulders.size();
        if(i == s)
        { return *std::max_element(jumps.begin(), jumps.end()); }

        if(memo.count(i) && 
           memo[i].count(used)) 
          return memo[i][used];

        uint32_t min_jump = UINT32_MAX;
        for(int j = i; j < s; j++) {
          uint32_t jump = boulders[j].d - boulders[i - 1].d;
          jumps.push_back(jump);
          if(boulders[j].is_one_time_usage && 
             !(used & (1LL << (s - j - 1))))
            min_jump = std::min(min_jump, backtrack(boulders, j + 1, jumps, used | (1LL << j), memo));
          else if(!boulders[j].is_one_time_usage)
            min_jump = std::min(min_jump, backtrack(boulders, j + 1, jumps, used, memo));
          jumps.pop_back();
        } 
        return memo[i][used] = min_jump;
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

        int tc, c = 1;
        std::cin >> tc;
        while(tc--)
        {
            uint32_t n, d;
            while_read(n, d);
            uint32_t s = 2 * n + 3;
            vb boulders(s);
            std::string token;
            boulders[n + 1] = {d, 0};
            boulders[s - 1] = {2 * d, 0};
            for(uint32_t i = 1; i <= n; i++) {
              std::cin >> token;
              char type = token[0]; // 'B' or 'S'
              uint32_t bd = std::stoi(token.substr(2)); // Get the number after '-'
              boulders[i] = {bd, type == 'S'};
              boulders[s - i - 1] = {2 * d - bd, type == 'S'};
            }

            vi jumps;
            mimii memo;
            printf("Case %d: %u\n", c++, backtrack(boulders, 1, jumps, 0, memo));
        }
    }
}