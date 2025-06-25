/*
───────────────────────────────────────────────────────────────
🧳 UVa 10653 Bombs! NO they are Mines!!, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bfs.cpp"

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


enum Field { Mine, Free };

std::ostream& operator << (std::ostream& os, const Field& field) 
{
    std::string s;
    if(field == Mine) s = "mine";
    else if(field == Free) s = "free";
    return os << s; 
}


namespace algorithms::onlinejudge::graph::bombs
{
    /** https://onlinejudge.org/external/106/10653.pdf */
    int R, C, B;
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
        

        while(while_read(R, C) && R && C) {
          while_read(B);
          std::vector<tools::vb> field(R, tools::vb(C, false));
          loop(B, [&](int _) {
            int r, c, n;
            while_read(r, n);
            loop(n, [&](int _) {
              while_read(c);
              field[r][c] = true;
            });
          });
        
          tools::GridGraph<Field, bool> graph = tools::init_grid_graph<Field, bool>();
          graph.cell_to_value = [](bool _) -> Field { return Free; };
          graph.is_blocked = [](Field field) { return field == Mine; };
          tools::grid_to_adj_list(graph, field, tools::dirs_4);

          int r, c;
          while_read(r, c);
          int start_node = r * C + c;
          tools::Node<Field> source = {start_node, Free};
          while_read(r, c);
          int end_node = r * C + c;
          tools::Node<Field> sink = {end_node, Free};  

          tools::Bfs<Field> bfs_s(R * C, source);
          bfs_s.check = 
            [&](const tools::Node<Field>& node)
              -> tools::BfsCheck { 
              if(node == sink) 
                return tools::IsFinished;
              return tools::GoOn;
            };

          tools::bfs(graph.adj, bfs_s);
          std::cout << bfs_s.getDistance(sink) << std::endl;
        }
    }
}