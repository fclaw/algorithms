#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>
#include <unordered_set>
#include <cctype>
#include <queue>
#include <bitset>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


const int MOD = 1e9;  // 10^9


int main(int argc, char* argv[])
{
    int N, M;
    while(std::cin >> N >> M)
    {
        vvi dishes(M);
        int S, v;
        for(int i = 0; i < M; i++)
        {
            std::cin >> S;
            vi xs;
            int ing;
            for(int j = 0; j < S; j++)
            {
                std::cin >> ing; 
                xs.push_back(ing);
            }
            dishes[i] = xs;  
        }      
        vi ingredient(N);
        for(int i = 0; i < N; i++)
          std::cin >> ingredient[i];
            
        bool isAny;
        int cnt = 0;
        for(int ing : ingredient)
        {
            isAny = false;
           for(int i = 0; i < M; i++)
           {
            if(dishes[i].second && dishes[i].first.none()) 
            { isAny = true; cnt++; dishes[i].second = false; }
          }
          std::cout << cnt << std::endl;
        }
    }
}