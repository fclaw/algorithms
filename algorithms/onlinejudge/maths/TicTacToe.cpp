/*
───────────────────────────────────────────────────────────────
🧳 UVa 10111 Find the Winning Move, https://onlinejudge.org/external/101/10111.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using Cell = std::pair<int, int>;
using v_cell = std::vector<Cell>;

constexpr char E = '$';
constexpr int SIZE = 4;
constexpr char X = 'x';
constexpr char O = 'o';

enum Player : uint32_t { EMPTY = 0, X_PLAYER = 1, O_PLAYER = 2 };

Player switch_player(Player player) {
  return player == X_PLAYER ? O_PLAYER : X_PLAYER;
}

void set_cell_value(uint32_t& board, int r, int c, Player p) {
    int pos = r * 4 + c;
    int start_bit = pos * 2;
    uint32_t player_value = static_cast<uint32_t>(p);
    uint32_t clear_mask = ~(3u << start_bit);
    board &= clear_mask;
    uint32_t set_mask = (player_value << start_bit);
    board |= set_mask;
}

uint32_t get_cell_value(uint32_t board, int r, int c) {
  int pos = r * SIZE + c;
  int start_bit = pos * 2;
  return (board >> start_bit) & 3;
}

/**
 * @brief Checks if a given player has won on the board.
 * 
 * Iterates through all 10 possible winning lines (4 rows, 4 columns, 2 diagonals)
 * to see if any are filled with the specified player's pieces.
 *
 * @param board The 32-bit integer representing the 4x4 board state.
 * @param player The player (X_PLAYER or O_PLAYER) to check for a win.
 * @return True if the player has won, false otherwise.
 */
bool has_player_won(uint32_t board, Player player) {
  // --- 1. Check Rows ---
  for(int r = 0; r < SIZE; ++r) {
    bool row_win = true;
    for(int c = 0; c < SIZE; ++c) {
      if(get_cell_value(board, r, c) != player) {
        row_win = false;
        break;
      }
    }
    if(row_win) return true;
  }

  // --- 2. Check Columns ---
  for(int c = 0; c < SIZE; ++c) {
    bool col_win = true;
    for(int r = 0; r < SIZE; ++r) {
      if(get_cell_value(board, r, c) != player) {
        col_win = false;
        break;
      }
    }
    if(col_win) return true;
  }

  // --- 3. Check Main Diagonal (top-left to bottom-right) ---
  bool main_diag_win = true;
  for(int i = 0; i < SIZE; ++i) {
    if(get_cell_value(board, i, i) != player) {
      main_diag_win = false;
      break;
    }
  }
  if(main_diag_win) return true;

  // --- 4. Check Anti-Diagonal (top-right to bottom-left) ---
  bool anti_diag_win = true;
  for(int i = 0; i < SIZE; ++i) {
    if(get_cell_value(board, i, SIZE - 1 - i) != player) {
      anti_diag_win = false;
      break;
    }
  }
  if(anti_diag_win) return true;

  // If no winning lines were found
  return false;
}

enum Outcome { WIN, LOSS, DRAW };

/**
 * @brief Creates a 1-bit-per-cell mask indicating occupied squares.
 *
 * @param board The 32-bit (2-bit-per-cell) board state.
 * @return A bitmask where the k-th bit is 1 if cell k is occupied, 0 otherwise.
 */
uint32_t get_occupied_mask(uint32_t board) {
    uint32_t occupied_mask = 0;

    for (int i = 0; i < SIZE * SIZE; ++i) {
        // Extract the 2-bit value for cell 'i'
        uint32_t cell_value = (board >> (i * 2)) & 3;

        // If the cell is not EMPTY (i.e., its value is non-zero)
        if (cell_value != EMPTY) {
            // Set the corresponding bit in the output mask.
            occupied_mask |= (1u << i);
        }
    }
    return occupied_mask;
}


Outcome can_win(uint32_t board, const v_cell& cells, Player current_player) {

   // --- Base Cases ---
    // Has the PREVIOUS player just made a winning move?
    // Player opponent = switch_player(current_player);
    if (has_player_won(board, current_player)) {
        // We start our turn in a state where we've already lost.
        return  WIN;
    }
    // Is the board full (and we already know no one won)?
    if (__builtin_popcount(get_occupied_mask(board)) == SIZE * SIZE) {
        return DRAW;
    }

    // --- Recursive Step: Explore moves ---
    bool can_force_draw = false;


  for(const Cell& cell : cells) {
    int r = cell.first;
    int c = cell.second;
    uint32_t new_board = board;
    uint32_t cp = get_cell_value(new_board, r, c);
    if(cp == static_cast<uint32_t>(EMPTY)) {
      set_cell_value(new_board, r, c, current_player);
      Outcome outcome = can_win(new_board, cells, switch_player(current_player));
      if(outcome == LOSS) {
          return WIN;
      } else if(outcome == DRAW) {
          can_force_draw = true;
      }
    }
  }


  // --- Final Conclusion for this State ---
    // If we finished the loop without finding a winning move...
    if (can_force_draw) {
        // ...but we found a move that leads to a draw, that's our best option.
        return DRAW;
    } else {
        // ...and we couldn't even force a draw, it means all our moves lead to a
        // win for the opponent. This is a losing position.
        return LOSS;
    }

}


namespace algorithms::onlinejudge::maths::tic_tac_toe
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

        char c;
        while(while_read(c) && c != E) {
          uint32_t board = 0;
          v_cell start_cells;
          for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
              while_read(c);
              if(c == X) {
                set_cell_value(board, i, j, X_PLAYER);
              } else if(c == O) {
                set_cell_value(board, i, j, O_PLAYER);
              } else start_cells.push_back({i, j});
            }
          }
 
          bool found_winning_move = false;
          for(const Cell& cell : start_cells) {
            int r = cell.first;
            int c = cell.second;
            uint32_t new_board = board;
            set_cell_value(new_board, r, c, X_PLAYER);
            Outcome outcome = can_win(new_board, start_cells, O_PLAYER);
            if(outcome == LOSS) {
              printf("(%d,%d)\n", r, c);
              found_winning_move = true;
              goto finished;
            }
          }

          finished: if(!found_winning_move) printf("#####\n");
        }
    }
}