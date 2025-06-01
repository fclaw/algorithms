/*
───────────────────────────────────────────────────────────────
🧳 UVa 1261 String popping, rt: 0.130s
───────────────────────────────────────────────────────────────
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
typedef std::vector<bool> vb;
typedef std::pair<std::string, vi> psvi;


psvi compressAB(const std::string& s) 
{
    std::string pattern;
    vi freq;

    char current = s[0];
    int count = 1;

    for (size_t i = 1; i < s.size(); ++i)
      if(s[i] == current) ++count;
      else {
       pattern += current;
       freq.push_back(count);
       current = s[i];
       count = 1;
      }

    // Push the last run
    pattern += current;
    freq.push_back(count);

    return {pattern, freq};
}


namespace algorithms::onlinejudge::dp::string_popping
{
    /** https://onlinejudge.org/external/12/1261.pdf */
    int tc;
    bool backtrack(const std::string& str, int mask, const vi& freq, vi& memo)
    {
        int s = (int)str.size();
        if(__builtin_popcount(mask) == s) // exhausted all symbols
          return true;

        if(~memo[mask]) return memo[mask];

        bool can_popped = false;
        for(int i = 0; i < s; ++i)
          if(!(mask & (1 << i))) {

            int cnt = freq[i];
            int new_mask = mask | (1 << i);

            // try finding the fist relevant symbol to the left
            int l_idx = i;
            while(--l_idx >= 0 && (mask & (1 << l_idx)));
            if(l_idx >= 0 && 
               !(mask & (1 << l_idx)) &&
               str[l_idx] == str[i]) {
              cnt += freq[l_idx];
              new_mask |= (1 << l_idx);
            }
            // do the same in the right direction
            int r_idx = i;
            while(++r_idx < s && (mask & (1 << r_idx)));
            if(r_idx < s && 
               !(mask & (1 << r_idx)) &&
               str[r_idx] == str[i]) {
              cnt += freq[r_idx];
              new_mask |= (1 << r_idx);
            }

            if(cnt >= 2) can_popped |= backtrack(str, new_mask, freq, memo);
          }
        memo[mask] = (int)can_popped;  
        return can_popped;  
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
        
        while_read(tc);
        while(tc--)
        {
            std::string in;
            while_read(in);
            psvi p = compressAB(in);
            vi memo(1 << (int)p.first.size(), -1);
            printf("%d\n", backtrack(p.first, 0, p.second, memo));
        }
    }
}