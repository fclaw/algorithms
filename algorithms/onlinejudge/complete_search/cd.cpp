#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



typedef std::vector<int> vi;

namespace algorithms::onlinejudge::complete_search::cd
{
    /** https://onlinejudge.org/external/6/624.pdf, 
     * input size is small, backtracking is enough */
    // ...
    int ids = 0;
    int tape = INT32_MIN;
    int N;
    int MAX;
    void backtrack(const vi& tracks, int mask, int duration, int idx)
    {
        if(duration > MAX || idx > N)
          return;
        if(duration <= MAX)
          if(duration > tape || 
            (duration == tape && 
             __builtin_popcount(mask) > 
             __builtin_popcount(ids)))
          { tape = duration; ids = mask; }

        backtrack(tracks, mask | (1 << idx), duration + tracks[idx], idx + 1);
        backtrack(tracks, mask, duration, idx + 1);
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(std::cin >> MAX >> N && MAX && N)
        {
            tape = INT32_MIN;
            ids = 0;
            vi tracks(N);
            for(int i = 0; i < N; i++)
              std::cin >> tracks[i];

            backtrack(tracks, 0, 0, 0);

            for(int i = 0; i < tracks.size(); i++)
              if(ids & (1 << i))
               std::cout << tracks[i] << " ";
            std::cout << "sum:" << tape << std::endl;
        }
    }
}