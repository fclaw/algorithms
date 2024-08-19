#include <vector>


namespace algorithms::graph::articulation_point
{

using graph = std::vector<std::vector<int>>;

    /**
     * https://codeforces.com/blog/entry/71146
     * Let's say there is a node 𝑉 in some graph 𝐺 that can be reached by a node 𝑈
     * through some intermediate nodes (maybe non intermediate nodes) following some DFS traversal, 
     * if 𝑉 can also be reached by 𝐴 = "ancestor of 𝑈 " without passing through 𝑈 then, 𝑈
     * is NOT an articulation point because it means that if we remove 𝑈 from 𝐺
     * we can still reach 𝑉 from A, hence, the number of connected components will remain the same.
     * So, we can conclude that the only 2 conditions for 𝑈 to be an articulation point are:
     * 1 - If all paths from 𝐴 to 𝑉 require 𝑈 to be in the graph.
     * 2 - If 𝑈 is the root of the DFS traversal with at least 2 children subgraphs disconnected from each other.
     */
    int dfs_num = 0;
    std::vector<int> dfs_disc;
    std::vector<int> dfs_low;
    std::vector<bool> ap;
    int dfs(const graph& g, int u)
    {
        int children = 0;
        dfs_disc[u] = dfs_low[u] = ++dfs_num;
        for(auto v : g[u])
        {
            // we don't want to go back through the same path.
            // if we go back is because we found another way back
            if (v == u) continue;
            // if V has not been discovered before
            if (!dfs_disc[v])
            {
                children++;
                dfs(g, v); // recursive DFS call
                if (dfs_disc[u] <= dfs_low[v]) // condition #1
                  ap[u] = true;
                // // low[v] might be an ancestor of u 
                dfs_low[u] = std::min(dfs_low[u], dfs_low[v]);
            } 
            else // if v was already discovered means that we found an ancestor
                 // finds the ancestor with the least discovery time
             dfs_low[u] = std::min(dfs_low[u], dfs_disc[v]);
        }
        return children;
    }
    std::vector<bool> getAP(int v, const graph& g)
    {
        ap = std::vector<bool>(v, false);
        dfs_disc = dfs_low = std::vector<int>(v);
        for(int u = 0; u < v; u++)
          if (!dfs_disc[u])
            // u is a root with at least 2 subtrees
            ap[u] = dfs(g, u) > 1;
        return ap;
    }
}