/*
───────────────────────────────────────────────────────────────
🧳 UVa 11432 Busy Programmer, https://onlinejudge.org/external/114/11432.pdf, rt: s
───────────────────────────────────────────────────────────────
 * Category: Dynamic Programming with Streak & Finite-Horizon Constraints
 *
 * ============================================================================
 * PROBLEM RULES & INVARIANTS:
 * ============================================================================
 * 1. Two Projects: Project 0 (MICRO) and Project 1 (GOO).
 * 2. Day Quotas: Gordov must work exactly D days on each project (Total: 2D days).
 * 3. The Streak Rule: Cannot work on either project for more than G consecutive days.
 *    -> EXCEPTION: If one project is already complete, this restriction is lifted!
 * 4. The Finish Rule: The project that starts on Day 1 MUST finish first!
 *    -> In other words: root_pid must reach D days strictly before the other project.
 *
 * ============================================================================
 * DP STATE DEFINITION:
 * ============================================================================
 * cache[pid][root_pid][days[0]][days[1]][curr_streak]
 *   - pid         : Current project being worked on (0 or 1).
 *   - root_pid    : The project that started on Day 1 (determines who must finish first).
 *   - days[0]     : Remaining work days needed for Project 0.
 *   - days[1]     : Remaining work days needed for Project 1.
 *   - curr_streak : Number of consecutive days worked on 'pid' up to today.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



ll cache[2][2][34][34][34];


int MAX_DAYS;    // Total days in the schedule (2 * D)
int MAX_STREAK;  // Maximum allowed consecutive days on one project (G)


ll dfs(int pid, int root_pid, vi& days, int curr_streak, std::vector<bool>& is_finished) {

  // ------------------------------------------------------------------------
  // 1. PRUNING / INVALID BOUNDS
  // ------------------------------------------------------------------------
  // 1. Streak exceeded the maximum allowed G days.
  // 2. We over-allocated days for a project (days < 0).
  if(curr_streak > MAX_STREAK || 
     days[pid] < 0) {
    return 0LL;
  }

  // ------------------------------------------------------------------------
  // 2. EARLY TERMINATION (THE MASTER SHORTCUT)
  // ------------------------------------------------------------------------
  // If the project that started on Day 1 (root_pid) has finished its D days,
  // and the other project has NOT finished yet:
  //   - Rule satisfied: root_pid finished first!
  //   - All remaining days MUST be spent on the other project (zero branching).
  //   - Since root_pid is finished, the G-streak constraint is lifted!
  //   - Therefore, there is EXACTLY 1 deterministic way to finish the schedule.
  if(is_finished[root_pid] && 
     !is_finished[(root_pid + 1) % 2]) {
    return 1LL;
  }
 
   
  if(~cache[pid][root_pid][days[0]][days[1]][curr_streak]) {
    return cache[pid][root_pid][days[0]][days[1]][curr_streak];
  }

  ll ways = 0LL;
  int days_left = days[pid] +  days[(pid + 1) % 2];

  // ========================================================================
  // CHOICE A: CONTINUE ON THE SAME PROJECT ('pid')
  // ========================================================================
  if(!is_finished[pid]) {
    // Dynamic Anchor: On Day 1, lock in who started first!
    if(days_left == MAX_DAYS) {
      root_pid = pid;
    }
    days[pid]--;
    if(days[pid] == 0) {
      is_finished[pid] = true;
    }
    ways += dfs(pid, root_pid, days, curr_streak + 1, is_finished);
    if(days[pid] == 0) {
      is_finished[pid] = false;
    }
    days[pid]++;
  }

  // ========================================================================
  // CHOICE B: SWITCH TO THE OTHER PROJECT ('(pid + 1) % 2')
  // ========================================================================
  int other = (pid + 1) % 2;

  if(days_left == MAX_DAYS) {
    root_pid = other;
  }

  days[other]--;
  if(days[other] == 0) {
    is_finished[other] = true;
  }
  ways += dfs(other, root_pid, days, 1, is_finished);
  if(days[other] == 0) {
    is_finished[other] = false;
  }
  days[other]++;

  return (cache[pid][root_pid][days[0]][days[1]][curr_streak] = ways);
}



ll get_all_schedules_number(int days_per_project, int max_streak) {
  MAX_DAYS = 2 * days_per_project;
  MAX_STREAK = max_streak;
  std::memset(cache, -1, sizeof cache);
  vi days(2, days_per_project);
  std::vector<bool> is_finished(2, false);
  return dfs(0, 0, days, 0, is_finished);
}


namespace algorithms::onlinejudge::advanced_topics::busy_programmer
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

        int days_per_project, max_streak, t_case = 1;
        while(stdin_read(days_per_project, max_streak) && 
              (days_per_project != -1 && max_streak != -1)) {
          printf("Case %d: %lld\n", t_case++, get_all_schedules_number(days_per_project, max_streak));
        }
    }
}