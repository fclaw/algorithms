#include <vector>
#include <optional>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <sstream>
#include "../lp_dag.cpp"


namespace algorithms::graph::onlinejudge::project_scheduling
{

namespace lp = algorithms::graph::lp_dag;
typedef std::vector<int> ds;
typedef std::vector<int> table;


const int MAX = 28;

    int taskToNode(char c) { return (int)c - 65; }

    /** https://onlinejudge.org/external/4/452.pdf */
    int timeRequired(int start, const lp::adj& graph, const ds& days)
    {
        auto s = std::make_optional(start);
        int V = graph.size();
        lp::vs vertices = lp::topological_sort(V, s, graph);
        table dp(V, 0);
        dp[start] = days[start];  
        for(auto v : vertices)
          for(auto u : graph[v])
            dp[u] = std::max(dp[u], days[u] + dp[v]);
        return *std::max_element(dp.begin(), dp.end());
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(freopen(file.value(), "r", stdin) != nullptr);
        int tests;
        std::cin >> tests;
        std::cin.ignore();
        std::cin.ignore();
        while(tests-- > 0)
        {
            std::string in;
            char node, dep;
            int d;
            std::vector<int> starts;
            ds days(MAX, -1);
            lp::adj graph(MAX);
            while(std::getline(std::cin, in))
            {
                if(in.length() == 0)
                  break;
                std::stringstream ss(in);
                ss >> node >> d;
                int v = taskToNode(node);
                days[v] = d;
                bool isRoot = true;
                while(ss >> dep)
                {
                   isRoot = false;
                   graph[taskToNode(dep)].push_back(v);
                }

               if(isRoot) starts.push_back(v);

            }
            int ans = 0;
            for(auto s : starts)
              ans = std::max(ans, timeRequired(s, graph, days));
            printf("%d\n\n", ans);
        }
    }
}