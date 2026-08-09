/*
───────────────────────────────────────────────────────────────
🧳 UVa 710 The Game, https://onlinejudge.org/external/7/710.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using ii = std::pair<int, int>;


int W, H;

enum Dir { NONE, DN, DE, DS, DW};

struct State
{
    int r;
    int c;
    Dir dir;
    int segs;
    // We want the priority queue to pop the state with the lowest number of segments
    bool operator < (const State& other) const {
      return segs > other.segs;
    }
};

const std::vector<std::pair<Dir, ii>> dirs4 = { {DN, {-1, 0}}, {DE, {0, 1}}, {DS, {1, 0}}, {DW, {0, -1}} };

void print_board(int W, int H, const vvi& board, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1) {
    std::cout << "\n--- Padded Board (Cols 0.." << W + 1 << ", Rows 0.." << H + 1 << ") ---\n";
    
    // Print column index header
    std::cout << "    ";
    for (int c = 0; c <= W + 1; ++c) {
        std::cout << c << (c >= 10 ? "" : " ");
    }
    std::cout << "\n";

    for (int r = 0; r <= H + 1; ++r) {
        // Print row index header
        std::cout << std::setw(2) << r << " | ";

        for (int c = 0; c <= W + 1; ++c) {
            // Highlight Start (S), Target (T), Obstacle (X), or Empty (.)
            if (c == x1 && r == y1) {
                std::cout << "S ";
            } else if (c == x2 && r == y2) {
                std::cout << "T ";
            } else if (board[r][c] == 1) {
                std::cout << "X ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "-----------------------------------------------\n\n";
}


int get_connected_segments(const ii& source, const ii& sink, const vvi& board) {
 
    // print_board(W, H, board, source.first, source.second, sink.first, sink.second);

    vvi curr_board = board;
    curr_board[source.second][source.first] = 0;
    curr_board[sink.second][sink.first] = 0;
    vvvi dist(H + 2, vvi(W + 2, vi(5, INT32_MAX)));
    std::priority_queue<State> queue;
    queue.push({source.second, source.first, NONE, 0});
    while(!queue.empty()) {
      auto state = queue.top(); queue.pop();
      if(state.r == sink.second && 
         state.c == sink.first) {
        return state.segs;
      }

      // Lazy deletion check for Dijkstra
      if (state.segs > dist[state.r][state.c][state.dir]) {
        continue;
      }

      for(auto p : dirs4) {
        Dir next_dir = p.first;
        ii tpl = p.second;
        int next_r = state.r + tpl.first;
        int next_c = state.c + tpl.second;
        auto inBoard = 
              [&](int r, int c) -> bool {
                return r >= 0 && 
                       r < H + 2 && 
                       c >= 0 && 
                       c < W + 2;
              };
        if(inBoard(next_r, next_c) && 
           !curr_board[state.r][state.c]) {
          int new_segs = state.segs;
          if(state.dir != next_dir) {
            new_segs++;
          }  
          if (new_segs < dist[next_r][next_c][next_dir]) {
            dist[next_r][next_c][next_dir] = new_segs;
            queue.push({next_r, next_c, next_dir, new_segs});
          }
        }
      }
    }

  return INT32_MAX;
}


namespace algorithms::onlinejudge::advanced_topics::the_game
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

        int t_case = 1;
        while(std::cin >> W >> H && (W && H)) {
          // Safely consume the ENTIRE rest of the "W H" line (including any trailing spaces and '\n')
          std::string dummy;
          std::getline(std::cin, dummy);
          vvi board(H + 2, vi(W + 2, 0)); 
          for(int h = 1; h <= H; ++h) {
            std::string str;
            std::getline(std::cin, str);
            for (int w = 1; w <= W; ++w) {
              if (w - 1 < (int)str.length() && str[w - 1] == 'X') {
                board[h][w] = 1; // Mark 'X' as blocked game piece
              }
            }
          }

          printf("Board #%d:\n", t_case++);
 
          int n = 1;
          ii source, sink;
          while(std::cin >> source >> sink && 
                source.first && 
                source.second && 
                sink.first && 
                sink.second) {
            // std::cin >> sink.second >> sink.first;
            int min_segs = get_connected_segments(source, sink, board);
            printf("Pair %d: %s\n", n++, min_segs == INT32_MAX ? "impossible." : (std::to_string(min_segs) + " segments.") .c_str());
          }
          std::cout << std::endl;
        }
    }
}