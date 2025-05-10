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




typedef long long ll;



namespace algorithms::onlinejudge::greedy::bit_mask
{
    /** https://onlinejudge.org/external/107/10718.pdf */
    const uint32_t M = 32;
    ll n, l, u;
    void backtrack(ll base, int msb_base, ll mask, ll& max_or, ll& max_n, std::unordered_map<ll, ll>& memo)
    {
         if(memo.count(mask)) return;
         
         memo[mask] = base;
         
         if(base >= l && base <= u) {
           if(max_or < (n | base))
           { max_or = (n | base); max_n = base; }
           else if(max_or == (n | base)) 
           { max_n = std::min(max_n, base); }
         }

         for(int i = msb_base; i >= 0; --i)
           if((base & (1U << i)) && !(mask & (1LL << i)))
             backtrack(base & ~(1U << i), msb_base - 1, mask | (1LL << i), max_or, max_n, memo);
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

        while(while_read(n, l, u))
        {
            // Calculate the most significant bit for n and u
            uint32_t msb_n = M - __builtin_clz(n);
            uint32_t msb_u = M - __builtin_clz(u);
            int msb = std::min(M, std::max(msb_n, msb_u));
            uint32_t max = (1LL << msb) - 1;
            uint32_t base = max ^ n;
            int msb_base = M - __builtin_clz(base);

            std::unordered_set<int> used;
            int i = 0;
            while(base < l && i < (int)M)
              if(!(base & (1 << i))) {
                used.insert(i);
                base |= (1U << (i++));
              }
              else ++i;

            dbg(l, base);
             
            // int j = msb_base - 1;
            // while(base > u ) base &= ~(1U << (j--));

            // dbg(base, l, msb_base);

            // 11000011001010100101101001000111
            // 00111100110101011010010110111000
            // 11111111111111111111111111111111

            // 10111100110101011010010110111000
            

            // dbg(base, l, base >= l, base <= u);

            // ll max_or = 0;
            // ll max_n = 0;
            // std::unordered_map<ll, ll> memo;
            // backtrack(base, msb_base, 0, max_or, max_n, memo);
            // std::cout << max_n << std::endl;
        }
    }
}