#include <vector>

namespace algorithms::leetcode::dp
{
    /*
       https://leetcode.com/problems/minimum-falling-path-sum
       Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
       A falling path starts at any element in the first row and chooses 
       the element in the next row that is either directly below or diagonally left/right. 
       Specifically, the next element from position 
       (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1)
    */
    int n; // rows 
    int m; // cols

    int minFallingPathSum(std::vector<std::vector<int>> matrix) 
    {
        n = matrix.size();
        m = matrix[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m + 2, INT32_MAX));

        for(int i = 1; i <= m; i++)
          dp[0][i] = matrix[0][i - 1];

        for (int r = 1; r < n; r++)
         for(int c = 1; c <= m; c++)
           dp[r][c] = std::min(dp[r][c - 1], matrix[r][c - 1] + std::min(dp[r - 1][c - 1], std::min(dp[r - 1][c], dp[r - 1][c + 1])));

        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
}