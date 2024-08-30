#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::min_effort
{

using heights = std::vector<std::vector<int>>;
using dir = std::vector<std::pair<int, int>>;
using eff = std::vector<std::vector<int>>;
using cell = std::tuple<int, int, int>;
using pq = std::priority_queue<cell, std::vector<cell>, std::greater<cell>>;

    /**
     * https://leetcode.com/problems/path-with-minimum-effort
     * You are a hiker preparing for an upcoming hike. 
     * You are given heights, a 2D array of size rows x columns, where heights[row][col] 
     * represents the height of cell (row, col). 
     * You are situated in the top-left cell, (0, 0), and 
     * you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). 
     * You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
     * A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
     * Return the minimum effort required to travel from the top-left cell to the bottom-right cell. 
     * hints: 
     *  - Consider the grid as a graph, where adjacent cells have an edge with cost of the difference between the cells
     *  - If you are given threshold k, check if it is possible to go from (0, 0) to (n-1, m-1) using only edges of ≤ k cost
     *  - Binary search the k value */
    int M;
    int N;
    const int inf = 5 * 1e+05;
    int effort = inf;
    dir dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < M && c >= 0 && c < N; }
    std::vector<std::vector<int>> efforts;
    void bfs(const heights& grid, pq& q) 
    {
       while(!q.empty())
       {
            auto v = q.top();
            q.pop();
            int cy, cx, e;
            std::tie(cy, cx, e) = v;
            for(auto d : dirs)
            {
                int y = cy + d.first;
                int x = cx + d.second;
                if(!checkBoundary(y, x))
                  continue;
                int diff = std::abs(grid[y][x] - grid[cy][cx]);
                int local_eff = std::max(diff, e);
                if(local_eff < efforts[y][x])
                { 
                    q.push({y, x, local_eff});
                    efforts[y][x] = local_eff;
                }
            }
        }
    }
    int minimumEffortPath(const heights& xs) 
    {
        M = xs.size();
        N = xs[0].size();
        efforts = eff(M, std::vector<int>(N, inf));
        efforts[0][0] = 0;
        pq q;
        q.push({0, 0, 0});
        bfs(xs, q);
        return efforts[M - 1][N - 1];
    }
}