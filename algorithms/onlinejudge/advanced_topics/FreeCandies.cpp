/*
───────────────────────────────────────────────────────────────
🧳 UVa 10118 Free Candies, https://onlinejudge.org/external/101/10118.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;


int cache[55][55][55][55]; // Cache for memoization, initialized to -1

int dp(int pile1_idx, int pile2_idx, int pile3_idx, int pile4_idx, const vvi& piles, int64_t basket) {
  
    if(__builtin_popcountll(basket) >= 5) {
      return 0; // Invalid state, more than 4 unique candies
    }

    if(~cache[pile1_idx][pile2_idx][pile3_idx][pile4_idx]) {
      return cache[pile1_idx][pile2_idx][pile3_idx][pile4_idx];
    }
     

   int max_pairs = 0;
   if(pile1_idx < (int)piles[0].size()) {
     vi pile = piles[0];
     bool is_in_basket = (basket & (1 << pile[pile1_idx])) != 0;
     if(is_in_basket) {
       // If the candy is already in the basket, we can form a pair
       int64_t new_basket = basket & ~(1 << pile[pile1_idx]); // Remove the candy from the basket after forming a pair
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx + 1, pile2_idx, pile3_idx, pile4_idx, piles, new_basket)); // Remove the candy from the basket after forming a pair
     } else {
       // If the candy is not in the basket, we can add it to the basket
       int64_t new_basket = basket | (1 << pile[pile1_idx]);
       max_pairs = std::max(max_pairs, dp(pile1_idx + 1, pile2_idx, pile3_idx, pile4_idx, piles, new_basket));
     }
     
   }
   if(pile2_idx < (int)piles[1].size()) {
     vi pile = piles[1];
     bool is_in_basket = (basket & (1 << pile[pile2_idx])) != 0;
     if(is_in_basket) {
       int64_t new_basket = basket & ~(1 << pile[pile2_idx]);
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx, pile2_idx + 1, pile3_idx, pile4_idx, piles, new_basket));
     } else {
       int64_t new_basket = basket | (1 << pile[pile2_idx]);
       max_pairs = std::max(max_pairs, dp(pile1_idx, pile2_idx + 1, pile3_idx, pile4_idx, piles, new_basket));
     }
   }
   if(pile3_idx < (int)piles[2].size()) {
     vi pile = piles[2];
     bool is_in_basket = (basket & (1 << pile[pile3_idx])) != 0;
     if(is_in_basket) {
       int64_t new_basket = basket & ~(1 << pile[pile3_idx]);
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx, pile2_idx, pile3_idx + 1, pile4_idx, piles, new_basket));
     } else {
       int64_t new_basket = basket | (1 << pile[pile3_idx]);
       max_pairs = std::max(max_pairs, dp(pile1_idx, pile2_idx, pile3_idx + 1, pile4_idx, piles, new_basket));
     }
   }
   if(pile4_idx < (int)piles[3].size()) {
     vi pile = piles[3];
     bool is_in_basket = (basket & (1 << pile[pile4_idx])) != 0;
     if(is_in_basket) {
       int64_t new_basket = basket & ~(1 << pile[pile4_idx]);
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx, pile2_idx, pile3_idx, pile4_idx + 1, piles, new_basket));
     } else {
       int64_t new_basket = basket | (1 << pile[pile4_idx]);
       max_pairs = std::max(max_pairs, dp(pile1_idx, pile2_idx, pile3_idx, pile4_idx + 1, piles, new_basket));
     }
   }

   return (cache[pile1_idx][pile2_idx][pile3_idx][pile4_idx] = max_pairs);
}


int get_max_pairs_from_piles(const vvi& piles) {
  std::memset(cache, -1, sizeof(cache)); // global cache for memoization, initialized to -1
  return dp(0, 0, 0, 0, piles, 0LL);
}

namespace algorithms::onlinejudge::advanced_topics::free_candies
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

        int pile_height;
        while (std::cin >> pile_height && 
               pile_height != 0) {
          vvi piles(4, vi(pile_height));
          for(int j = 0; j < pile_height; ++j) {
            for(int i = 0; i < 4; ++i) {
              std::cin >> piles[i][j];
              --piles[i][j]; // Convert to 0-based indexing
            }
          }
          printf("%d\n", get_max_pairs_from_piles(piles));
        }
    }
}