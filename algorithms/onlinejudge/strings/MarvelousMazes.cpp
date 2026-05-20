/*
───────────────────────────────────────────────────────────────
🧳 UVa 445 Marvelous Mazes, https://onlinejudge.org/external/4/445.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vs = std::vector<std::string>;

std::string mazeBuilder(const std::string& line, int& acc) {
  std::string maze;
  for(char c : line) {
    // apply the rules
    if(c == '*') {
      maze += std::string(acc, c);
      acc = 0;
    } else if (c == 'b') {
      maze += std::string(acc, ' ');
      acc = 0;
    } else if(std::isupper(c)) {
      maze += std::string(acc, c);
      acc = 0;
    } else if (c == '!') {
      maze += std::string(1, '\n');
    } else {
      acc += c - '0';
    }
  }
  return maze;
}

namespace algorithms::onlinejudge::strings::marvelous_mazes
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
        int acc = 0;
        while(std::getline(std::cin, line)) {
          printf("%s\n", mazeBuilder(line, acc).c_str());
        }
    }
}