/*
───────────────────────────────────────────────────────────────
🧳 UVa 10633 Rare Easy Problem, rt: s
───────────────────────────────────────────────────────────────
 * --- The Core Mathematical Insight for UVa 10633 ---
 *
 * The problem gives us C = N - M, where M is the number N with its last digit removed.
 * Our goal is to find all possible values of N given C.
 * The key is to establish a direct mathematical relationship between N, M, and C.
 *
 * Let's define the parts of N:
 * - Let 'M' be the number N with the last digit chopped off.
 * - Let 'a0' be the last digit of N.
 *
 * Any integer N can be expressed in terms of M and a0. For example, if N = 123,
 * then M = 12 and a0 = 3. The relationship is N = 10 * M + a0.
 *
 * Now, let's use the value C that the problem gives us:
 * C = N - M
 *
 * Substitute the expression for N into this equation:
 * C = (10 * M + a0) - M
 *
 * Simplify by combining the 'M' terms:
 * C = 9 * M + a0
 *
 * This formula, C = 9*M + a0, is the key to the entire problem. We can rearrange
 * it to solve for M:
 * 9 * M = C - a0
 *
 * This tells us a critical fact: for a last digit 'a0' to be valid, the
 * expression (C - a0) MUST be perfectly divisible by 9.
 *
 * The Algorithm:
 * Since 'a0' is a single digit, it can only be an integer from 0 to 9.
 * We can iterate through every possible last digit (a0 from 0 to 9) and
 * check if our condition holds.
 *
 * For each a0 in [0, 9]:
 * 1. Check if (C - a0) is non-negative and divisible by 9.
 * 2. If it is, we have found a valid solution.
 *    - Calculate M = (C - a0) / 9.
 *    - Reconstruct N = 10 * M + a0.
 *    - (Sanity Check): The last digit of our calculated N must be a0. This is always true with this formula.
 *
 * This gives us all possible values for N.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



// namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ull = unsigned long long;

// constexpr ll a = 9;
// constexpr ll b = 1;


namespace algorithms::onlinejudge::maths::rare_easy_problem
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

    //    ll c;
    //    while(scanf("%lld", &c) == 1 && c) {
    //      arith::Diophantine<> sol = arith::diophantine_equation<>(a, b, c);
    //      ll low = std::ceil((-sol.x * sol.gcd) / b);
    //      ll up = std::floor((sol.y * sol.gcd) / a);
    //      std::vector<std::string> ans;
    //      for(ll s = up; s >= low; --s) {
    //        ll m = sol.x + (s * b) / sol.gcd;
    //        ll last_digit = sol.y - (s * a) / sol.gcd;
    //        if(last_digit < 0 || m < 0) continue;
    //        if(std::floor(std::log10l(last_digit)) + 1 > 1) break;
    //        std::string res = std::to_string(m) + std::to_string(last_digit); 
    //        ans.push_back(res);
    //      }
    //      std::string s;
    //      int size = ans.size();
    //      for(int i = size - 1; i >= 0; --i) {
    //        s += ans[i];
    //        if(i != 0) s += " ";
    //      }
    //      printf("%s\n", s.c_str());
    //    }
       ull C; // This is the given N-M
       while(scanf("%llu", &C) == 1 && C) {
         
         std::vector<ull> possible_N;

         // Iterate through all possible last digits (a0)
         for (ull a0 = 0; a0 <= 9; ++a0) {
            
            // Check if C - a0 is a non-negative multiple of 9.
            // C = 9*M + a0  =>  9*M = C - a0
            if (C >= a0 && (C - a0) % 9 == 0) {
                
                // If it is, we have found a valid M and can reconstruct N.
                ull M = (C - a0) / 9;
                ull N = 10 * M + a0;
                
                // A quick sanity check (not strictly necessary but good practice):
                // Does the reconstructed N actually have a0 as its last digit?
                if (N % 10 == a0) {
                    possible_N.push_back(N);
                }
            }
         }

         // Sort the answers in ascending order as required by the problem.
         std::sort(possible_N.begin(), possible_N.end());

         // Print the results.
         for (size_t i = 0; i < possible_N.size(); ++i) {
             printf("%llu%c", possible_N[i], i == possible_N.size() - 1 ? '\n' : ' ');
         }
       }
    }
}