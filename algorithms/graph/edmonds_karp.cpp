#pragma once
#include <vector>
#include <queue>
#include <optional>
#include <cassert>
#include <limits>

/**
 *  some notes on improvements
 *  The main weakness of the simple code shown in this section is that
 *  enumerating the neighbors of a vertex takes O(V) instead of O(k) (where k is the number
 *  of neighbors of that vertex). The other (but not significant) weakness is that we also do
 *  not need vi dist as bitset (to flag whether a vertex has been visited or not) is sufficient
 *  Modify the Edmonds Karp’s code above so that it achieves its O(VE2) time complexity
 */


namespace algorithms::graph::max_flow
{

typedef std::vector<int> vi;
typedef std::vector<std::vector<int>> res;

const int inf = numeric_limits<int>::max();
// int MAX_V = 40; // enough for sample graph in Figure 4.21/4.22/4.23/UVa 259
int MAX_V;

int max_flow, flow, source, sink; vi p, dist; // global variables
res residual_graph;


    void augment(int v, int minEdge)
    {  // traverse BFS spanning tree from s to t
        if (v == source) 
        { flow = minEdge; return; }  // record minEdge in a global variable f
        
        if (p[v] != -1)
        {
            int w = std::min(minEdge, residual_graph[p[v]][v]);
            augment(p[v], w); // recursive
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
            // run BFS, compare with the original BFS shown in Section 4.2.2
             flow = 0; // reset flow to zero on every iteration
             std::queue<int> q; 
             q.push(source);
             dist.assign(MAX_V, inf); 
             dist[source] = 0; 
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

typedef int cost;
typedef std::tuple<int, int, cost> edge;
typedef std::vector<edge> graph;

    void test(std::optional<char*> file)
    {
        if(!file.has_value())
          std::cout << "the file must be provided!\n";

        assert(freopen(file.value(), "r", stdin) != NULL);
        graph g;
        int V, edges, s, t, touchstone;
        std::cin >> V >> edges >> s >> t >> touchstone;
        while(--edges >= 0)
        {
            int from, to, w;
            std::cin >> from >> to >> w;
            --from; --to;
            g.push_back({from, to, w});
            g.push_back({to, from, w});
        }

        MAX_V = V;
        source = --s;
        sink = --t;
        residual_graph.resize(MAX_V);
        for(auto& x : residual_graph)
          x.resize(MAX_V);

        for(int i = 0; i < MAX_V; i++)
          for(int j = 0; j < MAX_V; j++)
            residual_graph[i][j] = 0;
        
        for(edge t : g)
        {
            int from = std::get<0>(t);
            int to = std::get<1>(t);
            cost c = std::get<2>(t);
            residual_graph[from][to] = c;
        }

        edmonds_karp();
        assert(max_flow == touchstone);
        std::cout << "ok!";
    }
}