#include <cassert>
#include <optional>
#include <cstdio>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

namespace algorithms::graph::onlinejudge::injured_queen
{

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<std::vector<int>> vvi;
typedef std::unordered_set<int> si;
typedef std::vector<std::pair<int, int>> dirs;
typedef std::vector<ll> table;
namespace lp = algorithms::graph::lp_dag;

    /** https://onlinejudge.org/external/104/10401.pdf
     * counting paths in implicit DAG; DP; s: col, row; t: next col, avoid 2 or 3 adjacent rows
     * Input file contains several lines of input. Each line expresses a certain board status. The length of these
     * status string is the board dimension n (0 < n ≤ 15). The first character of the string denotes the status
     * of first column, the second character of the string denotes the status of the second column and so on. 
     * So if the first character of the status string is 2, it means that we are looking for arrangements (no two
     * injured queen attack each other) which has injured queen in column a, row 2. The possible numbers
     * for rows are 1, 2, 3, . . . , D, E, F which indicates row 1, 2, 3... 13, 14, 15. If any column contains ‘?’
     * it means that in that column the injured queen can be in any row. So a status string ‘1?4??3 means
     * that you are asked to find out total number of possible arrangements in a (6 × 6) chessboard which
     * has three of its six injured queens at a1, c4 and f3. Also note that there will be no invalid inputs. For
     * example ‘1?51’ is an invalid input because a (4 × 4) chessboard does not have a fifth row */
    int S;
    ll countWays(const lp::adj& graph, int source) 
    { 
        lp::vs vertices = lp::topological_sort(graph.size(), source, graph);
        table dp(S * S, 0);
        dp[source] = 1;
        for(auto v : vertices)
          for(auto u : graph[v])
            dp[u] += dp[v];

        ll ans = 0;
        for(int j = 1; j <= S; j++)
          ans += dp[S * j - 1];

        return ans; 
    }

    dirs ds = { {-1, 1}, {0, 1}, {1, 1} };
    int convertToInt(char c) { return !std::isdigit(c) ? (int)c - 55 : int(c) - 48; }
    bool isSafe(int s, int t) { return s - 1 != t && s != t && s + 1 != t; }
    bool checkBoundary(int r, int c) { return r >= 0 && r < S && c >= 0 && c < S; }
    
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        std::string line;
        while(std::cin >> line)
        {
            S = line.size();
            // initially the graph consists of S components
            vvi vertices = vvi(S, vi(S));
            int init = 0;
            int source = 0;
            for(auto& r : vertices)
              for(auto& x : r) x = init++;
            
            si forbidden;
            for(int c = 0; c < S; c++)
              if(line[c] != '?')
              {
                  int r = convertToInt(line[c]) - 1;
                  // c - the current column
                  // all vertices in the current column are made forbidden
                  for(int i = 0; i < S; i++)
                    if(i != r) forbidden.insert(vertices[i][c]);
                  // adjacent vertices
                  for(auto d : ds)
                  {
                      int adj_r = r + d.first;
                      int adj_c = c + d.second;
                      if(checkBoundary(adj_r, adj_c))
                        forbidden.insert(vertices[adj_r][adj_c]);
                  }

              }

            lp::adj graph(S * S);
            
            // process matrix in a row-wise fashion
            for(int r = 0; r < S; r++)
              for(int c = 1; c < S; c++)
              {
                 auto it = forbidden.find(vertices[r][c]);
                 if(it != forbidden.end()) continue;
                 int lower = r - 2;
                 int upper = r + 2;
                 int prev = c - 1;

                 for(int j = lower; j >= 0; j--)
                   if(forbidden.find(vertices[j][prev]) 
                      == forbidden.end())
                     graph[vertices[j][prev]].push_back(vertices[r][c]);

                 for(int j = upper; j < S; j++)
                   if(forbidden.find(vertices[j][prev]) 
                      == forbidden.end())
                       graph[vertices[j][prev]].push_back(vertices[r][c]);
              }

            for(int i = 1; i < S; i++)
              graph[0].push_back(vertices[i].front());

            printf("%llu\n", countWays(graph, source));   
        } 
    }
}