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




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Site
{
    // National Construction and Project Centre (NCPC)
    vi costs_n;
    // Bureau of Civil Engineering Works (BCEW)
    vi costs_b;
    // actual number of rods at this site
    int size;
};

typedef std::vector<Site> v_site;

struct Ans
{
    int min_cost;
    vi samples;
};

bool operator < (const Ans& lhs, const Ans& rhs) 
{ return lhs.min_cost < rhs.min_cost; }

bool operator == (const Ans& lhs, const Ans& rhs) 
{ return lhs.min_cost == rhs.min_cost; }

typedef std::vector<Ans> v_ans;
typedef std::vector<v_ans> vv_ans;
typedef std::vector<vv_ans> vvv_ans;

Ans def = {0, {}};


namespace algorithms::onlinejudge::dp::rods
{
    /** https://onlinejudge.org/external/100/10086.pdf */
    int rods_n, rods_b, n;
    Ans min_cost(const v_site& sites, int i, int rem_n, int rem_b, vvv_ans& memo)
    {
        if(rem_n < 0 || rem_b < 0) {
          Ans err = def;
          err.min_cost = INT32_MAX;
          return err;
        }
        if(i == n) return def;

        if(!(memo[i][rem_n][rem_b] == def)) 
          return memo[i][rem_n][rem_b];

        Ans best = def;
        best.min_cost = INT32_MAX;
        int s = sites[i].size;
        for(int c = 0; c <= s; ++c) {
          int new_rem_n = rem_n - c;
          int new_rem_b = rem_b - (s - c);
          Ans candidate = min_cost(sites, i + 1, new_rem_n, new_rem_b, memo);
          if(candidate.min_cost == INT32_MAX) continue;
          candidate.samples.push_back(c);
          candidate.min_cost += (sites[i].costs_n[c] + sites[i].costs_b[s - c]);
          best = std::min(best, candidate);
        }
        return memo[i][rem_n][rem_b] = best;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        while(while_read(rods_n, rods_b) && 
              (rods_n || rods_b))
        {
            while_read(n);
            v_site sites(n);
            loop(n, [&sites](int i) {
              int k;
              while_read(k);
              vi ncpc(k + 1), bcew(k + 1);
              loop(k, [&ncpc](int i) 
              { while_read(ncpc[i + 1]); });
              loop(k, [&bcew](int i) 
              { while_read(bcew[i + 1]); });
              sites[i] = {ncpc, bcew, k};
            });

            vvv_ans dp(n + 1, vv_ans(rods_n + 1, v_ans(rods_b + 1, {INT32_MAX, {}})));

            dp[0][0][0] = def;

            for(int i = 0; i < n; ++i)
              for(int rem_n = 0; rem_n <= rods_n; ++rem_n)
                for(int rem_b = 0; rem_b <= rods_b; ++rem_b)
                  if(dp[i][rem_n][rem_b].min_cost != INT32_MAX) {
                    int s = sites[i].size;
                    for(int c = 0; c <= s; ++c) {
                      int new_rem_n = rem_n + c;
                      int new_rem_b = rem_b + (s - c);
                      if(new_rem_n <= rods_n && new_rem_b <= rods_b) {
                        Ans ans = dp[i][rem_n][rem_b];
                        ans.samples.push_back(c);
                        ans.min_cost += sites[i].costs_n[c] + sites[i].costs_b[s - c];
                        dp[i + 1][new_rem_n][new_rem_b] = std::min(dp[i + 1][new_rem_n][new_rem_b], ans);
                      }
                    }
                  }

            Ans ans = dp[n][rods_n][rods_b];
            std::string s;
            for(int n : ans.samples)
              s += std::to_string(n) + " ";
            s.pop_back();
            printf("%d\n%s\n\n", ans.min_cost, s.c_str());  
        }
    }
}