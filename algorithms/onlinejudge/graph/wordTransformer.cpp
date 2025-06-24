/*
───────────────────────────────────────────────────────────────
🧳 UVa 429	Word Transformation, rt: s
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

typedef std::unordered_map<std::string, int> msi;
typedef std::pair<std::string, int> psi;

const std::string letters = "abcdefghijklmnopqrstuvwxyz0123456789";

namespace algorithms::onlinejudge::graph::word_transformer
{
    /** https://onlinejudge.org/external/4/429.pdf */
    int t_cases;
    void backtrack(
      const psi& p, 
      const msi& words, 
      tools::Graph<>& graph, 
      std::unordered_set<std::string>& used) {

      int n = p.second;
      std::string w = p.first;
      for(int i = 0; i < (int)w.size(); ++i)
        for(char c : letters) {

          std::string tmp = w;
          tmp[i] = c;
          if(words.count(tmp) && 
             !used.count(tmp)) {
            int cn = words.at(tmp);
            graph[n].push_back(tools::mkDefNode(cn));
            graph[cn].push_back(tools::mkDefNode(n));
            used.insert(tmp);
            psi cp = {tmp, cn};
            backtrack(cp, words, graph, used);
            used.erase(tmp);
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
        
        while_read(t_cases);
        std::cin.ignore();
        std::cin.ignore();
        while(t_cases--) {

          msi words;
          std::string in;
          int idx = 0;
          while(std::getline(std::cin, in) && in != "*") {
            words[in] = idx++;
          }

          int V = idx;

          tools::Graph<> graph(V);
          std::unordered_set<std::string> used;
          for(auto& p : words) {
            if(used.count(p.first)) continue;
             used.insert(p.first);
             backtrack(p, words, graph, used);
          }
 
          while(std::getline(std::cin, in) && !in.empty()) {
            std::stringstream ss(in);
            std::string source, sink, tmp;
            bool is_source = true;
            while(ss >> tmp) {
              if(is_source) {
                source = tmp;
                is_source = false;
              } else sink = tmp;
            }

            tools::Node<> start = tools::mkDefNode(words.at(source));
            tools::Node<> end = tools::mkDefNode(words.at(sink));
            tools::Bfs<> bfs_s(V, start);
            bfs_s.check = 
              [&](const tools::Node<>& node)
                  -> tools::BfsCheck {  
                if(node == end) 
                  return tools::IsFinished;
                return tools::GoOn;
              }; 
            tools::bfs(graph, bfs_s);
            int d = bfs_s.getDistance(end);
            printf("%s %s %d\n", source.c_str(), sink.c_str(), d);
          }
          if(t_cases) std::cout << std::endl;
        }  
    }
}