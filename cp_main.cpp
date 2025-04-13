#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <string>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


const int MOD = 1e9;  // 10^9

int main(int argc, char* argv[])
{
    long long N, K;
    std::cin >> N >> K;

     
    std::cout << (N > K ? ((N - K) * (K + N) / 2) % MOD : 1) << std::endl;  
    
        
}