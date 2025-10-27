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


    mp::cpp_int combinations_bigint_boost(int n, int k) {
      if (k < 0 || k > n) {
        return 0;
      }
    
      // Use the symmetry C(n, k) = C(n, n-k) for a massive speedup
      // when k is large.
      if (k > n / 2) {
        k = n - k;
      }

      if(k == 0) {
        return 1;
      }
    
      mp::cpp_int numerator(1);
      mp::cpp_int denominator(1);
    
      // Calculate the numerator: n * (n-1) * ... * (n-k+1)
      // and denominator: k!
      for(int i = 1; i <= k; ++i) {
        numerator = numerator * mp::cpp_int(n - i + 1);
        denominator = denominator * mp::cpp_int(i);
      }

      // The final result is numerator / denominator.
      // Your BigInt library must have a correct division operator.
      return numerator / denominator;
    }


int main(int argc, char* argv[])
{
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
      for(int i = 0; i < n; ++i) {
        if(i < m)
          printf("OK\n");
        else
          printf("Too Many Requests\n");
      }
    }
}