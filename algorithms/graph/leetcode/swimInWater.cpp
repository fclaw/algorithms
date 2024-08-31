#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::swim_in_water
{

using grid = std::vector<std::vector<int>>;
using dir = std::vector<std::pair<int, int>>;
using cell = std::tuple<int, int, int>;
using pq = std::priority_queue<std::pair<int, cell>, std::vector<std::pair<int, cell>>, std::greater<std::pair<int, cell>>>;
using vi = std::vector<std::vector<bool>>;

    /**
     * https://leetcode.com/problems/swim-in-rising-water
     * You are given an n x n integer matrix grid where each value grid[i][j] 
     * represents the elevation at that point (i, j).
     * The rain starts to fall. At time t, the depth of the water everywhere is t. 
     * You can swim from a square to another 4-directionally adjacent square 
     * if and only if the elevation of both squares individually are at most t. 
     * You can swim infinite distances in zero time. 
     * Of course, you must stay within the boundaries of the grid during your swim.
     * Return the least time until you can reach the bottom right square (n - 1, n - 1) 
     * if you start at the top left square (0, 0) 
     * hint: Use either Dijkstra's, or binary search for the best time T 
     * for which you can reach the end if you only step on squares at most T */
    int M;
    int N;
    const int inf = 5 * 1e+05;
    dir dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < M && c >= 0 && c < N; }
    int ans = inf;
    vi visited;
    void bfs(const grid& g, pq& q)
    {
        while(!q.empty())
        {
            auto v = q.top();
            q.pop();
            int cy, cx, e;
            std::tie(cy, cx, e) = v.second;
            
            if(cy == M - 1 && cx == N - 1)
                ans = std::min(ans, e);

            for(auto d : dirs)
            {
                int y = cy + d.first;
                int x = cx + d.second;
                if(!checkBoundary(y, x) || visited[y][x])
                  continue;
                visited[y][x] = true;
                if(e > g[y][x]) q.push({0, {y, x, e}});
                else q.push({g[y][x], {y, x, g[y][x]}});
            }
        }
    }
    int swimInWater(const grid& g)
    {
        M = g.size();
        N = g[0].size();
        pq q;
        q.push({0, {0, 0, g[0][0]}});
        visited = vi(M, std::vector<bool>(N, false));
        visited[0][0] = true;
        bfs(g, q);
        return ans;
    }
}