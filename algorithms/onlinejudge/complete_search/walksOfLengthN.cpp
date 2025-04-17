#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::complete_search::walks_of_Length
{
    /** https://onlinejudge.org/external/6/677.pdf, print all solutions with backtracking */
    int V, W;
    void print(const vi& path) 
    {
        std::string s = "(";
        for(int p : path)
        {
           s += std::to_string(p + 1);
           s += ",";
        }
        s.pop_back();
        s += ")";
        std::cout << s <<std::endl;
    }
    void backtrack(const vvi& graph, int walk, int u, vi& path, vi& visited, bool& isWalk)
    {
        if(walk == W)
        { 
            if(!isWalk) isWalk = true;
            print(path); 
            return; 
        }

        visited[u] = 1;
        for(int v : graph[u])
          if(!visited[v])
          {
              path.push_back(v);
              backtrack(graph, walk + 1, v, path, visited, isWalk);
              path.pop_back();
              visited[v] = 0;
          }
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        bool isFirst = true;
        while(std::cin >> V >> W)
        {
            if(!isFirst) std::cout << std::endl;
            isFirst = false;
            vvi graph(V);
            int rel, garbage;
            for(int i = 0; i < V; i++)
              for(int j = 0; j < V; j++)
              {
                  std::cin >> rel;
                  if(rel) graph[i].push_back(j);
              }
            vi visited(V);
            vi path = {0};
            bool isWalk = false;
            backtrack(graph, 0, 0, path, visited, isWalk);
            if(!isWalk) printf("no walk of length %d\n", W);
            scanf("%d\n", &garbage);
        } 
    }
}