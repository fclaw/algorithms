#include <vector>

namespace algorithms::graph::dijkstra
{

using graph = std::vector<std::tuple<int, int, int>>;
using dist = std::vector<int>;

    /**
     * A straightforward implementation keeps track of which vertices are in X 
     * by associating a Boolean variable with each vertex. 
     * Each iteration, it performs an exhaustive search through all the edges, 
     * computes the Dijkstra score for each edge with tail in X 
     * and head outside X (in constant time per edge), 
     * and returns the crossing edge with the smallest score (or correctly identifies that
     * no crossing edges exist). After at most n - 1 iterations, 
     * the Dijkstra algorithm runs out of new vertices to add to its set X. 
     * Because the number of iterations is O(n) and each takes time O(m), the overall running time is O(mn).
     * 
     */
    const int inf = 5 * (int)1e+05;
    dist sf_dijkstra(int v, const graph& g, int src)
    {
        std::vector<int> dist(v, inf);
        int V = v;
        int E = g.size();
        dist[src] = 0;
        int c = V + E;
        while(--c >= 0)
        {
            int min = inf;
            int vertex;
            for(int k = 0; k < V; k++)
              if(dist[k] != inf)
              {
                  for(int e = 0; e < E; e++)
                  {
                      int from, to, w;
                      std::tie(from, to, w) = g[e];
                      if(from == k && dist[to] == inf)
                        if(dist[from] + w < min)
                        {
                            vertex = to;
                            min = dist[from] + w;
                        }
                  }
              }
            dist[vertex] = min;
        }
        return dist;
    }
}