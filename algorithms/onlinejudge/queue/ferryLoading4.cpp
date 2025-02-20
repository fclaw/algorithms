#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>


const std::string LEFT = "left";
const std::string RIGHT = "right";

typedef std::queue<int> qi;

namespace algorithms::onlinejudge::queue::ferry_4
{
    
    /** https://onlinejudge.org/external/110/11034.pdf */
    std::string changeBank(std::string b) { return b == LEFT ? RIGHT : LEFT; }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int cargo_length, N;
            scanf("%d %d", &cargo_length, &N);
            
            cargo_length *= 100; // convert to centimetres
            int car_length;
            std::string bank;
            qi leftBank, rightBank;
            for(int i = 0; i < N; i++)
            { 
                std::cin >> car_length >> bank;
                if(bank == LEFT)
                  leftBank.push(car_length);
                else rightBank.push(car_length);
            }

            int runs = 0, curr_length = 0;
            bank = LEFT;
            while(!leftBank.empty() || 
                  !rightBank.empty())
            {
                // where to go choice
                if ((bank == LEFT && leftBank.empty() && !rightBank.empty()) ||
                (bank == RIGHT && rightBank.empty() && !leftBank.empty()))
                { bank = changeBank(bank); runs++; }

                curr_length = 0;
                if(bank == LEFT)
                {
                    while(!leftBank.empty())
                    {
                        int l = leftBank.front();
                        if(l + curr_length > cargo_length) break;
                        leftBank.pop();
                        curr_length += l;
                    }
                }
                else
                {
                    while(!rightBank.empty())
                    {
                        int l = rightBank.front();
                        if(l + curr_length > cargo_length) break;
                        rightBank.pop();
                        curr_length += l;
                    }
                }
                runs++;
                bank = changeBank(bank);
            }
            std::cout << runs << std::endl;
        }
    }
}