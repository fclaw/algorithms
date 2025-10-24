/*
───────────────────────────────────────────────────────────────
🧳 UVa 10111 Find the Winning Move, https://onlinejudge.org/external/101/10111.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ull = unsigned long long;
using Cell = std::pair<int, int>;
using v_cell = std::vector<Cell>;

constexpr char E = '$';
constexpr int SIZE = 4;
constexpr char X = 'x';
constexpr char O = 'o';
constexpr int Empty = '.';

enum Player {
  X_PLAYER,
  O_PLAYER
};

Player switch_player(Player player) {
  return player == X_PLAYER ? O_PLAYER : X_PLAYER;
}

// This struct will hold the board state for ONE player.
// You would have two of these: one for 'X' and one for 'O'.
struct PlayerBoard {
  std::array<uint32_t, SIZE> rows;
  std::array<uint32_t, SIZE> cols;
  uint32_t main_diag;
  uint32_t aux_diag;
    
  PlayerBoard() : rows{}, cols{}, main_diag(0), aux_diag(0) {}

  void place_piece(int r, int c) {
    // For row 'r', set the bit corresponding to the column 'c'.
    rows[r] |= (1u << c);
    // For column 'c', set the bit corresponding to the row 'r'.
    cols[c] |= (1u << r);
    if (r == c) {
      main_diag |= (1u << r);
    }
    if (r + c == SIZE - 1) {
      aux_diag |= (1u << r);
    }
  }

  bool has_won() const {
    // A full line is represented by a bitmask where all SIZE bits are set.
    // E.g., for SIZE=3, this is 0b111 = 7. ( (1u << 3) - 1 )
    const uint32_t WIN_MASK = (1u << SIZE) - 1;

    // Check rows and columns
    for(int i = 0; i < SIZE; ++i) {
      // Your popcount logic is great too, this is just another way.
      if(rows[i] == WIN_MASK || 
         cols[i] == WIN_MASK) {
        return true;
      }
    }
        
    // Check diagonals
    if(main_diag == WIN_MASK || 
       aux_diag == WIN_MASK) {
      return true;
    }
        
    return false;
  }

  // undo
  void remove_piece(int r, int c) {
    rows[r] ^= (1u << c);
    cols[c] ^= (1u << r);
    if(r == c) {
      main_diag ^= (1u << r);
    }
    if(r + c == SIZE - 1) {
      aux_diag ^= (1u << r);
    }
  }
};

using v_PlayerBoard = std::vector<PlayerBoard>;


bool can_win(uint32_t board, const v_cell& cells, Player curr_player, std::vector<PlayerBoard>& boards, bool& has_o_won) {

  for(auto& curr_cell : cells) {
    int r = curr_cell.first;
    int c = curr_cell.second;
    int p = r * SIZE + c;
    if(!(board & (1u << p))) { // If cell is empty
      PlayerBoard& player_board = boards[curr_player];
      uint32_t new_board = board | (1u << p);
      player_board.place_piece(r, c);

      // --- CHECK OUTCOME ---
      // Base Case 1: Did this move result in an immediate win?
      bool has_player_won = player_board.has_won();
      if(has_player_won) {
        player_board.remove_piece(r, c);
        if(curr_player == O_PLAYER) has_o_won = true;
        return true;
      }

      if(__builtin_popcount(new_board) < SIZE * SIZE) {
        Player next_player = switch_player(curr_player);
        if(!can_win(new_board, cells, next_player, boards, has_o_won)) {
          player_board.remove_piece(r, c); // BACKTRACK
          if(curr_player == O_PLAYER) has_o_won = true;
          return true;
        }
      }
      // --- BACKTRACK THE MOVE ---
      // Must undo the move before the next iteration of the for loop.
      player_board.remove_piece(r, c);
    }
  }

  return false;
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
          uint32_t initial_board = 0;
          v_cell start_cells;
          PlayerBoard x_board;
          PlayerBoard o_board;
          for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
              while_read(c);
              if(c == X) {
                int position = i * SIZE + j;
                initial_board |= (1u << position); 
                x_board.place_piece(i, j);
              } else if(c == O) {
                int position = i * SIZE + j;
                initial_board |= (1u << position); 
                o_board.place_piece(i, j);
              } else start_cells.push_back({i, j});
            }
          }      
 
          bool found_winning_move = false;
          for(const Cell& cell : start_cells) {
            v_PlayerBoard boards = {x_board, o_board};
            uint32_t board = initial_board;
            bool has_o_won = false;
            if(can_win(board, start_cells, X_PLAYER, boards, has_o_won)) {
              if(!has_o_won) {
                printf("(%d,%d)\n", cell.first, cell.second);
                found_winning_move = true;
                goto finished;
              }
            }
          }

          finished: if(!found_winning_move) printf("#####\n");
        }
    }
}