/*
───────────────────────────────────────────────────────────────
🧳 UVa 10056 What is the Probability?, https://onlinejudge.org/external/100/10056.pdf, get the closed form formula, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 * STRATEGIC GUIDE: SOLVING UVa 10056 - What is the Probability?
 * =====================================================================================
 *
 * This problem asks for the probability of a specific player 'I' winning a turn-based
 * game. A key feature is that the game has no fixed number of rounds; it could
 * theoretically continue forever. This is a strong signal that we cannot solve it by
 * counting discrete outcomes. Instead, the solution lies in finding and summing an
 * infinite series of probabilities.
 *
 * -------------------------------------------------------------------------------------
 * The Core Insight: Pattern Spotting in an Infinite Process
 * -------------------------------------------------------------------------------------
 *
 * The heuristic for this type of problem is to "write out the first few terms" to
 * spot a mathematical pattern. Let's analyze the mutually exclusive scenarios in which
 * Player 'I' can win.
 *
 * Let:
 *   - N = number of players
 *   - p = probability of success on a single throw
 *   - I = the 1-indexed serial of our player
 *
 * SCENARIO 1: Player 'I' wins on their very first turn (in Round 1).
 *   - For this to happen, the first (I-1) players must fail, then Player 'I' must succeed.
 *   - The probability of this sequence is: P(Win in R1) = (1-p)^(I-1) * p
 *
 * SCENARIO 2: Player 'I' wins on their second turn (in Round 2).
 *   - This requires two stages:
 *     1. Everyone fails in the first full round. The probability of this complete cycle
 *        of failure is (1-p)^N.
 *     2. The "Win in R1" sequence from above must then occur in the second round.
 *   - The total probability is: P(Win in R2) = [ (1-p)^N ] * [ (1-p)^(I-1) * p ]
 *
 * SCENARIO 3: Player 'I' wins on their third turn (in Round 3).
 *   - This requires everyone to fail in Round 1 AND Round 2, followed by the winning sequence.
 *   - The total probability is: P(Win in R3) = [ (1-p)^N ]^2 * [ (1-p)^(I-1) * p ]
 *
 * -------------------------------------------------------------------------------------
 * Identifying the Geometric Series
 * -------------------------------------------------------------------------------------
 *
 * The total probability is the sum of all these infinite scenarios:
 *   P_total = P(Win in R1) + P(Win in R2) + P(Win in R3) + ...
 *
 * Let's define two terms for clarity:
 *   - Let 'A' = (1-p)^(I-1) * p   (The probability of the winning turn sequence)
 *   - Let 'R' = (1-p)^N             (The probability of a full round of failures)
 *
 * Now, the sum becomes:
 *   P_total = A + A*R + A*R^2 + A*R^3 + ...
 *
 * We can factor out 'A':
 *   P_total = A * (1 + R + R^2 + R^3 + ...)
 *
 * The term in the parentheses is an infinite geometric series. Its sum is given by the
 * classic formula: Sum = 1 / (1 - R).
 * (This formula is valid because 0 <= R < 1).
 *
 * -------------------------------------------------------------------------------------
 * The Final Closed-Form Formula
 * -------------------------------------------------------------------------------------
 *
 * By substituting our 'A' and 'R' back into the equation, we get the final formula:
 *
 *   P_total = A * (1 / (1 - R))
 *           = [ (1-p)^(I-1) * p ] / [ 1 - (1-p)^N ]
 *
 * This elegant closed-form solution allows us to calculate the sum of an infinite number
 * of scenarios with a single, fast computation. The code implements this final formula directly.
 *
 * The special case where p=0 means winning is impossible, so the probability is 0.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





namespace algorithms::onlinejudge::maths::what_is_probability
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

        int t_cases, players, serial;
        double prob;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d %lf %d", &players, &prob, &serial);
          printf("%0.4f\n", prob > 0.0 ? prob * std::pow(1 - prob, serial - 1) / (1 - std::pow(1 - prob, players)) : 0.0);
        }
    }
}