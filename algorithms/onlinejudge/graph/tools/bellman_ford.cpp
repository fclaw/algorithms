/* courtesy of https://github.com/stevenhalim/cpbook-code/blob/master/ch4/sssp/bellman_ford.cpp */

#pragma once

#include "w_graph.cpp"

#include <queue>
#include <functional>


namespace wg = algorithms::onlinejudge::graph::tools::wg;


template<typename W>
inline constexpr W inf = std::numeric_limits<W>::max();

namespace algorithms::onlinejudge::graph::tools::bellman_ford
{

    template<typename T = tools::Unit, typename W = int>
    struct BellmanFord
    {
        int V;
        std::vector<W> dist;
        // For some improvement, we can add a Boolean flag modified = false in the outermost
        // loop (the one that repeats all E edges relaxation V -1 times). If at least one relaxation
        // operation is done in the inner loops (the one that explores all E edges), set modified = true.
        // We immediately break the outermost loop if variable modified is still false after all E edges
        // have been examined. If this no-relaxation happens at the (outermost) loop iteration i, then
        // there will be no further relaxation in iteration i+1, i+2, . . . , i = V -1 either. This way, the
        // time complexity of Bellman-Ford becomes O(kV) where k is the number of iteration of the
        // outermost loop. Note that k is still O(V ) though
        bool hasNegativeCycle;
        std::function<W(W, W)> mappend;
        BellmanFord(
          int V, 
          const wg::WNode<T, W>& source, 
          std::function<W(W, W)> mappend) {
          this->V = V;
          dist.assign(V, inf<W>);
          dist[source.node] = 0;
          hasNegativeCycle = false;
          this->mappend = mappend;
        }
    };
    
    template<typename T, typename W>
    void bellman_ford(
      const wg::WGraph<T, W>& graph, 
      BellmanFord<T, W>& bellman_s) {
      int V = bellman_s.V;
      for(int i = 0; i < V - 1; ++i) {             // total O(V*E)
        bool modified = false;                     // optimization
        for(int u = 0; u < V; ++u)                 // these two loops = O(E)
          if (dist[u] != inf<W>)                   // important check
            for(wg::WNode<T, W>& n : graph[u]) {
              W nw = bellman_s.mappend(dist[u], n.weight);
              if(nw < dist[v]) {
                dist[v] = nw                       // relax operation
                modified = true;                   // optimization
              }                   
            }
        // no more relaxations has happened in the second loop    
        if(!modified) break;                        // optimization
      }

      bool hasNegativeCycle = false;
      for(int u = 0; u < V; ++u)                     // one more pass to check
        if(dist[u] != inf<W>) {
          for(wg::WNode<T, W>& n : graph[u]) {
            W w = bellman_s.mappend(dist[u], n.weight)
            // As the corollary: if we can still relax an edge, 
            // there must be at least one negative cycle in our weighted graph.
            // should be false
            if(dist[v] > w) hasNegativeCycle = true; // if true => -ve cycle
          }
        }
    }


    template<typename T = tools::Unit, typename W = int>
    struct BellmanFordMoore
    {
        int V;
        std::vector<W> dist;
        std::queue<int> queue;
        tools::vi in_queue;
        std::function<W(W, W)> mappend;
        BellmanFordMoore(
          int V,
          const wg::WNode<T, W>& source, 
          std::function<W(W, W)> mappend) {
          this->V = V;
          dist.assign(V, inf<W>);
          dist[source.node] = 0;
          in_queue.assign(V, 0);
          in_queue[source.node] = 1;
          queue.push(source.node);
          this->mappend = mappend;
        }
    };

    template<typename T, typename W>
    void bellman_ford_moore(
      const wg::WGraph<T, W>& graph,
      BellmanFordMoore<T, W>& bellman_s) {
      auto queue = bellman_s.queue;
      while (!q.empty()) {
        int u = q.front(); q.pop(); 
        bellman_s.in_queue[u] = 0;               // pop from queue
        for(wg::WNode<T, W>& n : graph[u]) {
          W w = bellman_s.mappend(dist[u], n.weight);
          if(w >= dist[v]) continue;             // not improving, skip
          dist[v] = w;                           // relax operation
          if(!in_queue[v]) {                     // add to the queue
            q.push(v);                           // only if v is not
            in_queue[v] = 1;                     // already in the queue
          }
        }
      }
    }
}