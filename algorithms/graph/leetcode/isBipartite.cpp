#include <vector>
#include <queue>

// https://leetcode.com/problems/is-graph-bipartite
/**
 * Formally, a graph G = (V, E) is bipartite if and only if
 * its vertex set V can be partitioned into two non-empty subsets X and Y, 
 * such that every edge in E has one endpoint in X and the other endpoint in Y. 
 * This partition of vertices is also known as bi-partition
 * To identify whether a given graph is bipartite, you can use the following algorithm:
 * Choose any vertex in the graph and assign it to one of the two sets, say X.
 * Assign all of its neighbors to the other set, say Y.
 * For each vertex in set Y, assign its neighbors to set X, and for each vertex in set X, assign its neighbors to set Y.
 * Repeat step 3 until all vertices have been assigned to a set.
 * Check if any two adjacent vertices are in the same set. 
 * If yes, then the graph is not bipartite. Otherwise, it is bipartite.
 */
namespace algorithms::graph::leetcode::bipartite
{

using graph = std::vector<std::vector<int>>;
enum Colour { White = 0, Black = 1, None = 2 };

    int V;
    bool isBipartiteBfs(const graph& g, std::vector<Colour>& c)
    {
        std::queue<int> q;
        bool isBipartite = true;
        for(int i = 0; i < V && isBipartite; i++)
        {
          if(c[i] != None)
            continue;
          q.push(i);
          c[i] = White;
          while(!q.empty() && 
                isBipartite)
          {
            int u = q.front();
            q.pop();
            for(auto v : g[u])
              if(c[v] == None)
              {
                c[v] = (Colour)(1 - c[u]);
                q.push(v);
              }
              else if(c[v] == c[u]) 
              {
                isBipartite = false;
                break;   
              }
          }
        }
        return isBipartite;
    }
    bool isBipartite(const graph& g) 
    {
        V = g.size();
        std::vector<Colour> c(V, None);
        return isBipartiteBfs(g, c);
    }
}