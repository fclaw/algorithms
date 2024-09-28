#include <optional>
#include <iostream>
#include <cassert>
#include "../lp_dag.cpp"

namespace algorithms::graph::onlinejudge::snowboard
{

typedef std::vector<std::vector<int>> adj;
typedef std::vector<std::vector<std::pair<int, int>>> matrix;
namespace lp = algorithms::graph::lp_dag;
typedef std::vector<int> table;

    /**  https://onlinejudge.org/external/102/10285.pdf 
     *  longest paths on implicit DAG; however, the graph is small enough for recursive backtracking solution 
     *  1  2  3  4 5
     * 16 17 18 19 6
     * 15 24 25 20 7
     * 14 23 22 21 8
     * 13 12 11 10 9
     * One can slide down from one point to a connected other one if and only if the height decreases. 
     * One point is connected to another if it’s at left, at right, above or below it. In the sample map, a possible
     * slide would be 24-17-16-1 (start at 24, end at 1). Of course if you would go 25-24-23-…-3-2-1, 
     * it would be a much longer run. In fact, it’s the longest possible */
    int longestRun(int V, const adj& graph)
    {
        lp::vs vs = lp::topological_sort(V, std::nullopt, graph);
        table dp(V, 1);
        for(auto v : vs)
          for(auto u : graph[v])
            dp[u] = std::max(dp[u], 1 + dp[v]);

        return *std::max_element(dp.begin(), dp.end());
    }
    int rows, cols;
    std::vector<std::pair<int, int>> dirs = 
    { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < rows && c >= 0 && c < cols; }
    adj makeGraph(const matrix& mtx, int rows, int cols) 
    {
        adj graph(rows * cols);
        for(int r = 0; r < rows; r++)
          for(int c = 0; c < cols; c++)
          {
              for(auto d : dirs)
              {
                 int adj_r = r + d.first;
                 int adj_c = c + d.second;
                 if(checkBoundary(adj_r, adj_c) && 
                    mtx[r][c].second < mtx[adj_r][adj_c].second)
                    graph[mtx[r][c].first].push_back(mtx[adj_r][adj_c].first);
              }
            }
        return graph;
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(freopen(file.value(), "r", stdin) != nullptr);
        adj graph;
        int tc;
        std::cin >> tc;
        while(--tc >= 0)
        {
            std::string s;
            std::string track;
            matrix mtx;
            std::cin >> track >> rows >> cols;
            int vertex = 0;
            for(int r = 0; r < rows; r++)
            {
                int height;
                std::vector<std::pair<int, int>> cx;
                for(int c = 0; c < cols; c++)
                {
                    std::cin >> height;
                    cx.push_back({vertex++, height});
                }
                mtx.push_back(cx);
            }

            adj graph = makeGraph(mtx, rows, cols);
            std::cout << track << ": " <<  longestRun(vertex, graph) << std::endl;
        }
    }
}