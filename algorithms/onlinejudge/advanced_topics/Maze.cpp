/*
───────────────────────────────────────────────────────────────
🧳 UVa 10890 Maze, https://onlinejudge.org/external/108/10890.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvii = std::vector<vii>;



void backtrack(int i, int S, const vvii& dist, int collected_boxes, int sink, int& curr_dist, int& min_dist) {
   
    if(i == sink || curr_dist >= min_dist) {
        return;
    }

    int BOXES = __builtin_popcount(collected_boxes ^ (1 << 0));
    // Valid Solution Check: Whenever we have collected AT LEAST S boxes
    if (BOXES == S) {

      int dist_to_sink = 0;
      for(ii box : dist[i]) {
        if(box.second == sink) {
          dist_to_sink = box.first;
          break;
        }
      }
      int tmp_dist = curr_dist + dist_to_sink;
      min_dist = std::min(min_dist, tmp_dist);
      return;
    }


    for(ii box : dist[i]) {
      int j = box.second;
      int ij_dist = box.first;

      // PRUNING: Early break because neighbors are sorted by distance
      // If the step cost alone exceeds min_dist, all remaining neighbors will also exceed it!
      if (curr_dist + ij_dist >= min_dist) {
        break; 
      }

      int bit = 1 << j;
      if(!(collected_boxes & bit)) {
        curr_dist += ij_dist;
        backtrack(j, S, dist, collected_boxes | bit, sink, curr_dist, min_dist);
        curr_dist -= ij_dist;
      }
    }
}

namespace algorithms::onlinejudge::advanced_topics::maze
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

        int N, T, S, t_case = 1;
        while(std::cin >> N >> T >> S && N) {
          int SIZE = T + 2;
          vii points(SIZE);
          points[0] = {0, 0};
          points[T + 1] = {N - 1, N - 1};
          for(int i = 1; i <= T; ++i) {
            std::cin >> points[i];
          }
          // Pre-calculate distance matrix using O(1) Manhattan Distance
          vvii dist(SIZE);
          for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
              int d = std::abs(points[i].first - points[j].first) + 
                      std::abs(points[i].second - points[j].second);
              dist[i].push_back({d, j}); // Fast contiguous insertion
            }
          }
          
          // Sort neighbors of i by distance 'd' in ascending order
          for(int i = 0; i < SIZE; ++i) {
            std::sort(dist[i].begin(), dist[i].end());
          }
          int min_dist = INT32_MAX;
          int curr_dist = 0;
          backtrack(0, S, dist, 0 | (1 << 0), T + 1, curr_dist, min_dist);
          printf("Case %d: %d\n", t_case++, min_dist);
        }

    }
}