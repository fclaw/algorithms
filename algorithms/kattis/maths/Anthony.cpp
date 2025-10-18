/*
───────────────────────────────────────────────────────────────
🧳  Anthony and Cora, https://open.kattis.com/problems/anthony, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ld = long double;
using vd = std::vector<ld>;

constexpr int MAX = 1000;

// std::unordered_map<std::pair<int, int>, ld> memo;
ld memo[MAX + 1][MAX + 1];
bool is_init[MAX + 1][MAX + 1];

int INITIAL_N;
int INITIAL_M;

ld calculate_p_b(int Anthony_points, int Cora_points, const vd& rounds_prob) {
  if(Anthony_points == 0 || 
     Cora_points == 0)
    return Anthony_points > 0 ? 1.0 : 0.0;
      
  if(is_init[Anthony_points][Cora_points]) {
    return memo[Anthony_points][Cora_points];
  }

  is_init[Anthony_points][Cora_points] = true;

  // Recover the round number from the other two parameters!
  int rounds_played = (INITIAL_N - Anthony_points) + (INITIAL_M - Cora_points);

  ld anthony_wins_point = rounds_prob[rounds_played] * calculate_p_b(Anthony_points, Cora_points - 1, rounds_prob);
  ld cora_wins_point = (1.0 - rounds_prob[rounds_played]) * calculate_p_b(Anthony_points - 1, Cora_points, rounds_prob);
  return memo[Anthony_points][Cora_points] = anthony_wins_point + cora_wins_point;
}


namespace algorithms::kattis::maths::Anthony_and_Cora
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

       int Anthony_points, Cora_points, rounds;
       while(scanf("%d %d", &Anthony_points, &Cora_points) == 2) {
         rounds = Anthony_points + Cora_points - 1;
         vd rounds_prob(rounds);
         for(int i = 0; i < rounds; ++i)
           scanf("%Lf", &rounds_prob[i]);
         INITIAL_N = Anthony_points;
         INITIAL_M = Cora_points;
         std::memset(memo, -1.0, sizeof(memo));
         std::memset(is_init, false, sizeof(is_init));  
         printf("%.6Lf\n", calculate_p_b(Anthony_points, Cora_points, rounds_prob));
       }
    }
}