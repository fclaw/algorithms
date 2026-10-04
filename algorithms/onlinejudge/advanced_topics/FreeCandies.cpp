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


int64_t get_basket_mask(const vvi& piles, int pile1_idx, int pile2_idx, int pile3_idx, int pile4_idx) {

    vi piles1(piles[0].begin(), piles[0].begin() + pile1_idx);
    vi piles2(piles[1].begin(), piles[1].begin() + pile2_idx);
    vi piles3(piles[2].begin(), piles[2].begin() + pile3_idx);
    vi piles4(piles[3].begin(), piles[3].begin() + pile4_idx);

    // Sort the vector
    sort(piles1.begin(), piles1.end());
    sort(piles2.begin(), piles2.end());
    sort(piles3.begin(), piles3.end());
    sort(piles4.begin(), piles4.end());

    piles1.erase(std::unique(piles1.begin(), piles1.end()), piles1.end());
    piles2.erase(std::unique(piles2.begin(), piles2.end()), piles2.end());
    piles3.erase(std::unique(piles3.begin(), piles3.end()), piles3.end());
    piles4.erase(std::unique(piles4.begin(), piles4.end()), piles4.end());


    int64_t mask = 0;
    for(int i = 0; i < pile1_idx; ++i) {
      for(int j = 0; j < pile2_idx; ++j) {
        for(int k = 0; k < pile3_idx; ++k) {
          for(int l = 0; l < pile4_idx; ++l) {
            if(piles1[i] == piles2[j] ||
               piles1[i] == piles3[k] ||
               piles1[i] == piles4[l] ||
               piles2[j] == piles3[k] ||
               piles2[j] == piles4[l] ||
               piles3[k] == piles4[l]) {
              continue; // Skip if any two candies are the same
            }
            mask |= (1 << piles1[i]) 
                 | (1 << piles2[j]) 
                 | (1 << piles3[k]) 
                 | (1 << piles4[l]);
            if(__builtin_popcountll(mask) >= 5) {
              return -1;
            }
          }
        }
      } 
    }

  return mask;
}

int dp(int pile1_idx, int pile2_idx, int pile3_idx, int pile4_idx, const vvi& piles, int64_t basket) {
  
    if(__builtin_popcountll(basket) >= 5) {
      return 0; // Invalid state, more than 4 unique candies
    }

   int max_pairs = 0;
   if(pile1_idx < (int)piles[0].size()) {
     vi pile = piles[0];
     bool is_in_basket = (basket & (1 << pile[pile1_idx])) != 0;
     if(is_in_basket) {
       // If the candy is already in the basket, we can form a pair
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx + 1, pile2_idx, pile3_idx, pile4_idx, piles, basket & ~(1 << pile[pile1_idx]))); // Remove the candy from the basket after forming a pair
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
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx, pile2_idx + 1, pile3_idx, pile4_idx, piles, basket & ~(1 << pile[pile2_idx])));
     } else {
       int64_t new_basket = basket | (1 << pile[pile2_idx]);
       max_pairs = std::max(max_pairs, dp(pile1_idx, pile2_idx + 1, pile3_idx, pile4_idx, piles, new_basket));
     }
   }
   if(pile3_idx < (int)piles[2].size()) {
     vi pile = piles[2];
     bool is_in_basket = (basket & (1 << pile[pile3_idx])) != 0;
     if(is_in_basket) {
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx, pile2_idx, pile3_idx + 1, pile4_idx, piles, basket & ~(1 << pile[pile3_idx])));
     } else {
       int64_t new_basket = basket | (1 << pile[pile3_idx]);
       max_pairs = std::max(max_pairs, dp(pile1_idx, pile2_idx, pile3_idx + 1, pile4_idx, piles, new_basket));
     }
   }
   if(pile4_idx < (int)piles[3].size()) {
     vi pile = piles[3];
     bool is_in_basket = (basket & (1 << pile[pile4_idx])) != 0;
     if(is_in_basket) {
       max_pairs = std::max(max_pairs, 1 + dp(pile1_idx, pile2_idx, pile3_idx, pile4_idx + 1, piles, basket & ~(1 << pile[pile4_idx])));
     } else {
       int64_t new_basket = basket | (1 << pile[pile4_idx]);
       max_pairs = std::max(max_pairs, dp(pile1_idx, pile2_idx, pile3_idx, pile4_idx + 1, piles, new_basket));
     }
   }

   return max_pairs;
}


int get_max_pairs_from_piles(const vvi& piles) {
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