/*
───────────────────────────────────────────────────────────────
🧳 UVa 1240 ICPC Team Strategy, https://onlinejudge.org/external/12/1240.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





constexpr int TIME_LIMIT = 280;
constexpr int TEAM_SIZE = 3;
constexpr int PROBLEMS = 12;
constexpr int SOLVER_MASK = ((1 << TEAM_SIZE) - 1) << PROBLEMS;


// Returns solver_id: 0, 1, 2... (or -1 if no solver assigned)
int get_problem_solver(int mask) {
  int solver_bits = (mask >> PROBLEMS) & ((1 << TEAM_SIZE) - 1);
  if (solver_bits == 0) return -1;
  return __builtin_ctz(solver_bits); // Converts 0b0001 -> 0, 0b0010 -> 1, 0b0100 -> 2
}

// Clears any existing solver and assigns the new solver_id
int set_problem_solver(int mask, int solver_id) {
  // 1. Clear old solver bits in the upper region
  mask &= ~SOLVER_MASK;
  // 2. Set the bit for solver_id
  return mask | (1 << (PROBLEMS + solver_id));
}


void dp(int mask, int time_elapsed, int problems_solved, const vvi& team, int& max_problem_solved, int N, vi& times) {

  if (time_elapsed >= times[mask]) {
    return;
  }

  times[mask] = time_elapsed; // Record the new best time for this state

  int prev_solver = get_problem_solver(mask);
  for(int solver = 0; solver < TEAM_SIZE; ++solver) {
    if(solver != prev_solver) {
      for(int p = 0; p < N; ++p) {
        int bit = 1 << p;
        int new_time_elapsed = time_elapsed + team[solver][p];
        if(!(mask & bit) && new_time_elapsed <= TIME_LIMIT) {
          int new_mask = set_problem_solver(mask, solver);
          dp(new_mask | bit, new_time_elapsed, problems_solved + 1, team, max_problem_solved, N, times);
        }
      }
    }
  }

  max_problem_solved = std::max(max_problem_solved, problems_solved);
}

int get_max_solved_problems(const vvi& team, int N) {
  int max_problem_solved = 0;
  vi times(1 << 15, Inf);
  dp(0, 0, 0, team, max_problem_solved, N, times);
  return max_problem_solved;
}


namespace algorithms::onlinejudge::advanced_topics::ICPC_team_strategy
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
        stdin_read(t_cases);
        while(t_cases--) {
          int n_problems;
          stdin_read(n_problems);
          vvi team(TEAM_SIZE, vi(n_problems));
          for(int i = 0; i < TEAM_SIZE; ++i) {
            for(int j = 0; j < n_problems; ++j) {
              stdin_read(team[i][j]);
            }
          }
          printf("%d\n", get_max_solved_problems(team, n_problems));
        }
    }
}