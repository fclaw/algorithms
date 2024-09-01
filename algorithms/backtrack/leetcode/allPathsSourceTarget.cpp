
#include <vector>

namespace algorithms::backtrack::leetcode::all_path
{

using graph = std::vector<std::vector<int>>;
using paths = std::vector<std::vector<int>>;

    /** 
     * https://leetcode.com/problems/all-paths-from-source-to-target
     * Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, 
     * find all possible paths from node 0 to node n - 1 and return them in any order.
     * The graph is given as follows: graph[i] is a list of all nodes you can visit 
     * from node i (i.e., there is a directed edge from node i to node graph[i][j]). */
    int S;
    int target;
    paths ans;
    void backtrack(const graph& g, int source, std::vector<int>& acc)
    {
         if(source == target)
         {
             ans.push_back(acc);
             return;
         }
         for(auto v : g[source])
         {
             acc.push_back(v);
             backtrack(g, v, acc);
             if(!acc.empty()) acc.pop_back();
         }
    }
    paths allPathsSourceTarget(const graph& g)
    {
        S = g.size();
        target = S - 1;
        std::vector<int> acc = {0};
        backtrack(g, 0, acc);
        return ans;
    }
}