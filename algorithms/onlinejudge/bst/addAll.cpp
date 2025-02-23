#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <queue>




typedef std::priority_queue<int> pqi;


namespace algorithms::onlinejudge::bst::add_all
{
    // https://onlinejudge.org/external/109/10954.pdf, use priority queue, greedy
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(true)
        {
            int N;
            pqi numbers;
            std::cin >> N;
            if(N == 0) break;
            int n;
            for(int i = 0; i < N; i++) 
            { std::cin >> n; numbers.push(-n); }

            int cost = 0;
            while(numbers.size() > 1)
            {
                int first = (-1) * numbers.top();
                numbers.pop();
                int second = (-1) * numbers.top();
                numbers.pop();
                cost += first + second;
                numbers.push(-(first + second));
            }
            std::cout << cost << std::endl;
        }  
    }
}