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


ld calculate_win_probability(int l, int r, int team_id, const vvd& prob_matrix) {
  int num_teams = r - l;

  // --- Base Case ---
  // If there is only one team in the bracket, its probability of winning is 100%.
  if(num_teams == 1) return 1.0;

  int m = (l + r) / 2;

  int opp_half_start_idx;
  int opp_half_end_idx;
  int our_half_start_idx;
  int our_half_end_idx;

  // Is our team in the first or second half of this bracket?
  if(team_id < m) {
    // We are in the first half
    opp_half_start_idx = m;
    opp_half_end_idx = r;
    our_half_start_idx = l;
    our_half_end_idx = m;
  } else {
    // We are in the second half
    opp_half_start_idx = l;
    opp_half_end_idx = m;
    our_half_start_idx = m;
    our_half_end_idx = r;
  }

  // --- Recursive Step ---

  // 1. Get the probability of our team (team_id) reaching this round.
  // This is the "first_p" from your insight.
  ld prob_reach_this_round = calculate_win_probability(our_half_start_idx, our_half_end_idx, team_id, prob_matrix);


  // 2. Calculate the probability of winning the match in this round.
  // This is the "second_p" (the summation) from your insight.
  ld prob_win_match_in_round = 0.0;


  // Sum over all potential opponents in the other half of the bracket.
  for(int opp_id = opp_half_start_idx; opp_id < opp_half_end_idx; ++opp_id) {
    // Prob that this specific opponent wins their half to reach the match against us.
    ld prob_opp_reaches = calculate_win_probability(opp_half_start_idx, opp_half_end_idx, opp_id, prob_matrix);
    
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
        for(int i = 0; i < N; ++i) {
          win_prob[i] = 100.0 * calculate_win_probability(0, 16, i, prob_matrix);
        }

        for(int i = 0; i < N; ++i) {
          printf("%-11sp=%.2Lf%%\n", teams[i].c_str(), win_prob[i]);
        }
    }
}