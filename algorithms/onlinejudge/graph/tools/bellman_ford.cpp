/* courtesy of https://github.com/stevenhalim/cpbook-code/blob/master/ch4/sssp/bellman_ford.cpp */

#pragma once

#include "dfs.cpp"

#include <queue>
#include <functional>


namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::tools::bellman_ford
{

    constexpr int inf = 1e5;
    typedef std::vector<int> vi;
    typedef std::pair<int, int> pii;

    struct BellmanFord
    {
        vi dist;
        // For some improvement, we can add a Boolean flag modified = false in the outermost
        // loop (the one that repeats all E edges relaxation V -1 times). If at least one relaxation
        // operation is done in the inner loops (the one that explores all E edges), set modified = true.
        // We immediately break the outermost loop if variable modified is still false after all E edges
        // have been examined. If this no-relaxation happens at the (outermost) loop iteration i, then
        // there will be no further relaxation in iteration i+1, i+2, . . . , i = V -1 either. This way, the
        // time complexity of Bellman-Ford becomes O(kV) where k is the number of iteration of the
        // outermost loop. Note that k is still O(V ) though
        bool hasNegativeCycle;
        int V;
        BellmanFord(int V, int source) {
          this->V = V;
          dist.assign(V, inf);
          dist[source] = 0;
          hasNegativeCycle = false;
        }
    };
    
    template<typename T>
    void bellman_ford(
      const tools::Graph<T>& graph, 
      BellmanFord& bellman_s) {
      int V = bellman_s.V;
      for(int i = 0; i < V - 1; ++i) {             // total O(V*E)
        bool modified = false;                     // optimization
        for(int u = 0; u < V; ++u)                 // these two loops = O(E)
          if (dist[u] != inf)                      // important check
            for(tools::Node<T>& n : graph[u]) {
              if(dist[u] + n.value < dist[v]) {
                dist[v] = dist[u]+w;                // relax operation
                modified = true;                    // optimization
              }                   
            }
        // no more relaxations has happened in the second loop    
        if(!modified) break;                        // optimization
      }

      bool hasNegativeCycle = false;
      for(int u = 0; u < V; ++u)                     // one more pass to check
        if(dist[u] != inf)
          for(tools::Node<T>& n : graph[u])
            // As the corollary: if we can still relax an edge, 
            // there must be at least one negative cycle in our weighted graph.
            if(dist[v] > dist[u] + n.value)          // should be false
              hasNegativeCycle = true;               // if true => -ve cycle
    }
}