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


bool can_form_palindrome_ascii(const std::string& s) {
    // ASCII character frequency table
    std::vector<int> freq(256, 0);
    for (char c : s) {
        freq[static_cast<unsigned char>(c)]++;
    }

    int odd_count = 0;
    for (int count : freq) {
        if (count % 2 != 0) {
            odd_count++;
        }
    }

    return odd_count <= 1;
}


bool can_be_palindrome_by_one_replacement(const std::string& s) {
  int count = 0;
  for(int i = 0; i < s.size(); ++i) {
    if(s[i] != s[s.size() - i]) {
      count++;
      if(count > 1) {
        return false;
      }
    }
  }
  return true;
}


int main(int argc, char* argv[])
{
  std::string s;
  while(std::cin >> s) {
    int count = 0;
    std::set<char> un(s.begin(), s.end());
    for(int i = 0; i < s.size(); ++i) {
      for(int j = i; j < s.size(); ++j) {
        auto sub = s.substr(i, j - i + 1);
        if(can_form_palindrome_ascii(sub) || can_be_palindrome_by_one_replacement(sub)) {
          count++;
        }
      }
    }
    std::cout << count << std::endl;
  }
}