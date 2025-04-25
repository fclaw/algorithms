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




typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


const int MOD = 1e9;  // 10^9


int main(int argc, char* argv[])
{
    int tc;
    std::cin >> tc;
    while(tc--)
    {
        int N;
        std::string in;
        std::cin >> N;
        std::cin >> in;
        std::bitset<11> s(in);
        int cnt = 0;
        for(int i = 0; i < N; i++)
        {
            s.flip(i);
            cnt += s.count();
            s.flip(i);
        }
        std::cout << cnt << std::endl;
    }
}