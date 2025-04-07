#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>




typedef std::vector<int> vi;

namespace algorithms::onlinejudge::complete_search::antiarithmetic
{
    /** https://onlinejudge.org/external/107/10730.pdf 
     * 2 nested loops with pruning can possibly pass the weaker test cases; 
     * note that this brute force solution is too slow for 
     * the larger test data generated in the solution of UVa 11129 */
    bool is_number(const std::string& s) 
    { return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit); }
    bool isAntiarithmetic(const vi& nums, vi& valToIdx)
    {
        int s = nums.size();
        bool right = true;
        for(int i = 0; i < s && right; i++)
          for(int j = i + 1; j < s && right; j++)
          {
              // 2 * c (num[j]) = a(num[i])  + b(num[k])
              int b = 2 * nums[j] - nums[i];
              if(b >= 0 && b < s && valToIdx[b] > j)
              { right = false; break; }
          }
        return right;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(std::cin >> N && N)
        {
            vi numbers;
            std::string in, s;
            std::getline(std::cin, in);
            std::stringstream ss(in);
            while(ss >> s)
              if(is_number(s))
                numbers.push_back(std::atoi(s.c_str()));
            vi valToIdx(N);
            for(int i = 0; i < N; i++)
              valToIdx[numbers[i]] = i;              
            std::cout << (isAntiarithmetic(numbers, valToIdx) ? "yes" : "no") << std::endl;
        }  
    }
}