/*
───────────────────────────────────────────────────────────────
🧳 UVa 118 Mutant Flatworld Explorers, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

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



namespace tools = algorithms::onlinejudge::graph::tools;


enum WD { West, East, North, South };

namespace algorithms::onlinejudge::graph::flatworld
{
    /** https://onlinejudge.org/external/1/118.pdf */
    int R, C;
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

        while(while_read(R, C)) {
          std::vector<std::vector<char>> grid(R + 1, std::vector<char>(C + 1, ' '));
          tools::GridGraph<WD, char> g;
          g.cell_to_value = [](char _) { return West; };
          tools::grid_to_adj_list<>(g, grid);
          
          dbg(g.adj);
        }  
    }
}