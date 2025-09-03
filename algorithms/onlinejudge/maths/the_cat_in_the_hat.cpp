/*
───────────────────────────────────────────────────────────────
🧳 UVa 00107 The Cat in the Hat, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 *
 * --- Analysis: Deconstructing the Problem with a Tree Model ---
 *
 * The whimsical "Cat in the Hat" story describes a recursive, hierarchical structure
 * that can be perfectly modeled as a full, rooted N-ary tree. The key to solving
 * the problem is to translate the story's elements into tree properties and then
 * solve for the tree's unknown parameters.
 *
 * As outlined in the initial sketch, the problem boils down to solving a system of
 * two equations with two unknowns.
 *
 *
 * ### Step 1: Translate Story Elements to Tree Terminology ###
 *
 *   - "Initial cat": The ROOT of the tree.
 *   - "Cats with hats": The INTERNAL NODES of the tree.
 *   - "Cats without hats" (workers): The LEAF NODES of the tree.
 *   - `N` (cats inside a hat): The BRANCHING FACTOR. Every internal node has N children.
 *   - `H` (initial cat height): The height attribute of the root node.
 *   - `W` (worker cats): The total number of leaf nodes.
 *
 *
 * ### Step 2: Formulate the First Equation (Based on Cat Counts) ###
 *
 * The structure is a full N-ary tree. Let `d` be the depth of the tree, where the
 * root is at depth 0 and the leaves are at depth `d`.
 *
 *   - The number of nodes at depth `i` is `N^i`.
 *   - The leaves are all at depth `d`. Therefore, the number of worker cats `W` is
 *     equal to the number of nodes at depth `d`.
 *
 *   >> Equation 1:  W = N^d
 *
 *
 * ### Step 3: Formulate the Second Equation (Based on Cat Heights) ###
 *
 * The height of a child cat is `1/(N+1)` times the height of its parent.
 *
 *   - Height at depth 0 (root): `H`
 *   - Height at depth 1: `H / (N+1)`
 *   - Height at depth `i`: `H / (N+1)^i`
 *
 * The smallest cats (leaves) are at depth `d` and have a height of 1.
 *   `Height at depth d = H / (N+1)^d = 1`
 *
 * Rearranging this gives our second key equation:
 *
 *   >> Equation 2:  H = (N+1)^d
 *
 *
 * ### Step 4: Solving the System of Equations ###
 *
 * As the sketch correctly concludes, we are given `H` and `W`, and we need to find
 * the two integer unknowns, `N` and `d`. A direct algebraic solution is complex, but
 * a simple search is very efficient.
 *
 * We can iterate on the depth `d` (from 1 upwards). For each `d`, we can calculate a
 * candidate `N` from one equation and verify it with the other.
 *
 * From Equation 1: `N = W^(1/d)`
 * From Equation 2: `N+1 = H^(1/d)`
 *
 * The algorithm is to find a `d` for which `round(W^(1/d)) + 1` is equal to
 * `round(H^(1/d))`. This `d` and the corresponding `N` define the tree's structure.
 *
 *
 * ### Step 5: Calculating the Final Answers ###
 *
 * Once `N` and `d` are known, we can calculate the two required outputs.
 *
 *   1. Number of Non-Working Cats (Internal Nodes):
 *      This is the sum of nodes at depths 0 to d-1: `N^0 + N^1 + ... + N^(d-1)`.
 *      This is a geometric series which sums to `(N^d - 1) / (N - 1)`. Since `W = N^d`,
 *      the formula is simply `(W - 1) / (N - 1)`.
 *
 *   2. Total Height of All Cats (Sum of all node heights):
 *      Sum = ∑_{i=0 to d} [ (Nodes at depth i) * (Height at depth i) ]
 *      Sum = ∑_{i=0 to d} [ N^i * (H / (N+1)^i) ] = H * ∑ [ N/(N+1) ]^i
 *      This geometric series simplifies to the elegant formula `(N+1) * H - N * W`.
 * ====================================================================================
*/

#include "../debug.h"
#include <bits/stdc++.h>



constexpr int MAX_D = 65; // max depth, since 2^30 > 10^9
using ll = long long;


namespace algorithms::onlinejudge::maths::the_cat_in_the_hat
{
    /** https://onlinejudge.org/external/1/107.pdf */
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

        int H, W;
        while(scanf("%d %d", &H, &W) == 2 && H != 0 && W != 0) {
          
          // branching factor
          int branch_f = 0;
          int depth = 0;
          
          // Handle the special case W=1 separately, as it can cause issues.
          if (W == 1) {
            // If W=1, then N must be 1. We just need to find d.
            // H = (1+1)^d = 2^d
            // d = log2(H)
            branch_f = 1;
            depth = static_cast<int>(round(log2(H)));

            // It's still a good idea to verify.
            if(std::pow(2, depth) != H) {
              // This case should not happen with valid inputs.
              // Handle error if needed.
            }

          } else {
            // Your original loop for N > 1 cases.
            for(int d = MAX_D; d >= 1; --d) { // Looping downwards can be faster
                                               // if small N, large d is common.
              ll n_w = static_cast<ll>(std::round(std::pow(W, 1.0 / d)));
              ll n_h = static_cast<ll>(std::round(std::pow(H, 1.0 / d))) - 1;

              // Initial check - must be positive and must match.
              if(n_w > 0 && n_w == n_h) {
                // --- ROBUST VERIFICATION STEP ---
                // Use integer exponentiation to confirm the candidate is exact.
                if(std::pow(n_w, d) == W && std::pow(n_w + 1, d) == H) {
                  branch_f = n_w;
                  depth = d;
                  break; // Found the unique, exact solution.
                }
              }
            }
          }

          // number of non-working cats
          int non_working = branch_f > 1 ? (W - 1) / (branch_f - 1) : (int)std::log2(H);
          // total height of all cats
          // (N+1)^(d+1) - N^(d+1) after simplification
          // = (N + 1) * H - N * W for (N + 1) ^ d = H and N ^ d = W
          int total_height = (branch_f + 1) * H - branch_f * W;
          printf("%d %d\n", non_working, total_height);
        }
    }
}