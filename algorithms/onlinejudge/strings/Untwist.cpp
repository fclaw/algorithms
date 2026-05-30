/*
───────────────────────────────────────────────────────────────
🧳 UVa 641 Do the Untwist, https://onlinejudge.org/external/6/641.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


const std::string CHAR_MAP = "_abcdefghijklmnopqrstuvwxyz.";

const std::unordered_map<char, int> CHAR_TO_INDEX = {
  {'_', 0},
  {'a', 1},
  {'b', 2},
  {'c', 3},
  {'d', 4},
  {'e', 5},
  {'f', 6},
  {'g', 7},
  {'h', 8},
  {'i', 9},
  {'j', 10},
  {'k', 11},
  {'l', 12},
  {'m', 13},
  {'n', 14},
  {'o', 15},
  {'p', 16},
  {'q', 17},
  {'r', 18},
  {'s', 19},
  {'t', 20},
  {'u', 21},
  {'v', 22},
  {'w', 23},
  {'x', 24},
  {'y', 25},
  {'z',26 },
   {'.',27 }
};


std::string do_decryption(int k, const std::string& encypted) {
  int n = (int)encypted.size();
  auto origin = std::string(encypted.size(), ' '); // Initialize with spaces
  for (int i = 0; i < n; ++i) {
    char origin_val = CHAR_MAP[(CHAR_TO_INDEX.at(encypted[i]) + i) % 28];
    int j = (k * i) % n;
    origin[j] = origin_val;
  }
  return origin;
}

namespace algorithms::onlinejudge::strings::untwist
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

        int k;
        std::string encypted;
        while(std::cin >> k && k) {
          std::cin >> encypted;
          std::string origin = do_decryption(k, encypted);
          std::cout << origin << std::endl;
        }
    }
}