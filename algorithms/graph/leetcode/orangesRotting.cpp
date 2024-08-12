#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::rottenOranges
{

enum S { Empty = 0, Fresh = 1, Rotten = 2 };
using Cell = std::pair<int, int>;
using field = std::vector<std::vector<int>>;
using tm = std::vector<std::pair<Cell, int>>;

    // https://leetcode.com/problems/rotting-oranges/
   /** 
    * You are given an m x n grid where each cell can have one of three values:
    * 0 representing an empty cell,
    * 1 representing a fresh orange, or
    * 2 representing a rotten orange.
    * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
    * Return the minimum number of minutes that must elapse until no cell has a fresh orange. 
    * If this is impossible, return -1
   */
    int m;
    int n;
    std::vector<std::pair<int, int>> dirs = 
    { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < m && c >= 0 && c < n; }
    bool visited(const tm& times, int x, int y)
    {
        bool res = false;
        for(auto t : times)
          if(t.first.first == x && 
             t.first.second == y && 
             t.second != INT32_MAX)
          {
              res = true;
              break;
          }
        return res;
    }
    void setVisited(tm& times, int d, Cell c)
    {
        for(auto& t : times)
          if(t.first.first == c.first && 
             t.first.second == c.second)
               t.second = d + 1;
    }
    void bfs(const field& grid, std::queue<Cell>& q, tm& times) 
    {
        while(!q.empty())
        {
            auto x = q.front();
            q.pop();
            int d = 0;
            for(auto t : times)
              if(t.first.first == x.first && 
                 t.first.second == x.second)
                 d = t.second;

            for(auto dr : dirs)
            {
                int r = x.first + dr.first;
                int c = x.second + dr.second;
                if(checkBoundary(r, c) && 
                   grid[r][c] == Fresh &&
                   !visited(times, r, c))
                {
                    q.push({r, c});
                    setVisited(times, d, {r, c});
                }
            }
        }
    }
    int timeToSpoilAllOranges(field grid)
    {
        m = grid.size();
        n = grid[0].size();
        std::queue<Cell> rotten;
        tm times;
        // collect rotten oranges. it takes O(n * m)
        for(int i = 0; i < m; i++)
          for(int j = 0; j < n; j++)
          {
            if(grid[i][j] == Rotten)
              rotten.push({i, j});
            if(grid[i][j] == Fresh)
              times.push_back({{i, j}, INT32_MAX});  
          }
        bfs(grid, rotten, times);

        int ans = 0;
        if(times.size() > 0)
        {
            auto res = 
              std::max_element(
                times.begin(), 
                times.end(), 
                [](std::pair<Cell, int> a, std::pair<Cell, int> b) 
                { return a.second < b.second; });
            ans = (*res).second == INT32_MAX ? -1 : (*res).second;
        }
        return ans;
    }
}