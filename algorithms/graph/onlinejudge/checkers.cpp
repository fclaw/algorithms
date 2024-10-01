#include <vector>
#include <iostream>
#include <cassert>
#include <optional>
#include "../lp_dag.cpp"

namespace algorithms::graph::onlinejudge::checkers
{

typedef std::vector<std::pair<int, int>> dir;
typedef std::vector<std::vector<std::pair<bool, int>>> vvp;
typedef std::vector<std::pair<bool, int>> vp;
typedef long long ll;
typedef std::vector<ll> table;
namespace lp = algorithms::graph::lp_dag;

    /** https://onlinejudge.org/external/119/11957.pdf, counting paths in DAG; DP */
    int MOD = 1000007;
    const char Empty = '.';
    const char Black = 'B';
    const char White = 'W';
    int R, C;
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < R && c >= 0 && c < C; }
    /**  All checkers moving rules (for the white piece) are applied:
     *   • Target cell must be free.
     *   • From position (x, y) checker can move only forward by one of diagonals 
     *     to position (x + 1, y + 1) or (x − 1, y + 1).
     *   • If cell (x + 1, y + 1) or (x−1, y+ 1) is occupied by enemy piece 
     *     it can jump over to cell (x + 2, y + 2) or (x − 2, y + 2) respectively */
    dir main_dirs = { {-1, 1}, {-1, -1} };
    dir aux_dirs =  { {-2, 2}, {-2, -2} };
    ll countPaths(const lp::adj& graph, int source) 
    {
        lp::vs vertices = lp::topological_sort(graph.size(), std::nullopt, graph);

        table dp(R * C, 0);
        for(int i = 0; i < C; i++)
          dp[i] = 1;
        for(auto v : vertices)
          for(auto u : graph[v])
            dp[u] += dp[v] % MOD;
        return dp[source] % MOD;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(freopen(file.value(), "r", stdin) != nullptr);
        int tc, c = 1;
        std::cin >> tc;
        while(--tc >= 0)
        {
            int d;
            std::cin >> d;
            R = C = d;
            lp::adj graph(R * C);
            int vertex = 0;
            vvp vertices = vvp(R, vp(C, {false, 0}));
            for(auto& r : vertices)
              for(auto& x : r) x.second = vertex++;
            int source;
            std::string col;
            std::cin >> col; // fill in the first col
            for(int i = 0; i < C; i++)
              if(col[i] != Black)
                vertices[0][i].first = true;
            for(int r = 1; r < R; r++)
            {
                col.clear();
                std::cin >> col;
                for(int c = 0; c < C; c++)
                {
                  if(col[c] != Black)
                  {
                      for(int i = 0; i < main_dirs.size(); i++)
                      {
                          int m_r = r + main_dirs[i].first;
                          int m_c = c + main_dirs[i].second;
                          if(!checkBoundary(m_r, m_c))
                            continue;
                          if(vertices[m_r][m_c].first)
                            vertices[r][c].first = true,
                            graph[vertices[m_r][m_c].second].push_back(vertices[r][c].second);
                          else
                          {
                              int m_r = r + aux_dirs[i].first;
                              int m_c = c + aux_dirs[i].second;
                              if(!checkBoundary(m_r, m_c))
                                continue;
                              if(vertices[m_r][m_c].first)
                                vertices[r][c].first = true,
                                graph[vertices[m_r][m_c].second].push_back(vertices[r][c].second);
                          }
                      }
                  }
                  if(col[c] == White)
                    source = vertices[r][c].second;
                }
            }

            printf("Case %d: %llu\n", c++, countPaths(graph, source));
        }
    }
}