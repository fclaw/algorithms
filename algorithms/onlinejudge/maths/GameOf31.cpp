/*
───────────────────────────────────────────────────────────────
🧳 UVa 10578 The Game of 31, https://onlinejudge.org/external/105/10578.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int NUM = 6;
constexpr int MAX = 4;
constexpr int TARGET = 31;

using vi = std::vector<uint32_t>;

enum Player { A, B };

Player switch_player(Player player) { return player == A ? B : A; }

std::string player_to_str(Player p) {
  if(p == A) return "A";
  else return "B";
}


bool clear_msb(uint32_t& number) {
  if(!number) return false;
  // --- Step 1: Find the position of the highest set bit ---
  // The most efficient way is to use a compiler builtin for "Count Leading Zeros".
  int num_leading_zeros = __builtin_clz(number);
  int highest_bit_pos = (sizeof(number) * 8 - 1) - num_leading_zeros;

  // --- Step 2: Create a mask and apply it ---
  // Create a mask with only that bit set (e.g., 00100000)
  uint32_t bit_to_clear = (1u << highest_bit_pos);
    
  // Apply the mask by XORing. Since XORing with 1 flips the bit.
  // Or equivalently, `number &= ~bit_to_clear;`
  number ^= bit_to_clear;
  return true;
}

void set_msb(uint32_t& number) {
  if(__builtin_popcount(number) == MAX) return;
  const int num_bits = sizeof(number) * 8;
  // Find the position of the highest set bit
  int num_leading_zeros = __builtin_clz(number);
  int highest_bit_pos = (num_bits - 1) - num_leading_zeros;
    
  // Calculate the position of the bit to the left (the next higher bit)
  int bit_to_set_pos = highest_bit_pos + 1;
  // Create a mask with only that bit turned on and apply it
  number |= (1u << bit_to_set_pos);
}


std::map<std::pair<int, vi>, bool> memo;

bool can_win(int sum, vi& deck, Player player) {

  // Check memo
  if (memo.count({sum, deck})) {
    return memo[{sum, deck}];
  }

  bool is_win_pos = false;
  for(int n = 1; n <= NUM; ++n) {
    if(!clear_msb(deck[n])) continue;
    player = switch_player(player);
    if(sum + n <= TARGET) 
      is_win_pos |= !can_win(sum + n, deck, player);
    set_msb(deck[n]);
  }

  return memo[{sum, deck}] = is_win_pos;
}


std::string make_answer(Player player, bool has_won) {
  if(has_won) return player_to_str(player);
  else return player_to_str(switch_player(player));
}

namespace algorithms::onlinejudge::maths::game_of_31
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

        std::string game;
        while(while_read(game)) {
          int start_sum = 0;
          Player player = A;
          vi deck(NUM + 1, (1u << MAX) - 1);
          for(auto c : game) {
            player = switch_player(player);
            int n = c - '0';
            start_sum += n;
            clear_msb(deck[n]);
          }
          bool can_player_win = can_win(start_sum, deck, player);
          printf("%s %s\n", game.c_str(), make_answer(player, can_player_win).c_str());
        }
    }
}