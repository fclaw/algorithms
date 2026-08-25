/*
───────────────────────────────────────────────────────────────
🧳 UVa 658 It’s not a Bug, it’s a Feature!, https://onlinejudge.org/external/6/658.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


struct Patch
{
    /**
     * 1. time (Edge Weight / Cost)
     * ----------------------------
     * The time in seconds required to install/apply this patch.
     * Used as edge cost in Dijkstra's Algorithm (priority queue).
     */
    int time;

    /**
     * ==========================================
     * PRECONDITIONS (From String 1)
     * ==========================================
     * 
     * 2. req_present (Must have '+' bugs):
     *    Bitmask of bugs that MUST BE PRESENT in the software before 
     *    this patch can be installed.
     *    Condition: (curr_state & req_present) == req_present
     * 
     * 3. req_absent (Must NOT have '-' bugs):
     *    Bitmask of bugs that MUST BE ABSENT from the software before 
     *    this patch can be installed.
     *    Condition: (curr_state & req_absent) == 0
     */
    int req_present;
    int req_absent;

    /**
     * ==========================================
     * EFFECTS / POSTCONDITIONS (From String 2)
     * ==========================================
     * 
     * 4. fix_bugs (Bugs removed by '-'):
     *    Bitmask of bugs that this patch ELIMINATES/FIXES.
     *    Operation: Clear these bits using (state & ~fix_bugs)
     * 
     * 5. add_bugs (Bugs introduced by '+'):
     *    Bitmask of new bugs that this patch CREATES/INTRODUCES.
     *    Operation: Set these bits using (state | add_bugs)
     */
    int fix_bugs;
    int add_bugs;
};

using v_patch = std::vector<Patch>; 

struct State 
{
    /**
     * 1. bugs (Software Bug Bitmask)
     * ------------------------------
     * The bitmask representing which bugs are currently present in the software.
     *   - Bit i == 1 : Bug 'i' is currently active.
     *   - Bit i == 0 : Bug 'i' is absent / fixed.
     * 
     * Initial State (Source) : (1 << n) - 1  (All n bits are 1)
     * Target State (Goal)    : 0             (All bugs fixed)
     */
    int bugs;

    /**
     * 2. time (Accumulated Path Cost / Distance g(n))
     * ----------------------------------------------
     * The total accumulated time (in seconds) taken to reach this 
     * specific bug configuration from the initial buggy version.
     * This is the value we want to minimize.
     */
    int time;

    /**
     * 3. Priority Queue Min-Heap Comparator
     * -------------------------------------
     * Inverts '<' using 'time > other.time' so that `std::priority_queue<State>` 
     * pops the state with the SHORTEST accumulated time first.
     */
    bool operator < (const State& other) const {
      return time > other.time; 
    }
};

/**
 * Checks if a patch can be applied to the current bug state.
 * 
 * Rules:
 * 1. All bugs in 'req_present' (marked with '+') MUST be present in bugs_left.
 * 2. All bugs in 'req_absent'  (marked with '-') MUST be absent from bugs_left.
 */
inline bool check_prerequisites(int bugs_left, const Patch& patch) {
  // 1. Check all required '+' bugs are 1
  bool has_required = ((bugs_left & patch.req_present) == patch.req_present);

  // 2. Check all forbidden '-' bugs are 0
  bool no_forbidden = ((bugs_left & patch.req_absent) == 0);

  return has_required && no_forbidden;
}

/**
 * Applies the patch and returns the new bug state.
 * 
 * Effects:
 * 1. Clears (fixes) all bugs in 'fix_bugs' (marked with '-').
 * 2. Sets (adds) all bugs in 'add_bugs'   (marked with '+').
 */
inline int apply_patch(int bugs_left, const Patch& patch) {
  // 1. Clear fixed bugs via bitwise NOT & AND (~fix_bugs)
  // 2. Add newly introduced bugs via bitwise OR (| add_bugs)
  return (bugs_left & ~patch.fix_bugs) | patch.add_bugs;
}

std::string min_time_required(const v_patch& patches, int bugs) {

  std::priority_queue<State> queue;
  vi time(bugs + 1, INT32_MAX);
  // init
  time[bugs] = 0;
  queue.push({bugs, 0});
  
  int min_time = INT32_MAX;
   
  while(!queue.empty()) {
    State state = queue.top(); queue.pop();
    int time_so_far = state.time;
    int bugs_left = state.bugs;

    if(bugs_left == 0) {
      min_time = time_so_far;
      break;
    }

    // prune
    if(time_so_far > time[bugs_left]) {
      continue;
    }

    for(auto patch : patches) {
      if(check_prerequisites(bugs_left, patch)) {
        int new_time = time_so_far + patch.time;
        int new_bug_left = apply_patch(bugs_left, patch);
        if(new_time < time[new_bug_left]) {
          time[new_bug_left] = new_time;
          queue.push({new_bug_left, new_time});
        }
      } 
    }
  }

  if(min_time == INT32_MAX) {
    return "Bugs cannot be fixed.";
  } else {
    return "Fastest sequence takes " + std::to_string(min_time) + " seconds.";
  }
}


namespace algorithms::onlinejudge::advanced_topics::bug
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

        int t_case = 1;
        int n_bugs, m_patches;
        while(std::cin >> n_bugs 
                       >> m_patches && 
              (n_bugs && m_patches)) {
          v_patch patches(m_patches);
          std::string pre, post;
          for(int i = 0; i < m_patches; ++i) {
            Patch patch;
            patch.req_present = 0;
            patch.req_absent  = 0;
            patch.fix_bugs    = 0;
            patch.add_bugs    = 0;
            std::cin >> patch.time >> pre >> post;
            // pre
            for(int j = 0; j < n_bugs; ++j) {
              int bit = (1 << j);
              if(pre[j] == '-') {
                patch.req_absent |= bit;
              } else if(pre[j] == '+') {
                patch.req_present |= bit;
              }
            }
            // post
            for(int k = 0; k < n_bugs; ++k) {
              int bit = (1 << k);
              if(post[k] == '-') {
                patch.fix_bugs |= bit;
              } else if(post[k] == '+') {
                patch.add_bugs |= bit;
              }
            }            
            patches[i] = patch;
          }
          printf("Product %d\n%s\n\n", t_case++, min_time_required(patches, (1 << n_bugs) - 1).c_str());
        }
    }
}