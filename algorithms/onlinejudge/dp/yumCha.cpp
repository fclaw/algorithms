/*
───────────────────────────────────────────────────────────────
🧳 UVa 11566 Let’s Yum Cha!, rt: s
───────────────────────────────────────────────────────────────

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





struct DimSum
{
    int price;
    int favour_idx;
};


std::ostream& operator << 
  (std::ostream& out, const DimSum& dimSum) 
  { return out << "{" << dimSum.price << ", " << dimSum.favour_idx << "}"; }


typedef std::vector<DimSum> v_dimSum;
typedef std::vector<int> vi;

struct Ans 
{
    int favour_index_sum;  // Total favour index of selected dim sums
};


typedef std::vector<Ans> v_ans;
typedef std::vector<v_ans> vv_ans;
typedef std::vector<vv_ans> vvv_ans;

std::ostream& operator << 
  (std::ostream& out, const Ans& ans) 
  { return out << "{" << ans.favour_index_sum << "}"; }

Ans def = {0};

bool operator < (const Ans& lhs, const Ans& rhs) 
{ return lhs.favour_index_sum < rhs.favour_index_sum; }


bool operator != (const Ans& lhs, const Ans& rhs) 
{ return !(lhs.favour_index_sum == rhs.favour_index_sum); }


namespace algorithms::onlinejudge::dp::yum_cha
{
    /** https://onlinejudge.org/external/115/11566.pdf */
    int friends, budget, tea, k;
    const int max_tries = 2;
    const int extra = 500;
    double full_cost(int dumSums_cost) 
    {
        double base = tea * (friends + 1) + dumSums_cost;
        return base + base / 10.0;
    }
    Ans knapsack(const v_dimSum& dimSums, int i, int rem_dishes, int money_spent, vvv_ans& memo)
    {
        if(i == k || rem_dishes == 0) 
          return def;
        
        Ans& best = memo[i][rem_dishes][money_spent];
        if(best != def) return best;  

        Ans try_dish = def;
        best = knapsack(dimSums, i + 1, rem_dishes, money_spent, memo);
        for(int t = 1; t <= std::min(rem_dishes, max_tries); ++t) {
          int new_money_spent = money_spent + t * dimSums[i].price;
          double curr_full_cost = full_cost(new_money_spent);
          if(curr_full_cost <= budget * (friends + 1) + 1e-9) {
            try_dish = knapsack(dimSums, i + 1, rem_dishes - t, new_money_spent, memo);
            try_dish.favour_index_sum += (t * dimSums[i].favour_idx);
            best = std::max(try_dish, best);
          }
        }
        return best;
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
        
        while(while_read(friends, budget, tea, k) && friends)
        {
            v_dimSum dimSums(k);
            int sum_of_prices = 0;
            loop(k, [&dimSums, &sum_of_prices](int i){
              int p, idx, total_idx = 0;
              while_read(p);
              sum_of_prices += p;
              for(int j = 0; j <= friends; ++j) {
                std::cin >> idx;
                total_idx += idx;
              }
              dimSums[i] = {p, total_idx};
            });

            vv_ans dp(2 * (friends + 1) + 1, v_ans(sum_of_prices + extra, def));
            for(auto& d : dimSums)
              for(int c = 2 * (friends + 1); c >= 0; --c)
                for(int p = sum_of_prices + extra - 1; p >= 0; --p)
                  for(int t = 1; t <= 2; ++t) {
                    int nc = c + t;
                    int np = p + t * d.price;
                    if (nc <= 2 * (friends + 1) && np < sum_of_prices + extra) {
                      Ans from = dp[c][p];
                      double curr_full_cost = full_cost(np); // try adding a dish
                      if(curr_full_cost <= budget * (friends + 1) + 1e-9) {
                        Ans new_ans = from;
                        new_ans.favour_index_sum += t * d.favour_idx;
                        dp[nc][np] = std::max(dp[nc][np], new_ans);
                      }
                    }
                }

            int best = 0;
            for(int p = 0; p < sum_of_prices + extra; ++p)
              if(p <= budget * (friends + 1))
                best = std::max(best, dp[c][p].favour_index_sum);
            std::cout << std::setprecision(2) << std::fixed << ((double) best) / (friends + 1) << std::endl;
        }
    }
}