
#pragma once

#include "w_graph.cpp"

#include <queue>
#include <functional>


namespace wg = algorithms::onlinejudge::graph::tools::wg;


// Custom comparator for the priority queue
template<typename T, typename W>
struct Compare {
    bool operator () (
      const std::pair<int, wg::WNode<T, W>>& a, 
      const std::pair<int, wg::WNode<T, W>>& b) const {
      // First compare by the 'int' value (node index)
      return a.first > b.first || (a.first == b.first && a.second.node < b.second.node); 
    }
};

namespace algorithms::onlinejudge::graph::tools::dijkstra
{

    constexpr int inf = 1e5;
    template<typename T, typename W>
    using piwn = std::pair<int, wg::WNode<T, W>>;
    typedef std::vector<int> vi;
    typedef std::pair<int, int> pii;
    template<typename T, typename W>
    using PQ = std::priority_queue<std::pair<int, wg::WNode<T, W>>, std::vector<std::pair<int, wg::WNode<T, W>>>, Compare<T, W>>;

    template<typename T = tools::Unit, typename W = int>
    struct Dijkstra
    {
        std::vector<W> dist;
        PQ<T, W> queue;
        Dijkstra(int V, const wg::WNode<T, W>& source) {
          const W inf = std::numeric_limits<W>::max();
          dist.assign(V, inf);
          dist[source.node] = 0;
          queue.emplace(0, source);
        }
    };
    
    // priority queue
    template<typename T, typename W>
    void dijkstra(
      const wg::WGraph<T, W>& graph, 
      Dijkstra<T, W>& dijkstra_s) {
      auto& queue = dijkstra_s.queue;
      while(!queue.empty()) {
        piwn<T, W> p = queue.top(); queue.pop();
        int d = p.first;
        wg::WNode<T, W> node = p.second;
        int u = node.node;
        if(d > dijkstra_s.dist[u]) continue; // lazy deletion
        for(const wg::WNode<T, W>& neigh : graph[u]) {
          int v = neigh.node;
          W w = neigh.weight;
          if(dijkstra_s.dist[v] > 
             dijkstra_s.dist[u] + w) {
            dijkstra_s.dist[v] = dijkstra_s.dist[u] + w;
            queue.emplace(dijkstra_s.dist[v], neigh);
          }
        }
      }
    }
}