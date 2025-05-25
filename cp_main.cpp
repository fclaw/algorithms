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



template<typename F>
inline void loop(size_t n, F&& f)
{
    for (size_t i = 0; i < n; ++i)
      std::forward<F>(f)(i);
}

template<typename... Args>
bool while_read(Args&... args) { return (... && static_cast<bool>(std::cin >> args)); }


typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<bool> vb;

const int MOD = 1e9;  // 10^9


int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n, m;
    while_read(n, m);
    vvi grid(n, vi(m));
    int total_or = 0;
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < m; ++j) {
        std::cin >> grid[i][j];
        total_or |= grid[i][j];
      }
    std::cout << total_or << std::endl; 
}