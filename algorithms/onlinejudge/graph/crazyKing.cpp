/*
───────────────────────────────────────────────────────────────
🧳 UVa 11352 Crazy King, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bfs.cpp"

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
#include <set>
#include <queue>
#include <cctype>




typedef std::pair<int, int> pii;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;

constexpr int MOVES = 8;

const int dx[MOVES] = { -2, -1, 1, 2,  2,  1, -1, -2 };
const int dy[MOVES] = {  1,  2, 2, 1, -1, -2, -2, -1 };

const int king_dx[MOVES] = { -1, -1, 0, 1, 1, 1, 0, -1};
const int king_dy[MOVES] = { 0, 1, 1, 1, 0, -1, -1, -1};

struct State 
{
    pii pos;
    int steps;
};


namespace algorithms::onlinejudge::graph::crazy_king
{
    /** https://onlinejudge.org/external/113/11352.pdf */
    int t_cases, M, N;
    bool in_bounds(int r, int c) { return r >= 0 && r < M && c >= 0 && c < N; }
    void fill_blocked(const std::vector<pii>& knights, vvb& blocked) {

      for(auto p : knights) {
        blocked[p.first][p.second] = true;
        for(int m = 0; m < MOVES; ++m) {
          int nr = p.first + dx[m];
          int nc = p.second + dy[m];
          if(in_bounds(nr, nc))
            blocked[nr][nc] = true;
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
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(M, N);
          std::cin.ignore();
          pii source, sink;
          std::vector<pii> knights;
          std::string s;
          loop(M, [&] (int i) {
            std::getline(std::cin, s);
            for(int j = 0; j < (int)s.size(); ++j) {
              if(std::isalpha(s[j])) {
                if(s[j] == 'A') {
                  source = {i, j}; 
                } else if(s[j] == 'B') {
                  sink = {i, j}; 
                } else {
                  knights.push_back({i, j});
                }
              }
            }
          });

          int min_steps = -1;
          vvb blocked(M, vb(N, false));
          fill_blocked(knights, blocked);
          vvb visited(M, vb(N, false));
          std::queue<State> queue;
          queue.push({source, 0});
          visited[source.first][source.second] = true;
          while(!queue.empty()) {
            State state = queue.front(); queue.pop();
            pii pos = state.pos;
            if(pos == sink) 
            { min_steps = state.steps; break; }
            for(int m = 0; m < MOVES; ++m) {
              int nr = pos.first + king_dx[m];
              int nc = pos.second + king_dy[m];
              if(in_bounds(nr, nc) && 
                 !visited[nr][nc] && 
                 (std::make_pair(nr, nc) == sink || !blocked[nr][nc])) {
                visited[nr][nc] = true;
                queue.push({{nr, nc}, state.steps + 1});
              }
            }
          }
          min_steps != -1 ? printf("Minimal possible length of a trip is %d\n", min_steps) : printf("King Peter, you can't go now!\n");
        }
    }
}