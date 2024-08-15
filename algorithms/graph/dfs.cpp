#include <vector>
#include <stack>

namespace algorithms::graph::dfs
{

using graph = std::vector<std::vector<int>>;

    std::vector<int> dfs_stack(int v, const graph& g, int start)
    {
        std::vector<bool> visited(v, false);
        std::stack<int> s;
        s.push(start);
        while(!s.empty())
        {
            int u = s.top();
            s.pop();
            if(!visited[u])
            {
                visited[u] = true;
                for(auto v : g[u])
                  s.push(v);
            }
        }
    }
}