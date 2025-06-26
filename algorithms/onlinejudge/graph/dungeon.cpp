/*
───────────────────────────────────────────────────────────────
🧳 UVa 532 Dungeon Master, rt: s
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
#include <queue>


// For 4-directional movement (up, right, down, left)
int diff_x[6]= {0,0,0,-1,0,1};
int diff_y[6]= {0,0,-1,0,1,0};
int diff_l[6]= {1,-1,0,0,0,0};

struct State 
{
    std::pair<int, int> pos;
    int time;
    int level;
};


constexpr int MAX = 31;
bool visited[MAX][MAX][MAX];
bool obstacle[MAX][MAX][MAX];


namespace algorithms::onlinejudge::graph::dungeon
{
    /** https://onlinejudge.org/external/5/532.pdf */
    int R, C, L;
    bool in_bounds(int l, int r, int c) { return l >= 0 && l < L && r >= 0 && r < R && c >= 0 && c < C; }
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
         
        while(while_read(L, R, C) && L && R && C) {
          std::memset(obstacle, false, sizeof obstacle);
          std::memset(visited, false, sizeof visited);
          int source_r, source_c, sink_r, sink_c, source_l, sink_l;
          for(int l = 0; l < L; ++l) {
            for(int r = 0; r < R; ++r)
              for(int c = 0; c < C; ++c) {
                char w;
                while_read(w);
                if(w == 'S') {
                  source_l = l;   
                  source_r = r;
                  source_c = c;
                } else if(w == 'E') {
                  sink_l = l;
                  sink_r = r;
                  sink_c = c;
                } else if(w == '#') {
                  obstacle[l][r][c] = true;
                }
            }
         }
          
          std::queue<State> queue;
          queue.push({{source_r, source_c}, 0, source_l});
          int min_time = -1;
          while(!queue.empty()) {
            State state = queue.front(); queue.pop();
            int r = state.pos.first;
            int c = state.pos.second;
            int l = state.level;
            if(l == sink_l && r == sink_r && c == sink_c) 
            { min_time = state.time; break; };
            for(int i = 0; i < 6; ++i) {
              int nl = l + diff_l[i];
              int nr = r + diff_x[i];
              int nc = c + diff_y[i];
              if(in_bounds(nl, nr, nc) && 
                 !visited[nl][nr][nc] && 
                 !obstacle[nl][nr][nc]) {
                visited[nl][nr][nc] = true;
                queue.push({{nr, nc}, state.time + 1, nl});
              }
            }
          }
          min_time != -1 ? printf("Escaped in %d minute(s).\n", min_time) : printf("Trapped!\n");
       }
    }
}