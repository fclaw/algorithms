/*
───────────────────────────────────────────────────────────────
🧳 1211 Atomic Car Race, https://onlinejudge.org/external/12/1211.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;
using vd = std::vector<double>;
using vvd = std::vector<vd>;

constexpr double MAX = std::numeric_limits<double>::max();


vd precompute_costs(int max_dist, int r, double v, double e, double f) {
  vd cost(max_dist + 1);
  cost[0] = 0.0;
  for (int L = 1; L <= max_dist; ++L) {
    int x = L - 1; // Segment from x to x + 1
    double t_1km = 0.0;

    if (x < r) {
      t_1km = 1.0 / (v - f * (r - x)); // Warming up
    } else {
      t_1km = 1.0 / (v - e * (x - r)); // Wearing out
    }
    cost[L] = cost[L - 1] + t_1km; // Accumulate the sum!
  }
  return cost;
}


double memo[105];

double dp(int curr_checkpoint, const vvd& time, double change_cost, int N) {

  // Check memo:
  if (memo[curr_checkpoint] >= 0.0) {
    return memo[curr_checkpoint];
  }

  // Default option: Drive directly from here to the finish line (N - 1)
  double best = time[curr_checkpoint][N - 1];

  // Try making the NEXT pit stop at any intermediate checkpoint:
  for(int next_checkpoint = curr_checkpoint + 1; next_checkpoint < N - 1; ++next_checkpoint) {
     double cost_to_next = time[curr_checkpoint][next_checkpoint] + change_cost;
     double best_remaining = dp(next_checkpoint, time, change_cost, N);
     best = std::min(best, cost_to_next + best_remaining);
  }
  return (memo[curr_checkpoint] = best);
}


double get_min_elapsed_time(const vi& checkpoints, double b, double r, double v, double e, double f) {
  int N = (int)checkpoints.size();
  vd cost = precompute_costs(checkpoints.back(), r, v, e, f);
  vvd time(N + 1, vd(N + 1, 0));
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      int dist = checkpoints[j] - checkpoints[i];
      // Exact sum in O(1)!
      time[i][j] = cost[dist];
    }
  }

  return dp(0, time, b, N);
}


namespace algorithms::onlinejudge::advanced_topics::atomic_car_race
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

        int N;
        while(std::cin >> N && N) {
          std::fill(memo, memo + N, -1.0);
          vi checkpoints(N);
          for(int i = 0; i < N; ++i) {
            std::cin >> checkpoints[i];
          }
          checkpoints.insert(checkpoints.begin(), 0);
          double b, r, v, e, f;
          std::cin >> b >> r >> v >> e >> f;
          std::cout << std::fixed << std::setprecision(4) << get_min_elapsed_time(checkpoints, b, r, v, e, f) << std::endl;
        }
    }
}
