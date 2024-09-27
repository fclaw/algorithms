#include <vector>
#include <cstdio>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <optional>
#include "../lp_dag.cpp"

namespace algorithms::graph::onlinejudge::ways_to_live
{

typedef std::vector<int> table;
namespace lp = algorithms::graph::lp_dag;


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
    int countWays(const lp::adj& graph, const std::vector<int>& sinks) 
    {
        lp::vs vertices = lp::topological_sort(graph.size(), std::nullopt, graph);
        table dp(graph.size(), 0);
        dp[0] = 1;
        for(auto v : vertices)
          for(auto u : graph[v])
            dp[u] += dp[v];

        int events = 0;
        for(auto s : sinks)
          events += dp[s];

        return events;
    }
}

namespace wl = algorithms::graph::onlinejudge::ways_to_live;

void submit_wl(std::optional<char*> file)
{
    if(file.has_value())
      assert(freopen(file.value(), "r", stdin) != NULL);
    int v;
    bool line = false;
    while((std::cin >> v))
    {
        if(v == 0) break;
        wl::lp::adj graph(v);
        std::vector<int> sinks;
        for(int i = 0; i < v; i++)
        {
            int m, x;
            std::cin >> m;
            if(m == 0) sinks.push_back(i);
            for(int j = 0; j < m; j++)
              std::cin >> x,
              graph[i].push_back(x);

        }
        line ? printf("\n") : line = true;
        printf("%d\n", wl::countWays(graph, sinks));
    }
}