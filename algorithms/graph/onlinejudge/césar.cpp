#include <vector>
#include <optional>
#include <iostream>
#include <cassert>
#include <cstdio>
#include "../lp_dag.cpp"


namespace algorithms::graph::onlinejudge::césar
{

typedef std::vector<int> table;
namespace lp = algorithms::graph::lp_dag;

     /** https://onlinejudge.org/external/100/10000.pdf */
    std::pair<int, int> longestPath(int start, int V, const lp::adj& graph)
    {
        auto s = std::make_optional(start);
        lp::vs vertices = lp::topological_sort(V, s, graph);
        table dp(V, 0);
        for(auto v : vertices)
          for(auto u : graph[v])
            dp[u] = std::max(dp[u], 1 + dp[v]);
        /** if there are several paths of maximum length, print the final place with smallest number */
        int place = V - 1;
        int path = *std::max_element(dp.begin(), dp.end());
        for(int i = 0; i < V; i++)
          if(dp[i] == path) place = std::min(place, i);
        return {path, ++place};
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(freopen(file.value(), "r", stdin) != NULL);
        int V;
        int c = 0;
        while(true)
        {
            std::cin >> V;
            if(V == 0) break;
            int start;
            std::cin >> start;
            int from, to;
            lp::adj graph(V);
            while(true)
            {
                std::cin >> from >> to;
                if(from == 0 && to == 0)
                  break;
                --from; --to;
                graph[from].push_back(to);
            }
            auto ans = longestPath(--start, V, graph);
            // Case 1: The longest path from 1 has length 1, finishing at 2
            int place = ans.second;
            int length = ans.first;
            printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n", ++c, ++start, length, place);
        }
    }
}