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


int t_case, n, sec;

bool backtrack(const vi& doors, int i, bool is_used, int sec_left)
{
    if (i == (int)doors.size()) return true; // base case first!

    int s = doors[i];

    // If the door is closed and the button is used up and time expired, stop
    if (s == 1 && is_used && sec_left <= 0) return false;

    if (s == 0) {
        int new_sec_left = is_used ? sec_left - 1 : sec_left;
        if (new_sec_left >= 0)
            return backtrack(doors, i + 1, is_used, new_sec_left);
        return false;
    }
    else if (s == 1) {
        if (!is_used) {
            return backtrack(doors, i + 1, true, i + sec - 1);
        } else {
            int new_sec_left = sec_left - 1;
            if (new_sec_left >= 0)
                return backtrack(doors, i + 1, is_used, new_sec_left);
            return false;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    
    while_read(t_case);
    while(t_case--)
    {
         while_read(n, sec);
         vi doors(n);
         loop(n, [&doors](int i){  
           int s;
           while_read(s);
           doors[i] = s;
         });
         std::cout << (backtrack(doors, 0, false, 0) ? "YES" : "NO") << std::endl;
    }
}