#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef std::vector<int> vi;


namespace algorithms::onlinejudge::complete_search::start_grid
{
    /** https://onlinejudge.org/external/124/12488.pdf, 2 nested loops; simulate overtaking process */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(std::cin >> N)
        {
            vi start(N), finish(N), valToidx(N + 1);
            int s;
            for(int i = 0; i < N; i++)
            {
                std::cin >> s;
                start[i] = s;
                valToidx[s] = i;
            }
            for(int i = 0; i < N; i++)
              std::cin >> finish[i];
           
            int overtakes = 0;
            for(int i = 0; i < N; i++)
              for(int j = 0; j < N; j++)
              {
                  if(start[i] == finish[j]) break;
                  // the val (j) overtakes val(i) must be behind in the inital array
                  if(valToidx[finish[j]] > i)
                    overtakes++;
              }
            std::cout << overtakes << std::endl;
        }
    }
}