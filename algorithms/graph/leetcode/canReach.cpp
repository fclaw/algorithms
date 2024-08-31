#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::can_reach
{

using graph = std::vector<std::vector<int>>;
using vi = std::vector<bool>;

    /**
     * https://leetcode.com/problems/jump-game-iii
     * Given an array of non-negative integers arr, you are initially positioned at start index of the array. 
     * When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
     * Notice that you can not jump outside of the array at any time. */
    int S;
    bool isReachable = false;
    vi visited;
    std::vector<bool> targets(S, false);
    void bfs(const graph& g, int source)
    {
        std::queue<int> q;
        q.push(source);
        visited[source] = true;
        while(!q.empty() && !isReachable)
        {
            int u = q.front();
            q.pop();
            if(targets[u])
            {
                isReachable = true;
                continue;
            }
            for(auto v : g[u])
              if(!visited[v])
              {
                   visited[v] = true;
                   q.push(v);
              }
        }
    }
    bool canReach(const std::vector<int>& xs, int start)
    {
        S = xs.size();
        graph g(S);
        for(int i = 0; i < S; i++)
        {
            if(xs[i] == 0)
              targets[i] = true;
            else  
            { 
                std::vector<int> adj;
                if(i + xs[i] < S) 
                adj.push_back(i + xs[i]);
                if(i - xs[i] >= 0)
                adj.push_back(i - xs[i]);
                g[i] = adj;
            }
        }
        visited = vi(S, false); 
        bfs(g, start);
        return isReachable;
    }
}