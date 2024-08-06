#include <vector>
#include <string>

using boards = std::vector<std::vector<std::string>>;
using solutions = std::vector<std::vector<std::pair<int, int>>>;

namespace algorithms::backtrack::leetcode
{
    // https://leetcode.com/problems/n-queens
    int size;
    solutions sol;
    bool canPlaced(int r, int c, const std::vector<std::pair<int, int>>& tmp) 
    { 
        if(tmp.empty())
          return true;
        bool ok = true;
        for(auto t : tmp)
          if(c == t.second ||
             (std::abs(t.first - r) == 
             std::abs(t.second - c)))
          {
            ok = false;
            break;
          }
        return ok; 
    }
    void backtrack(int r, std::vector<std::pair<int, int>>& tmp)
    {
        // termination condition
        if(r == size)
        {
            sol.push_back(tmp);
            return;
        }

        for(int c = 0; c < size; c++)
        {
            if(!canPlaced(r, c, tmp))
              continue;  
            tmp.push_back({r, c});
            backtrack(r + 1, tmp);
            tmp.pop_back();
        }
    }
    boards solveNQueens(int n)
    {
        size = n;
        std::vector<std::pair<int, int>> tmp;
        backtrack(0, tmp);
        boards ans;
        for(auto ss : sol)
        {
            std::vector<std::string> xs;
            for(auto s : ss)
            {
                std::string l(size, '.');
                l[s.second] = 'Q';
                xs.push_back(l);
            }
            ans.push_back(xs);
        }
        return ans;
    }
}