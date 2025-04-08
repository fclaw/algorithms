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
    bool isCyclicShift(const vi& xs, const vi& ys) 
    {
        vi double_xs = xs;
        double_xs.insert(double_xs.end(), xs.begin(), xs.end());  // A + A
        return std::search(double_xs.begin(), double_xs.end(), ys.begin(), ys.end()) != double_xs.end();
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int N;
        bool first = true;
        while(std::cin >> N)
        {
            if(!first) std::cout << std::endl;
            first = false;

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
                        bool isOk = true;
                        for(auto& xs : ans)
                          if(isCyclicShift(xs, {i, j, k}))
                          { isOk = false; break; }
                        if(isOk) ans.push_back({i, j, k});
                    }

            for(int i = 0; i < ans.size(); i++)
            {
                std::string s;
                for(int v : ans[i])
                  s += std::to_string(v + 1) + " ";
                s.pop_back();  
                std::cout << s << std::endl;
            }
            std::cout << "total: " << ans.size() << std::endl;
        }
    }
}