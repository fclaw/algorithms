#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>


typedef std::stack<int> si;
typedef std::vector<int> vi;
#define loop(x, s, n) for(int x = s; x < n; x++)

namespace algorithms::onlinejudge::stack::rails
{
    
    /** https://onlinejudge.org/external/5/514.pdf, use stack to simulate the process */
    bool isMoved(const vi& track_a, const vi& track_b)
    {
        si tmp;
        int i = 0, j = 0;
        while(i < track_a.size())
        {
            tmp.push(track_a[i++]);
            while(!tmp.empty() && tmp.top() == track_b[j])
            { tmp.pop(); j++; }
        }

        return tmp.empty() && j == track_b.size();
    } 
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(true)
        {
            std::cin >> N;
            if(N == 0) break;
            vi track_a = vi(N);
            loop(i, 1, N + 1) 
              track_a[i - 1] = i;
            
            int el;
            bool isFinished = false;
            while(!isFinished)
            {
                vi track_b = vi(N);
                loop(i, 0, N)
                {
                    std::cin >> el;
                    if(el == 0)
                    { isFinished = true; break; }
                    track_b[i] = el;
                }
                if(!isFinished)
                  std::cout << (isMoved(track_a, track_b) ? "Yes" : "No") << std::endl;
            }
            std::cout << std::endl;
        }
    }
}