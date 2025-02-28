h#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>



namespace algorithms::onlinejudge::complete_search::y2k
{
    /** https://onlinejudge.org/external/105/10576.pdf, 
     * generate all, prune, take max
     * Given:
     * - A company earns 'S' units of money in a profitable month.
     * - A company loses 'D' units of money in a deficit month.
     * - We need to decide the sequence of 12 months (either profit or deficit) 
     * to maximize the total sum while ensuring that **every** 5-month consecutive 
     * period has a strictly positive sum.
     * Constraints:
     * - Each month can have either +S (profit) or -D (deficit).
     * - Any **five consecutive months** must have a sum > 0.
     * - If a valid sequence exists, print the **maximum total sum** across 12 months.
     * - Otherwise, print `"Deficit"`.
     * Approach:
     * 1. Use **backtracking** or **bitmasking** to try all possible assignments of profit/deficit.
     * 2. For each configuration, check if every five-month window satisfies the constraint.
     * 3. Keep track of the maximum total sum over 12 months.
     * Observations:
     * - If S is too small compared to D, a deficit is unavoidable.
     * - The problem can be solved optimally using exhaustive search due to small constraints (2^12 possibilities).
     * */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
    }
}