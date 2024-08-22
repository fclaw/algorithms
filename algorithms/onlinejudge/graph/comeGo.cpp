#include <cstdio>
#include <vector>
#include <stack>

namespace algorithms::onlinejudge::graph::uva_11838
{

using graph = std::vector<std::vector<int>>;
using components = std::vector<std::vector<int>>;
using vi = std::vector<bool>;

    /**
     *  https://onlinejudge.org/external/118/11838.pdf
     *  The input contains several test cases. The first line of a test case contains two integers N and M,
     * separated by a space, indicating the number of intersections (2 ≤ N ≤ 2000) and number of streets
     * (2 ≤ M ≤ N(N − 1)/2). The next M lines describe the city street system, with each line describing
     * one street. A street description consists of three integers V , W and P, separated by a blank space,
     * where V and W are distinct identifiers for intersections (1 ≤ V , W ≤ N, V ̸= W ) and P can be 1 or
     * 2; if P = 1 the street is one-way, and traffic goes from V to W; if P = 2 then the street is two-way and
     * links V and W. A pair of intersections is connected by at most one street.
     * The last test case is followed by a line that contains only two zero numbers separated by a blank space.
     */
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
    components solve(int v, const graph& g)
    {
        components ans;
        std::vector<bool> visited(v, false);
        dfs_disc = dfs_low = std::vector<int>(v, inf);
        for(int i = 0; i < v; i++)
          if(dfs_disc[i] == inf)
            tweaked_dfs(i, g, ans, visited);
        return ans;
    }
    void submit()
    {        
        /**
         * V denotes the number of intersections (vertexes)
         * E denotes the number of street connecting intersections
         * */
        int V, E;
        while(true)
        {
            scanf("%d %d", &V, &E);
            if(V == 0) break;
            graph g(V);
            while(E-- > 0)
            {
                int from, to, dir;
                scanf("%d %d %d", &from, &to, &dir);
                g[from - 1].push_back(to - 1);
                if(dir == 2) g[to - 1].push_back(from - 1);
            }
            printf("%d\n", (int)(solve(V, g).size() == 1));
        }
    }
}