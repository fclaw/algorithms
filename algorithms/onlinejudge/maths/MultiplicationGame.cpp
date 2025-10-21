/*
───────────────────────────────────────────────────────────────
🧳 UVa 847 A Multiplication Game, https://onlinejudge.org/external/8/p847.pdf, rt: s
───────────────────────────────────────────────────────────────
2 <- Stan 1st winning streak starts
3
4
5
6
7
8
9 <- Stan 1st winning streak ends
10 <- Ollie 1st winning streak starts
11
12
13
14
15
16
18 <- Ollie 1st winning streak ends
19 <- Stan 2nd winning streak starts 18 + 1
160
161
162 <- Stan 2nd winning streak ends at 18 * 9
163 <- Ollie 2nd winning streak starts 18 * 9 + 1

transition rule: Stan -> Ollie: 2, Ollie -> Stan: 9

 * =====================================================================================
 * STRATEGIC GUIDE: SOLVING UVa 847 - A Multiplication Game
 * =====================================================================================
 *
 * This is a classic impartial game that can be solved by analyzing winning and losing
 * positions. While a standard recursive game theory DP would work, the state space (the
 * number 'p') grows exponentially, making a simple DP too slow.
 *
 * The key insight is to realize that both players will play optimally to end the game
 * as quickly as possible (for them) or prolong it as much as possible (for the opponent).
 *
 * -------------------------------------------------------------------------------------
 * The Core Insight: Optimal Play Creates "Winning Intervals"
 * -------------------------------------------------------------------------------------
 *
 * Let's analyze the game from the perspective of the current accumulated product 'p',
 * starting with p=1.
 *
 * - Stan's Optimal Move: To win, Stan needs to reach a number >= n. To do this as fast
 *   as possible and give Ollie the worst possible position, Stan will always multiply by
 *   the largest available factor, which is 9.
 *
 * - Ollie's Optimal Move: To counter Stan, Ollie also wants to reach 'n'. However, if he
 *   can't win on his turn, his goal is to keep 'p' as small as possible to limit Stan's
 *   options on the next turn. Therefore, Ollie will always multiply by the smallest
 *   available factor, which is 2.
 *
 * This optimal back-and-forth (`*9`, `*2`, `*9`, `*2`, ...) creates a sequence of winning
 * intervals for each player.
 *
 * - The very first interval: If the target `n` is between 2 and 9, Stan can win on his
 *   first move by picking a number >= `n`. So, [2, 9] is Stan's first winning interval.
 *
 * - Ollie's first winning interval: If Stan is forced to leave 'p' in the range [2, 9],
 *   and Ollie can multiply it to reach `n`, Ollie wins. Stan's worst-case for Ollie is to
 *   pick 9. Ollie's best-case is to pick 2. After Stan picks 9, p=9. Ollie multiplies by 2,
 *   making p=18. Ollie can win if `n` is in the range (9, 18].
 *
 * - Stan's second winning interval: If the game continues, 'p' is now 18. Stan multiplies
 *   by 9, reaching p = 162. Stan can win if `n` is in the range (18, 162].
 *
 * This reveals the pattern you discovered:
 *
 *   - Stan wins if n is in: [2, 9], [19, 162], [325, 2916], ...
 *   - Ollie wins if n is in: [10, 18], [163, 324], [2917, 5832], ...
 *
 * The transition rule between these intervals is:
 *   - The end of Stan's interval, `end_stan`, becomes the start of Ollie's, `start_ollie = end_stan + 1`.
 *   - Ollie wins up to `end_ollie = end_stan * 2`.
 *   - The start of Stan's next interval is `start_stan = end_ollie + 1`.
 *   - Stan wins up to `end_stan = end_ollie * 9`.
 *
 * The solution is a simple loop that simulates this optimal game turn by turn, alternating
 * the multiplication factor, until 'p' reaches the target 'n'. The winner is the player
 * whose turn it is when 'p' first becomes >= 'n'.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


enum Player { Stan, Ollie };

using ull = unsigned long long;

constexpr ull two = 2;
constexpr ull nine = 9;


// transition rule
ull apply_transition_rule(ull n, ull p) {
  return p == Stan ? n * two : n * nine;
}

// to reveal pattern
bool can_win(ull a, ull target) {
  if(a >= target) return false;

  bool is_win_state = false;
  for(ull k = two; k <= nine; ++k)
    is_win_state = is_win_state || !can_win(a * k, target);
  return is_win_state;
}

Player do_multiplication(std::pair<ull, ull> win_streak, Player player, ull target) {
  if(target >= win_streak.first && 
     target <= win_streak.second)
    return player;
  ull first_v = win_streak.second + 1;
  ull second_v = apply_transition_rule(win_streak.second, player);
  return do_multiplication({first_v, second_v}, player == Stan ? Ollie : Stan, target);
}


namespace algorithms::onlinejudge::maths::multiplication_game
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

        ull target;
        while(scanf("%llu", &target) == 1) {
          printf("%s.\n", target > 1 && do_multiplication({two, nine}, Stan, target) == Stan ? "Stan wins" : "Ollie wins");
        }
    }
}