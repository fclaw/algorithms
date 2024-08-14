#include <vector>
#include <string>

using mx = std::vector<std::vector<char>>;
using vis = std::vector<std::vector<bool>>;
using dir = std::vector<std::pair<int, int>>;

namespace algorithms::backtrack::leetcode::word_search
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
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    void dfs(mx& board, const std::string& word, bool& ans, int i, int j, int idx, vis& visited)
    {
        if(idx == word.size())
        {
              ans = true;
              return;
        }

        if(i == M || j == N || j < 0 || i < 0) return;
        
        for(auto d : dirs)
        {
            int y = i + d.first;
            int x = j + d.second;
            if(!visited[i][j] && board[i][j] == word[idx])
            {
                visited[i][j] = true;
                dfs(board, word, ans, y, x, idx, visited);
                visited[i][j] = false;
            }
        }
    }
    bool search(mx board, std::string word) 
    {
        M = board.size();
        N = board[0].size();
        bool ans = false;
        vis visited(M, std::vector<bool>(N, false));
        for(int i = 0; i < M; i++)
          for(int j = 0; j < N; j++)
            if(!ans)
              dfs(board, word, ans, i, j, 0, visited);
        return ans;
    }
}