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
   - Prim’s is preferred for dense graphs (many edges). E >= a * V ^ 2
   - Kruskal’s is better for sparse graphs (fewer edges). E <= b * V

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

     // Define comparison: first by weight (ascending), then by id (ascending)
     // smaller weights have higher priority
     // smaller ids have higher priority if weights are equal
     template <typename T, typename W>
     struct PrimCmp {
        bool operator () 
          (const wg::WNode<T, W>& a, 
           const wg::WNode<T, W>& b) const {
            return a.weight > b.weight || 
                   (a.weight == b.weight && 
                    a.node > b.node);
        }
     };

     typedef std::pair<int, int> ii;
     tools::vb taken;
     template <typename T, typename W>
     using queue = std::priority_queue<wg::WNode<T, W>, std::vector<wg::WNode<T, W>>, PrimCmp<T, W>>;

     template <typename T = tools::Unit, typename W = int> 
     struct Prim
     {
         int V;
         W min_cost;
         bool is_finished;
         bool is_min;
         std::function<void(W&, W)> mappend;
         std::function<void(const wg::WNode<T, W>&)> on_adding_point;
     };

     template <typename T = tools::Unit, typename W = int>
     Prim<T, W> initPrim(int V) {
       auto def_mappend = [](W& acc, W val) { acc += val; }; // generic default
       auto def_on_adding_point = [](const wg::WNode<T, W>&) {};
        return {V, W{}, false, true, def_mappend, def_on_adding_point};
     }

     template <typename T, typename W> 
     void enqueue_neighs
       (const wg::WGraph<T, W>& graph, 
        wg::WNode<T, W> node,
        const Prim<T, W>& prim_s,
        queue<T, W>& pq) { // set u as taken and enqueue neighbors of u
        taken[node.node] = true;
        for(wg::WNode<T, W> neigh : graph[node.node]) {
          if(!taken[neigh.node]) {
            auto tmp = neigh;
            if(!prim_s.is_min) tmp.weight *= (-1);
            pq.emplace(tmp);  // sort by non-dec weight, then by inc id
          }
        }
     }

    template <typename T, typename W>    
    void prim
      (const wg::WGraph<T, W>& graph, 
       Prim<T, W>& prim_s, 
       wg::WNode<T, W>& node) {

      if(!prim_s.mappend && 
         !prim_s.on_adding_point) 
        throw std::runtime_error("prim: callbacks are not set!");

      queue<T, W> pq;   
      taken.assign(prim_s.V, false);
      enqueue_neighs(graph, node, prim_s, pq);
      int num_taken = 0;                            // no edge has been taken
      while(!pq.empty()) {                          // up to O(E)
        wg::WNode<T, W> next = pq.top(); pq.pop();
        if(!prim_s.is_min) next.weight *= (-1);
        if(taken[next.node]) continue;                     // already taken, skipped
        prim_s.mappend(prim_s.min_cost, next.weight);       // add w of this edge
        prim_s.on_adding_point(next);
        enqueue_neighs(graph, next, prim_s, pq);        // take+process vertex u
        ++num_taken;                                // 1 more edge is taken
        if(num_taken == prim_s.V - 1 || prim_s.is_finished) break; // optimization
      }
    }

    template <typename W = int>
    struct Edge 
    {
        int from;
        int to;
        W weight;
        Edge(int a, int b, int w) {
          from = std::min(a, b);
          to = std::max(a, b);
          weight = w;
        }
        bool operator == (const Edge& other) const {
          return from == other.from && to == other.to && weight == other.weight;
        }
    };

    template <typename W>
    std::ostream& operator << 
    (std::ostream& out, const Edge<W>& edge) 
    { return out << "{from: " << edge.from << ", to: "  << edge.to << ", w: " << edge.weight << "}"; }


    template <typename W>
    bool operator < (const Edge<W>& lhs, const Edge<W>& rhs) {
      return lhs.weight < rhs.weight || 
             (lhs.weight == rhs.weight && 
              (std::tie(lhs.from, lhs.to) <
               std::tie(rhs.from, rhs.to)));
    }

    template <typename W = int>
    using VEdge = std::vector<Edge<W>>;

    template<typename W = int>
    Edge<W> mkDefEdge(int from, int to, W weight) {
      return Edge<W>(from, to, weight);
    }

    enum EdgeAction {
        Skip,  // Skip the current edge and continue
        GoOn,   // Proceed with the current edge
        Terminate
    };

    template <typename W = int> 
    struct Kruskal
    {
         int E;
         int V;
         W min_cost;
         tools::UnionFind uf;
         bool is_finished;
         std::function<void(W&, W)> mappend;
         std::function<void(int i, const Edge<W>&)> on_adding_edge;
         std::function<bool(const Edge<W>&, const Edge<W>& b)> cmp;
         std::function<EdgeAction(const Edge<W>&)> check_edge;
    };

    template <typename W = int>
    Kruskal<W> initKruskal(int V, int E, W def) {
      auto def_mappend = [](int& acc, int x) { acc += x; };
      auto def_on_adding_edge = [](int _, const Edge<W>& __) {};
      auto def_cmp = 
        [](const Edge<W>& a, const Edge<W>& b) 
        { return a.weight < b.weight; }; // Min-heap
      auto def_check = [](const Edge<W>& _) -> EdgeAction { return GoOn; };
      return {E, V, def, tools::UnionFind(V), false, def_mappend, def_on_adding_edge, def_cmp, def_check};
    }
 
    template <typename W = int>
    void kruskal(VEdge<W>& edges, Kruskal<W>& kruskal_s) {

      if(!kruskal_s.mappend && 
         !kruskal_s.on_adding_edge && 
         !kruskal_s.cmp) 
        throw std::runtime_error("kruskal: callbacks are not set!");

      std::sort(edges.begin(), edges.end(), kruskal_s.cmp);
      int num_taken = 0;                             // no edge has been taken
      tools::UnionFind& uf = kruskal_s.uf;
      for(int i = 0; i < kruskal_s.E; ++i) {         // up to O(E)
        Edge<W> e = edges[i];  
        if(uf.isSameSet(e.from, e.to)) continue;     // already in the same CC

        // decision-making block
        EdgeAction action = kruskal_s.check_edge(e);
        if(action == Skip) continue;
        else if(action == Terminate) break;
        else if(action == GoOn) {
          kruskal_s.mappend(kruskal_s.min_cost, e.weight); // add w of this edge
          uf.unionSet(e.from, e.to);                   // link them
          ++num_taken;                                 // 1 more edge is taken
          kruskal_s.on_adding_edge(i, e);
          if(num_taken == kruskal_s.V - 1 || 
             kruskal_s.is_finished) break;      // optimization
        }
      }
    }
}