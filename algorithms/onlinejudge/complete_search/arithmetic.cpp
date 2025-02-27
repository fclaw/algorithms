#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>


typedef std::vector<int> vi;
typedef std::vector<char> vc;


namespace algorithms::onlinejudge::complete_search::arithmetic
{
    /** https://onlinejudge.org/external/103/10344.pdf, 
     * rearrange the 5 operands and the 3 operators,
     * the precedence of operators doesn't matter, 
     * the whole expression is evaluated in a left-right fashion */
    vc ops = {'*', '-', '+'};
    const int N = 5;
    const int M = 3;
    const int ref = 23;
    int eval(int first, int second, char op) 
    {
        switch (op) 
        {
            case '*': return first * second;
            case '+': return first + second;
            case '-': return first - second;
            default: throw std::invalid_argument("Unsupported operator");
        }
    }
    void backtrack(const vi& nums, int mask, int val, bool& ans)
    {
        if(ans) return;

        if(mask ==  ((1 << N) - 1))
        { ans = ref == val; return; }

        for (int i = 0; i < N; i++) 
          if(!(mask & (1 << i)))
            for (int j = 0; j < M; j++) 
            {
                backtrack(nums, mask | (1 << i), eval(val, nums[i], ops[j]), ans);
                if(ans) return;
            }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string line;
        bool isFinished = false;
        while(std::getline(std::cin, line))
        {
            std::istringstream iss(line);
            int n;
            vi numbers;
            while (iss >> n && n != 0)
              numbers.push_back(n);

            if(!numbers.empty())
            {
                bool ans = false;
                for(int i = 0; i < numbers.size() && !ans; i++)
                   backtrack(numbers, 0 | (1 << i), numbers[i], ans);
                std::cout << (ans ? "Possible" : "Impossible") << std::endl;
            }
        }
    }
}