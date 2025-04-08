#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>



typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::complete_search::ecosystem
{
    /**  https://onlinejudge.org/external/6/626.pdf, 3 nested loops */
    std::string toString(const vi& xs)
    {
        std::string s;
        for(int x : xs) s += std::to_string(x) + "_";
        return s;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int N;
        while(std::cin >> N)
        {

            vvi foodchain_matrix(N, vi(N, 0));
            for(int i = 0; i < N; i++)
              for(int j = 0; j < N; j++)
                std::cin >> foodchain_matrix[i][j];
            
            vvi ans;
            for(int i = 0; i < N; i++)
              for(int j = 0; j < N; j++)
                for(int k = 0; k < N; k++)
                  if(i != j && i != k && j != k)
                    if(foodchain_matrix[i][j] && 
                       foodchain_matrix[j][k] && 
                       foodchain_matrix[k][i])
                    {
                        // k, i, j and j, k, i are equivalent to i, j, k
                        // and must be omitted
                        if(i < j && j < k || i > j && j > k)
                          ans.push_back({i, j, k});
                    }

            for(int i = 0; i < ans.size(); i++)
            {
                std::string s;
                for(int v : ans[i])
                  s += std::to_string(v + 1) + " ";
                s.pop_back();  
                std::cout << s << std::endl;
            }
            std::cout << "total:" << ans.size() << std::endl << std::endl;
        }
    }
}