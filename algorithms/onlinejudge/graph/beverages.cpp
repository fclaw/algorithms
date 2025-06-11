/*
───────────────────────────────────────────────────────────────
🧳 UVa 11060 Beverages, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bfs.cpp"

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
#include <cctype>


namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::beverages
{
    /** https://onlinejudge.org/external/110/11060.pdf */
    int V, E, t_cases = 1;
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
        
        while(while_read(V)) {  
          std::unordered_map<std::string, int> beverage_name;
          std::unordered_map<int, std::string> beverage_idx;
          tools::vv_def_node beverages(V);
          std::string name;
          loop(V, [&](int n) {
            while_read(name);
            beverage_name[name] = n;
            beverage_idx[n] = name;
          });

          while_read(E);
          loop(E, [&beverages, beverage_name] (int _) {
            std::string from_n, to_n;
            while_read(from_n, to_n);
            int from = beverage_name.at(from_n);
            int to = beverage_name.at(to_n);
            auto n = tools::def_node;
            n.node = to;
            beverages[from].push_back(n);
          });

          tools::TopSortKahn res = tools::top_sort_kahn(V, beverages);
          std::string ans;
          for(int s : res.top_sort) 
            ans += beverage_idx.at(s) + " ";
          ans.pop_back();
          printf("Case #%d: Dilbert should drink beverages in this order: %s.\n\n", t_cases++, ans.c_str());
        }
    }
}