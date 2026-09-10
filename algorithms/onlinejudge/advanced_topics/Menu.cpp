/*
───────────────────────────────────────────────────────────────
🧳 10645 Menu, https://onlinejudge.org/external/106/10645.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


// 22 elements (Index 0..21)
// Index 1 = 1.0, Index 2 = 0.5, Index 3..21 = 0.0
constexpr double BENEFIT_FACTOR[22] = {
    0.0, 1.0, 0.5, // 0, 1, 2
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, // 3..10
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 // 11..21
};


/**
 * Represents the evaluation outcome of a chosen menu plan.
 */
struct State
{
    /**
     * 1. benefit (Primary Metric to MAXIMIZE)
     * ---------------------------------------
     * The total accumulated satisfaction value from all k days.
     * Note: Must be `double` because repeating a dish gives 50% benefit (e.g., 7.5).
     */
    double benefit;

    /**
     * 2. cost (Secondary Metric to MINIMIZE)
     * --------------------------------------
     * Total money spent on ingredients over the k days.
     * Constraint: cost <= budget (m).
     * Tie-breaker: If two menus yield the same benefit, pick the CHEAPER one!
     */
    int cost;

    /**
     * 3. dishes (Ordered Menu Sequence)
     * ---------------------------------
     * The sequence of 1-based dish IDs chosen for day 1, day 2, ..., day k.
     * Length must be exactly k days.
     */
    vi dishes;

    /**
     * Strict Weak Ordering (<) for std::max(a, b):
     * --------------------------------------------
     * std::max(a, b) picks 'b' whenever (a < b) evaluates to true:
     * 
     * 1. Primary     : MAXIMIZE benefit (a.benefit < b.benefit)
     * 2. Tie-Breaker : MINIMIZE cost    (a.cost > b.cost)
     */
    bool operator < (const State& o) const {
      if(benefit != o.benefit) {
        return benefit < o.benefit; // Higher benefit is better!
      }
      return cost > o.cost; // Lower cost is better!
    }
};

State def = {0.0, 0, {}};


struct Dish 
{
    int idx;
    int cost;
    double value;
};

using v_state = std::vector<State>;
using vv_state = std::vector<v_state>;
using vvv_state = std::vector<vv_state>;
using vvvv_state = std::vector<vvv_state>;


State get_max_benefit(int days, int budget, int i, int curr_dish_streak, const std::vector<Dish>& dishes, vvvv_state& cache) {

    // base case: all days passed
  if(days == 0) {
    return (cache[days][budget][i][curr_dish_streak] = def);
  }

  if(~cache[days][budget][i][curr_dish_streak].cost) {
    return cache[days][budget][i][curr_dish_streak];
  }

  State best = def;

  // go on with the current dish
  if(budget >= dishes[i].cost) {
    State stay_i = get_max_benefit(days - 1, budget - dishes[i].cost, i, curr_dish_streak + 1, dishes, cache);
    double multiplier = BENEFIT_FACTOR[curr_dish_streak + 1];
    stay_i.benefit += dishes[i].value * multiplier;
    stay_i.cost += dishes[i].cost;
    stay_i.dishes.push_back(dishes[i].idx);
    best = std::max(best, stay_i);
  }

  // chose another one
  for(int j = 0; j < (int)dishes.size(); ++j) {
    if(i != j && budget >= dishes[j].cost) {
      State chose_j = get_max_benefit(days - 1, budget - dishes[j].cost, j, 1, dishes, cache);
      chose_j.benefit += dishes[j].value * BENEFIT_FACTOR[1];
      chose_j.cost += dishes[j].cost;
      chose_j.dishes.push_back(dishes[j].idx);
      best = std::max(best, chose_j);
    }
  }

  // check whether we have a dish per day
  if((int)best.dishes.size() != days) {
    best = def;
  }

  return (cache[days][budget][i][curr_dish_streak] = best);
}


namespace algorithms::onlinejudge::advanced_topics::menu
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

        int days, N, budget;
        bool is_first = true;
        while(std::cin >> days >> N >> budget && 
              (days && N && budget)) {

          if(!is_first) std::cout << "\n";
          is_first = false;
                
          std::vector<Dish> dishes(N);
          for(int i = 0; i < N; ++i) {
            Dish dish;
            dish.idx = i + 1;
            std::cin >> dish.cost >> dish.value;
            dishes[i] = dish;
          }

          vvvv_state cache(days + 1, vvv_state(budget + 1, vv_state(N + 1, v_state(days + 1, {0.0, -1, {}}))));
          State state = get_max_benefit(days, budget, 0, 0, dishes, cache);
          std::string preferable_dishes = "\n";
          for(int i : state.dishes) {
            preferable_dishes += std::to_string(i) + " ";
          }
          if(!preferable_dishes.empty()) {
              preferable_dishes.pop_back();
          }
          std::cout << std::fixed << std::setprecision(1) << state.benefit << preferable_dishes << std::endl;
        }
    }
}
