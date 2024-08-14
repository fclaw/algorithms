#include <vector>

namespace algorithms::backtrack::leetcode::maximum_gold
{

using grid = std::vector<std::vector<int>>;
using vs = std::vector<std::vector<bool>>;
using dir = std::vector<std::pair<int, int>>;

    /**
     * https://leetcode.com/problems/path-with-maximum-gold
     * In a gold mine grid of size m x n, each cell in this mine has an integer
     * representing the amount of gold in that cell, 0 if it is empty.
     * Return the maximum amount of gold you can collect under the conditions:
     * Every time you are located in a cell you will collect all the gold in that cell.
     * From your position, you can walk one step to the left, right, up, or down.
     * You can't visit the same cell more than once.
     * Never visit a cell with 0 gold.
     * You can start and stop collecting gold from any position in the grid that has some gold.
     */
    int M;
    int N;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool checkBoundary(int r, int c)
      { return r >= 0 && r < M && c >= 0 && c < N; }
    int dfs(const grid& mine, int r, int c, vs& visited)
    {
        int gold = 0;
        for(auto d : dirs)
        {
            int y = r + d.first;
            int x = c + d.second;
            if(checkBoundary(y, x) && 
               !visited[y][x] &&
               mine[y][x] != 0)
            {
                visited[y][x] = true;   
                gold = std::max(gold, mine[y][x] + dfs(mine, y, x, visited));
                visited[y][x] = false;
            }
        }
        return gold;
    }
    int getMaximumGold(const grid& mine)
    {
        M = mine.size();
        N = mine[0].size();
        int gold = 0;
        for(int r = 0; r < M; r++)
          for(int c = 0; c < N; c++)
            if(mine[r][c] != 0)
            {
                vs visited(M, std::vector<bool>(N, false));
                visited[r][c] = true;
                gold = std::max(gold, mine[r][c] + dfs(mine, r, c, visited));
            }
        return gold;
    }
}