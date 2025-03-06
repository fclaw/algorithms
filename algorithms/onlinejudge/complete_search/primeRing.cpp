#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




namespace algorithms::onlinejudge::complete_search::prime_ring
{

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


    /** https://onlinejudge.org/external/5/524.pdf */
    int N;
    bool checkPrime(int n)
    {
        bool isPrime = true;
        for(int i = 2; i * i <= n; i++)
          if(n % i == 0)
          { isPrime = false; break; }
        return n >= 2 && isPrime;
    }

    void backtrack(vi& seq, vvi& ans, int mask)
    {
        if(seq.size() == N)
        {
            int sum = seq[0] + seq.back();
            if(checkPrime(sum)) 
              ans.push_back(seq);
            return;
        }

        for(int i = 2; i <= N; i++)
          if(checkPrime(i + seq.back()) && 
             !(mask & (1 << i)))
          {
              seq.push_back(i);
              backtrack(seq, ans, mask | (1 << i));
              seq.pop_back();
          }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int c = 1;
        bool isEnd = false;
        while(std::cin >> N)
        { 
            if(isEnd) std::cout << std::endl;
            isEnd = true;
            vi seq;
            vvi ans;
            seq.push_back(1);
            backtrack(seq, ans, 0);
            printf("Case %d:\n", c++);
            for(auto nums : ans)
            {
                for(int i = 0; i < nums.size(); i++)
                {  std::cout << nums[i];
                   if(i != nums.size() - 1) std::cout << " ";
                }
                std::cout << std::endl;
            }
        } 
    }
}
