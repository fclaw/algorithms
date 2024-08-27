#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::shortest_path 
{

using grid = std::vector<std::vector<int>>;
using dist = std::vector<std::vector<std::vector<int>>>;
using el = std::tuple<int, int, int>;
using dir = std::vector<std::pair<int, int>>;
using vi = std::vector<std::vector<std::vector<bool>>>;

    /** 
     * https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination
     * You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). 
     * You can move up, down, left, or right from and to an empty cell in one step.
     * Return the minimum number of steps to walk from the upper left corner (0, 0) 
     * to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. 
     * If it is not possible to find such walk return -1. */
    const int inf = 5 * 1e+05;
    int M, N, K;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < M && c >= 0 && c < N; }
    void bfs(const grid& g, std::queue<el>& q, vi& visited, dist& ds) 
    {
        while(!q.empty())
        {
            int x, y, l;
            auto v = q.front();
            q.pop();
            std::tie(l, x, y) = v;
            for(auto d : dirs)
            {
                int next_x = x + d.first;
                int next_y = y + d.second;
                bool canMove = checkBoundary(next_x, next_y);
                if(!canMove || visited[next_x][next_y][l])
                  continue;  
                bool isObstacle = (bool)g[next_x][next_y];
                if(isObstacle)
                {
                    if(l + 1 < K)
                    {
                        visited[next_x][next_y][l + 1] = true;
                        visited[next_x][next_y][l] = true;
                        ds[next_x][next_y][l + 1] = ds[x][y][l] + 1;
                        q.push({l + 1, next_x, next_y});
                    }
                }
                else
                {
                    visited[next_x][next_y][l] = true;
                    ds[next_x][next_y][l] = ds[x][y][l] + 1;
                    q.push({l, next_x, next_y});
                }
            }
        }
    }
    int shortestPath(const grid& g, int k)
    {
        M = g.size();
        N = g[0].size();
        K = k + 1;
        dist distance(M, std::vector<std::vector<int>>(N, std::vector<int>(K, inf)));
        vi visited(M,  std::vector<std::vector<bool>>(N, std::vector<bool>(K, false)));
        std::queue<el> q;
        q.push({0, 0, 0});
        distance[0][0][0] = 0;
        visited[0][0][0] = true;
        bfs(g, q, visited, distance);

        auto ans = distance[M - 1][N - 1];
        int min_step = *std::min_element(ans.begin(), ans.end());
        return min_step != inf ? min_step : -1;
    }
}