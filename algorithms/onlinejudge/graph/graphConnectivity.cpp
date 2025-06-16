/*
───────────────────────────────────────────────────────────────
🧳 UVa  459 Graph Connectivity, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/uf.cpp"

#include <optional>
#include <iostream>
#include <sstream>
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


typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;


namespace algorithms::onlinejudge::graph::graph_connectivity
{
    /** https://onlinejudge.org/external/4/459.pdf */
    int t_cases, V;
    int to_int(char c) { return c - 'A'; }
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
        
        while_read(t_cases);
        std::cin.ignore();
        bool is_first = true;
        while(t_cases--) {
          char Max;
          while_read(Max);
          V = to_int(Max) + 1;
          vvb rel(V, vb(V, false));
          tools::UnionFind uf(V);
          std::cin.ignore();
          std::string in;
          while(std::getline(std::cin, in) && 
                !in.empty()) {
            int from = to_int(in.front());
            int to = to_int(in.back());
            rel[from][to] = true;
            rel[to][from] = true;
          }

          for(int i = 0; i < V; ++i)
            for(int j = i + 1; j < V; ++j)
              if(rel[i][j]) uf.unionSet(i, j);
           
          if(!is_first) std::cout << std::endl;
          else is_first = false;
          std::cout << uf.numDisjointSets() << std::endl;
        }  
    }
}