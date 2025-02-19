#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::tuple<int, int, vi> factor_state;

namespace algorithms::onlinejudge::stack::factorization
{
    
    /** https://onlinejudge.org/external/108/10858.pdf, 
     * use stack to help solving this problem
     */
    vvi vec_of_factors;
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int number;
        while(true)
        {
            vec_of_factors.clear();
            std::cin >> number;
            if(number == 0) break;

            std::stack<factor_state> state;
            // init state
            state.push({2, number, {}});
            while(!state.empty())
            {
                factor_state st = state.top();
                state.pop();
                int factor = std::get<0>(st);
                int quotient = std::get<1>(st);
                vi factors = std::get<2>(st);
                if(quotient == 1)
                  vec_of_factors.push_back(factors);
                else 
                  for(int n = factor; n <= quotient; n++)
                    if(!(quotient % n))
                    {
                        factors.push_back(n);
                        state.push({n, quotient / n, factors});
                        factors.pop_back();
                    }
            }

            std::cout << vec_of_factors.size() - 1 << std::endl;
            for(int i = vec_of_factors.size() - 1; i > 0; i--)
            {
                for(int j = 0; j < vec_of_factors[i].size(); j++)
                { std::cout << vec_of_factors[i][j];
                  if(j < vec_of_factors[i].size() - 1) 
                    std::cout << " "; 
                }
                std::cout << std::endl;  
            }
        }
    }
}