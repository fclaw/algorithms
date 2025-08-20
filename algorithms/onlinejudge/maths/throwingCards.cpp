/*
───────────────────────────────────────────────────────────────
🧳 UVa 10940 Throwing cards away II, rt: s
───────────────────────────────────────────────────────────────
[..hs/throwingCards.cpp:44 (submit)] cards_n = 1 (int32_t), deck.front() = 1 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 2 (int32_t), deck.front() = 2 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 3 (int32_t), deck.front() = 2 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 4 (int32_t), deck.front() = 4 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 5 (int32_t), deck.front() = 2 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 6 (int32_t), deck.front() = 4 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 7 (int32_t), deck.front() = 6 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 8 (int32_t), deck.front() = 8 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 9 (int32_t), deck.front() = 2 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 10 (int32_t), deck.front() = 4 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 11 (int32_t), deck.front() = 6 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 12 (int32_t), deck.front() = 8 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 13 (int32_t), deck.front() = 10 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 14 (int32_t), deck.front() = 12 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 15 (int32_t), deck.front() = 14 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 16 (int32_t), deck.front() = 16 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 17 (int32_t), deck.front() = 2 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 18 (int32_t), deck.front() = 4 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 19 (int32_t), deck.front() = 6 (int32_t&)
[..hs/throwingCards.cpp:44 (submit)] cards_n = 20 (int32_t), deck.front() = 8 (int32_t&)
 *
 * --- Mathematical Analysis ---
 *
 * This problem is a variation of the classic Josephus problem. A direct simulation
 * using a queue or deque is too slow for large N (up to 500,000). The key to an
 * efficient O(1) solution is to discover a mathematical formula by observing the
 * behavior for small instances of N.
 *
 *
 * STEP 1: Simulate for small N and collect data.
 *
 * Let f(N) be the last remaining card when starting with N cards.
 *
 * N  | f(N)
 * ---|-----
 * 1  | 1
 * 2  | 2
 * 3  | 2
 * 4  | 4
 * 5  | 2
 * 6  | 4
 * 7  | 6
 * 8  | 8
 * 9  | 2
 * 10 | 4
 * 11 | 6
 * 12 | 8
 * 13 | 10
 * 14 | 12
 * 15 | 14
 * 16 | 16
 *
 *
 * STEP 2: Observe patterns in the collected data.
 *
 * The results reveal a striking pattern centered around powers of two.
 *
 *   a) Perfect Powers of Two:
 *      Whenever N is a power of two (1, 2, 4, 8, 16, ...), the result f(N) is always N itself.
 *      This is because the "halving" nature of the problem is perfect. After one pass,
 *      N cards become N/2, and all remaining cards are even. This clean reduction
 *      continues until only the last card, N, remains.
 *
 *   b) Numbers Between Powers of Two:
 *      For any N that is not a power of two, the results form a simple arithmetic
 *      progression of even numbers.
 *      - After f(4)=4, the sequence for N=5,6,7 is 2, 4, 6.
 *      - After f(8)=8, the sequence for N=9,10,11...15 is 2, 4, 6, 8, 10, 12, 14.
 *      This pattern resets at every power of two.
 *
 *
 * STEP 3: Generalize the pattern into a mathematical formula.
 *
 * We can express any number N in relation to the largest power of two less than or equal to it.
 * Let `p2` be the largest power of two such that `p2 <= N`.
 * Let `l` be the "leftover" or remainder, such that `N = p2 + l`. (Note: `l >= 0`).
 *
 * From our observations:
 * - If `l = 0`, it means `N` is a perfect power of two. The answer is `N`.
 * - If `l > 0`, the answer is the `l`-th even number in the sequence. The `l`-th
 *   positive even number is `2 * l`.
 *
 * This gives us a unified formula:
 * f(N) = 2 * l = 2 * (N - p2)
 *
 * Let's test this:
 *   N=13: `p2 = 8`. `l = 13 - 8 = 5`. f(13) = 2 * 5 = 10. Correct.
 *   N=7:  `p2 = 4`. `l = 7 - 4 = 3`. f(7) = 2 * 3 = 6. Correct.
 *
 * This formula holds for all cases except N=1, which is a simple base case. (Or, it can
 * be seen as `p2=1`, `l=0`, so `N` is a power of two, and the answer is `N`).
 *
 *
 * STEP 4: Implement the formula efficiently.
 *
 * The main task is to find `p2` (the largest power of two <= N). This can be done
 * with a simple loop, bit manipulation, or logarithms. The provided code uses a
 * clever logarithmic approach.
 *
 *   double log_base_2 = std::log2(N);
 *
 *   - `log_base_2` will be an integer if and only if N is a perfect power of two.
 *     We can check this by seeing if the fractional part of `log_base_2` is zero.
 *     If `log_frac == 0`, N is a power of two, and the answer is N.
 *
 *   - If N is not a power of two, `log_int = floor(log_base_2)` gives us the exponent `m`
 *     such that `p2 = 2^m`.
 *     `nearest_pow_2 = std::pow(2, log_int)` calculates `p2`.
 *
 *   - The remainder `l` is not explicitly needed. The final formula `2 * l` can be
 *     written as `2 * (N - p2)`. The provided code uses a different but arithmetically
 *     equivalent approach. Let's analyze `rem = N % p2`.
 *     For N = p2 + l, rem = (p2 + l) % p2 = l.
 *     So `rem` is exactly our `l`. The code then correctly computes `last_card = 2 * rem`.
 *
 * This O(1) mathematical approach completely bypasses the need for simulation.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::throwing_cards
{
    /** /https://onlinejudge.org/external/109/10940.pdf */
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

        
        int cards_n;
        while(scanf("%d", &cards_n) == 1 && cards_n > 0) {
          double log = std::log2(cards_n);
          double log_int;
          double log_frac = std::modf(log, &log_int);
          if(log_frac > 0) {
            int nearest_pow_2 = std::pow(2, log_int);
            int rem = cards_n % nearest_pow_2;
            int last_card = 2 * rem;
            printf("%d\n", last_card);
          } else { printf("%d\n", cards_n); }
        }
    }
}