/*
───────────────────────────────────────────────────────────────
🧳 UVa 495 Fibonacci Freeze, (O(n) DP; Big Integer, https://onlinejudge.org/external/4/495.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>


namespace bg = algorithms::onlinejudge::maths::utility::big_integer;


const int MAX = 5000;


namespace algorithms::onlinejudge::maths::fibonacci_freeze
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

        int fib_n;
        std::vector<bg::bigint> fib(MAX + 1);
        fib[0] = bg::bigint(0);
        fib[1] = bg::bigint(1);
        for (int i = 2; i <= MAX; i++) {
          fib[i] = fib[i - 1] + fib[i - 2];
        }

        while (std::cin >> fib_n) {
          std::cout << "The Fibonacci number for " << fib_n << " is " << fib[fib_n] << "\n";
        }
    }
}