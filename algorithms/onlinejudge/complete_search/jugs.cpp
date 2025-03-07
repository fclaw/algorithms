#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <queue>
#include <tuple>
#include <set>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::queue<std::tuple<int, int, vi>> qpii;
typedef std::set<std::pair<int, int>> sii;

namespace algorithms::onlinejudge::complete_search::jugs
{
    /** https://onlinejudge.org/external/5/571.pdf, 
     * solution can be suboptimal, add flag to avoid cycling */
    int capacity_a;
    int capacity_b;
    int target;
    vi ans;
    bool finished;
    enum Action { FillA, PourAB, EmptyA, FillB, PourBA, EmptyB };
    void bfs(qpii& state, sii& visited)
    {
        while(!state.empty() && !finished)
        {
            auto t = state.front();
            state.pop();
            int curr_a = std::get<0>(t);
            int curr_b = std::get<1>(t);
            vi seq = std::get<2>(t);

            // If already visited, skip
            if (visited.count({curr_a, curr_b})) continue;
            visited.insert({curr_a, curr_b});

            if(curr_b == target)
            { ans = seq; finished = true; }
            for(int i = FillA; i <= EmptyB; i++)
            {
                vi next_seq = seq; // Copy sequence
                if(curr_a == 0 && i == FillA)
                {
                  next_seq.push_back(FillA);
                  state.push({capacity_a, curr_b, next_seq});
                }
      
                if (i == PourAB && 
                    curr_a > 0 && 
                    curr_b < capacity_b) 
                {
                   int diff = std::min(curr_a, capacity_b - curr_b);
                   int next_a = curr_a - diff;
                   int next_b = curr_b + diff;
                   next_seq.push_back(PourAB);
                   state.push({next_a, next_b, next_seq});  
                }
         
                if(curr_a > 0 && i == EmptyA)
                { 
                   next_seq.push_back(EmptyA);
                   state.push({0, curr_b, next_seq});
                }

                if(curr_b == 0 && i == FillB)
                {
                   next_seq.push_back(FillB);
                   state.push({curr_a, capacity_b, next_seq});
                }
        
                if(i == PourBA && 
                   curr_b > 0 && 
                   curr_a < capacity_a) 
                {
                   int diff = std::min(curr_b, capacity_a - curr_a);
                   int next_a = curr_a + diff;
                   int next_b = curr_b - diff;
                   next_seq.push_back(PourBA);
                   state.push({next_a, next_b, next_seq});
                }
         
                if(curr_b > 0 && i == EmptyB)
                {
                   next_seq.push_back(EmptyB);
                   state.push({curr_a, 0, next_seq});
                }
            }
        }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        while(std::cin >> 
              capacity_a >>
              capacity_b >> 
              target)
        {
            finished = false;
            ans = {};
            qpii state;
            sii visited;
            state.push({0, 0, {}});
            bfs(state, visited);
            for(int a : ans)
              if(a == FillA)
                std::cout << "fill A" << std::endl;
              else if(a == FillB)
                std::cout << "fill B" << std::endl;
              else if(a == PourAB)
                std::cout << "pour A B" << std::endl;
              else if(a == PourBA)
                std::cout << "pour B A" << std::endl;
              else if(a == EmptyA)
                std::cout << "empty A" << std::endl;
              else std::cout << "empty B" << std::endl;
            std::cout << "success" << std::endl;  
        }
    }
}