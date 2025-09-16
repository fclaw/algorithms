/*
───────────────────────────────────────────────────────────────
🧳 UVa 10407 Simple division, https://onlinejudge.org/external/104/10407.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ='====================================================================================
 *
 * --- Analysis: From Common Remainders to a Common Divisor ---
 *
 * The problem asks for an integer `d` such that a given set of numbers
 * {n₁, n₂, n₃, ...} all produce the same remainder when divided by `d`.
 *
 * This problem can be elegantly solved by transforming the condition on remainders
 * into a condition on the differences between the numbers.
 *
 *
 * ### Step 1: Formalizing the Condition ###
 *
 * If all numbers `n_i` have the same remainder `r` when divided by `d`, we can
 * write this using the definition of integer division:
 *   n₁ = q₁*d + r
 *   n₂ = q₂*d + r
 *   n₃ = q₃*d + r
 *   ... for some integer quotients q_i.
 *
 *
 * ### Step 2: The Key Insight - The Difference of Pairs ###
 *
 * Let's subtract any two of these equations, for example, the first two:
 *   (n₁ - n₂) = (q₁*d + r) - (q₂*d + r)
 *   (n₁ - n₂) = (q₁ - q₂) * d
 *
 * This algebraic step reveals a crucial property: the difference between any two
 * numbers in the original set (`n₁ - n₂`) must be a multiple of `d`. In other
 * words, `d` must be a common divisor of all such differences.
 *
 *
 * ### Step 3: Finding the Greatest Common Divisor ###
 *
 * To find the largest possible divisor `d` that satisfies this condition for the
 * entire set, we need to find the Greatest Common Divisor (GCD) of all possible
 * pairwise differences.
 *
 *   d = gcd(|n₁-n₂|, |n₁-n₃|, |n₂-n₃|, ...)
 *
 * A property of the GCD is that gcd(a, b, c) = gcd(a, gcd(b, c)). Another is that
 * if d divides 'a' and 'b', it also divides 'a-b'. This means we don't need to
 * compute the GCD of all N*(N-1)/2 differences.
 *
 * We can simplify the problem by picking an arbitrary number from the set as a pivot
 * (e.g., the first element, `first_el`) and calculating the GCD of the differences
 * relative to this pivot.
 *
 *   d = gcd(|n₂ - first_el|, |n₃ - first_el|, |n₄ - first_el|, ...)
 *
 * The code implements this exact logic.
 *
 *
 * ### Code Implementation ###
 *
 * 1. Read the sequence of numbers.
 * 2. Store the first element `first_el` as a pivot.
 * 3. Create a vector of the differences between every subsequent number and `first_el`.
 * 4. Compute the GCD of all the elements in this new vector of differences.
 * 5. The absolute value of this final GCD is the desired divisor `d`.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>

namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;
using v_ll = std::vector<ll>;

auto ___gcd = arithmetics::__gcd<ll>;

namespace algorithms::onlinejudge::maths::simple_division
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
       
        std::string s;
        while(std::getline(std::cin, s) && 
              s.front() != '0') {
          std::stringstream ss(s);
          ll n;
          int i = 0;
          ll first_el;
          v_ll nums;
          while(ss >> n && n) {
            if(i == 0) {
              first_el = n;
            } else {
              nums.push_back(n - first_el);
            }
            ++i;
          }

          ll divisor = nums.front();
          for(size_t i = 1; i < nums.size(); ++i)
            divisor = ___gcd(divisor, nums[i]);
          printf("%lld\n", std::abs(divisor));  
        }
    }
}