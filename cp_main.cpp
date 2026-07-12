#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp> // The header for the bigint class


namespace mp = boost::multiprecision;

using ll = long long;


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
  int lines, colours;
  while(std::cin >> lines >> colours) {
    vi balls(colours, -1);
    int ball, size;
    for(int l = 0; l < lines; ++l) {
      std::cin >> ball >> size;
      balls[ball - 1] = std::max(balls[ball - 1], size);
    }

    for(int i = 0; i < (int)balls.size(); ++i) {
      std::cout << balls[i];
      if(i != (int)balls.size() - 1) {
        std::cout << " ";
      }
    }
  }
}