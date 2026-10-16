/*
───────────────────────────────────────────────────────────────
🧳 Two Sets, https://cses.fi/problemset/task/1092, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../onlinejudge/debug.h"
#include "../aux.h"
#include <bits/stdc++.h>



namespace algorithms::cses::two_sets
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
        
        int N;
        while(stdin_read(N)) {
          ll sum = 0;
          for(int i = 1; i <= N; ++i) {
            sum += i;
          }
          if((sum % 2)) {
            std::cout << "NO\n";
          } else {
            std::cout << "YES\n";
            ll target = sum / 2;
            ll set_sum = 0;
            int i = 1;
            while(set_sum <= target) {
              set_sum += i;
              i++;
            }
            ll diff = set_sum - target;
            std::cout << (i - 2) << "\n";
            for(int k = 1; k < i; ++k) {
              if(k == diff) continue;
              std::cout << k << " ";
            }
            std::cout << "\n";
            std::cout << N - i + 2 << "\n";
            if(diff > 0) std::cout << diff << " ";
            for(int p = i; p <= N; ++p) {
              std::cout << p << " ";
            }
            std::cout << "\n";
          }
        }
    }
}
