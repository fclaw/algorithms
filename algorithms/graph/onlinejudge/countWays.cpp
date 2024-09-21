#include <vector>
#include <cstdio>

namespace algorithms::graph::onlinejudge::ways_to_live
{


typedef std::vector<std::vector<int>> graph;
typedef std::vector<int> table;
typedef std::vector<int> terminus;


    /** https://onlinejudge.org/external/9/988.pdf
     * UVa 988 - Many paths, one destination
     * Motivating problem (UVa 988 - Many paths, one destination): In life, one has many paths
     * to choose, leading to many different lives. Enumerate how many different lives one can live,
     * given a specific set of choices at each point in time. One is given a list of events, and a
     * number of choices that can be selected, for each event. The objective is to count how many
     * ways to go from the event that started it all (birth, index 0) to an event where one has no 
     * further choices (that is, death, index n).
     * Clearly the underlying graph of the problem above is a DAG as one can move forward in
     * time, but cannot go backward. The number of such paths can be found easily by computing
     * one (any) topological order in O(V +E) (in this problem, vertex 0/birth will always be the
     * first in the topological order and the vertex n/death will always be the last in the topological
     * order). We start by setting num paths[0] = 1. Then, we process the remaining vertices
     * one by one according to the topological order. When processing a vertex u, we update each
     * neighbor v of u by setting num paths[v] += num paths[u]. After such O(V + E) steps, 
     * we will know the number of paths in num paths[n] */
    int countWays(int sink, const graph& g) { return 1; }
}

namespace wl = algorithms::graph::onlinejudge::ways_to_live;

int submit_wl()
{
    int v;
    bool line = false;
    while((bool)scanf("%d", &v))
    {
        if(v == 0) break;
        wl::graph g(v, std::vector<int>());
        for(int i = 0; i < v; i++)
        {
            int m, x;
            scanf("%d", &m);
            for(int j = 0; j < m; j++)
              scanf("%d", &x),
              g[i].push_back(x);

        }
        line ? printf("\n") : line = true;
        int ans = 0;
        ans = wl::countWays(--v, g);
        printf("%d\n\n", ans);
    }
    return 0;
}