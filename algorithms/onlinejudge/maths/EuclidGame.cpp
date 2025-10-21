/*
───────────────────────────────────────────────────────────────
🧳 UVa 10368 Euclid's Game, https://onlinejudge.org/external/103/p10368.pdf, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: Recursive Exploration ("Dive Deep") for Euclid's Game
 * =====================================================================================
 *
 * This game is solved using a recursive (top-down DP) approach that determines if a
 * given state (a, b) is a Winning (W) or Losing (L) position. The core mental model
 * for this function is to "dive deep until a winning state is found."
 *
 * -------------------------------------------------------------------------------------
 * The "Dive Deep" Process (Recursion):
 * -------------------------------------------------------------------------------------
 * The `can_win(a, b)` function explores the game tree by making recursive calls. Each
 * call represents a player making a move and "diving" one level deeper to see the
 * consequences. This process continues until the recursion hits a state where the
 * outcome is known without further exploration.
 *
 * -------------------------------------------------------------------------------------
 * Reaching a "Known State" (The Base Cases and Shortcuts):
 * -------------------------------------------------------------------------------------
 * The dive stops when it reaches a state with a definitive, pre-determined outcome.
 * These are our base cases and crucial optimizations:
 *
 * 1. THE TERMINAL LOSS (b == 0): If a player starts their turn with b=0, they have
 *    no moves. The dive stops; this is a Losing position.
 *
 * 2. THE IMMEDIATE WIN (a % b == 0): A player can subtract a multiple of 'b' to
 *    leave 0. The dive stops; this is a Winning position.
 *
 * 3. THE STRATEGIC WIN (a >= 2*b): This is a powerful shortcut. If the larger number
 *    is at least twice the smaller, the current player has a CHOICE of multiple
 *    moves. A perfect player can always leverage this choice to force the opponent
 *    into a losing position. The dive stops; this is a Winning position.
 *
 * -------------------------------------------------------------------------------------
 * The Logic of Perfect Play
 * -------------------------------------------------------------------------------------
 *
 * The function embodies the rules of optimal play. From a state (a, b) that is not a
 * known win/loss state (i.e., where 1 < a/b < 2):
 *
 * - A player has only ONE possible move: to the state (b, a-b). They have no choice.
 *
 * - The function then makes a single recursive "dive" to determine the fate of the
 *   opponent from this new state: `can_win(b, a-b)`.
 *
 * - Since the player has no other options, their fate is the exact opposite of their
 *   opponent's. The result is `!can_win(b, a-b)`.
 *
 * Memoization is used to cache the results of these "dives" so that the outcome for
 * any given state is only ever computed once.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



bool can_win(uint32_t a, uint32_t b) {

  // Case 1: If b is 0, the previous player made the last move. This is a losing position for us.
  // Case 2: If a is a multiple of b, we can subtract k*b to leave (0, b). This is an immediate win.
  if(b == 0 || !(a % b)) 
    return true;

  // =====================================================================================
  // THE STRATEGIC SHORTCUT: The Power of Choice
  // =====================================================================================
  // This 'if' statement is the most important part of the algorithm. It is the core
  // insight that reduces the problem from an exponential brute-force search to a
  // fast, logarithmic-time solution. It "draws the line" between a state where the
  // player has agency and a state where their fate is sealed.
  //
  // 1. The Situation: `a / b >= 2` means the larger number is at least twice the smaller.
  //
  // 2. The Consequence: This gives the current player a CHOICE of multiple distinct moves.
  //    They can subtract k=1 times 'b', k=2 times 'b', and possibly more. This puts them
  //    in control of the game's direction.
  //
  // 3. The Optimal Strategy: A perfect player can analyze the sub-games resulting from
  //    each choice. It is a proven property of this game that if a player has this choice,
  //    at least one of their available moves will lead to a state that is a guaranteed
  //    "Losing Position" for the opponent. They can "steer" the game onto a path that
  //    is fatal for their opponent.
  //
  // 4. The Conclusion: Because a winning move is always available from this state, this is
  //    by definition a "Winning Position". We can stop the recursive exploration ("dive")
  //    and return 'true' immediately. This shortcut prunes massive branches from the game tree.
  if(a / b >= 2) return true;

  bool is_win_state = false;
  for(uint32_t k = 1; k * b <= a; ++k)
    is_win_state = is_win_state || !can_win(std::max(a - k * b, b), std::min(a - k * b, b));

  return is_win_state;
}


namespace algorithms::onlinejudge::maths::euclid_game
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

        // std::memset(memo, -1, sizeof(memo));
        uint32_t a, b;
        while(scanf("%u %u", &a, &b) == 2 && a && b) {
          printf("%s\n", can_win(std::max(a, b), std::min(a, b)) ? "Stan wins" : "Ollie wins");
        }
    }
}