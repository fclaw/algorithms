/*
───────────────────────────────────────────────────────────────
🧳  UVa 11181 Probability|Given, https://onlinejudge.org/external/111/11181.pdf, rt: s
───────────────────────────────────────────────────────────────
https://en.wikipedia.org/wiki/Conditional_probability: P(A∣B) = P(A ∩ B) / P(B)
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vd = std::vector<double>;
using vvd = std::vector<vd>;


/* Calculates P(B), the total probability that exactly 'who_bought_left' people
 * buy something from the pool of friends starting at 'idx'.
 *
 * This function recursively explores the decision for each friend:
 *  - They buy something (with probability p_i).
 *  - They do not buy something (with probability 1 - p_i).
 * It sums the probabilities of all complete scenarios (paths in the decision tree)
 * where the final count of buyers is exactly the required number. This is our denominator.
*/
double calculate_p_b(int idx, const vd& friends_p, int who_bought_left) {
  if(idx == (int)friends_p.size()) {
     return who_bought_left == 0 ? 1.0 : 0.0;
  }

  // --- Recursive Step ---
  // The total probability is the sum of two mutually exclusive scenarios for friend 'idx'.

  // Scenario 1: Friend 'idx' BUYS something.
  // Probability = P(idx buys) * P(remaining friends fulfill the rest).
  double p_bought = friends_p[idx] * calculate_p_b(idx + 1, friends_p, who_bought_left - 1);
  // Scenario 2: Friend 'idx' does NOT buy something.
  // Probability = P(idx doesn't buy) * P(remaining friends fulfill the rest).
  double p_no_bought = (1.0 - friends_p[idx]) * calculate_p_b(idx + 1, friends_p, who_bought_left);
  return p_bought + p_no_bought;
}



namespace algorithms::onlinejudge::maths::friends_go_shopping
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

        double p;
        int friends, n_who_bought, t_case = 1;
        while(scanf("%d %d", &friends, &n_who_bought) == 2 && friends) {
          vd friends_p = vd(friends);
          for(int f = 0; f < friends; ++f) {
            scanf("%lf", &p);
            friends_p[f] = p;
          }

          // This is P(B) in the formula P(A|B) = P(A ∩ B) / P(B).
          // It represents our new "universe": the total probability that ANY group of
          // 'n_who_bought' friends made a purchase.
          double p_b = calculate_p_b(0, friends_p, n_who_bought);

          // For each friend 'i', calculate P(friend_i_buys | exactly_r_buy).
          // To calculate the numerator P(A ∩ B), we need the probability that
          // "friend 'i' buys AND exactly 'n_who_bought' people in total buy".
          // This can be broken down using the rule P(X and Y) = P(X) * P(Y|X).
          // = P(friend_i_buys) * P(exactly n_who_bought-1 others buy | friend_i_buys)
          // The second term is a recursive call on the remaining N-1 friends.
          vd p_b_a(friends);
          for(int i = 0; i < friends; ++i) {
            vd friends_without_i = friends_p;
            friends_without_i.erase(friends_without_i.begin() + i);
            p_b_a[i] = friends_p[i] * calculate_p_b(0, friends_without_i, n_who_bought - 1);
          }
          
          printf("Case %d:\n", t_case++);
          for(double d : p_b_a) printf("%0.6lf\n", d / p_b);
        }
    }
}