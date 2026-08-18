/*
───────────────────────────────────────────────────────────────
🧳 UVa 11471 Arrange the Tiles, https://onlinejudge.org/external/114/11471.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 

enum Colour { Y, G, B, R }; 


const int COL = 3;
const int ROW = 4;
const int D = ROW * COL;


using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using ll = long long;
using vi = std::vector<int>;

// Precompute factorials up to 12
ll fact[D + 1];

void precompute_factorials() {
  fact[0] = 1;
  for(int i = 1; i <= D; ++i) {
    fact[i] = fact[i - 1] * i;
  }
}



// Pack [Top, Right, Bottom, Left] into a single 16-bit integer
int pack_tile_colors(const std::vector<Colour>& colours) {
    return (static_cast<int>(colours[0]) << 12) | // Top
           (static_cast<int>(colours[1]) << 8)  | // Right
           (static_cast<int>(colours[2]) << 4)  | // Bottom
           (static_cast<int>(colours[3]));        // Left
}

// Unpack a 16-bit integer back to [Top, Right, Bottom, Left]
std::vector<Colour> unpack_tile_colors(int packed) {
    return {
        static_cast<Colour>((packed >> 12) & 0xF), // 0: Top
        static_cast<Colour>((packed >> 8)  & 0xF), // 1: Right
        static_cast<Colour>((packed >> 4)  & 0xF), // 2: Bottom
        static_cast<Colour>(packed & 0xF)          // 3: Left
    };
}

// Checks if placing 'mask' with 'colours' conflicts with adjacent filled tiles
bool is_fragile(int r, int c, const std::vector<Colour>& colours, const vi& tiles) {
    
  // Directional offsets: 0: Top, 1: Right, 2: Bottom, 3: Left
  const int dr[] = {-1, 0, 1, 0};
  const int dc[] = {0, 1, 0, -1};

  // Check 4 directional neighbors
  for (int dir = 0; dir < 4; ++dir) {
    int nr = r + dr[dir];
    int nc = c + dc[dir];

    if (nr >= 0 && nr < ROW && nc >= 0 && nc < COL) {
      int adj_idx = nr * COL + nc;

      // Neighbor condition: Must be FILLED (!= -1) and NOT part of the new tile itself
      if (tiles[adj_idx] != -1) {
                    
        // Unpack neighbor's 4 edge colors [Top, Right, Bottom, Left]
        std::vector<Colour> neighbor_colours = unpack_tile_colors(tiles[adj_idx]);

        // Side-by-side comparison for touching edges
        int opposite_dir = (dir + 2) % 4; // Top <-> Bottom, Right <-> Left

        if (colours[dir] != neighbor_colours[opposite_dir]) {
          return true; // Edge color mismatch -> Fragile!
        }     
      }
    }
  }
  return false; // Placement is valid! Touching edges match.
}



void backtrack(int r, int c, std::map<std::vector<Colour>, int>& freq, vi& tiles, ll& total_physical_ways) {

  if(c == COL) {
    c = 0;
    r++;
  }

  if(r == ROW) {
    total_physical_ways++;
    return;
  }

  for(auto [colours, count] : freq) {
    if(count > 0 && !is_fragile(r, c, colours, tiles)) {
      int idx = r * COL + c;
      tiles[idx] = pack_tile_colors(colours);
      freq[colours]--;
      backtrack(r, c + 1, freq, tiles, total_physical_ways);
      tiles[idx] = -1;
      freq[colours]++;
    }
  }

}

ll find_all_none_fragile_placements(std::map<std::vector<Colour>, int>& freq) {

  ll factor = 1;
  for(auto [_, c] : freq) {
    factor *= fact[c];
  }

  // 1. Run backtracking to get the count of valid TILE TYPE layouts
  ll total_physical_ways = 0;
  vi tiles(D + 1, -1);
  backtrack(0, 0, freq, tiles, total_physical_ways);
  // 2. Multiply by the factorials of the frequencies of each unique tile type
  total_physical_ways *= factor;

  return total_physical_ways;
}

namespace algorithms::onlinejudge::advanced_topics::arrange_the_tiles
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

        precompute_factorials();

        int t_cases, t_case = 1;
        std::cin >> t_cases;
        while(t_cases--) {
          std::map<std::vector<Colour>, int> freq;
          std::string str;
          for(int tile = 1; tile <= D; ++tile) {
            std::cin >> str;
            std::vector<Colour> colours;
            for(char c : str) {
              if(c == 'Y') {
               colours.push_back(Y); 
              } else if (c == 'G') {
                colours.push_back(G); 
              } else if (c == 'B') {
                colours.push_back(B);
              } else {
                colours.push_back(R);
              }
            }
            freq[colours]++;
          }
          printf("Case %d: %lld\n", t_case++, find_all_none_fragile_placements(freq));
        }
    }
}
