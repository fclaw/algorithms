#include <vector>
#include <cstdio>
#include <numeric>
#include <iostream>

namespace algorithms::backtrack::uv
{
    // https://onlinejudge.org/external/6/624.pdf
    /**
     * You have a long drive by car ahead. You have a tape recorder, but unfortunately your best music is on
     * CDs. You need to have it on tapes so the problem to solve is: you have a tape N minutes long. How
     * to choose tracks from CD to get most out of tape space and have as short unused space as possible.
     * Assumptions:
     * • number of tracks on the CD does not exceed 20
     * • no track is longer than N minutes
     * • tracks do not repeat
     * • length of each track is expressed as an integer number
     * • N is also integer
     * Program should find the set of tracks which fills the tape best and print it in the same sequence as
     * the tracks are stored on the CD
     */
    int SIZE;
    int CAPACITY;
    int songs;
    int mask;
    void dfs(const std::vector<int>& cd, int pos, int c, int m)
    {
        if(c > CAPACITY)
          return;

        if(c > songs)
        {
            songs = c;
            mask = m; 
        }

        if(pos >= SIZE)
          return;

        dfs(cd, pos + 1, c + cd[pos], m | (1 << pos));
        dfs(cd, pos + 1, c, m);  
    }
 
    void submit_uv_624()
    {
        int capacity, s, v;
        while(std::cin >> capacity)
        {
            std::cin >> s;
            std::vector<int> cd;
            for(int i = 0; i < s; i++)
            {
                std::cin >> v;
                cd.push_back(v);
            }
            CAPACITY = capacity;
            SIZE = cd.size(); 
            dfs(cd, 0, 0, 0);
            
            for(auto c : cd)
              if(mask & (1 << c))
                printf("%d ", c);
            printf("sum:%d\n", songs);
        }
    }
}