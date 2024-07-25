#include <vector>
#include <string>

using mx = std::vector<std::vector<char>>;

namespace algorithms::backtrack::leetcode
{
    // https://leetcode.com/problems/word-search
    /*
      Given an m x n grid of characters board and a string word, 
      return true if word exists in the grid
      The word can be constructed from letters of sequentially adjacent cells, 
      where adjacent cells are horizontally or vertically neighboring. 
      The same letter cell may not be used more than once.
    */
    int M;
    int N;
    void dfs(mx& board, const std::string& word, bool& ans, int i, int j, int idx)
    {
        if(idx == word.size())
        {
              ans = true;
              return;
        }

        if(i == M || j == N || j < 0 || i < 0) return;
        
        if(board[i][j] == word[idx])
        {
            board[i][j] = '*';
            dfs(board, word, ans, i, j + 1, idx); 
            dfs(board, word, ans, i + 1, j, idx);
            dfs(board, word, ans, i, j - 1, idx);
            dfs(board, word, ans, i - 1, j, idx);
            board[i][j] = word[idx];
        }
    }
    bool search(mx board, std::string word) 
    {
        M = board.size();
        N = board[0].size();
        bool ans = false;
        for(int i = 0; i < M; i++)
          for(int j = 0; j < N; j++)
            if(!ans)
              dfs(board, word, ans, i, j, 0);
        return ans;
    }
}