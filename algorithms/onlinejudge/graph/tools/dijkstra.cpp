
#pragma once

#include "w_graph.cpp"

#include <queue>
#include <functional>


namespace wg = algorithms::onlinejudge::graph::tools::wg;


template<typename W>
inline constexpr W inf = std::numeric_limits<W>::max();

// Custom comparator for the priority queue
template<typename T, typename W>
struct DijkstraCmp {
    bool operator () (
      const std::pair<int, wg::WNode<T, W>>& a, 
      const std::pair<int, wg::WNode<T, W>>& b) const {
      // First compare by the 'int' value (node index)
      return a.first > b.first || (a.first == b.first && a.second.node < b.second.node); 
    }
};

namespace algorithms::onlinejudge::graph::tools::dijkstra
{

    template<typename T, typename W>
    using piwn = std::pair<int, wg::WNode<T, W>>;
    typedef std::vector<int> vi;
    typedef std::pair<int, int> pii;
    template<typename T, typename W>
    using PQ = std::priority_queue<std::pair<int, wg::WNode<T, W>>, std::vector<std::pair<int, wg::WNode<T, W>>>, DijkstraCmp<T, W>>;

    template<typename T = tools::Unit, typename W = int>
    struct Dijkstra
    {
        std::vector<W> dist;
        PQ<T, W> queue;
        std::function<W(W, W)> mappend;
        std::function<void(int, int)> on_relaxation;
        std::function<void(int, int)> on_tied_path;
        Dijkstra(
          int V, 
          const wg::WNode<T, W>& source, 
          std::function<W(W, W)> mappend) {
          dist.assign(V, inf<W>);
          dist[source.node] = 0;
          queue.emplace(0, source);
          this->mappend = mappend;
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