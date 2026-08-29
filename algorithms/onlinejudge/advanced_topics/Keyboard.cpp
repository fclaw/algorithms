/*
───────────────────────────────────────────────────────────────
🧳 UVa 1714 Keyboarding, https://onlinejudge.org/external/17/1714.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * Problem   : UVa 1714 / ICPC World Finals 2015 - Problem F: Keyboarding
 * Paradigm  : Multi-Stage Layered State-Space BFS (Layered Graph Model)
 * Verdict   : ACCEPTED (19/19 Testcases)
 * ============================================================================
 * 
 * 🏢 THE "LAYERED BUILDING" MENTAL MODEL (Why 2D Fails):
 * ----------------------------------------------------
 * • In a standard 2D maze, each physical cell (r, c) is visited at most once.
 * • In Keyboarding, you must revisit the EXACT SAME physical key multiple times 
 *   (e.g., to type "AZAZ*", you must visit 'A' at stage 0, and visit 'A' again at stage 2).
 * 
 * • If we track visited only by (r, c), visiting 'A' early prevents us from 
 *   ever typing 'A' later in the word, causing the BFS to get stuck!
 * 
 * 🧱 THE LAYER ARCHITECTURE:
 * --------------------------
 * Imagine a 3D skyscraper with L floors (layers), where Floor `idx` represents 
 * having successfully typed the prefix of length `idx`:
 * 
 *   Floor (idx = 0) : Need to type target[0]
 *   Floor (idx = 1) : Need to type target[1]
 *   ...
 *   Floor (idx = L) : All characters (including '*') typed ===> 🏁 GOAL REACHED!
 * 
 * 🚶 THE 2 TYPES OF TRANSITIONS:
 * ------------------------------
 * 1. INTRA-LAYER MOVES (Walking on the same floor):
 *    - Pressing an Arrow Key jumps across contiguous duplicate keys from 
 *      (r, c) -> (nr, nc) within the SAME floor `idx`.
 *    - Cost: +1 arrow press.
 * 
 * 2. INTER-LAYER ELEVATOR (Ascending to the next floor):
 *    - When standing on a key where keyboard[r][c] == target[idx], pressing 
 *      'Select' takes the elevator UP from Floor `idx` -> Floor `idx + 1`.
 *    - Cost: +freq[idx] select presses (via Run-Length Compression).
 * 
 * ⚡ EFFICIENCY:
 * -------------
 * • State Space : R x C x (Target_Length + 1) ≈ 50 x 50 x 10,000 ≈ 2.5 x 10^7
 * • Graph Traversal: Pure Unweighted BFS explores layer-by-layer in O(V + E) time.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>;
using vvvii = std::vector<vvii>; // 3D vector: [row][col] -> vector<ii>
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
using vvvb = std::vector<vvb>;
using vvvvb = std::vector<vvvb>;
using vc = std::vector<char>;
using Keyboard = std::vector<vc>;



constexpr int MAX_LENGTH = 10000;
constexpr int TOTAL_CHARS = 38;

int R, C;


// 1. Fast O(1) Mapper: char -> [0 .. 37]
const vi char_to_id = []() {
    vi table(128, -1);

    // 'A'-'Z' -> 0 .. 25
    for (char c = 'A'; c <= 'Z'; ++c) {
        table[c] = c - 'A';
    }
    // '0'-'9' -> 26 .. 35
    for (char c = '0'; c <= '9'; ++c) {
        table[c] = 26 + (c - '0');
    }
    // '-' -> 36
    table['-'] = 36;
    // '*' -> 37
    table['*'] = 37;

    return table;
}();


struct State
{
    /**
     * 1. row & 2. col (Cursor Grid Position)
     * --------------------------------------
     * The current 2D grid coordinates (r, c) of the remote control cursor.
     * Range: 0 <= row < R, 0 <= col < C.
     */
    int row;
    int col;

    /**
     * 3. idx (Target Text Progress)
     * -----------------------------
     * The index of the NEXT character in the target string that needs to be typed.
     * 
     * Target text: original_word + "*"  (e.g., "CONTEST*")
     *   - idx = 0 : Need to type 'C'
     *   - idx = 3 : Already typed "CON", now need to type 'T'
     *   - idx = target.length() : Entire text (including '*') typed ===> GOAL REACHED!
     */
    int idx;

    /**
     * 4. presses (Total Key Presses / Cost g(n))
     * ------------------------------------------
     * The total number of button presses made so far (Arrows + Selects).
     * This is the value to minimize.
     */
    int presses;

};

bool in_keyboard(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; };


struct CompressedText {
    std::string text;           // Deduplicated string (e.g. "9RKR9...")
    std::vector<int> freq;      // freq[i] = how many times text[i] repeats
};

CompressedText remove_duplicates_with_freq(const std::string& input) {
    CompressedText result;
    int n = input.length();

    for (int i = 0; i < n; ) {
        char c = input[i];
        int count = 0;

        // Count consecutive repeats of character 'c'
        while (i < n && input[i] == c) {
            count++;
            i++;
        }

        result.text += c;
        result.freq.push_back(count);
    }

    return result;
}

/**
 * Precalculates reachable neighbours for all cells.
 * Access pattern: adj[r][c] -> vector of {next_r, next_c}
 */
vvvii precalculate_neighbours(const Keyboard& keyboard) {
  int R = keyboard.size();
  int C = keyboard[0].size();

  // 2D grid of neighbor vectors: adj[R][C]
  vvvii adj(R, vvii(C));

  // 4 Direction deltas: Up, Right, Down, Left
  const int dr[] = {-1, 0, 1,  0};
  const int dc[] = { 0, 1, 0, -1};

  for(int r = 0; r < R; ++r) {
    for(int c = 0; c < C; ++c) {
      char curr_char = keyboard[r][c];
      // adj[r][c].push_back({r, c});
      for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d];
        int nc = c + dc[d];

        // Walk past all cells with the same character
        while (in_keyboard(nr, nc) && 
               keyboard[nr][nc] == curr_char) {
          nr += dr[d];
          nc += dc[d];
        }

        // If landed on a different key within bounds:
        if (in_keyboard(nr, nc)) {
          adj[r][c].push_back({nr, nc});
        }
      }
    }
  }

  return adj;
}


int get_min_presses(const Keyboard& keyboard, const std::string& raw) {

  auto compressed = remove_duplicates_with_freq(raw);

  std::string text = compressed.text;
  auto freq = compressed.freq;

  vvvii neighs = precalculate_neighbours(keyboard);

  std::queue<State> queue;
  vvvvb visited(R, vvvb(C, vvb(TOTAL_CHARS + 1, vb(MAX_LENGTH + 2, false))));
  
  // init
  queue.push({0, 0, 0, 0});
  int min_pressess = 0;
  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    int row = state.row;
    int col = state.col;
    int idx = state.idx;
    char curr_letter = text[idx];
    int presses = state.presses;
   
    if(curr_letter == keyboard[row][col]) {
      presses += freq[idx];
      ++idx;
    }

    if(idx == (int)text.size()) {
      min_pressess = presses;
      break;
    } 

    for(ii neigh : neighs[row][col]) {
      int neigh_row = neigh.first;
      int neigh_col = neigh.second;
      char neigh_letter = keyboard[neigh_row][neigh_col];
      int neigh_id = char_to_id[neigh_letter];
      if(!visited[neigh_row][neigh_col][neigh_id][idx]) {
        visited[neigh_row][neigh_col][neigh_id][idx] = true;
        queue.push({neigh_row, neigh_col, idx, 1 + presses});
      }
    }
  }

  return min_pressess;
}


namespace algorithms::onlinejudge::advanced_topics::keyboard
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
     
        while(std::cin >> R >> C) {
          std::string text;
          Keyboard keyboard(R, vc(C));
          for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
              std::cin >> keyboard[r][c];
            }
          }
          std::cin >> text;
          text += "*"; // append enter
          printf("%d\n", get_min_presses(keyboard, text));
        }
    }
}
