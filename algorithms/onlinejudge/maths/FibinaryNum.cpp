/*
───────────────────────────────────────────────────────────────
🧳 UVa 763 Fibinary Numbers, Zeckendorf representation, greedy, use Java BigInteger, https://onlinejudge.org/external/7/763.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>


namespace bg = algorithms::onlinejudge::maths::utility::big_integer;

constexpr int MAX = 500;


namespace algorithms::onlinejudge::maths::fibinary_num
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        std::vector<bg::bigint> fib(MAX + 1);
        fib[0] = bg::bigint(0);
        fib[1] = bg::bigint(1);
        for (int i = 2; i <= MAX; i++) {
          fib[i] = fib[i - 1] + fib[i - 2];
        }

        std::string a, b;
        while (std::cin >> a >> b) {

          if(a == "0" && b == "0") {
            std::cout << 0 << "\n\n";
            continue;
          };

          bg::bigint first;
          for(int i = 0; i < (int)a.size(); i++) {
            if(a[i] == '1') first += fib[a.size() - i + 1];
          }
          bg::bigint second;
          for(int i = 0; i < (int)b.size(); i++) {
            if(b[i] == '1') second += fib[b.size() - i + 1];
          }

          size_t max_len = 0;
          std::vector<int> fibs;
          bg::bigint sum = first + second;
          auto it = std::lower_bound(fib.begin(), fib.end(), sum);
          while(sum > bg::bigint(0)) {
            if(it == fib.begin()) break;
            if(*it > sum) --it;
            if(*it <= sum) {
              int idx = std::distance(fib.begin(), it);  
              fibs.push_back(idx);
              max_len = std::max(max_len, (size_t)idx);
              sum = sum - *it;
              it -= 2; // skip next fib number to ensure non-consecutiveness
            }
          }
          
          std::reverse(fibs.begin(), fibs.end());
          std::string ans(max_len, '0');
          for(int idx : fibs) {
            ans[ans.size() - idx] = '1';
          }
          if(ans.size() > 1) ans.erase(ans.size() - 1, 1); // remove the last '0' which is for fib[1]
          std::cout << ans << "\n\n";
        }
    }
}