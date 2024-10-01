/** https://onlinejudge.org/external/115/11506.pdf */

#include <vector>
#include <tuple>
#include <cstdio>
#include <unordered_map>
#include <cassert>
#include <unordered_set>
#include "../edmonds_karp.cpp"

namespace algorithms::graph::onlinejudge::angry_programmer
{

typedef int cost;
typedef std::vector<std::vector<std::pair<int, int>>> adj;
typedef std::vector<std::vector<int>> adj_matrix;
typedef std::vector<int> vv;
typedef std::unordered_set<int> sv;
typedef std::unordered_map<int, int> mi;

namespace mf = algorithms::graph::max_flow;



   /** Minimum Cut problem
    *  Let’s define an s-t cut C = (S-component, T-component) as a partition of V ∈ G such that
    *  source s ∈ S-component and sink t ∈ T-component.
    * The by-product of computing Max Flow is Min Cut! 
    * After Max Flow algorithm stops, we run graph traversal (DFS/BFS)
    * from source s again. All reachable vertices from source s using positive weighted edges in 
    * the residual graph belong to the S-component. All other unreachable vertices belong to the T-component (i.e. vertex 1 and 3). 
    * All edges connecting the S-component to the T-component belong to the cut-set of C */
   void performEdmondsKarp(int V, int director, int server, const adj_matrix& graph)
   {
        mf::MAX_V = V;
        mf::source = director;
        mf::sink = server;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = graph[i][j];

        mf::edmonds_karp();
   }

    /** dfs based function to find all reachable vertices from s. 
     *  The function marks visited[i] as true if i is reachable from s. 
     *  The initial values in visited[] must be false. 
     * We can also use BFS to find reachable vertices */
    void reachableVertices(int V, int s, sv& visited)
    {
        visited.insert(s);
        for (int i = 0; i < V; i++)
          if(mf::residual_graph[s][i] > 0 && 
             visited.find(i) == visited.end())
            reachableVertices(V, i, visited);
    }

   void submit(std::optional<char*> file)
   {
      if(file.has_value())
        assert(freopen(file.value(), "r", stdin) != NULL);
      int vertices, edges;
      while(true)
      {
          std::cin >> vertices >> edges;
          if(vertices == 0 && edges == 0) break;
          
          int director = 0;
          int server = vertices - 1;
          // machine number
          int mn = vertices - 2;
          // overall vertices in the network amount to two times the number of machines plus director and server
          int V = mn * 2 + 2 + 1;
          adj_matrix graph = adj_matrix(V, vv(V, 0));
          graph[server][server] = graph[director][director] = INT32_MAX;
          int ans = 0;
          while(--mn >= 0)
          {
              int i, cost;
              std::cin >> i >> cost;
              int from = --i;
              int to = vertices + from;
              graph[from][to] = cost;
          }
          printf("%d\n", ans);
      }
   }
}