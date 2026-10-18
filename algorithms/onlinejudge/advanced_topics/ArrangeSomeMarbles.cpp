/*
───────────────────────────────────────────────────────────────
🧳 UVa 11125 Arrange Some Marbles, https://onlinejudge.org/external/111/11125.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int BITS_COLOUR = 6; // up to 63
constexpr int BITS_SIZE   = 6; // up to 63
constexpr int BITS_MARBLE = 7; // up to 127 per marble type

constexpr uint64_t MASK_COLOUR = (1ULL << BITS_COLOUR) - 1;
constexpr uint64_t MASK_SIZE   = (1ULL << BITS_SIZE) - 1;
constexpr uint64_t MASK_MARBLE = (1ULL << BITS_MARBLE) - 1;



struct Block
{
    int size;
    int colour;
    bool operator != (const Block& o) const {
      return size != o.size &&
             colour != o.colour;
    }
};

bool has_all_marbles_used(const vi& marbles) {
  for(int i = 0; i < (int)marbles.size(); ++i) {
    if(marbles[i]) {
      return false;
    }
  }
  return true;
}


std::unordered_map<uint64_t, ll> cache;

uint64_t make_key(Block first, Block last, bool is_first_set, const vi& marbles) {
    uint64_t key = 0;
    int shift = 0;

    // 1. Pack is_first_set (1 bit)
    key |= (uint64_t(is_first_set ? 1 : 0) << shift);
    shift += 1;

    // IMPORTANT GUARD:
    // If first is not set yet, zero it out so uninitialized/irrelevant
    // values don't create duplicate entries in your DP cache!
    if (!is_first_set) {
        first.colour = 0;
        first.size = 0;
    }

    // 2. Pack first Block (6 bits colour + 6 bits size)
    key |= ((uint64_t(first.colour) & MASK_COLOUR) << shift);
    shift += BITS_COLOUR;
    key |= ((uint64_t(first.size) & MASK_SIZE) << shift);
    shift += BITS_SIZE;

    // 3. Pack last Block (6 bits colour + 6 bits size)
    key |= ((uint64_t(last.colour) & MASK_COLOUR) << shift);
    shift += BITS_COLOUR;
    key |= ((uint64_t(last.size) & MASK_SIZE) << shift);
    shift += BITS_SIZE;

    // 4. Pack marbles counts (each into 7 bits)
    for (int count : marbles) {
        key |= ((uint64_t(count) & MASK_MARBLE) << shift);
        shift += BITS_MARBLE;
    }

    return key;
}


/**
 * Problem: UVa 11125 - Arrange Some Marbles
 * Category: Circular Dynamic Programming / Backtracking with Global Memoization
 *
 * ============================================================================
 * THE CIRCULAR INVARIANT:
 * ============================================================================
 * Marbles are placed in contiguous same-color blocks of size 1, 2, or 3.
 * The arrangement forms a closed circle subject to two strict constraints:
 *   1. Adjacent blocks must have DIFFERENT colors.
 *   2. Adjacent blocks must have DIFFERENT sizes.
 *
 * Both constraints apply to:
 *   - Any two consecutive blocks placed in the sequence (last vs. curr).
 *   - The very first block and the very last block (first vs. last) to close the circle!
 *
 * ============================================================================
 * SEMANTIC HACK: Block::operator!=
 * ============================================================================
 * In this code, 'operator!=' is customized to represent ADJACENCY COMPATIBILITY:
 *     (A != B) is TRUE  <==>  A and B have different color AND different size!
 *
 * This allows two elegant checks:
 *   - 'last != curr': Can block 'curr' follow block 'last'?
 *   - 'first != last': Can the circle close validly between first and last?
 *
 * ============================================================================
 * STATE PARAMETERS:
 * ============================================================================
 * @param first        The very first block placed (anchors the start of the circle).
 * @param last         The most recently placed block (current head of the chain).
 * @param is_first_set Flag indicating whether the anchor 'first' has been chosen.
 * @param marbles      Vector storing the remaining counts for each marble color.
 * @return             Total number of valid circular arrangements from this state.
 * ============================================================================
 */
ll dfs(Block first, Block last, bool is_first_set, vi& marbles) {

  // ------------------------------------------------------------------------
  // 1. BASE CASE: All marbles have been placed
  // ------------------------------------------------------------------------
  // The chain is complete. Now we verify circular closure!
  // The very last block must be compatible with the very first block:
  // they must have DIFFERENT color AND DIFFERENT size (first != last).
  if(has_all_marbles_used(marbles)) {
     if(first != last) {
       return 1LL;
     } else {
       return 0LL;
     }
  }
 
  // ------------------------------------------------------------------------
  // 2. GLOBAL MEMOIZATION CHECK
  // ------------------------------------------------------------------------
  // 'make_key' packs {first, last, is_first_set, marbles} into a single 64-bit uint64_t.
  // The cache is global and persistent across test cases for instant O(1) hits!
  uint64_t key = make_key(first, last, is_first_set, marbles);
  if(auto it = cache.find(key); 
     it != cache.end()) {
    return it->second;
  }

  ll ways = 0LL;
  // ------------------------------------------------------------------------
  // 3. TRY PLACING ALL VALID NEXT BLOCKS
  // ------------------------------------------------------------------------
  // Iterate over all available marble colors
  for(int c = 0; c < (int)marbles.size(); ++c) {
    // A block can consist of 1, 2, or 3 contiguous marbles of color 'c'
    for(int size = 1; size <= 3; ++size) {
      if(size > marbles[c]) continue;  // Not enough marbles of color 'c'
      marbles[c] -= size; // Consume marbles for this block
      if(!is_first_set) { 
        // First block of the circle!
        // It serves as both the 'first' anchor and the current 'last' block.
        ways += dfs({size, c}, {size, c}, true, marbles);
      } else {
        Block curr = {size, c};
        // Check adjacency constraint:
        // 'last != curr' verifies that 'curr' differs in BOTH color and size from 'last'
        if(last != curr) {
          ways += dfs(first, curr, is_first_set, marbles);
        }
      }
      // Backtracking: restore marble count for the next branch
      marbles[c] += size;
    }
  }

  return (cache[key] = ways);
}


namespace algorithms::onlinejudge::advanced_topics::arrange_some_marbles
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

        int t_cases;
        stdin_read(t_cases);
        while(t_cases--) {
          int n, m;
          stdin_read(n);
          vi marbles;
          for(int i = 0; i < n; ++i) {
            stdin_read(m);
            if(m) {
              marbles.push_back(m);
            }
          }
          ll ways = 0LL;
          if(marbles.empty()) {
            ways = 1LL;
          } else if(marbles.size() == 1) {
             if(marbles.front() <= 3) {
              ways = 1LL;
            }
          } else {
            ways =  dfs({-1, -1}, {-1, -1}, false, marbles);
          }
          std::cout << ways << "\n";
        }
    }
}