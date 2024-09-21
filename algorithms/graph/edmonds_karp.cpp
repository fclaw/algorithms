#pragma once
#include <vector>
#include <queue>

namespace algorithms::graph::mf
{

typedef std::vector<int> vi;
typedef std::vector<std::vector<int>> res;

const int inf = 5 * 1e+05;
// int MAX_V = 40; // enough for sample graph in Figure 4.21/4.22/4.23/UVa 259
int MAX_V;

int max_flow, flow, source, sink; vi p; // global variables
res residual_graph;


    void augment(int v, int minEdge)
    {  // traverse BFS spanning tree from s to t
        if (v == source) 
        { flow = minEdge; return; }  // record minEdge in a global variable f
        else if (p[v] != -1)
        {
            augment(p[v], std::min(minEdge, residual_graph[p[v]][v])); // recursive
            residual_graph[p[v]][v] -= flow; 
            residual_graph[v][p[v]] += flow; // update
        }
    }

    // O(VE^2) (actually O(V^3E) Edmonds Karp's algorithm
    void edmonds_karp()
    {
        // mf stands for max_flow
         max_flow = 0;
         while (true) 
         {
             flow = 0;
             // run BFS, compare with the original BFS shown in Section 4.2.2
             vi dist(MAX_V, inf); 
             dist[source] = 0; 
             std::queue<int> q; 
             q.push(source);
             // record the BFS spanning tree, from source to sink
             p.assign(MAX_V, -1);
             while (!q.empty()) 
             {
                int u = q.front(); 
                q.pop();
                // immediately stop BFS if we already reach sink t
                if (u == sink) break;
                // note: this part is slow
                for (int v = 0; v < MAX_V; v++)
                  if (residual_graph[u][v] > 0 && 
                      dist[v] == inf)
                    dist[v] = dist[u] + 1, q.push(v), p[v] = u;
             }
             augment(sink, inf);     // find the min edge weight `f' along this path, if any
             if (flow == 0) break;      // we cannot send any more flow (`f' = 0), terminate
             max_flow += flow;                 // we can still send a flow, increase the max flow!
         }
    }
}