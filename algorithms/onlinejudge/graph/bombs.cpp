/*
───────────────────────────────────────────────────────────────
🧳 UVa 10653 Bombs! NO they are Mines!!, rt: s
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
const std::vector<std::pair<int, int>> dirs_4 = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

constexpr int MAXN = 1000;

bool visited[MAXN][MAXN];
int dist[MAXN][MAXN];
bool mines[MAXN][MAXN];

namespace algorithms::onlinejudge::graph::bombs
{
    /** https://onlinejudge.org/external/106/10653.pdf */
    int R, C, B;
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
        

        while(while_read(R, C) && R && C) {

          memset(visited, false, sizeof(visited));
          memset(mines, false, sizeof(mines));
          while_read(B);
          loop(B, [&](int _) {
            int r, c, n;
            while_read(r, n);
            loop(n, [&](int _) {
              while_read(c);
              mines[r][c] = true;
            });
          });


          int source_r, source_c;
          while_read(source_r, source_c);
          int sink_r, sink_c;
          while_read(sink_r, sink_c);

          std::queue<std::pair<int, int>> q;
          memset(dist, -1, sizeof(dist));
          dist[source_r][source_c] = 0;
          q.push({source_r, source_c});
          visited[source_r][source_c] = true;
          while(!q.empty()) {
            auto p = q.front(); q.pop();
            int r = p.first;
            int c = p.second;
            if(mines[r][c]) continue;
            if(r == sink_r && c == sink_c) break;
            for(auto d : dirs_4) {
              int dr = d.first;
              int dc = d.second;
              int nr = r + dr, nc = c + dc;
              auto in_bounds = [&](int r, int c) -> bool {
                 return r >= 0 && r < R && c >= 0 && c < C; 
                };
              if(in_bounds(nr, nc) && 
                 !visited[nr][nc] && 
                 !(~dist[nr][nc])) {
                dist[nr][nc] = dist[r][c] + 1;
                visited[nr][nc] = true;
                q.push({nr, nc});
              }
            }
          }
          std::cout << dist[sink_r][sink_c] << std::endl;  
        }
    }
}