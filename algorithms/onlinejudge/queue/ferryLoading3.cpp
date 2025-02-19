#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <algorithm>
#include <limits.h>


const std::string LEFT = "left";
const std::string RIGHT = "right";

typedef std::queue<std::pair<int, int>> qi;
typedef std::vector<int> vi;

namespace algorithms::onlinejudge::queue::ferry_3
{
    
    /** https://onlinejudge.org/external/109/10901.pdf, simulation with queue  */
    std::string changeBank(std::string b) { return b == LEFT ? RIGHT : LEFT; }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int capacity, cross_time, N;
            scanf("%d %d %d", &capacity, &cross_time, &N);
            int time;
            std::string bank;
            qi leftBank, rightBank;
            for(int i = 0; i < N; i++)
            { 
                std::cin >> time >> bank;
                if(bank == LEFT)
                  leftBank.push({time, i});
                else rightBank.push({time, i});
            }
            
            int start = 0, load = 0;
            bank = LEFT;
            vi arrivals = vi(N);
            while(!leftBank.empty() || 
                  !rightBank.empty())
            {
                /**
                 * 1. If there are cars waiting at the current bank (bank == LEFT or RIGHT), 
                 * load as many as possible. No crossing needed yet.
                 * 2. If no cars are waiting at the current bank, check when and where the earliest car will arrive.
                 * If the earliest car is on the other bank, cross to that bank.
                 * If both banks have cars, choose the earlier arrival.
                 * If the earlier arrival is on the opposite bank, the ferry must cross.
                 * 3. Avoid crossing unnecessarily
                 * If both banks have cars at the same time, prefer to stay and load from the current bank.
                 * If both banks have future arrivals, pick the earlier one and go there.
                 */
                int tm = std::min(
                    leftBank.empty() ? INT_MAX : leftBank.front().first,
                    rightBank.empty() ? INT_MAX : rightBank.front().first);
                if(start < tm) start = tm;
                 
                load = 0;
                if(bank == LEFT && leftBank.front().first <= start)
                {
                    while(!leftBank.empty() && 
                          load < capacity)
                    {
                        auto p = leftBank.front();
                        int tm = p.first;
                        int idx = p.second;
                        if(tm > start) break;
                        load++;
                        leftBank.pop();
                        arrivals[idx] = start + cross_time;
                    }
                }
                else if(bank == RIGHT && rightBank.front().first <= start)
                {
                    while(!rightBank.empty() && 
                          load < capacity)
                    {
                        auto p = rightBank.front();
                        int tm = p.first;
                        int idx = p.second;
                        if(tm > start) break;
                        load++;
                        rightBank.pop();
                        arrivals[idx] = start + cross_time;
                    }
                }
                
                start += cross_time;
                bank = changeBank(bank);
            }
            for(auto t : arrivals) std::cout << t << std::endl;
            if(tc) std::cout << std::endl;
        }  
    }
}