#include <vector>
#include <cassert>
#include <optional>
#include <unordered_set>
#include <iostream>
#include <cstdio>

namespace algorithms::graph::onlinejudge::salesman
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<std::vector<int>> adj_list;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::unordered_set<int> si;
typedef std::vector<vi> table;

const int inf = 5 * 1e+05;
const int MAX_CITIES = 110;
const int MAX_POINTS = 1010;


    /** https://onlinejudge.org/external/107/10702.pdf, state: pos, given speech */
    int optimalItinerary(const adj_list& graph, const vvi& cost, const si& ends, table& memo, int i, int k) 
    {
 
        auto it = ends.find(i);
        if(k < 0 && it != ends.end())
          return 0;

        if(k < 0 && it == ends.end())
          return -inf;

        int &profit = memo[i][k];
        if(~profit) return memo[i][k];

        profit = -inf;
        for(int v : graph[i])
          profit = std::max(profit, cost[i][v] + optimalItinerary(graph, cost, ends, memo, v, k - 1));
        

         return memo[i][k] = profit;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        /** Each set starts with four integers C (2 ≤ C ≤ 100), the number of cities, S (1 ≤ S ≤ 100), the
           identifier of the starting city, E (1 ≤ E ≤ 100), the number of cities his tour can end at, and T
           (1 ≤ T ≤ 1000), the number of inter-city travels he wants to do. */
        int c, start, e, t;
        while(std::cin >> c >> start >> e >> t)
        {
            if(c == 0 && start == 0 && e == 0 && t == 0)
              break;

            adj_list graph(c);
            vvi cost;
            si ends;
            int v;
            loop(i, 0, c)
            {
                vi xs;
                loop(j, 0, c)
                {
                    std::cin >> v;
                    if(v != 0) graph[i].push_back(j);
                    xs.push_back(v);
                }
                cost.push_back(xs);
            }
            loop(i, 0, e)
              std::cin >> v,
              ends.insert(--v);

            table memo(MAX_CITIES, vi(MAX_POINTS, -1));
            int ans = optimalItinerary(graph, cost, ends, memo, --start, --t);
            printf("%d\n", ans < 0 ? 0 : ans);
        }
    }
}