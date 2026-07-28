/*
───────────────────────────────────────────────────────────────
🧳  Watersheds, https://open.kattis.com/contests/xer2wv/problems/watersheds, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/graph/tools/uf.cpp"
#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


namespace graph = algorithms::onlinejudge::graph::tools;


using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

enum Direction { South, East, West, North };

const vii dirs = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

Direction calculate_direction(const ii& dir) {
  int dr = dir.first;
  int dc = dir.second;

  if (dr == -1 && dc == 0) return North;
  if (dr == 0 && dc == -1) return West;
  if (dr == 0 && dc == 1)  return East;
  if (dr == 1 && dc == 0)  return South;

  return South; // Default fallback (theoretically unreachable for valid steps)
}

struct Flow
{
    int alt;
    ii cell;
    Direction dir;
    // Const-qualified comparison operator
    bool operator < (const Flow& other) const {
      if(this->alt != other.alt) {
        return this->alt < other.alt; // Lower altitude is preferred
      }
      return this->dir > other.dir;     // Higher enum value (North > West > East > South) is preferred
    }
};


int H, W;

void dfs(const ii& cell, const vvi& area, vvi& visited, graph::UnionFind& basins) {

  int r = cell.first;
  int c = cell.second;
  if(visited[r][c]) {
    return;
  }

  visited[r][c] = 1;
  int prev_alt = area[r][c];
  Flow best = {prev_alt, {0, 0}, South}; 
  for(const ii& d : dirs) {
    int nr = r + d.first;
    int nc = c + d.second;
    if(nr >= 0 && nr < H && nc >= 0 && nc < W) {
      auto dir = calculate_direction(d);
      int alt = area[nr][nc];
      Flow flow = {alt, {nr, nc}, dir};
      best = std::min(best, flow);
    }
  }
  if(best.alt != prev_alt) {
    int curr_idx = r * W + c;
    int next_idx = best.cell.first * W + best.cell.second;
    basins.unionSet(curr_idx, next_idx);
    dfs({best.cell.first, best.cell.second}, area, visited, basins);
  }

}

namespace algorithms::kattis::dp::watersheds
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

        int t_cases, t_case = 1;
        std::cin >> t_cases;
        while(t_cases--) {
          std::cin >> H >> W;
          vvi area(H, vi(W));
          for(int h = 0; h < H; ++h) {
            for(int w = 0; w < W; ++w) {
              std::cin >> area[h][w];
            }
          }

          vvi visited(H, vi(W, 0));
          graph::UnionFind basins(H * W);
          
          for(int h = 0; h < H; ++h) {
            for(int w = 0; w < W; ++w) {
              if(!visited[h][w]) {
                dfs({h, w}, area, visited, basins);
              }
            }
          }
          printf("Case #%d:\n", t_case++);
          std::unordered_map<int, char> labels;
          int last_label = -1;
          for(int h = 0; h < H; ++h) {
            for(int w = 0; w < W; ++w) {
              int idx = h * W + w;
              int rep = basins.findSet(idx);
              auto it = labels.find(rep);
              // new basin is found
              if(it == labels.end()) {
                last_label += 1;
                labels[rep] = (char)(last_label + 'a');
                std::cout << (char)(last_label + 'a');
              } else {
                std::cout << it->second;
              }
              if(w != W - 1) {
                std::cout << " ";
              }
            }
            std::cout << std::endl;
          }
        }
    }
}