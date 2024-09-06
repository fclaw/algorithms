#include <vector>
#include <unordered_map>

namespace algorithms::graph::leetcode::grid_cycles
{

struct hash_pair {
  size_t operator()(const std::pair<int, int>& p) const
    {
        // Hash the first element
        size_t hash_f = std::hash<int>{}(p.first);
        // Hash the second element
        size_t hash_s = std::hash<int>{}(p.second);
        // Combine the two hash values
        return hash_f ^ (hash_s + 0x9e3779b9 + (hash_f << 6) + (hash_f >> 2));
    }
};

using grid = std::vector<std::vector<char>>;
using dir = std::vector<std::pair<int, int>>;
using cell = std::pair<int, int>;
using vi = std::vector<std::vector<bool>>;


    /**
     * https://leetcode.com/problems/detect-cycles-in-2d-grid
     * Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle 
     * consisting of the same value in grid. A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. 
     * From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), 
     * if it has the same value of the current cell. Also, you cannot move to the cell that you visited in your last move. 
     * For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) 
     * which was the last visited cell. Return true if any cycle of the same value exists in grid, otherwise, return false.
     * hints: Keep track of the parent (previous position) to avoid considering an invalid path.
     * Use DFS or BFS and keep track of visited cells to see if there is a cycle. */
    int M;
    int N;
    vi visited;
    dir dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int r, int c)
    { return r >= 0 && r < M && c >= 0 && c < N; }
    bool isParent(int r, int c, std::optional<cell> p)
    {
        if(!p.has_value())
          return false;
        return p.value().first == r && p.value().second == c;  
    }
    bool dfs(const grid& g, cell x, std::optional<cell> p, std::unordered_map<cell, int, hash_pair>& acc)
    {
        if(auto it = acc.find(x); it != acc.end())
          if((*it).second >= 2)
              return true;

        bool res = false;
        for(const auto& dr : dirs)
        {
            int r = x.first + dr.first;
            int c = x.second + dr.second;
            if(!checkBoundary(r, c) || 
               (g[r][c] != g[x.first][x.second]) ||
               isParent(r, c, p))
              continue;

            acc[{r, c}] += 1;
            visited[r][c] = true;
            res |= dfs(g, {r, c}, std::make_optional<cell>(x), acc);
        }
        return res;
    }
    bool containsCycle(const grid& g) 
    {
        M = g.size();
        N = g[0].size();
        visited = vi(M, std::vector<bool>(N, false));
        std::unordered_map<cell, int, hash_pair> acc;
        bool ans = false;
        for(int r = 0; r < M; r++)
          for(int c = 0; c < N; c++)
            if(!visited[r][c] && !ans)
            {
               visited[r][c] = true;
               acc[{r, c}] = 1;
               ans |= dfs(g, {r, c}, std::nullopt, acc);
               acc.clear();
            }
        return ans;
    }
}