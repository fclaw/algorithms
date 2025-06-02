/*
 *
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 10465 HomerSimpson, rt: 0.880s top-down
 * ───────────────────────────────────────────────────────────────
 * Problem Subtlety:
 * -----------------
 * The main challenge in this problem is not the dynamic programming logic itself,
 * but the correct prioritisation when choosing between valid options.
 *
 * Homer has two burger options (sizes m and n), and he wants to eat as many burgers as possible
 * in exactly t minutes. However, if it's not possible to use up all t minutes, he must 
 * minimise the leftover time (which he spends drinking beer).
 *
 * Therefore, when comparing two possible outcomes:
 *   - The one with LESS leftover time (beer time) is always preferred.
 *   - If both have the same leftover time, the one with MORE burgers is preferred.
 *
 * This subtle comparison rule must be encoded in the comparison operator used 
 * during dynamic programming or recursive selection.
 *
 * This is a common pitfall: even if your state transitions and recursion/memoisation are correct,
 * using the wrong comparison can yield incorrect results — especially in corner cases.
 *
 * Correct Comparison Logic:
 *     - Prefer smaller beer_time (leftover time)
 *     - If equal, prefer greater burgers
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <sstream>


struct Ans
{
    int burgers;
    int beer_time;
};


bool operator < (const Ans& lhs, const Ans& rhs) 
{
    // Case 1: One of the answers avoids beer
    if (lhs.beer_time == 0 && rhs.beer_time != 0) return false; // lhs preferred
    if (lhs.beer_time != 0 && rhs.beer_time == 0) return true;  // rhs preferred

    // Case 2: Both drink beer or both avoid it
    // // less beer is better
    return lhs.beer_time > rhs.beer_time || (lhs.beer_time == rhs.beer_time && lhs.burgers < rhs.burgers);
}

bool operator == (const Ans& lhs, const Ans& rhs) 
{ return lhs.burgers == rhs.burgers && lhs.beer_time == rhs.beer_time; }

std::ostream& operator << 
  (std::ostream& out, const Ans& ans) 
  { return out << "{" << ans.burgers << ", " << ans.beer_time << "}"; }


Ans def = {0, 0};

typedef std::vector<Ans> v_ans;


namespace algorithms::onlinejudge::dp::homer
{
    /** https://onlinejudge.org/external/104/10465.pdf */
    int m, n, t;
    // f(t) = 1 + min(f(t + m), f(t + n))
    Ans eat_burgers(int curr_t, v_ans& memo)
    {
        if(curr_t == t) return def;
    
        if(memo[curr_t] != def) return memo[curr_t];

        Ans best = def;
        best.beer_time = std::abs(t - curr_t);
        if(curr_t + m <= t) {
          Ans ans = eat_burgers(curr_t + m, memo);
          ans.burgers++;
          best = std::max(best, ans);
        }

        if(curr_t + n <= t) {
          Ans ans = eat_burgers(curr_t + n, memo);
          ans.burgers++;
          best = std::max(best, ans);
        }

        return memo[curr_t] = best;
    }
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
        
        while(while_read(m, n, t))
        {
            v_ans memo(t + 1, def);
            Ans ans = eat_burgers(0, memo);
            ans.beer_time > 0 ? printf("%d %d\n", ans.burgers, ans.beer_time) : printf("%d\n", ans.burgers);
        }
    }
}