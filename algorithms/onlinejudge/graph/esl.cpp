/*
───────────────────────────────────────────────────────────────
🧳 UVa 10029 Edit Step Ladders, rt: s
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
#include <set>
#include <map>



namespace tools = algorithms::onlinejudge::graph::tools;


namespace algorithms::onlinejudge::graph::esl
{
    /** https://onlinejudge.org/external/100/10029.pdf  */
    void backtrack(
      const std::map<std::string, int>& word_node,
      const std::string& w, 
      tools::vv_def_node& graph,
      std::set<std::string>& used) {

      int node = word_node.at(w);
      for(int i = 0; i < (int)w.size(); ++i) {
        auto tmp = w;
        // delete char
        tmp.erase(i, 1);
        if(word_node.count(tmp) && 
           used.insert(tmp).second) {
          int n = word_node.at(tmp);
          graph[node].push_back(tools::mkDefNode(n));
          backtrack(word_node, tmp, graph, used);
        }
        // replace by next
        for (char c = 'a'; c <= 'z'; ++c) {
          if(c == w[i]) continue; // skip same character
          tmp = w;
          tmp[i] = c;
          if(word_node.count(tmp) && 
             used.insert(tmp).second) {  
            int n = word_node.at(tmp);
            graph[node].push_back(tools::mkDefNode(n));
            backtrack(word_node, tmp, graph, used);
          }
        }
        // add
        for(char c = 'a'; c <= 'z'; ++c)
          for(int j = 0; j < (int)w.size(); ++j) {
            std::string tmp;
            std::string left = w.substr(0, j);
            std::string right = w.substr(j, w.size() - j); // Fixing substring length
            left.push_back(c);
            tmp = left + right;
            if(word_node.count(tmp) && 
               used.insert(tmp).second) {
              int n = word_node.at(tmp);
              graph[node].push_back(tools::mkDefNode(n));
              backtrack(word_node, tmp, graph, used);
            }
            
            tmp = w;
            tmp.push_back(c);
            if(word_node.count(tmp) && 
               used.insert(tmp).second) {
              int n = word_node.at(tmp);
              graph[node].push_back(tools::mkDefNode(n));
              backtrack(word_node, tmp, graph, used);
            }

            tmp = w;
            tmp[0] = c;
            if(word_node.count(tmp) && 
               used.insert(tmp).second) {
              int n = word_node.at(tmp);
              graph[node].push_back(tools::mkDefNode(n));
              backtrack(word_node, tmp, graph, used);
            }
          }
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
        
        std::map<std::string, int> word_node;
        std::string word;
        int node = 0;
        while(while_read(word))
          word_node[word] = node++;

        int V = node;
        tools::Dfs<> dfs_s = tools::init_dfs<>(V);
        tools::vv_def_node words(V);
        std::set<std::string> used;
        for(const auto& p : word_node)
          if(used.insert(p.first).second)
            backtrack(word_node, p.first, words, used);
 
        auto top_res = top_sort_kahn(V, words);
        tools::vi dp(V, 1);
        for(int u : top_res.top_sort)
          for (auto& v : words[u])
            dp[v.node] = std::max(dp[v.node], dp[u] + 1);
        int max_ladder = *std::max_element(dp.begin(), dp.end());
        std::cout << max_ladder << std::endl;
    }
}