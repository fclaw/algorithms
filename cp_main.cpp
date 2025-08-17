#include <bits/stdc++.h>


template<typename F>
inline void loop(size_t n, F&& f) {
  for(size_t i = 0; i < n; ++i)
    std::forward<F>(f)(i);
}

// Overloading the >> operator for std::pair<int, int>
std::istream& operator >> (std::istream& is, std::pair<int, int>& p) { return is >> p.first >> p.second; }

template<typename... Args>
bool while_read(Args&... args) { return (... && static_cast<bool>(std::cin >> args)); }


typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;

constexpr int MOD = 1e9;  // 10^9
constexpr int inf = 1e5;



int main(int argc, char* argv[])
{
}