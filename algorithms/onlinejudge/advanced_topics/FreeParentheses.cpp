/*
───────────────────────────────────────────────────────────────
🧳 UVa 1238 Free Parentheses, https://onlinejudge.org/external/12/1238.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * PROBLEM DESCRIPTION:
 * ============================================================================
 * Given an arithmetic expression of addition and subtraction on non-negative 
 * integers, determine the total number of DISTINCT values that can be produced 
 * by freely inserting any valid set of matching parentheses.
 *
 * ============================================================================
 * KEY MATHEMATICAL INSIGHTS:
 * ============================================================================
 * 1. Why Parentheses Only Open After Minus ('-'):
 *    - Opening after '+':  + (a - b)  ==  + a - b  (Signs do not change!)
 *    - Opening after '-':  - (a + b)  ==  - a - b  (Flips '+' to '-')
 *                          - (a - b)  ==  - a + b  (Flips '-' to '+')
 *    Therefore, inserting '(' after a positive operator is strictly redundant 
 *    and produces no new values. We ONLY branch to open a new parenthesis 
 *    when the current operator is negative (`token.is_negative`).
 *
 * 2. Parity of Nested Negations (The Sign Flip Rule):
 *    Every active open parenthesis flips the signs of all operations inside it:
 *    - 0 open parens: Normal signs.
 *    - 1 open paren:  Inverts all signs inside.
 *    - 2 open parens: - ( ... - ( ... ) ) -> Inverts twice -> Normal signs!
 *    Hence, the effective sign multiplier is simply:
 *        sign_multiplier = (open_parentheses % 2 == 0) ? +1 : -1
 *
 * 3. The Negative Index Trap & OFFSET:
 *    Because subtractions can accumulate, `val` can be negative:
 *        Max value: ~30 * 100 =  3000
 *        Min value: ~30 * -100 = -3000
 *    Since C++ array indices cannot be negative, we add an `OFFSET` (e.g., 3000 
 *    or 6000) so that `val + OFFSET >= 0`.
 *
 * ============================================================================
 * DP STATE & TRANSITIONS:
 * ============================================================================
 * State: (idx, open_parentheses, val)
 * - `idx`: Current operand index (0 to N).
 * - `open_parentheses`: Number of unclosed '(' opened by preceding '-' signs.
 * - `val`: Current accumulated mathematical value.
 *
 * Transitions from state (idx, open, val):
 * 1. Do nothing (continue current nesting): (idx + 1, open, nval)
 * 2. Close a parenthesis (if open >= 1):   (idx + 1, open - 1, nval)
 * 3. Open a parenthesis (if token is '-'): (idx + 1, open + 1, nval)
 *
 * Base Case:
 * - When `idx == tokens.size()`:
 *   If `open_parentheses == 0`, all parentheses are matched and syntactically 
 *   valid. We record `val` into our set of unique results.
 *
 * ============================================================================
 * COMPLEXITY:
 * ============================================================================
 * - States: O(N * N * Range(val))
 *           N <= 30 tokens, open <= 30, Range(val) ~ 6000.
 *           30 * 30 * 6000 = ~5.4 x 10^6 total boolean states.
 * - Time Complexity:  O(N^2 * Range(val)) — each state evaluated at most once.
 * - Space Complexity: O(N * N * Range(val)) for the 3D boolean visited table.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



const int MAX_N = 30;
const int MAX_SUM = 3000;
const int OFFSET = 3000;


struct Token
{
    int val;
    bool is_negative;   
};


bool visited[MAX_N + 5][MAX_N + 5][MAX_SUM + OFFSET + 10];


void dp(int idx, int open_parentheses, int val, 
        const std::vector<Token>& tokens, 
        std::unordered_set<int>& values) {

    // Base Case: Reached the end of the expression
    if (idx == (int)tokens.size()) {
        // Valid expression only if all opened parentheses have been closed
        if (open_parentheses == 0) {
            values.insert(val);
        }
        return;
    }

    // Memoization / Visited Check: Avoid re-exploring the same subproblem
    if (visited[idx][open_parentheses][val + OFFSET]) {
        return;
    }
    visited[idx][open_parentheses][val + OFFSET] = true;

    Token token = tokens[idx];

    // Compute effective sign:
    //  Determine if the current nesting scope inverts signs:
    //    - Outside all blocks (open == 0): normal sign (+1)
    //    - Inside an active '-' block (open == 1): inverts sign (-1)
    //    - Nested '-' blocks toggle back and forth (double negation: -(-x) = +x)
    int nesting_sign = (open_parentheses % 2 == 0) ? 1 : -1;
    int op_sign      = token.is_negative ? -1 : 1;
    int nval         = val + (nesting_sign * op_sign * token.val);

    // Transition 1: Close an open parenthesis (if any exist)
    if (open_parentheses >= 1) {
        dp(idx + 1, open_parentheses - 1, nval, tokens, values);
    }

    // Transition 2: Proceed without changing parenthesis count
    dp(idx + 1, open_parentheses, nval, tokens, values);

    // Transition 3: Open a NEW parenthesis.
    // Crucial rule: ONLY valid after a '-' sign! Opening after '+' changes nothing.
    if (token.is_negative) {
        dp(idx + 1, open_parentheses + 1, nval, tokens, values);
    }
}


int count_different_numbers(const std::vector<Token>& tokens) {
  std::memset(visited, false, sizeof visited);
  std::unordered_set<int> values;
  dp(0, 0, 0, tokens, values);
  return values.size();
}


namespace algorithms::onlinejudge::advanced_topics::free_parentheses
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

        std::string expr;
        while(std::getline(std::cin, expr)) {
          expr.insert(expr.begin(), '+');
          std::vector<Token> tokens;
          std::stringstream ss(expr);
          char sign;
          int val;
          Token token;
          while(ss >> sign >> val) {
            if(tokens.empty()) {
              tokens.push_back({val, false});
            } else {
              token.is_negative = (sign == '-');
              token.val = val;
              tokens.push_back(token);
            }
          }
          printf("%d\n", count_different_numbers(tokens));
        }
    }
}