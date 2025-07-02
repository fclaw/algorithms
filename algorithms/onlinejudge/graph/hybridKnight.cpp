/*
───────────────────────────────────────────────────────────────
🧳 UVa 10477 The Hybrid Knight, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dijkstra.cpp"
#include "tools/w_graph.cpp"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cctype>




typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;

enum PieceType { Knight, MutantKnight, MutantPawn };

PieceType next(PieceType piece) 
{ return static_cast<PieceType>((static_cast<int>(piece) + 1) % 3); }


const int knight_dx[] = { -2, -1, 1, 2,  2,  1, -1, -2 };
const int knight_dy[] = { 1,  2, 2, 1, -1, -2, -2, -1 };

const int m_knight_dx[] = { -3, -1, 1, 3,  3,  1, -1, -3 };
const int m_knight_dy[] = { 1,  3, 3, 1, -1, -3, -3, -1 };

const int m_pawn_dx[] = { -1, 0, 1, 0 };
const int m_pawn_dy[] = { 0, 1, 0, -1 };

const int m_pawn_extra_dx[] = { -1, 1, 1, -1 };
const int m_pawn_extra_dy[] = { 1, 1, -1, -1 };


struct State {
    pii pos; // position
    PieceType type; // piece type
    int dist; // distance from the source
};


namespace algorithms::onlinejudge::graph::hybrid_knight
{
    /** https://onlinejudge.org/external/104/10477.pdf */
    int S, Q, t_cases = 1;
    bool in_board(int r, int c) { return r >= 0 && r < S && c >= 0 && c < S; }
    void do_bfs(
      pii sink,
      vvvi& dist, 
      std::queue<State>& queue) {
        while(!queue.empty()) {
            State state = queue.front(); queue.pop();
            pii pos = state.pos;
            int d = state.dist;
            PieceType type = state.type;
            if(pos == sink) { break; }

            if(type == Knight) {
              for(int n = 0; n < 8; ++n) {
                int nr = pos.first + knight_dx[n];
                int nc = pos.second + knight_dy[n];
                PieceType next_type = next(type);
                if(in_board(nr, nc) && !(~dist[nr][nc][next_type])) {
                  queue.push({{nr, nc}, next_type, d + 1});
                  dist[nr][nc][next_type] = d + 1; // Update distance
                }
              }
            } else if(type == MutantKnight) {
              for(int n = 0; n < 8; ++n) {
                int nr = pos.first + m_knight_dx[n];
                int nc = pos.second + m_knight_dy[n];
                PieceType next_type = next(type);
                if(in_board(nr, nc) && !(~dist[nr][nc][next_type])) {
                  queue.push({{nr, nc}, next_type, d + 1});
                  dist[nr][nc][next_type] = d + 1; // Update distance
                }
              }
            } else if(type == MutantPawn) {
              PieceType next_type = next(type);
              bool is_extra = false; // Flag to check if an extra move is made
              for(int n = 0; n < 4; ++n) {
                int nr = pos.first + m_pawn_extra_dx[n];
                int nc = pos.second + m_pawn_extra_dy[n];
                pii n_sink = {nr, nc};
                if(in_board(nr, nc) && 
                   n_sink == sink) {
                  queue.push({{nr, nc}, next_type, d + 1});
                  dist[nr][nc][next_type] = d + 1; // Update distance
                  is_extra = true; // Mark as extra move
                  break; // Only one extra move is allowed
                }
              }
              if(!is_extra) { // If no extra move was made
                for(int n = 0; n < 4; ++n) {
                  int nr = pos.first + m_pawn_dx[n];
                  int nc = pos.second + m_pawn_dy[n];
                  if(in_board(nr, nc) && !(~dist[nr][nc][next_type])) {
                    queue.push({{nr, nc}, next_type, d + 1});
                    dist[nr][nc][next_type] = d + 1; // Update distance
                  }
                }
              }
            }
        }
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        while(while_read(S, Q) && S) {
          printf("Set %d:\n", t_cases++);
          while(Q--) {
            int idx_source, idx_sink;
            while_read(idx_source, idx_sink);
            --idx_source; --idx_sink; // Convert to 0-based index
            pii source, sink;
            source.first = idx_source / S;
            source.second = idx_source % S;
            sink.first = idx_sink / S;
            sink.second = idx_sink % S;
            
            int min_moves = std::numeric_limits<int>::max();
            for(int i = 0; i < 3; ++i) {
              PieceType piece = static_cast<PieceType>(i);
              vvvi dist(S, vvi(S, vi(3, -1))); // 3 for each piece type
              dist[source.first][source.second][piece] = 0; // Starting point
              std::queue<State> queue;
              queue.push({source, piece, 0});
              do_bfs(sink, dist, queue);
              for(int p = 0; p < 3; ++p) {
                PieceType piece = static_cast<PieceType>(p);
                int moves = dist[sink.first][sink.second][piece];
                if(~moves) min_moves = std::min(min_moves, moves);
              }
            }
            std::cout << min_moves << std::endl;  
          }
        }
    }
}