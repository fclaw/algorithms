#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <stack>

namespace algorithms::onlinejudge::graph::uva_247
{

using graph = std::vector<std::vector<std::pair<int, std::string>>>;
using components = std::vector<std::vector<std::string>>;
using vi = std::vector<bool>;
using oi = std::ostream_iterator<std::string>;
using vv = std::vector<std::pair<int, std::string>>;

        /**
         *  problem statement: https://onlinejudge.org/external/2/247.pdf
         * The input file will contain one or more data sets. Each data set begins with a line containing two
         * integers, n and m. The first integer, n, represents the number of different people who are in the data
         * set. The maximum value for n is 25. The remainder of the data set consists of m lines, each representing
         * a phone call. Each call is represented by two names, separated by a single space. Names are first names
         * only (unique within a data set), are case sensitive, and consist of only alphabetic characters; no name
         * is longer than 25 letters
         */
        const char* delim = ", ";
        const int inf = 5 * (int)1e+05;
        int dfs_num = 0;
        std::vector<int> dfs_disc;
        std::vector<int> dfs_low;
        std::stack<std::pair<int, std::string>> vs;
        void tweaked_dfs(std::pair<int, std::string> u, const graph& g, components& cp, vi& visited)
        {
            dfs_disc[u.first] = dfs_low[u.first] = ++dfs_num;
            vs.push(u);
            visited[u.first] = true;
            for(auto v : g[u.first])
            {
                if(dfs_disc[v.first] == inf)
                tweaked_dfs(v, g, cp, visited);
                if(visited[v.first])
                dfs_low[u.first] = std::min(dfs_low[v.first], dfs_low[u.first]); 
            }

            if(dfs_disc[u.first] == 
               dfs_low[u.first])
            {
                std::vector<std::string> tmp;
                while(true)
                {
                    auto v = vs.top();
                    vs.pop();
                    tmp.push_back(v.second);
                    visited[v.first] = false;
                    if(v.first == u.first) break;
                }
                cp.push_back(tmp);
            }
        }
        components solve(int v, int e, const graph& g, const vv& vs) 
        { 
            components ans;
            std::vector<bool> visited(v, false);
            dfs_disc = dfs_low = std::vector<int>(v, inf);
            for(auto v : vs)
              if(dfs_disc[v.first] == inf)
                 tweaked_dfs(v, g, ans, visited);
            return ans;
        }
        int getIdx(std::string s, vv vs)
        {
            int res = -1;
            for(auto v : vs)
              if(v.second == s)
              {
                  res = v.first;
                  break;
              }
            return res;
        }
        void submit()
        {
            int V, E;
            int c = 0;
            do
            {
                scanf("%d %d", &V, &E);
                int e = E;
                graph g(V);
                int i = 0;
                vv vertex;
                while(e-- > 0)
                {
                    std::string from, to;
                    std::cin >> from >> to;
                    int i_from;
                    int i_to;
                    if(getIdx(from, vertex) != -1)
                      i_from = getIdx(from, vertex);
                    else 
                    {
                        i_from = i++;
                        vertex.push_back({i_from, from});
                    }
                    if(getIdx(to, vertex) != -1)
                      i_to = getIdx(to, vertex);
                    else 
                    {
                        i_to = i++;
                        vertex.push_back({i_to, to});
                    }
                    g[i_from].push_back({i_to, to});
                }
                auto comp = solve(V, E, g, vertex);
                printf("Calling circles for data set %d:\n", ++c);
                for(auto xs : comp)
                {
                    for(int i = 0; i < xs.size(); i++)
                      if(i == xs.size() - 1)
                        std::cout << xs[i];
                      else std::cout << xs[i] << ", ";
                    std::cout << std::endl;
                }
            }while(V != 0 && E != 0);
        }
}
