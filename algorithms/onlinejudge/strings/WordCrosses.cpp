/*
───────────────────────────────────────────────────────────────
🧳 UVa 159 Word Crosses, https://onlinejudge.org/external/1/159.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vs = std::vector<std::string>;
using pss = std::pair<std::string, std::string>;
using ii = std::pair<int, int>;

struct Match
{
    char letter;
    int dx;
    int dy;

    // This perfectly captures your "min dx, min dy" logic
    bool operator < (const Match& other) const {
      if(dx != other.dx) {
        return dx < other.dx; // Primary condition: min dx
      }
      return dy < other.dy;     // Tie-breaker: min dy
    }
};

Match findBestMatch(const pss& words) {
  Match bestMatch = {'a', INT32_MAX, INT32_MAX};
  std::string first = words.first;
  std::string second = words.second;
  for(int i = 0; i < (int)first.size(); ++i) {
    for(int j = 0; j < (int)second.size(); ++j) {
      if(first[i] == second[j]) {
        bestMatch = std::min(bestMatch, {first[i], i, j});
      }
    }
  }
  return bestMatch;
}

std::ostream& operator << (std::ostream& out, const Match& match) {
  return out << "{ letter: " << match.letter << ", dx: " << match.dx << ", dy: " << match.dy << " }";
}


namespace algorithms::onlinejudge::strings::word_crosses
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

        std::string line;
        bool is_first = true;
        while(std::getline(std::cin, line) && line != "#") {

          if(!is_first) std::cout << std::endl;
          else is_first = false;

          std::stringstream ss(line);
          vs words;
          std::string word;
          while(ss >> word) {
            words.push_back(word);
          }

          pss first = {words[0], words[1]};
          pss second = {words[2], words[3]};
          Match first_match = findBestMatch(first);
          Match second_match = findBestMatch(second);
          if(first_match.dx == INT32_MAX || 
             second_match.dx == INT32_MAX) {
            printf("Unable to make two crosses\n");
          } else {

            int max_x = (int)words[0].size() + (int)words[2].size() + 3;
            int max_y = std::max(first_match.dy, second_match.dy); // This is the BASE ROW
            int min_y = std::max((int)words[1].size() - first_match.dy - 1, (int)words[3].size() - second_match.dy - 1);

            int total_rows = max_y + min_y + 1;
            std::vector<std::string> canvas(total_rows, std::string(max_x, ' ')); // using '.' for visibility

            // 1. Draw Horizontals on the BASE ROW (max_y), not row 0!
            for(int x = 0; x < (int)words[0].size(); ++x) {
              canvas[max_y][x] = words[0][x];
            }
            int offset_h2 = (int)words[0].size() + 3;
            for(int x = 0; x < (int)words[2].size(); ++x) {
              canvas[max_y][offset_h2 + x] = words[2][x];
            }

            // 2. Draw the ENTIRE Vertical Word 1
            // Start at the ceiling, offset by dy, and draw DOWNWARDS (+ i)
            int start_row_v1 = max_y - first_match.dy;
            for(int i = 0; i < (int)words[1].size(); ++i) { 
              canvas[start_row_v1 + i][first_match.dx] = words[1][i];
            }

            // 3. Draw the ENTIRE Vertical Word 2
            int start_row_v2 = max_y - second_match.dy;
            int offset_v2_x = offset_h2 + second_match.dx;
            for(int i = 0; i < (int)words[3].size(); ++i) {
              canvas[start_row_v2 + i][offset_v2_x] = words[3][i];
            }

           // Print the canvas safely, removing trailing spaces!
           for(int y = 0; y < total_rows; ++y) {
              
              // Look from right-to-left for the first thing that IS NOT a space
              size_t last_idx = canvas[y].find_last_not_of(' ');
              
              // If the line has letters on it...
              if (last_idx != std::string::npos) {
                  // Slice the string from 0 up to that last letter, and print it
                  std::cout << canvas[y].substr(0, last_idx + 1) << "\n";
              } 
              // If the line is completely blank (all spaces)...
              else {
                  std::cout << "\n";
              }
           }
          }
        }
    }
}