/*
───────────────────────────────────────────────────────────────
🧳 UVa 12463 Little Nephew, https://onlinejudge.org/external/124/12463.pdf, rt: s
───────────────────────────────────────────────────────────────
 * --- From Backtracking to a Closed-Form Formula ---
 *
 * 1.  THE INITIAL MODEL (BACKTRACKING):
 *     The problem of counting unique outfits can be modeled by exploring a decision tree.
 *     A backtracking function naturally implements this:
 *
 *     ull backtrack(clothing_slot) {
 *         if (all_slots_filled) return 1;
 *
 *         ull total = 0;
 *         for (each choice for this slot) {
 *             total += backtrack(next_slot);
 *         }
 *         return total;
 *     }
 *
 *     This function correctly but slowly explores every possible combination.
 *
 * 2.  ANALYZING THE RECURSION:
 *     Let's trace the number of calls. Let N_hat, N_shirt, etc., be the number
 *     of choices for each clothing item. The total number of `return 1` calls will be:
 *
 *     Total Ways = N_hat * (ways for remaining slots)
 *                = N_hat * N_shirt * (ways for remaining slots)
 *                = N_hat * N_shirt * N_trousers * ...
 *
 *     The nested loops of the recursion are algorithmically equivalent to multiplication.
 *
 * 3.  THE MATHEMATICAL PRINCIPLE (THE RULE OF PRODUCT):
 *     The structure of the backtracking search reveals that we are making a sequence
 *     of independent choices. Combinatorics provides a direct way to count this,
 *     known as the "Rule of Product".
 *
 *     If there are 'a' ways to make choice 1, 'b' ways for choice 2, 'c' ways for
 *     choice 3, and so on, the total number of combined ways is simply a * b * c * ...
 *
 * 4.  DERIVING THE CLOSED-FORM FORMULA:
 *     We identify the independent choices for a complete outfit:
 *     - Choice 1: Pick a hat (a ways)
 *     - Choice 2: Pick a t-shirt (b ways)
 *     - Choice 3: Pick trousers (c ways)
 *     - Choice 4: Pick a matching pair of shoes (d ways)
 *     - Choice 5: Pick a matching pair of socks (e ways)
 *
 *     Applying the Rule of Product gives the O(1) closed-form formula:
 *     
 *     Total Outfits = a * b * c * d * e
 *
 *     This final formula replaces the entire backtracking search, providing an
 *     instantaneous solution.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ull = unsigned long long;
using ll = long long;
using vi = std::vector<int>;
using arr = std::array<vi, 7>;

const int HAT_BITS = 4;
const int TSHIRT_BITS = 5;
const int TROUSERS_BITS = 4;
const int SHOE_BITS = 6;
const int SOCK_BITS = 5;


struct Outfit
{
  int hat;
  int t_shirt;
  int trousers;
  int left_part_of_shoes;
  int right_part_of_shoes;
  int left_part_of_socks;
  int right_part_of_socks;
  // Let the compiler generate all comparison operators (==, !=, <, <=, >, >=)
  auto operator<=>(const Outfit&) const = default;
  void set_clothing(int type, int colour) {
    switch(type) {
      case 0:
        hat = colour;
        break;
      case 1:
        t_shirt = colour;
        break;
      case 2:
        trousers = colour;
        break;
      case 3:
        left_part_of_shoes = colour;
        break;
      case 4:
        right_part_of_shoes = colour;
        break;
      case 5:
        left_part_of_socks = colour;
        break;
      case 6:
        right_part_of_socks = colour;
        break;
    }
  } 
};


/**
 * Packs an Outfit struct into a single long long.
 * This is a form of state compression.
 */
ll pack_outfit(const Outfit& o) {
    ll packed_state = 0;

    // We build the packed integer from right to left, field by field.
    
    // 1. Add hat (lowest bits)
    packed_state |= o.hat;

    // 2. Shift and add t_shirt
    packed_state <<= TSHIRT_BITS;
    packed_state |= o.t_shirt;

    // 3. Shift and add trousers
    packed_state <<= TROUSERS_BITS;
    packed_state |= o.trousers;
    
    // 4. Shift and add left shoe
    packed_state <<= SHOE_BITS;
    packed_state |= o.left_part_of_shoes;

    // ...and so on for the rest.
    packed_state <<= SHOE_BITS;
    packed_state |= o.right_part_of_shoes;
    
    packed_state <<= SOCK_BITS;
    packed_state |= o.left_part_of_socks;

    packed_state <<= SOCK_BITS;
    packed_state |= o.right_part_of_socks;

    return packed_state;
}

ull backtrack(int curr_clothing, Outfit& curr_outfit, const arr& wardrobe, std::set<Outfit>& setups, std::unordered_map<std::pair<int, ll>, ull>& memo) {
  
  if(curr_clothing == 7) {
    if(setups.find(curr_outfit) == setups.end()) {
      setups.insert(curr_outfit);
      return 1;
    } else return 0;
  }

  ll packed_state = pack_outfit(curr_outfit);
  if(memo.find({curr_clothing, packed_state}) != memo.end()) {
    return memo[{curr_clothing, packed_state}];
  }

  ull ways = 0;
  for(int i = 0; i < (int)wardrobe[curr_clothing].size(); i++) {
    curr_outfit.set_clothing(curr_clothing, wardrobe[curr_clothing][i]);
    ways += backtrack(curr_clothing + 1, curr_outfit, wardrobe, setups, memo);
    curr_outfit.set_clothing(curr_clothing, -1);
  }
  return memo[{curr_clothing, packed_state}] = ways;
}


namespace algorithms::onlinejudge::maths::little_nephew
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

        int a, b, c, d, e; 
        while(scanf("%d %d %d %d %d", &a, &b, &c, &d, &e) == 5 && 
              (a && b && c && d && e)) {
          arr wardrobe;
          vi hat;
          for(int j = 0; j < a; j++)
            hat.push_back(j);
          vi t_shirt;
          for(int j = 0; j < b; j++)
            t_shirt.push_back(j);
          vi trousers;
          for(int j = 0; j < c; j++)
            trousers.push_back(j);
          vi left_shoes;
          for(int j = 0; j < d; j++)
            left_shoes.push_back(j);
          vi right_shoes;
          for(int j = 0; j < d; j++)
            right_shoes.push_back(j);
          vi left_socks;
          for(int j = 0; j < e; j++)
            left_socks.push_back(j);
          vi right_socks;
          for(int j = 0; j < e; j++)
            right_socks.push_back(j);
          wardrobe[0] = hat;
          wardrobe[1] = t_shirt;
          wardrobe[2] = trousers;
          wardrobe[3] = left_shoes;
          wardrobe[4] = right_shoes;
          wardrobe[5] = left_socks;
          wardrobe[6] = right_socks;
          Outfit curr_outfit;
          std::set<Outfit> setups;
          std::unordered_map<std::pair<int, ll>, ull> memo;
          // printf("%llu\n", backtrack(0, curr_outfit, wardrobe, setups, memo));
          printf("%llu\n", (ull)a * (ull)b * (ull)c * (ull)d * (ull)d * (ull)e * (ull)e);
        }
    }
}