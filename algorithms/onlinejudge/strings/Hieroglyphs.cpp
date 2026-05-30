/*
───────────────────────────────────────────────────────────────
🧳 UVa 10851 2D Hieroglyphs decoder, https://onlinejudge.org/external/108/10851.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "../maths/utility/arithmetics.cpp"
#include <bits/stdc++.h>


namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;
using vs = std::vector<std::string>;


std::string decodeHieroglyphs(const vs& grid) {
  std::string decoded;
  for(int col = 0; col < (int)grid[0].size(); ++col) {
    int hieroglyph = 0;
    for(int row = 7; row >= 0; --row) {
      hieroglyph += arithmetics::power<int>(2, row) * (grid[row][col] == '/' ? 0 : 1); 
    }
    decoded += static_cast<char>(hieroglyph);
  }
  return decoded;
}


namespace algorithms::onlinejudge::strings::hieroglyphs
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

        int t_cases;
        scanf("%d\n", &t_cases);
        while(t_cases--) {
          vs grid(10);
          for(int i = 0; i < 10; ++i) {
            std::string line;
            while_read(line);
            grid[i] = line;
          }
          grid.pop_back(); // Remove the last line which is just a  border
          grid.erase(grid.begin()); // Remove the first line which is just a border
          // remove the first and last character of each line which are just borders
          for(int i = 0; i < (int)grid.size(); ++i) {
            grid[i] = grid[i].substr(1, grid[i].size() - 2);
          }
          std::cout << decodeHieroglyphs(grid) << std::endl;
        }
    }
}