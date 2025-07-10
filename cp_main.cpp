#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <cctype>
#include <queue>
#include <bitset>
#include <cmath>
#include <functional>



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
    int N;
    while(while_read(N)) {
      int a, b;
      std::vector<int> q_vector(N);
      std::vector<int> compressed_vector(N);

      for(int i = 0; i < N; ++i)
        while_read(q_vector[i]);

      for(int i = 0; i < N; ++i)
        while_read(compressed_vector[i]);

      while_read(a, b);

      std::vector<int> d_vector(N);
      for(int i = 0; i < N; ++i) {

        // a >= b
        if (a == b) 
        { d_vector[i] = a; continue; }

        int c_i = compressed_vector[i];
        ll numerator = 1LL * c_i * (b - a);
        ll divisor = 255;
        //  round up
        ll rounded = (numerator + divisor / 2) / divisor;
        int d_i = a + rounded;
        d_vector[i] = d_i;
      }

      ll scalar_product = 0;
      for(int i = 0; i < N; ++i) {
        scalar_product += 1LL * q_vector[i] * d_vector[i];
      }

      std::cout << scalar_product << std::endl;
    }
}