#include <vector>
#include <unordered_map>


namespace algorithms::graph::leetcode::cheapest_flight
{

using graph = std::vector<std::vector<int>>;
using adj_list = std::vector<std::vector<std::pair<int, int>>>;
using memo = std::unordered_map<int, std::unordered_map<int, int>>;

    /** 
     * https://leetcode.com/problems/cheapest-flights-within-k-stops
     * There are n cities connected by some number of flights. 
     * You are given an array flights where flights[i] = [from, to, price] 
     * indicates that there is a flight from city from(i) to city to(i) with cost price(i).
     * You are also given three integers src, dst, and k, 
     * return the cheapest price from src to dst with at most k stops. 
     * If there is no such route, return -1
    */
    int N;
    int K;
    int D;
    const int inf = 5 * 1e+05;
    int dfs(const adj_list& adj, int u, int k, memo& m)
    {
        if(u == D)
          return 0;
 
        if (auto it = m.find(u); it != m.end())
          if(it->second.find(k) != it->second.end())
            return (*(it->second.find(k))).second;

        int cost = inf;
        for(auto v : adj[u])
          if(k <= K)
            cost = std::min(cost, v.second + dfs(adj, v.first, k + 1, m));
        return m[u][k] = cost;
    }
    int findCheapestPrice(int n, const graph& flights, int src, int dst, int k) 
    {
        N = n;
        K = k;
        D = src;
        adj_list adj(N);
        for(auto fl : flights)
        {
            int src = fl[1];
            int dest = fl[0];
            int c = fl[2];
            adj[src].push_back({dest, c});
        }
        memo m;
        auto ans = dfs(adj, dst, 0, m);
        return ans != inf ? ans : -1;
    }
}