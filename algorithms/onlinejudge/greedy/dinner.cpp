#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <queue>




struct CompareByCapacity
{
    bool operator ()
      (const std::tuple<int, int, std::vector<bool>>& a, 
       const std::tuple<int, int, std::vector<bool>>& b) {
      return std::get<0>(a) == std::get<0>(b) ? std::get<1>(a) > std::get<1>(b) : std::get<0>(a) < std::get<0>(b);  // min heap: choose a table with max capacity
    }
};

typedef size_t st;
typedef std::vector<bool> vb;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::priority_queue<std::pair<int, int>> qpii;
typedef std::priority_queue<std::tuple<int, int, vb>, std::vector<std::tuple<int, int, vb>>, CompareByCapacity> qtiivb;


namespace algorithms::onlinejudge::greedy::dinner
{
    /** https://onlinejudge.org/external/102/10249.pdf */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        enum IS_SOL { NO, YES };  
        st N, M;
        while(std::cin >> N >> M && N && M)
        {
             vvi teams(N);
             st s;
             qpii teams_q;
             for(size_t i = 0; i < N; i++) {
               std::cin >> s;
               teams_q.push({s, i});
               teams[i] = vi(s);
             }
            
             int cap;
             qtiivb tables_q;
             for(size_t i = 0; i < M; i++) {
               std::cin >> cap;
               tables_q.push({cap, i, vb(N, false)});
             }

             bool isf = true;
             while(!teams_q.empty())
             {
                int idx = teams_q.top().second;
                teams_q.pop();
                st S = teams[idx].size();
           
                if (tables_q.size() < S) 
                { isf = false; break; }

                for(st j = 0; j < S; j++)
                {
                    if(tables_q.empty())
                    { isf = false; break; }
                    std::vector<std::tuple<int, int, vb>> tmp;
                    bool found = false;
                    int cap, table_id; 
                    vb used;
                    while(!tables_q.empty())
                    {
                        std::tie(cap, table_id, used) = 
                          tables_q.top(); 
                        tables_q.pop();
                        if(!used[idx]) 
                        { found = true; break; }
                        tmp.push_back({cap, table_id, used});
                    }

                    for(auto t : tmp) tables_q.push(t);

                    if (!found) 
                    { isf = false; break; }

                    used[idx] = true;
                    teams[idx][j] = table_id;
                    if(--cap > 0) tables_q.push({cap, table_id, used});
                }
             }

             if(isf)
             {
                std::string ans;
                ans += std::to_string(YES) + "\n";
                for(const vi& ts : teams)
                {
                    for(int t : ts)
                      ans += std::to_string(++t) + " ";
                    ans.pop_back();
                    ans.push_back('\n');
                }
                std::cout << ans;
            } else std::cout << std::to_string(NO) << std::endl;
        }
    }
}