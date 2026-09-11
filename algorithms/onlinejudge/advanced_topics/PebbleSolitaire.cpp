/*
───────────────────────────────────────────────────────────────
🧳 10651 Pebble Solitaire, https://onlinejudge.org/external/106/10651.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




constexpr int SIZE = 12;


/**
 * Checks if the pebble at 'pos' can jump LEFT over 'pos - 1' into 'pos - 2'.
 * Pattern required: [pos - 2] is EMPTY (0), [pos - 1] has PEBBLE (1), [pos] has PEBBLE (1).
 */
bool can_left_move(int pos, int pebbles) {
    if (pos < 2) return false; // Not enough space to jump left
    
    bool has_c = (pebbles & (1 << pos)) != 0;       // Jumping pebble
    bool has_b = (pebbles & (1 << (pos - 1))) != 0; // Middle pebble (jumped over)
    bool empty_a = (pebbles & (1 << (pos - 2))) == 0; // Target cavity

    return has_c && has_b && empty_a;
}

/**
 * Checks if the pebble at 'pos' can jump RIGHT over 'pos + 1' into 'pos + 2'.
 * Pattern required: [pos] has PEBBLE (1), [pos + 1] has PEBBLE (1), [pos + 2] is EMPTY (0).
 */
bool can_right_move(int pos, int pebbles) {
    if (pos > 9) return false; // pos + 2 must be <= 11
    
    bool has_c = (pebbles & (1 << pos)) != 0;       // Jumping pebble
    bool has_b = (pebbles & (1 << (pos + 1))) != 0; // Middle pebble (jumped over)
    bool empty_a = (pebbles & (1 << (pos + 2))) == 0; // Target cavity

    return has_c && has_b && empty_a;
}

// ==========================================
// LEFT JUMP (pos -> pos - 2)
// ==========================================
void make_left_move(int pos, int& pebbles) {
    int mask = (1 << pos) | (1 << (pos - 1)) | (1 << (pos - 2));
    pebbles ^= mask; // Flips: 0 1 1 -> 1 0 0
}

void undo_left_move(int pos, int& pebbles) {
    int mask = (1 << pos) | (1 << (pos - 1)) | (1 << (pos - 2));
    pebbles ^= mask; // Self-inverse: Flips 1 0 0 -> 0 1 1 back!
}

// ==========================================
// RIGHT JUMP (pos -> pos + 2)
// ==========================================
void make_right_move(int pos, int& pebbles) {
    int mask = (1 << pos) | (1 << (pos + 1)) | (1 << (pos + 2));
    pebbles ^= mask; // Flips: 1 1 0 -> 0 0 1
}

void undo_right_move(int pos, int& pebbles) {
    int mask = (1 << pos) | (1 << (pos + 1)) | (1 << (pos + 2));
    pebbles ^= mask; // Self-inverse: Flips 0 0 1 -> 1 1 0 back!
}

/**
 * Returns true if no valid jump exists in either direction for any pebble.
 * (All remaining pebbles are completely isolated / solitary).
 */
bool are_all_pebbles_solitaire(int pebbles) {
    for (int pos = 0; pos < 12; ++pos) {
        if (can_left_move(pos, pebbles) || can_right_move(pos, pebbles)) {
            return false; // A move is still possible!
        }
    }
    return true; // No moves left! Game over.
}

void get_min_pebbles(int pebbles, int& min_pebbles_left) {
   
  if(are_all_pebbles_solitaire(pebbles)) {
    min_pebbles_left = std::min(min_pebbles_left, __builtin_popcount(pebbles));
    return;
   }
 
  for(int pos = 0; pos < SIZE; ++pos) {
    if(can_left_move(pos, pebbles)) {
      make_left_move(pos, pebbles);
      get_min_pebbles(pebbles, min_pebbles_left);
      undo_left_move(pos, pebbles); // backtrack
    }
    if(can_right_move(pos, pebbles)) {
      make_right_move(pos, pebbles);
      get_min_pebbles(pebbles, min_pebbles_left);
      undo_right_move(pos, pebbles); // backtrack
    }
  }
}


namespace algorithms::onlinejudge::advanced_topics::pebble_solitaire
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
        std::cin >> t_cases;
        while(t_cases--) {
          int pebbles = 0;
          std::string line;
          std::cin >> line;
          for(int i = 0; i < (int)line.size(); ++i) {
            if(line[i] == 'o') {
              pebbles |= (1 << i);
            }
          }
          int min_pebbles = SIZE;
          get_min_pebbles(pebbles, min_pebbles);
          printf("%d\n", min_pebbles);
        }
    }
}
