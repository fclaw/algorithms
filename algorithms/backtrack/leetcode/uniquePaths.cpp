#include <vector>


namespace algorithms::backtrack::leetcode::unique_paths
{

using grid = std::vector<std::vector<int>>;
using dir = std::vector<std::pair<int, int>>;
using visited = std::vector<std::vector<bool>>;

    /**
     *  https://leetcode.com/problems/unique-paths-iii
     *  You are given an m x n integer array grid where grid[i][j] could be:
     * 1 representing the starting square. There is exactly one starting square.
     * 2 representing the ending square. There is exactly one ending square.
     * 0 representing empty squares we can walk over.
     * -1 representing obstacles that we cannot walk over.
     * Return the number of 4-directional walks from the starting square to the ending square, 
     * that walk over every non-obstacle square exactly once
     */
    enum Legend 
      { Obstacle = -1,
        Empty = 0,
        Source = 1, 
        Sink = 2
      };
    int M;
    int N;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool checkBoundary(int r, int c) 
      { return r >= 0 && r < M && c >= 0 && c < N; }
    int dfs(const grid& maze, int r, int c, int cells, visited mask)
    {
        if(maze[r][c] == Sink && cells == -1)
            return 1;
        if(maze[r][c] == Obstacle || 
           maze[r][c] == Sink && cells >= 0)
          return 0;

        int paths = 0;
        for(auto d : dirs)
        {
            int y = r + d.first;
            int x = c + d.second;
            if(checkBoundary(y, x) && 
               !mask[y][x])
            {
                auto x_y_mask = mask;
                x_y_mask[y][x] = true;
                paths += dfs(maze, y, x, cells - 1, x_y_mask);
            }
        }
        return paths;
    }
    int uniquePaths(const grid& maze) 
    {
        M = maze.size();
        N = maze[0].size();
        std::pair<int, int> src;
        int cells = 0;
        for(int r = 0; r < M; r++)
          for(int c = 0; c < N; c++)
          {
            if(maze[r][c] == Source) src = {r, c};
            if(maze[r][c] == Empty) cells++;
          }
        visited mask(M, std::vector<bool>(N, false));
        mask[src.first][src.second] = true;
        return dfs(maze, src.first, src.second, cells, mask);
    }
}