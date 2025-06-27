
#pragma once

#include "dfs.cpp"

#include <queue>
#include <functional>


namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::tools::dijkstra
{

    constexpr int inf = 1e10;
    typedef std::vector<int> vi;
    typedef std::pair<int, int> pii;
    typedef std::priority_queue<int, std::vector<pii>, std::greater<pii>> pq;

    struct Dijkstra
    {
        vi dist;
        pq queue;
        Dijkstra(int V, int source) {
          dist.assign(V, inf);
          dist[source] = 0;
          queue.emplace(0, source);
        }
    };
    
    // priority queue
    template<typename T>
    void dijkstra(const tools::Graph<T>& graph, Dijkstra& dijkstra_s) {
      auto& queue = dijkstra_s.queue;
      while(!queue.empty()) {
        auto [d, u] = queue.top(); queue.pop();
        if(d > dijkstra_s.dist[u]) continue; // lazy deletion
        for(tools::Node<T>& node : graph[u]) {
          if(dijkstra_s.dist[u] + node.value < dijkstra_s.dist[v]) {
           dijkstra_s.dist[v] = dijkstra_s.dist[u] + node.value;
           queue.emplace(dijkstra_s.dist[v], v);
          }
        }
      }
    }
}