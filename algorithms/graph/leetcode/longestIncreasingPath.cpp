#include <vector>
#include <unordered_map>

namespace algorithms::graph::leetcode::lip
{

using matrix = std::vector<std::vector<int>>;
using m = std::vector<std::vector<int>>;
using dir = std::vector<std::pair<int, int>>;

    /**
     * https://leetcode.com/problems/longest-increasing-path-in-a-matrix
     * Given an m x n integers matrix, return the length of the longest increasing path in matrix.
     * From each cell, you can either move in four directions: left, right, up, or down. 
     * You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
    */
    int M;
    int N;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool checkBoundary(int r, int c)
    { return r >= 0 && r < M && c >= 0 && c < N; }
    int dfs(const matrix& mtx, int r, int c, std::vector<std::vector<int>>& memo)
    {
        if(r < 0 || 
           r == M || 
           c < 0 || 
           c == N)
          return 0;

        int &length = memo[r][c];
        if(~length) return length;

        length = 0;
        for(auto d : dirs)
        {
            int y = r + d.first;
            int x = c + d.second;
            if(checkBoundary(y, x) &&
               mtx[r][c] < mtx[y][x])
              length = std::max(length, dfs(mtx, y, x, memo));
        }
        return length += 1;
    }
    int longestIncreasingPath(const matrix& mtx)
    {
        M = mtx.size();
        N = mtx[0].size();
        m memo(M, std::vector<int>(N, -1));
        int ans = 0;
        for(int r = 0; r < M; r++)
          for(int c = 0; c < N; c++)
            ans = std::max(ans, dfs(mtx, r, c, memo));
        return ans;
    }
}