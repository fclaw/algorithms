/*
───────────────────────────────────────────────────────────────
🧳 UVa 627 The Net, rt: s
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



namespace algorithms::onlinejudge::graph::net
{
    /** https://onlinejudge.org/external/6/627.pdf */
    int V, Q;
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
          std::cin.ignore();
          tools::Graph<> graph(V);
          std::string s;
          loop(V, [&] (int _) {
            std::getline(std::cin, s);
            auto ns = s.substr(0, s.find('-')); 
            int from = std::atoi(ns.c_str());
            --from;
            auto rest = s.substr(s.find('-') + 1, s.size());
            std::stringstream ss(rest);
            int to;
            while(ss >> to) {
              --to;
              auto tn = tools::mkDefNode(to);
              graph[from].push_back(tn);
              if(ss.peek() == ',') ss.ignore();
            }
          });

          printf("-----\n");
          while_read(Q);
          while(Q--) {
            int from, to;
            while_read(from, to);
            --from; --to;
            tools::Node<> start = tools::mkDefNode(from);
            tools::Node<> end = tools::mkDefNode(to);
            tools::Bfs<> bfs_s(V, start);
            bfs_s.check = 
              [&](const tools::Node<>& node)
                  -> tools::BfsCheck {       
                if(node == end) 
                  return tools::IsFinished;
                return tools::GoOn;
              }; 
            tools::bfs(graph, bfs_s);
            if(bfs_s.dist[to] == INT32_MAX) 
              printf("connection impossible\n");
            else {
              tools::vi path = bfs_s.restore_path(end);
              std::string s;
              s += std::to_string(from + 1) + " ";
              for(int n : path) s += std::to_string(n + 1) + " ";
              s.pop_back();
              std::cout << s << std::endl; 
            }
          }
        } 
    }
}