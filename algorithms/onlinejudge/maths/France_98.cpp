/*
───────────────────────────────────────────────────────────────
🧳  UVa 542 France’98, https://onlinejudge.org/external/5/542.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ld = long double;
using vd = std::vector<ld>;
using vvd = std::vector<vd>;


constexpr int N = 16;


ld calculate_win_probability(int round, int team_id, const vvd& prob_matrix) {
  // base case
  if(round == 0) {
    return 1.0;
  }

  // --- Recursive Step ---
  // To win round 'round', a team must have won round 'round-1' AND win its match in this round.

  // 1. Get the probability of our team (team_id) reaching this round.
  // This is the "first_p" from your insight.
  ld prob_reach_this_round = calculate_win_probability(round - 1, team_id, prob_matrix);


  // 2. Calculate the probability of winning the match in this round.
  // This is the "second_p" (the summation) from your insight.
  ld prob_win_match_in_round = 0.0;

  // --- Determine the range of opponents for team_id in this round ---
  // This is the trickiest part.
  int teams_in_group = 1 << round;         // Size of the bracket at this round (2, 4, 8, 16)

  int group_start_idx = (team_id / teams_in_group) * teams_in_group;

  int opp_half_start_idx;
  int half_size = teams_in_group / 2;

  // Is our team in the first or second half of this bracket?
  if((team_id - group_start_idx) < half_size) {
    // We are in the first half
    opp_half_start_idx = group_start_idx + half_size;
  } else {
    // We are in the second half
    opp_half_start_idx = group_start_idx;
  }

  // Sum over all potential opponents in the other half of the bracket.
  for(int opp_id = opp_half_start_idx; opp_id < opp_half_start_idx + half_size; ++opp_id) {
    // Prob that this specific opponent wins their half to reach the match against us.
    ld prob_opp_reaches = calculate_win_probability(round - 1, opp_id, prob_matrix);
    
    // Prob that we beat this specific opponent if we meet them.
    ld prob_we_beat_opp = prob_matrix[team_id][opp_id];
    
    prob_win_match_in_round += prob_opp_reaches * prob_we_beat_opp;
  }

  // 3. Final Probability = P(reach round) * P(win match in round)
  // This is the "result = first_p * second_p" from your insight.
  ld final_prob = prob_reach_this_round * prob_win_match_in_round;

  return final_prob;
}


namespace algorithms::onlinejudge::maths::france_98
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

        std::vector<std::string> teams(N);
        for(int i = 0; i < N; ++i) {
          std::cin >> teams[i];
        }

        vvd prob_matrix(N, vd(N));
        for(int i = 0; i < N; ++i) {
          for(int j = 0; j < N; ++j) {
            std::cin >> prob_matrix[i][j];
            prob_matrix[i][j] /= 100.0;
          }
        }

        vd win_prob(N);
        int round = std::ceil(std::log2(N));
        for(int i = 0; i < N; ++i) {
          win_prob[i] = 100.0 * calculate_win_probability(round, i, prob_matrix);
        }


        for(int i = 0; i < N; ++i) {
          printf("%-11sp=%.2Lf%%\n", teams[i].c_str(), win_prob[i]);
        }
    }
}