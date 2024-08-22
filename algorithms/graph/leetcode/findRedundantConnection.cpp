#include <vector>


namespace algorithms::graph::leetcode::redundant_connection
{

using graph = std::vector<std::vector<int>>;
using edges = std::vector<std::vector<int>>;
using bridge = std::vector<int>;
using adj = std::vector<std::vector<int>>;


    /**
     *  https://leetcode.com/problems/redundant-connection
     *  seems about bridges
     *  In this problem, a tree is an undirected graph that is connected and has no cycles.
     *  You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. 
     *  The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. 
     *  The graph is represented as an array edges of length n where edges[i] = [ai, bi] 
     *  indicates that there is an edge between nodes ai and bi in the graph.
     *  Return an edge that can be removed so that the resulting graph is a tree of n nodes. 
     *  If there are multiple answers, return the answer that occurs last in the input.
     */
    int N;
    int dfs_num = 0;
    std::vector<int> dfs_disc;
    std::vector<int> dfs_low;
    edges es;
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
                  es.push_back({u, v});
                dfs_low[u] = std::min(dfs_low[u], dfs_low[v]);
            } 
            else dfs_low[u] = std::min(dfs_low[u], dfs_disc[v]);
        }
    }
    bridge findRedundantConnection(const edges& edges)
    {
        N = edges.size();
        adj adj_list(N);
        dfs_disc = dfs_low = std::vector<int>(N);
        for(auto c : edges)
        {
            int from = c[0];
            int to = c[1];
            adj_list[from - 1].push_back(to - 1);
            adj_list[to - 1].push_back(from - 1);
        }

        for(int u = 0; u < N; u++)
          if (!dfs_disc[u]) dfs(adj_list, u, u);

        if(!es.empty())
        {
            int i = N;
            while(--i >= 0)
            {
                std::vector<int> e = {edges[i][0] - 1, edges[i][1] - 1};
                std::vector<int> re = {edges[i][1] - 1, edges[i][0] - 1};
                auto pred = [&e, &re](std::vector<int> v) 
                { return (v == e) || (v == re); };
                auto it = std::find_if(es.begin(), es.end(), pred);
                if(it == es.end()) break;
            }
            return edges[i];
        }
        else return edges.back();
    }
}