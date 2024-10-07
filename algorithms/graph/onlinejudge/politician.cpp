#include <vector>
#include <cassert>
#include <optional>
#include <iostream>
#include <unordered_map>

namespace algorithms::graph::onlinejudge::politician
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<std::vector<int>> adj_list;
typedef std::vector<int> vi;
typedef std::vector<vi> table;

const int inf = 5 * 1e+05;
const int MAX_VERTICES = 55;
const int MAX_SPEECH = 25;

    /** https://onlinejudge.org/external/105/10543.pdf , 
     * topic: Converting General Graph to DAG
     * state: pos, given speech */
    int S;
    int Capital;
    int ans = 0;
    const int MAX_S = 20;
    int determineMinSpeeches(const adj_list& graph, int i, int s, table& memo)
    {

        if(s >= S && s <= MAX_S && i == Capital)
          return 1;
        
        if(s > MAX_S)
          return inf;

        int &speeches = memo[i][s];
        if(~speeches) return memo[i][s];

        speeches = inf;
        for(auto v : graph[i])
        {
          int res = determineMinSpeeches(graph, v, s + 1, memo);
          if(res != inf) speeches = std::min(speeches, 1 + res);
        }
        return speeches = memo[i][s];
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int v, e, s;
        while(std::cin >> v >> e >> s)
        {
            if(v == 0 && e == 0 && s == 0)
              break;

            S = s;
            Capital = v - 1;
            adj_list graph(v);
            while(--e >= 0)
            {
                int from, to;
                std::cin >> from >> to;
                graph[from].push_back(to);
            }

            table memo(MAX_VERTICES, vi(MAX_SPEECH, -1));
            int speeches = determineMinSpeeches(graph, 0, 1, memo);
            std::string ans = speeches != inf ? std::to_string(speeches) : "LOSER";
            printf("%s\n", ans.c_str());
        }
    }
}