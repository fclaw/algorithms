#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>



typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::complete_search::back_to_8_queens
{
    /** https://onlinejudge.org/external/110/11085.pdf, pre-calculation */
    const int SIZE = 8;
    const int SOL = 92;
    const size_t MAX_BIT = 2 * SIZE - 1;
    /**
     * Initially all n rows (rw), 2×n−1 left diagonals (ld), and 2×n−1 right diagonals (rd) are
     * unused (these three bitsets are all set to false). When a queen is placed at cell (r, c),
     * we flag rw[r] = true to disallow this row from being used again. Furthermore, all (a, b)
     * where abs(r - a) = abs(c - b) also cannot be used anymore. There are two possibilities
     * after removing the abs function: r - c = a - b and r + c = a + b. Note that r + c and
     * r - c represent indices for the two diagonal axes. As r - c can be negative, we add an
     * oﬀset of n - 1 to both sides of the equation so that r - c + n - 1 = a - b + n - 1. If a
     * queen is placed on cell (r, c), we flag ld[r - c + n - 1] = true and rd[r + c] = true 
     * to disallow these two diagonals from being used again
     */
    std::bitset<MAX_BIT> rw, ld, rd;
    bool checkPlacement(int c, int r) 
    { return !rw.test(r) && !ld.test(r - c + SIZE - 1) && !rd.test(r + c); }
    void bits_set(int r, int c, bool flag) 
    { rw.set(r, flag); ld.set(r - c + SIZE - 1, flag); rd.set(r + c, flag); }
    void backtrack(int c, int mask, vi& pos, vvi& dispositions)
    {
        if(mask == ((1 << SIZE) - 1))
        { dispositions.push_back(pos); return; }
    
        for(int r = 0; r < SIZE; r++)
          if(checkPlacement(c, r))
          {
              pos.push_back(r);
              bits_set(r, c, true);
              backtrack(c + 1, mask | (1 << c), pos, dispositions);
              pos.pop_back();
              bits_set(r, c, false);
          }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string line;
        int c = 1;
        while(std::getline(std::cin, line))
        {
            std::stringstream ss(line);
            vi queens;
            int r;
            while(ss >> r) 
              queens.push_back(--r);
            
            vvi dispositions;
            vi pos;
            backtrack(0, 0, pos, dispositions);

            int moves = INT32_MAX;
            for(auto d : dispositions)
            {
                int local_min = 0;
                for(int i = 0; i < SIZE; i++)
                  local_min += (d[i] != queens[i]);
                moves = std::min(moves, local_min); 
            }
            printf("Case %d: %d\n", c++, moves);
        }
    }
}