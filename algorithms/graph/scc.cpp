#include <vector>
#include <stack>

namespace algorithms::graph::scc
{

using graph = std::vector<std::vector<int>>;
using components = std::vector<std::vector<int>>;
using vi = std::vector<bool>;

    /**
     *  Book: Steven & Felix, cp, https://cpbook.net
     *  Finding Strongly Connected Components (Directed Graph)
     *  The basic idea of the algorithm is that SCCs form subtrees in the DFS spanning tree 
     *  (compare the original directed graph and the DFS spanning tree in Figure 4.9). 
     *  On top of computing dfs_num(u) and dfs_low(u) for each vertex, 
     *  we also append vertex u to the back of a stack S (here the stack is implemented with a vector) 
     *  and keep track of the vertices that are currently explored via vi visited. 
     *  The condition to update dfs_low(u) is slightly different from the previous DFS algorithm 
     *  for finding articulation points and bridges. 
     *  Here, only vertices that currently have visited flag turned on (part of the current SCC) 
     *  that can update dfs_low(u). Now, if we have vertex u in this DFS spanning tree with dfs_low(u) = dfs_num(u), 
     *  we can conclude that u is the root (start) of an SCC (observe vertex 0, 1, and 4) in Figure 4.9) 
     *  and the members of those SCCs are identified by popping the current content of stack S 
     *  until we reach vertex u (the root) of SCC again
     */
    int V;
    const int inf = 5 * (int)1e+05;
    int dfs_num = 0;
    std::vector<int> dfs_disc;
    std::vector<int> dfs_low;
    std::stack<int> vs;
    void tweaked_dfs(int u, const graph& g, components& cp, vi& visited)
    {
        dfs_disc[u] = dfs_low[u] = ++dfs_num;
        vs.push(u);
        visited[u] = true;
        for(auto v : g[u])
        {
            if(dfs_disc[v] == inf)
              tweaked_dfs(v, g, cp, visited);
            if(visited[v])
              dfs_low[u] = std::min(dfs_low[v], dfs_low[u]); 
        }

        if(dfs_disc[u] == dfs_low[u])
        {
            std::vector<int> tmp;
            while(true)
            {
                int v = vs.top();
                vs.pop();
                tmp.push_back(v);
                visited[v] = false;
                if(v == u) break;
            }
            cp.push_back(tmp);
        }
    }
    components tarjanSCC(int v, const graph& g)
    {
        V = v;
        components ans;
        std::vector<bool> visited(V, false);
        dfs_disc = dfs_low = std::vector<int>(V, inf);
        for(int i = 0; i < V; i++)
          if(dfs_disc[i] == inf)
            tweaked_dfs(i, g, ans, visited);
        return ans;
    }
}