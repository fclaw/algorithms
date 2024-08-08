#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

// https://onlinejudge.org/external/4/469.pdf
/**
 * The engineers divided the construction site by a grid into uniform square cells such that each square
 * cell entirely contained either water or land. (How they did it, of course, is anybody’s guess.) Now, the
 * question that the engineers are to answer is the following: “Given the row and column number of a
 * grid cell that contains water, what is the area of the lake containing that cell.” (an area is measured by
 * number of grid cells it contains. Diagonal cells are considered to be adjacent.)
 * 
 * The input consists of 0 < n ≤ 99 lines each containing 0 < m ≤ 99 character long sequence of
 * ‘L’s and ‘W’s followed by k > 0 lines each containing a pair of integers i and j. The first n lines will
 * represent the n×m grid covering the land where a ‘W’/‘L’ at the c-th character of the r-th line indicates
 * water/land within the cell at row r and column c of the grid. The pairs of integers on the last k lines,
 * each represent the row and column numbers of some grid cell that contains water
 * 
 */
namespace algorithms::onlinejudge::graph::wetlands
{

enum Cell { Water = 0, Land = 1 };
using wt = std::vector<std::vector<Cell>>;

    int m;
    int n;
    std::vector<std::pair<int, int>> dirs = 
    { {-1, 0}, // up
      {-1, 1}, // up - right
      {0, 1}, // right
      {1, 1}, // right - down
      {1, 0}, // down
      {1, -1}, // left - down
      {0, -1}, // left
      {-1, -1} // left - up
    };
    std::vector<std::vector<bool>> visited;
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < m && c >= 0 && c < n; }
    int area = 0;
    int dfs(const wt& grid, int r, int c)
    {
        if(grid[r][c] == Land)
          return 0;
        visited[r][c] = true;
        int area = 1;
        for(auto d : dirs)
        {
            int x = r + d.first;
            int y = c + d.second;
            if(checkBoundary(x, y) &&
               !visited[x][y])
              area += dfs(grid, x, y);
        }
        return area;
    }
    int measureWaterArea(const wt& grid, int r, int c)
    {
        m = grid.size();
        n = grid[0].size();
        visited.resize(m, std::vector<bool>(n, false));
        return dfs(grid, r, c);
    }

    void submit_469()
    {
        int TC;
        std::cin >> TC;
        std::string empty;
        std::getline(std::cin, empty);
        std::getline(std::cin, empty);
        while(--TC >= 0)
        {
            wt grid;
            std::string s;
            while(std::getline(std::cin, s) && !s.empty())
            {
                if(s[0] == 'W' || s[0] == 'L')
                {
                    std::vector<Cell> tmp;
                    for(auto x : s)
                      if(x == 'W')
                        tmp.push_back(Water);
                      else tmp.push_back(Land);
                    grid.push_back(tmp);
                }
                else
                {
                    int r, c;
                    sscanf(s.c_str(), "%d %d", &r, &c);
                    printf("%d\n", measureWaterArea(grid, r, c));
                }
            }
            if(TC) std::cout << std::endl;
        }
    }
}