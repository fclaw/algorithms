
#pragma once

#include "w_graph.cpp"

#include <queue>
#include <functional>


namespace wg = algorithms::onlinejudge::graph::tools::wg;


template<typename W>
inline constexpr W inf = std::numeric_limits<W>::max();

// Custom comparator for the priority queue
template<typename W, typename T>
struct DijkstraCmp {
    bool operator () (
      const std::pair<int, wg::WNode<W, T>>& a, 
      const std::pair<int, wg::WNode<W, T>>& b) const {
      // First compare by the 'int' value (node index)
      return a.first > b.first || (a.first == b.first && a.second.node < b.second.node); 
    }
};

namespace algorithms::onlinejudge::graph::tools::dijkstra
{

    template<typename W, typename T>
    using piwn = std::pair<int, wg::WNode<W, T>>;
    typedef std::vector<int> vi;
    typedef std::pair<int, int> pii;
    template<typename W, typename T>
    using PQ = std::priority_queue<std::pair<int, wg::WNode<W, T>>, std::vector<std::pair<int, wg::WNode<W, T>>>, DijkstraCmp<W, T>>;

    template<typename W = int, typename T = tools::Unit>
    struct Dijkstra
    {
        std::vector<W> dist;
        PQ<W, T> queue;
        std::function<W(W, W)> mappend;
        std::function<void(int, int)> on_relaxation;
        std::function<void(int, int)> on_tied_path;
        Dijkstra(int V, const wg::WNode<W, T>& source) {
          dist.assign(V, inf<W>);
          dist[source.node] = 0;
          queue.emplace(0, source);
        }
    };
    
    // priority queue
    template<typename W, typename T>
    void dijkstra(
      const wg::WGraph<W, T>& graph, 
      Dijkstra<W, T>& dijkstra_s) {

      if(!dijkstra_s.mappend) 
        throw std::runtime_error("dijkstra: mappend are not set!");

      auto& queue = dijkstra_s.queue;
      while(!queue.empty()) {
        piwn<W, T> p = queue.top(); queue.pop();
        int d = p.first;
        wg::WNode<W, T> node = p.second;
        int u = node.node;
        if(d > dijkstra_s.dist[u]) continue; // lazy deletion
        for(const wg::WNode<W, T>& neigh : graph[u]) {
          int v = neigh.node;
          W w = neigh.weight;
          W nw = dijkstra_s.mappend(dijkstra_s.dist[u], w);
          if(dijkstra_s.dist[v] > nw) {
            dijkstra_s.dist[v] = nw;
            if(dijkstra_s.on_relaxation)
              dijkstra_s.on_relaxation(u, v);
            queue.emplace(nw, neigh);
          }
          else if(dijkstra_s.dist[v] == nw) {
            if(dijkstra_s.on_tied_path)
              dijkstra_s.on_tied_path(u, v);
          }   
        }
      }
    }
}