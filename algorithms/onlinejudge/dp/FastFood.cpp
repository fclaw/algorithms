/*
───────────────────────────────────────────────────────────────
🧳 UVa 662 Fast Food, https://onlinejudge.org/external/6/662.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



const int MAX = (int)1e9;

int N, K;

using vi = std::vector<int>;

struct Depot
{
    int idx;
    int restaurant_id;
    int from;
    int to;
};

using v_depots = std::vector<Depot>;

struct Ans
{
    int dist;
    bool operator < (const Ans& other) const {
      return dist < other.dist;
    }

     // In-place addition
    Ans& operator += (const Ans& other) {
      this->dist += other.dist;
      return *this;
    }

    // Binary addition defined in terms of operator+=
    // Passing the first argument by value allows the compiler to optimize copies
    friend Ans operator + (Ans lhs, const Ans& rhs) { lhs += rhs; return lhs; }
};


Ans cache[201][201][31];


Ans minimize_sum(const vi& restaurants, int left, int right, int depots_left) {
  
   if(left >= right) {
     return (cache[left][right][depots_left] = {depots_left == 0 ? 0 : MAX});
   }

  if(~cache[left][right][depots_left].dist) {
    return cache[left][right][depots_left];
  }

   Ans ans = {MAX};
   for(int p = left; p < right; ++p) {
     int d = restaurants[p];
     for(int l = p; l >= left; --l) {
       for(int r = p; r < right; ++r) {
         int remaining_elements = (l - left) + (right - (r + 1));
         int remaining_depots = depots_left - 1;
         if (remaining_elements < remaining_depots) {
           continue;
         }
         int sum = 0;
         // prefix sum
          for(int i = l; i <= r; ++i) {
           sum += std::abs(restaurants[i] - d);
          }
         Ans curr_ans = {sum};
         for(int d = 0; d < depots_left; ++d) {
          int right_depots = depots_left - d - 1;
          if(l - left > d && right - r - 1 > right_depots) {
            continue;
           }
           Ans left_ans = minimize_sum(restaurants, left, l, d);
           Ans right_ans = minimize_sum(restaurants, r + 1, right, right_depots);
           Ans total = curr_ans + left_ans + right_ans;
           ans = std::min(ans, total);
         }
       }
     }
   }
   return (cache[left][right][depots_left] = ans);
}

void reconstruct_path(const vi& restaurants, int left, int right, int depots_left, v_depots& out_depots) {
  if (left >= right) {
    return;
  }

  int best_dist = cache[left][right][depots_left].dist;

  // Search the choices for the one that produced best_dist
  for(int p = left; p < right; ++p) {
    int d = restaurants[p];
    int idx = K - depots_left;
    for(int l = p; l >= left; --l) {
      for(int r = p; r < right; ++r) {
                
        int sum = 0;
        for(int i = l; i <= r; ++i) {
          sum += std::abs(restaurants[i] - d);
        }

        for (int d = 0; d < depots_left; ++d) {
          int right_depots = depots_left - d - 1;

          // Base case lookups
          int left_val = cache[left][l][d].dist;
          int right_val = cache[r + 1][right][right_depots].dist;

          if(sum + left_val + right_val == best_dist) {
            // Found the matching choice!
            out_depots.push_back({idx, p, l, r});
            // Recurse to solve left and right segments
            reconstruct_path(restaurants, left, l, d, out_depots);
            reconstruct_path(restaurants, r + 1, right, right_depots, out_depots);
            return; // Successfully reconstructed this branch
          }
        }
      }
    }
  }
}


namespace algorithms::onlinejudge::dp::fast_food
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

        int t_cases = 1;
        while(std::cin >> N >> K && N && K) {
          vi restaurants(N);
          for(int i = 0; i < N; ++i) {
            scanf("%d", &restaurants[i]);
          }

          for(int i = 0; i <= 200; ++i) {
            for(int j = 0; j <= 200; ++j) {
              for(int k = 0; k <= 30; ++k) {
                cache[i][j][k] = {-1};
              }
            }
          }

          Ans ans = minimize_sum(restaurants, 0, N, K);
          v_depots depots;
          reconstruct_path(restaurants, 0, N, K, depots);
          printf("Chain %d\n", t_cases++);
          for(auto& depot : depots) {
            int idx = depot.idx + 1;
            int r = depot.restaurant_id + 1;
            int from = depot.from + 1;
            int to = depot.to + 1;
            std::string served = 
              "restaurant " + 
              std::to_string(from);
            if(from < to) {
              served = 
                "restaurants " + 
                std::to_string(from) + 
                " to " + 
                std::to_string(to);
            }
            printf("Depot %d at restaurant %d serves %s\n", idx, r, served.c_str());
          }
          printf("Total distance sum = %d\n\n", ans.dist);
        }
    }
}