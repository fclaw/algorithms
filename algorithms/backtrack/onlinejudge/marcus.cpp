#include <vector>
#include <cstdio>
#include <iostream>

using cobbles = std::vector<std::vector<char>>;

namespace algorithms::backtrack::uv
{
    // https://onlinejudge.org/external/104/10452.pdf
    /**
     * The first line of the input contains a single number indicating the number of test cases that follow.
     * Each test case starts with a line containing two numbers m and n (2 ≤ m, n ≤ 8), the length m
     * and the width n of the cobblestone path. Then follow m lines, each containing n characters (‘A’ to ‘Z’,
     * ‘@’, ‘#’), the engravement of the respective cobblestone. Indy’s starting position is marked with the ‘@’
     * character in the last line, the destination with the character ‘#’ in the first line of the cobblestone path.
     * Each of the letters in ‘IEHOVA’ and the characters ‘@’ and ‘#’ appear exactly once in each test case.
     * There will always be exactly one path from Indy’s starting position via the stones with the letters
     * ‘IEHOVA’ engraved on (in that order) to the destination. There will be no other way to safely reach the destination.
     */
      const std::string wordOfGod = "IEHOVA#";
      const int size = wordOfGod.size();
      enum Move { Forth = 0, Right, Left };
      const std::vector<Move> mvs = { Forth, Right, Left };
      std::vector<Move> ans;
      int m;
      int n;
      std::string move_to_string(Move m)
      {
           std::string s;
           if(m == 0)
             s = "forth";
           if(m == 1)
             s = "right";
           if(m == 2)
             s = "left";
           return s;      
      }
      void dfs(const cobbles& cb, int r, int c, int pos, std::vector<Move>& path)
      { 
           if(pos == size)
           {
               for(auto x : path)
                 ans.push_back(x);
               return;  
           }
           
           if(c + 1 < n && cb[r][c + 1] == wordOfGod[pos])
           {
              path.push_back(Right);
              dfs(cb, r, c + 1, pos + 1, path);
              path.pop_back();
           }

           if(c - 1 >= 0 && cb[r][c - 1] == wordOfGod[pos])
           {
              path.push_back(Left);
              dfs(cb, r, c - 1, pos + 1, path);
              path.pop_back();
           }

           if(r - 1 >= 0 && cb[r - 1][c] == wordOfGod[pos])
           {
              path.push_back(Forth);
              dfs(cb, r - 1, c, pos + 1, path);
              path.pop_back();
           }
      }
      void solve_uv_10452(const cobbles& cb) 
      {
           int x = m - 1; 
           int y;
           for(int i = 0; i < n; i++)
             if(cb[m - 1][i] == '@')
             {
                y = i;
                break;
             } 
           std::vector<Move> path; 
           dfs(cb, x, y, 0, path);
      }
      void submit_uv_10452()
      {
           int TC;
           scanf("%d", &TC);
           while(--TC >= 0)
           {
                scanf("%d %d", &m, &n);
                cobbles cb;
                int i = m;
                while(--i >= 0)
                {
                    std::vector<char> tmp;
                    char s[n];
                    scanf("%s", s);
                    for(int i = 0; i < n; i++)
                      tmp.push_back(s[i]);
                    cb.push_back(tmp);
                }
                solve_uv_10452(cb);
                std::string s;
                for(int i = 0; i < ans.size(); i++)
                {
                    s += move_to_string(ans[i]);
                    s += " ";
                }
                printf("%s\n", s.c_str());
           }
      }
}