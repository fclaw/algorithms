#include <vector>

namespace algorithms::graph::leetcode::cc
{

using graph = std::vector<std::vector<int>>;
using adj = std::vector<std::vector<int>>;
using edges = std::vector<std::vector<int>>;

    /** 
     * https://leetcode.com/problems/critical-connections-in-a-network
     * 
     * There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections 
     * forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. 
     * Any server can reach other servers directly or indirectly through the network.
     * A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
     * Return all critical connections in the network in any order.
     */
    int N;
    int dfs_num = 0;
    std::vector<int> dfs_disc;
    std::vector<int> dfs_low;
    edges ans;
    void dfs(const graph& g, int u, int p)
    {
        dfs_disc[u] = dfs_low[u] = ++dfs_num;
        for(auto v : g[u])
        {
            if (v == p) continue;
            if (!dfs_disc[v])
            {
                dfs(g, v, u);
                if (dfs_disc[u] < dfs_low[v])
                  ans.push_back({u, v});
                dfs_low[u] = std::min(dfs_low[u], dfs_low[v]);
            } 
            else dfs_low[u] = std::min(dfs_low[u], dfs_disc[v]);
        }
    }
    edges criticalConnections(int n, const graph& connections) 
    {
        N = n;
        adj adj_list(N);
        dfs_disc = dfs_low = std::vector<int>(N);
        for(auto c : connections)
        {
            int from = c[0];
            int to = c[1];
            adj_list[from].push_back(to);
            adj_list[to].push_back(from);
        }

        for(int u = 0; u < N; u++)
          if (!dfs_disc[u]) dfs(adj_list, u, u);
        
        return ans;
    }
}