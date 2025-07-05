/*
───────────────────────────────────────────────────────────────
🧳 UVa 12878 Flowery Trails, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dijkstra.cpp"
#include "tools/w_graph.cpp"

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
#include <queue>
#include <cctype>
#include <utility>
#include <functional>
#include <set>


struct hash_pair 
{
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
      // Hash the first element
      size_t fh = std::hash<T1>{}(p.first);
      // Hash the second element
      size_t sh = std::hash<T2>{}(p.second);
      // Combine the two hash values
      return fh ^ (sh + 0x9e3779b9 + (fh << 6) + (fh >> 2));
    }
};


typedef std::unordered_map<std::pair<int, int>, int, hash_pair> map_piii;

namespace dijkstra = algorithms::onlinejudge::graph::tools::dijkstra;
namespace wg = algorithms::onlinejudge::graph::tools::wg;

namespace algorithms::onlinejudge::graph::flowery_trails
{
    /** https://onlinejudge.org/external/128/12878.pdf */
    int V, E;
    void backtrack(
      int v, 
      const std::vector<std::set<int>>& paths, 
      std::vector<int>& path, 
      const map_piii& lengths,
      const map_piii& counter, 
      int& total,
      // avoid repeated counting
      std::vector<tools::vb>& processed) {
      if(paths[v].empty()) {
        for(int i = 0; i < (int)path.size() - 1; ++i) {
          auto trail = std::minmax(path[i], path[i + 1]);
          if(!processed[trail.first][trail.second]) {
            processed[trail.first][trail.second] = true;
            total += counter.at(trail) * lengths.at(trail);
          }
        }
        return;
      }

      // Explore each predecessor of the current node v
      for(int u : paths[v]) {
        path.push_back(u);
        backtrack(u, paths, path, lengths, counter, total, processed);
        path.pop_back();
      }
    }
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
        
        while(while_read(V, E)) {
          map_piii lengths;
          map_piii counter;
          wg::WGraph<> trails(V);
          loop(E, [&] (int _) {
            int from, to, length;
            while_read(from, to, length);
            trails[from].push_back(wg::mkWNode(to, length));
            trails[to].push_back(wg::mkWNode(from, length));
            std::pair<int, int> edge_key = std::minmax(from, to);
            auto it = lengths.find(edge_key);
            if(it == lengths.end()) { 
                lengths[edge_key] = length;
                counter[edge_key] = 1;
            }
            else {
              int& trial_length = (*it).second;
              // Update minimum length between `from` and `to`
              if(trial_length > length) {
                trial_length = length;
              }
              // If you need to count equal length edges, you can store it in a separate counter map:
              else if (trial_length == length) {
                ++counter[edge_key];  // Assuming you need a counter for edges of equal length
              }
            }
          });

          std::vector<std::set<int>> paths(V, std::set<int>());
          wg::WNode<> start = wg::mkWNode(0, 0);
          dijkstra::Dijkstra<> dijkstra_s(V, start);
          dijkstra_s.mappend = [](int w, int a) { return w + a; };
          dijkstra_s.on_relaxation = 
            [&](int u, int v) {
              paths[v].clear();  // Clear previous longer paths
              paths[v].insert(u);  // Add u as the valid predecessor
            };
          dijkstra_s.on_tied_path = [&](int u, int v) { paths[v].insert(u); };
          dijkstra::dijkstra(trails, dijkstra_s);
          
          std::vector<tools::vb> processed(V, tools::vb(V, false));
          int total_length = 0;
          std::vector<int> path;
          path.push_back(V - 1);
          backtrack(V - 1, paths, path, lengths, counter, total_length, processed);
          std::cout << 2 * total_length << std::endl;
        }
    }
}