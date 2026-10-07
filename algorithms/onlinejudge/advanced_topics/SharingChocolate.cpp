/*
───────────────────────────────────────────────────────────────
🧳 UVa 1099 Sharing Chocolate, https://onlinejudge.org/external/10/1099.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



#define LSOne(S) ((S) & (-S))


int cache[101][101][1 << 15];


bool can_shared(int height, int length, const vi& shares, int mask, const vi& comb_shares_area) {
  
  // base case
  if(__builtin_popcount(mask) == 1) {
    int bit = LSOne(mask);
    int i = __builtin_ctz(bit);
    if(shares[i] == height * length) {
      return (cache[height][length][mask] = true);
    }
    return (cache[height][length][mask] = false);
  }

  if(~cache[height][length][mask]) {
    return cache[height][length][mask];
  }

  for (int A = (mask - 1) & mask; A > (mask ^ A); A = (A - 1) & mask) {
    int B = mask ^ A;

    // break along the horizontal line (height)
    for(int h = 1; h <= height; ++h) {
      int up_area = h * length;
      int down_area = (height - h) * length;
      if(comb_shares_area[A] == up_area && 
         comb_shares_area[B] == down_area) {
        if(can_shared(h, length, shares, A, comb_shares_area) &&
           can_shared(height - h, length, shares, B, comb_shares_area)) {
          return (cache[height][length][mask] = true);
        }
      }
      // along the vertical line
     for(int l = 1; l <= length; ++l) {
      int left_area = height * l;
      int right_area = height * (length - l);
      if(comb_shares_area[A] == left_area && 
         comb_shares_area[B] == right_area) {
        if(can_shared(height, l, shares, A, comb_shares_area) && 
           can_shared(height, length - l, shares, B, comb_shares_area)) {
          return (cache[height][length][mask] = true);
        }
      }
    }
  }
  }

  return false;
}


namespace algorithms::onlinejudge::advanced_topics::sharing_chocolate
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
        while(stdin_read(n) && n) {
          int height, length;
          stdin_read(height, length);
          vi shares(n);
          for(int i = 0; i < n; ++i) {
            std::cin >> shares[i];
          }
          vi comb_shares_area(1 << n);
          for(int mask = 0; mask < (1 << n); ++mask) {
            int size = 0;
            for(int i = 0; i < n; ++i) {
              if(mask & (1 << i)) {
                size += shares[i];
              }
            }
            comb_shares_area[mask] = size;
          }
          std::memset(cache, -1, sizeof cache);
          printf("Case %d: %s\n", t_case++, can_shared(height, length, shares, (1 << n) - 1, comb_shares_area) ? "Yes" : "No");
        }
    }
}