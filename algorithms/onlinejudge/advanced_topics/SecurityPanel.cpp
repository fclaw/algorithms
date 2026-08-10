/*
───────────────────────────────────────────────────────────────
🧳 UVa 10318 Security Panel, https://onlinejudge.org/external/103/10318.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vc = std::vector<char>;
using vvc = std::vector<vc>;
using vi = std::vector<int>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;

const int SIZE = 3;

// 8-directional grid offsets: {dr, dc}
const vii dirs8 = {
    {-1,  0}, // 1. North (Up)
    {-1,  1}, // 2. North-East (Up-Right)
    { 0,  1}, // 3. East (Right)
    { 1,  1}, // 4. South-East (Down-Right)
    { 1,  0}, // 5. South (Down)
    { 1, -1}, // 6. South-West (Down-Left)
    { 0, -1}, // 7. West (Left)
    {-1, -1}  // 8. North-West (Up-Left)
};


// Toggles bits in the 'panels' bitmask based on the 3x3 pattern centered at (r, c)
// R and C represent the total rows and columns of the grid.
int apply_pattern(int r, int c, int panels, const vvc& pattern, int R, int C) {
  int new_panels = panels;

  // 1. Check the center cell (1, 1) -> offset {0, 0}
  if (pattern[1][1] == '*') {
    int bit_idx = r * C + c;
    new_panels ^= (1 << bit_idx);
  }

  // 2. Check the 8 surrounding neighbors using dirs8
  for (ii d : dirs8) {
    int pr = 1 + d.first;
    int pc = 1 + d.second;

    if (pattern[pr][pc] == '*') {
      int nr = r + d.first;
      int nc = c + d.second;

      if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
        int bit_idx = nr * C + nc;
        new_panels ^= (1 << bit_idx); // Toggle bit using XOR
      }
    }
  }

  return new_panels;
}



// Returns true if current board state is valid so far, false if we should prune
bool check_left_diagonals(int r, int c, int panels, int C) {
    
    // Check top-left light (r - 1, c - 1): Permanently finalized by button (r, c)
    if (r - 1 >= 0 && c - 1 >= 0) {
        int bit_idx = (r - 1) * C + (c - 1);
        if (!(panels & (1 << bit_idx))) {
            return false; // Light (r-1, c-1) is OFF and can NEVER be turned ON!
        }
    }

    return true; // Valid progress, continue searching
}


void can_solved(int r, int c, int panels, const vvc& pattern, vi& buttons, int R, int C, vi& best) {

  // Advance to next row if we reach the end of column
  if(c == C) {
    r++;
    c = 0;
  }

  if(r == R) {
    if(__builtin_popcount(panels) == R * C) {
      if(best.empty() || 
        (buttons.size() <
         best.size()) || 
         (buttons.size() == 
          best.size() && 
          buttons < best)) {
        best = buttons;
      }
    }
    return;
  }
 
  // Size Pruning: If we already have a solution and current presses exceed best size
  if (!best.empty() && 
      buttons.size() >
      best.size()) {
    return;
  }

  // --- Choice 1: Press button (r, c) ---
  int new_panels = apply_pattern(r, c, panels, pattern, R, C);
  // after the button (i, j) is pressed, light (i − 1, j − 1) must be on 
  // (as no button afterwards will affect this light)
  if(check_left_diagonals(r, c, new_panels, C)) {
    // Button number (1-indexed as required by UVa 10318)
    int idx = r * C + c;
    int button = idx + 1;
    buttons.push_back(button);
    can_solved(r, c + 1, new_panels, pattern, buttons, R, C, best);
    buttons.pop_back();
  }

  // --- Choice 2: Don't press button (r, c) ---
  if (check_left_diagonals(r, c, panels, C)) {
    can_solved(r, c + 1, panels, pattern, buttons, R, C, best);
  }
}


namespace algorithms::onlinejudge::advanced_topics::security_panel
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

        int R, C, t_case = 1;
        while(std::cin >> R >> C && (R && C)) {
          vvc pattern(SIZE, vc(SIZE));
          for(int r = 0; r < SIZE; ++r) {
            for(int c = 0; c < SIZE; ++c) {
              std::cin >> pattern[r][c];
            }
          }
          vi buttons;
          vi sol;
          // Reset initial state
          int initial_panels = 0; // All buttons initially unlit (0)
          can_solved(0, 0, initial_panels, pattern, buttons, R, C, sol);
          if(sol.empty()) {
            printf("Case #%d\nImpossible.\n", t_case++);
          } else {
            std::string str;
            for(int b : sol) {
              str += std::to_string(b) + " ";
            }
            str.pop_back();
            printf("Case #%d\n%s\n", t_case++, str.c_str());
          }
        }
    }
}