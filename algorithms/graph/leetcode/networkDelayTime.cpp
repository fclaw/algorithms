#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::network_delay_time
{

using graph = std::vector<std::vector<int>>;
using adj = std::vector<std::vector<std::pair<int, int>>>;
using dist = std::vector<int>;
using vi = std::vector<bool>;
using q = std::priority_queue<std::pair<int, int>>;

    /**
     * https://leetcode.com/problems/network-delay-time
     * You are given a network of n nodes, labeled from 1 to n. You are also given times, 
     * a list of travel times as directed edges times[i] = (ui, vi, wi), 
     * where ui is the source node, vi is the target node, 
     * and wi is the time it takes for a signal to travel from source to target.
     * We will send a signal from a given node src. 
     * Return the minimum time it takes for all the n nodes to receive the signal. 
     * If it is impossible for all the n nodes to receive the signal, return -1
     */
    const int inf = 5 * (int)1e+05;
    int V;
    q queue;
    void dijkstra(const adj& g, dist& d, vi& visited)
    {
        while(!queue.empty())
        {
            int u = queue.top().second;
            queue.pop();
            if(visited[u])
              continue;

            visited[u] = true;

            for(auto x : g[u])
            {
                int v = x.first;
                int w = x.second;
                if(d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                    queue.push({-d[v], v});
                }
            }
        }
    }
    int networkDelayTime(const graph& times, int v, int src) 
    {
        V = v;
        adj adj_list(V);
        std::vector<int> dist(V, inf);
        std::vector<bool> visited(V, false);
        for(auto t : times) // O(e)
        {
            int src = t[0] - 1;
            int dest = t[1] - 1;
            int w = t[2];
            adj_list[src].push_back({dest, w}); // O(1)
        }
        
        dist[src - 1] = 0;
        queue.push({0, src - 1});
        dijkstra(adj_list, dist, visited); // O(v + e)
        int ans = *std::max_element(dist.begin(), dist.end());
        return ans != inf ? ans : -1;
    }
}