#include <vector>
#include <string>

namespace algorithms::graph::leetcode
{

enum Cell { Water = 0, Land = 1 };
using ocean = std::vector<std::vector<Cell>>;
using vv = std::vector<std::vector<bool>>;

    // https://leetcode.com/problems/number-of-islands
   /** 
    * Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water), 
    * return the number of islands.
    * An island is surrounded by water and is formed 
    * by connecting adjacent lands horizontally or vertically. 
    * You may assume all four edges of the grid are all surrounded by water.
   */
    int m;
    int n;
    std::vector<std::pair<int, int>> dirs = 
    { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    void dfs(const ocean& grid, int r, int c, std::vector<std::vector<bool>>& visited)
    {
        if(r >= m || c >= n || c < 0 || r < 0)
          return;
        if(grid[r][c] == Water)
          return;    
        if(visited[r][c]) return;
        visited[r][c] = true;
        for(auto d : dirs)
          dfs(grid, r + d.first, c + d.second, visited);
    }
    int numIslands(ocean grid)
    {
        m = grid.size();
        n = grid[0].size();
        vv visited(m, std::vector<bool>(n, false));
        int counter = 0;
        for(int r = 0; r < m; r++)
          for(int c = 0; c < n; c++)
          {
              if(visited[r][c] || 
                 grid[r][c] == Water) 
                continue;  
              dfs(grid, r, c, visited);
              counter++;
          }
        return counter;
    }
}