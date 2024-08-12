#include <vector>
#include <unordered_map>

namespace algorithms::graph::leetcode::pacificAtlantic
{

using heights = std::vector<std::vector<int>>;
using coords = std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>>;
using dir = std::vector<std::pair<int, int>>;
using visited = std::unordered_map<int, std::unordered_map<int, bool>>;

    /**
     * https://leetcode.com/problems/pacific-atlantic-water-flow
     * There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. 
     * The Pacific Ocean touches the island's left and top edges, 
     * and the Atlantic Ocean touches the island's right and bottom edges.
     * The island is partitioned into a grid of square cells. 
     * You are given an m x n integer matrix heights where heights[r][c] 
     * represents the height above sea level of the cell at coordinate (r, c).
     * The island receives a lot of rain, and the rain water can flow to neighboring cells 
     * directly north, south, east, and west if the neighboring cell's height 
     * is less than or equal to the current cell's height. 
     * Water can flow from any cell adjacent to an ocean into the ocean.
     * Return a 2D list of grid coordinates result where result[i] = [ri, ci] 
     * denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
     */
    enum Ocean { Pacific = 0, Atlantic = 1 };
    int M;
    int N;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    // ans
    coords cells;
    bool alreadyCalculated(int r, int c)
    {
        bool res = false;
        if (auto it = cells.find(r); it != cells.end())
          if(it->second.find(c) != it->second.end())
            res = true;
        return res;
    }
    bool dfs(const heights& ps, int r, int c, Ocean o, visited& mask)
    {
        if((o == Atlantic && (c == 0 || r == 0)) ||
           (o == Pacific && (c == N + 1 || r == M + 1)))
            return false;
        if(r == 0 ||
           r == M + 1 ||
           c == 0 ||
           c == N + 1)
          return true;
        
        bool ans = false;
        for(auto d : dirs)
        {
            int y = r + d.first;
            int x = c + d.second;
            if (auto it = mask.find(y); it != mask.end())
              if(it->second.find(x) != it->second.end())
                 continue;
            if(alreadyCalculated(y, x) && 
               ps[r][c] >= ps[y][x])
            {
                return ans = true;
                break;
            }     
            if(ps[r][c] >= ps[y][x])
            {
                mask[y][x] = true;
                ans |= dfs(ps, y, x, o, mask);
            }
        }
        return ans;
    }
    std::vector<std::vector<int>> flowToPacificAtlantic(const heights& xs)
    {
        visited mask;
        M = xs.size();
        N = xs[0].size();
        heights ys(M + 2, std::vector<int>(N + 2, INT32_MIN));
        for(int i = 1; i <= M; i++)
          for(int j = 1; j <= N; j++)
            ys[i][j] = xs[i - 1][j - 1];
  
        for(int r = 1; r <= M; r++)
          for(int c = 1; c <= N; c++)
          {
              bool rp = false;
              bool ra = false;
              if(r == 1 || c == 1)
                rp = true;
              else 
              {
                mask[r][c] = true;
                rp = dfs(ys, r, c, Pacific, mask);
              }
              if(rp && r != M && c != N)
              {
                mask.clear();
                mask[r][c] = true;
                ra = dfs(ys, r, c, Atlantic, mask);
              } else if(rp) ra = true;
              mask.clear();
              if(ra && rp) cells[r][c] = {r - 1, c - 1};
          }
        std::vector<std::vector<int>> ans;
        for(auto rows : cells)
          for(auto col : rows.second)
            ans.push_back({col.second.first, col.second.second});
        return ans;
    }
}