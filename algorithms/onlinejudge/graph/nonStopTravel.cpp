/*
───────────────────────────────────────────────────────────────
🧳 UVa 341 Non-Stop Travel, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/floyd_warshall.cpp"

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



namespace fd = algorithms::onlinejudge::graph::tools::floyd_warshall;
namespace wg = algorithms::onlinejudge::graph::tools::wg;



namespace algorithms::onlinejudge::graph::non_stop_travel
{
    constexpr int inf = 1e5;
    /** https://onlinejudge.org/external/3/341.pdf */
    int V, c = 1;
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
        
        while(while_read(V) && V) {
          wg::WGraph<> graph(V);
          std::string s;
          int u = 0;
          while(u < V) {
            std::string line;
            if(!std::getline(std::cin, line)) { break; }
            // Create a stringstream from the line. This handles empty lines
            // and lines with only whitespace gracefully.
            std::stringstream ss(line);
            // Attempt to read the first integer (number of edges).
            int num_edges;
            // --- THE KEY SANITIZATION STEP ---
            if(!(ss >> num_edges)) {
              // This block executes if:
              //  - The line was empty.
              //  - The line contained only whitespace.
              //  - The line did not start with a valid integer.
              // In this problem, we can assume this means there are no edges for this node.
              continue; // Safely skip to the next line.
            }
            
            // Now, read the pairs of (vertex, delay).
            for(int j = 0; j < num_edges; ++j) {
              int v, delay;
              // It's also good practice to check these reads, though less critical
              // if the input format is guaranteed to be correct.
              if(ss >> v >> delay) {
                wg::pair(graph, u, v - 1, delay, false); // Using your function
              } else {
                // Handle malformed line error if necessary, e.g., not enough pairs.      
                break; 
              }
            }
            ++u;
          }

          int start, end;
          while_read(start, end);
          --start; --end;

          fd::FloydWarshall<> fw_s(V, 0, inf);
          fw_s.mappend = [](int u, int v) { return u + v; };
          fd::floyd_warshall(graph, fw_s);

          std::string s_path;
          vi path = fw_s.getPath(start, end);
          for(int n : path) s_path += std::to_string(n + 1) + " ";
          s_path.pop_back();
          int min_delay = fw_s.matrix[start][end];
          printf("Case %d: Path = %s; %d second delay\n", c++, s_path.c_str(), min_delay); 

        }  
    }
}