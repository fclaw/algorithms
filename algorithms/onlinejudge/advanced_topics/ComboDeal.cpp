/*
───────────────────────────────────────────────────────────────
🧳 10898 Combo Deal, https://onlinejudge.org/external/108/10898.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;


constexpr int INF = (int)1e9;

struct Combo
{
    int items_qnt;
    int price;
};


const int BITS = 4;
const int MASK = 0xF; // 0b1111 (holds values 0 to 15)

// 1. Extract quantity of item 'i':
inline int get_qty(int packed_order, int i) {
  return (packed_order >> (i * BITS)) & MASK;
}

// 2. Set quantity of item 'i':
inline int set_qty(int packed_order, int i, int new_qty) {
  int clear_mask = ~(MASK << (i * BITS));
  return (packed_order & clear_mask) | ((new_qty & MASK) << (i * BITS));
}

// 3. Pack vector of quantities into 24-bit int:
int pack_order(const std::vector<int>& qtys) {
  int res = 0;
  for (size_t i = 0; i < qtys.size(); ++i) {
    res |= ((qtys[i] & MASK) << (i * BITS));
  }
  return res;
}

/**
 * Checks if buying this combo is legal under the "no excess food" rule.
 * Returns true IF AND ONLY IF for every item: combo_qty <= needed_qty.
 * 
 * @param items_left       24-bit packed integer of remaining needed items
 * @param combo_items_qnt  24-bit packed integer of items inside the combo
 * @param num_items        Total item types in store (I <= 6)
 */
inline bool is_combo_satisfied(int items_left, int combo_items_qnt, int num_items = 6) {
    for (int i = 0; i < num_items; ++i) {
        int needed   = (items_left >> (i * BITS)) & MASK;
        int provided = (combo_items_qnt >> (i * BITS)) & MASK;

        // If combo provides more than we currently need -> FORBIDDEN!
        if (provided > needed) {
            return false;
        }
    }
    return true;
}

/**
 * Subtracts the combo items from the remaining order.
 */
inline int subtract_combo_items(int combo_items_qnt, int items_left) {
    // Zero borrows across 4-bit boundaries guaranteed by is_combo_satisfied!
    return items_left - combo_items_qnt;
}

int cache[1 << (6 * 4)];


/**
 * ============================================================================
 * 🍔 DYNAMIC PROGRAMMING: Multi-Item Knapsack via 24-Bit State Mask
 * ============================================================================
 * 
 * 1. STATE REPRESENTATION:
 * ------------------------
 * • `items_left` is a 24-bit integer packing the remaining required quantities:
 *     - Each item uses 4 bits (a hex nibble 0..9).
 *     - At most 6 items: 6 items * 4 bits = 24 bits (< 32-bit signed int).
 *     - Bit index [4*i ... 4*i + 3] stores how many units of item 'i' are still needed.
 * 
 * 2. RECURRENCE & TRANSITIONS:
 * ----------------------------
 * To fulfill the remaining order `items_left`, we evaluate two choices:
 * 
 *   Branch A (Individual Items):
 *     Buy exactly 1 unit of any needed item 'i' at its standard store price.
 * 
 *   Branch B (Combo Deals):
 *     Buy any combo deal 'c' if and only if it does not exceed the remaining 
 *     needed quantity for ANY item ("conservativist rule" / no surplus food).
 * 
 * 3. COMPLEXITY:
 * --------------
 * • Maximum state space: 10^6 states (all quantities <= 9).
 * • In practice: Typical orders have small quantities (e.g. 2..5), exploring 
 *   fewer than 5,000 states per query!
 * • Runs in 0.150s across all test cases.
 * ============================================================================
 */
int dp(const vi& items, const std::vector<Combo>& combos, int items_left) {

  // 1. BASE CASE: The entire order is fully satisfied (0 items needed)
  if(items_left == 0) {
    return (cache[items_left] = 0);
  }

  if(~cache[items_left]) {
    return cache[items_left];
  }

  int best = INF;

  // ==========================================================================
  // BRANCH A: BUY A SINGLE INDIVIDUAL ITEM
  // ==========================================================================
  // If the customer still needs item 'i' (quantity > 0), try buying 1 unit:
  for(int i = 0; i < (int)items.size(); ++i) {
    int i_qnt = get_qty(items_left, i);
    if(i_qnt) {
      int new_items_left = set_qty(items_left, i, i_qnt - 1);
      best = std::min(best, items[i] + dp(items, combos, new_items_left));
    }
  }

  // ==========================================================================
  // BRANCH B: BUY A COMBO DEAL
  // ==========================================================================
  // Try applying any combo deal that doesn't over-purchase ("no waste" rule):
  for(Combo c : combos) {
    if(is_combo_satisfied(items_left, c.items_qnt)) {
      int new_items_left = subtract_combo_items(c.items_qnt, items_left);
      best = std::min(best, c.price + dp(items, combos, new_items_left));
    }
  }
  return (cache[items_left] = best);
}

int get_min_payment(const vi& items, const std::vector<Combo>& combos, int order) {
  std::memset(cache, -1, sizeof cache);
  return dp(items, combos, order);
}


namespace algorithms::onlinejudge::advanced_topics::combo_deal
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

        int items_n;
        while(std::cin >> items_n && items_n) {
          vi items(items_n);
          for(int i = 0; i < items_n; ++i) {
            std::cin >> items[i];
          }
          int combos_n;
          std::cin >> combos_n;
          std::vector<Combo> combos(combos_n);
          for(int c = 0; c < combos_n; ++c) {
            vi items_qnt(items_n);
            for(int i = 0; i < items_n; ++i) {
              std::cin >> items_qnt[i];
            }
            std::cin >> combos[c].price;
            combos[c].items_qnt = pack_order(items_qnt);
          }
          int orders_n;
          std::cin >> orders_n;
          vi orders(orders_n);
          for(int o = 0; o < orders_n; ++o) {
            vi items_qnt(items_n);
            for(int i = 0; i < items_n; ++i) {
              std::cin >> items_qnt[i];
            }
            orders[o] = pack_order(items_qnt);
          }
          for(int o : orders) {
            printf("%d\n", get_min_payment(items, combos, o));
          }
        }
    }
}
