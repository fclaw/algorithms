#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::shortest_path_in_binary_matrix
{

using matrix = std::vector<std::vector<int>>;
using dir = std::vector<std::pair<int, int>>;
using vi = std::vector<std::vector<bool>>;
using dist = std::vector<std::vector<int>>;

    /**
     * https://leetcode.com/problems/shortest-path-in-binary-matrix
     * Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. 
     * If there is no clear path, return -1.
     * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) 
     * to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
     * All the visited cells of the path are 0.
     * All the adjacent cells of the path are 8-directionally connected 
     * (i.e., they are different and they share an edge or a corner).
     * The length of a clear path is the number of visited cells of this path.
     * hint: Do a breadth first search to find the shortest path */
    const int inf = 5 * 1e+05;
    const int Empty = 0;
    const int Block = 1;
    int M, N;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < M && c >= 0 && c < N; }
    vi visited;
    dist distance;
    void bfs(const matrix& grid, std::queue<std::pair<int, int>>& q)
    {
        while(!q.empty())
        {
            auto u = q.front();
            q.pop();
            int curr_y = u.first;
            int curr_x = u.second;
            for(auto d : dirs)
            {
                int y = curr_y + d.first;
                int x = curr_x + d.second;
                if(!checkBoundary(y, x) || visited[y][x])
                  continue;
                visited[y][x] = true;  

                if(grid[y][x] == Empty)
                {
                    distance[y][x] = distance[curr_y][curr_x] + 1;
                    q.push({y, x});
                }
            }
        }
    }
    int shortestPathBinaryMatrix(const matrix& grid)
    {
        if(grid[0][0] == Block)
          return -1;
        M = grid.size();
        N = grid[0].size();
        std::queue<std::pair<int, int>> q;
        visited = vi(M, std::vector<bool>(N, false));
        distance = dist(M, std::vector<int>(N, inf));
        visited[0][0] = true;
        distance[0][0] = 0;
        q.push({0, 0});
        bfs(grid, q);
        return distance[M - 1][N - 1] != inf ? distance[M - 1][N - 1] : -1;
    }
}