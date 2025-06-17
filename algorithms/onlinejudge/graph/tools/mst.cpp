/*
--------------------------------------------
 Prim's vs Kruskal's Algorithm (MST Summary)
--------------------------------------------

🔹 Purpose: 
  Both algorithms find a Minimum Spanning Tree (MST) of a weighted undirected graph.

🔹 Key Differences:

1. Strategy:
   - Prim's: Grows the MST one vertex at a time, always choosing the minimum-weight edge
             that connects a new vertex to the growing tree.
   - Kruskal's: Adds edges one by one in increasing order of weight, ensuring no cycles are formed.

2. Data Structure:
   - Prim's: Uses a priority queue (min-heap) to select the next lightest edge.
   - Kruskal's: Uses Disjoint Set Union (Union-Find) to track connected components and avoid cycles.

3. Edge vs Vertex Focus:
   - Prim's: Vertex-based; starts from any node and expands outward.
   - Kruskal's: Edge-based; sorts all edges up front and processes them globally.

4. Graph Requirements:
   - Prim's: Requires a connected graph to function properly.
   - Kruskal's: Can handle disconnected graphs (returns a forest of MSTs).

5. Time Complexity:
   - Prim's: O(E log V) with min-heap and adjacency list.
   - Kruskal's: O(E log E) due to edge sorting and DSU operations.

🔹 When to Use:
   - Prim’s is preferred for dense graphs (many edges).
   - Kruskal’s is better for sparse graphs (fewer edges).

*/

#include "w_graph.cpp"
#include "uf.cpp"

#include <queue>
#include <tuple>
#include <algorithm>


namespace wg = algorithms::onlinejudge::graph::tools::wg;
namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::tools::mst
{
     typedef std::pair<int, int> ii;
     tools::vb taken;                                 // to avoid cycle
     std::priority_queue<ii> pq;                      // to select shorter edges


     template <typename T, typename W> 
     void enqueue_neighs(const wg::WGraph<T, W>& graph, int u, bool is_min) { // set u as taken and enqueue neighbors of u
        taken[u] = true;
        for(wg::WNode<T, W>& n : graph)
          if(!taken[n.node]) {
            if(is_min) n.weight = -n.weight;
            pq.push({n.weight, -n.node});  // sort by non-dec weight, then by inc id
        }
     }

    template <typename T, typename W>    
    int prim(const wg::WGraph<T, W>& graph, int V, int start, bool is_min) {
      taken.assign(V, false);
      enqueue_neighs(graph, start, is_min);
      int mst_cost = 0, num_taken = 0;              // no edge has been taken
      while(!pq.empty()) {                          // up to O(E)
         auto [w, u] = pq.top(); pq.pop();          
        if(is_min) w = -w; 
        u = -u;                                     // negate to reverse order
        if (taken[u]) continue;                     // already taken, skipped
        mst_cost += w;                              // add w of this edge
        enqueue_neighs(graph, u, is_min);           // take+process vertex u
        ++num_taken;                                // 1 more edge is taken
        if(num_taken == V - 1) break;               // optimization
      }
      return mst_cost;
    }

    template <typename W>
    struct Edge 
    {
        int from;
        int to;
        W weight;
    };

    template <typename W>
    bool operator < (const Edge<W>& lhs, const Edge<W>& rhs) {
      return lhs.weight < rhs.weight || 
             (lhs.weight < rhs.weight && 
              (std::tie(lhs.from, lhs.to) < 
               std::tie(rhs.from, rhs.to)));
    }

    template <typename W>
    using VEdge = std::vector<Edge<W>>;

    template<typename T = int>
    Edge<T> mkDefEdge(int from, int to, T weight) {
      return Edge<T>{from, to, weight};
    }

    template <typename W> 
    int kruskal(const VEdge<W>& edges, int V, int E, bool is_min) {
      auto cmp = is_min ? std::less<Edge<W>>() : std::greater<Edge<W>>();
      std::sort(edges.begin(), edges.end(), cmp);
      int mst_cost = 0, num_taken = 0;               // no edge has been taken
      tools::UnionFind uf(V);
      for(int i = 0; i < E; ++i) {                  // up to O(E)
        Edge<W> e = edges[i];              
        if(uf.isSameSet(e.from, e.to)) continue;     // already in the same CC
        mst_cost += e.weight;                        // add w of this edge
        uf.unionSet(e.from, e.to);                   // link them
        ++num_taken;                                 // 1 more edge is taken
        if(num_taken == V - 1) break;                // optimization
       }
      return mst_cost;
    }
}