#include <vector>
#include <queue>

namespace algorithms::graph::cc
{

using graph = std::vector<std::vector<int>>;
using cc = std::vector<std::pair<int, int>>;

    cc countComponents(int v, const graph& g)
    {
        std::vector<bool> visited(v, false);
        int n = 0;
        cc ans;
        for(int i = 0; i < v; i++)
          if(!visited[i])
          {
            n++;
            std::queue<int> q;
            q.push(i);
            while(!q.empty())
            {
                int v = q.front();
                q.pop();
                visited[v] = true;
                ans.push_back({v, n});
                for(auto u : g[v])
                  if(!visited[u])
                  {
                      q.push(u);
                      visited[u] = true;
                  }
            }
          }
        return ans;
    }
}