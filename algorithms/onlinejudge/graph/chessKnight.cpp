/*
───────────────────────────────────────────────────────────────
🧳 UVa 633 A Chess Knight, rt: s
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


typedef std::pair<int, int> pii;


namespace algorithms::onlinejudge::graph::chess_knight
{
    /** https://onlinejudge.org/external/6/633.pdf */
    int SIZE;
    bool in_board(int r, int c) { return r >= 0 && r < SIZE && c >= 0 && c < SIZE; }
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
        
        while(while_read(SIZE) && SIZE) {
          SIZE *= 2;
          int i = 0;
          int r, c;
          pii source, sink;
          while(while_read(r, c) && r && c) {
            --r; --c;
            if(i == 0) { 
              source.first = r; 
              source.second = c; 
            } else if(i == 1) {
              sink.first = r; 
              sink.second = c;
            } else {
            }
            ++i;
          }

          int min_moves = INT32_MAX;
          min_moves == INT32_MAX ? printf("Solution doesn't exist\n") : printf("Result: %d\n", min_moves);
        }
    }
}