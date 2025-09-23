/*
───────────────────────────────────────────────────────────────
🧳 UVa 10489 Boxes of Chocolates, keep values small with modulo, rt: s
───────────────────────────────────────────────────────────────
 * LOGIC EXPLANATION: The "Inside-Out" Unboxing Method
 * ---------------------------------------------------
 * The problem describes nested boxes of chocolates. An input line like:
 *
 *   3 2 3 4
 *
 * can be confusing. The first number (K=3) just tells us to multiply the next 3 numbers.
 * The core numbers are `2`, `3`, and `4`.
 *
 * A very intuitive way to calculate the total is to think like we're unboxing in reverse,
 * starting from the actual chocolates and working our way out:
 *
 * 1.  Start with the prize: The LAST number (4) is the number of chocolates
 *     in each of the smallest boxes.
 *     >> We have 4 chocolates.
 *
 * 2.  Move left to the next layer: The number before it (3) tells us how many
 *     of those smallest boxes are in the next bigger box.
 *     >> Total = 4 chocolates * 3 boxes = 12 chocolates.
 *
 * 3.  Move left to the outermost layer: The number before that (2) tells us how many
 *     of THOSE boxes are in the largest container for this line.
 *     >> Grand Total = 12 chocolates * 2 boxes = 24 chocolates.
 *
 * This confirms our calculation is simply the product: 4 * 3 * 2 = 24.
 * The program implements this by multiplying all numbers after K, using the
 * modulo operator at each step to prevent integer overflow.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;
using v_ll = std::vector<ll>;
using vv_ll = std::vector<v_ll>;


namespace algorithms::onlinejudge::maths::boxes_of_chocolates
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
       
       int t_cases;
       scanf("%d", &t_cases);
       while(t_cases--) {
         int friends, n_boxes;
         scanf("%d %d", &friends, &n_boxes);
         vv_ll outer_boxes(n_boxes);
         for(int i = 0; i < n_boxes; ++i) {
           int n;
           scanf("%d", &n);
           v_ll inner_box(n);
           for(int j = 0; j < n; ++j)
             scanf("%lld", &inner_box[j]);
           outer_boxes[i] = inner_box; 
         }
         ll leftover = 0;
         ll MOD = friends;
         for(size_t i = 0; i < outer_boxes.size(); ++i) {
           ll box_leftover = 1;
           v_ll box = outer_boxes[i];
           size_t size = box.size();
           for(size_t j = 0; j < size; ++j)
            box_leftover = ((box_leftover % MOD) * (box[j] % MOD)) % MOD;
           leftover = ((leftover % MOD) + (box_leftover % MOD)) % MOD;
         }
         printf("%lld\n", leftover);
       } 
    }
}