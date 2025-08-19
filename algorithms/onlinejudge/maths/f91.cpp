/*
───────────────────────────────────────────────────────────────
🧳 UVa 10696 f91, rt: s
───────────────────────────────────────────────────────────────
 * --- Mathematical Analysis of McCarthy's f91 Function ---
 *
 * The function is defined by two cases:
 * 1. f91(N) = N - 10,                if N >= 101
 * 2. f91(N) = f91(f91(N + 11)),      if N <= 100
 *
 * At first glance, the nested recursion in the second case, f91(f91(...)), suggests
 * a high computational complexity. However, as the sketch correctly intuits, the
 * function collapses to a much simpler, non-recursive form.
 *
 * Our goal is to prove the simplified closed-form solution:
 * 1. f91(N) = N - 10,                if N >= 101
 * 2. f91(N) = 91,                     if N <= 100
 *
 * --- Proof ---
 *
 * Case 1: N >= 101
 * This is the base case of the recursion. The definition is direct and requires no further analysis.
 * f91(N) = N - 10.
 *
 * Case 2: N <= 100
 * This is the interesting part. We need to prove that f91(N) consistently evaluates to 91.
 * Let's work backwards from N = 100, as demonstrated in the sketch.
 *
 * Sub-case 2a: 90 <= N <= 100
 *
 *   Let's analyze f91(100):
 *   f91(100) = f91(f91(100 + 11))
 *            = f91(f91(111))
 *   Since 111 >= 101, f91(111) = 111 - 10 = 101.
 *            = f91(101)
 *   Since 101 >= 101, f91(101) = 101 - 10 = 91.
 *   Therefore, f91(100) = 91.
 *
 *   Now let's analyze f91(99):
 *   f91(99) = f91(f91(99 + 11))
 *           = f91(f91(110))
 *   Since 110 >= 101, f91(110) = 110 - 10 = 100.
 *           = f91(100)
 *   We just proved f91(100) = 91.
 *   Therefore, f91(99) = 91.
 *
 *   This reveals a pattern. For any N in the range [90, 100], N+11 will be >= 101.
 *   The inner call f91(N + 11) becomes (N + 11) - 10 = N + 1.
 *   So, for 90 <= N < 101, the recursion simplifies to:
 *   f91(N) = f91(N + 1)
 *
 *   This confirms the hypothesis in the sketch. Since f91(100)=91, it follows that
 *   f91(99) = f91(100) = 91
 *   f91(98) = f91(99) = 91
 *   ...
 *   f91(90) = f91(91) = 91
 *
 * Sub-case 2b: N < 90
 *
 *   Let's analyze f91(89):
 *   f91(89) = f91(f91(89 + 11))
 *           = f91(f91(100))
 *   We know f91(100) = 91.
 *           = f91(91)
 *   We already proved from Sub-case 2a that f91(91) = 91.
 *   Therefore, f91(89) = 91.
 *
 *   This pattern holds true for all N <= 100. The repeated addition of 11 in the
 *   inner recursive call always pushes the argument into the [90, 100] range, which
 *   then collapses to the value 91.
 *
 * --- Complexity Analysis ---
 *
 * A naive recursive implementation would be highly inefficient, as it would
 * repeatedly re-calculate values like f91(91), f91(100), etc., leading to an
 * exponential number of function calls in the worst cases. The complexity would
 * be far from factorial, but still very slow.
 *
 * However, with the mathematical proof above, we can bypass recursion entirely.
 * The computation for any N becomes a simple O(1) check:
 * - If N is greater than or equal to 101, the answer is N - 10.
 * - Otherwise, the answer is 91.
 *
 * This insight transforms an expensive recursive problem into a trivial conditional statement.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::f_91
{
    /** https://onlinejudge.org/external/106/10696.pdf */
    int n;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while(scanf("%d", &n) == 1 && n > 0) {
          printf("f91(%d) = %d\n", n, n >= 101 ? n - 10 : 91);
        }  
    }
}