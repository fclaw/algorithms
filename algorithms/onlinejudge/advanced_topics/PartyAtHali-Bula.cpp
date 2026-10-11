/*
───────────────────────────────────────────────────────────────
🧳 UVa 1220 Party at Hali-Bula, https://onlinejudge.org/external/12/1220.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





enum State { NOT_INVITED = 0, INVITED = 1 };


// Global or per-testcase City ID Mapper
std::unordered_map<std::string, int> person_to_id;
int unique_person_counter;

int get_id(const std::string& raw_person) {
  auto it = person_to_id.find(raw_person);
  if (it != person_to_id.end()) return it->second;
  person_to_id[raw_person] = unique_person_counter++;
  return person_to_id.at(raw_person);
}

int root;


void dfs(int u, int parent, const vvi& tree, vvi& dp, vvi& is_unique) {
  // Base Case for node u:
  dp[u][INVITED] = 1;
  is_unique[u][INVITED] = 1;

  dp[u][NOT_INVITED] = 0;
  is_unique[u][NOT_INVITED] = 1;

  for(int v : tree[u]) {
    if(v != parent) {
      dfs(v, u, tree, dp, is_unique);

      // ================================================================
      // 1. If u IS INVITED:
      // ================================================================
      // All children v MUST be NOT_INVITED
      dp[u][INVITED] += dp[v][NOT_INVITED];
            
      // If child v's NOT_INVITED choice was not unique, u inherits it!
      if (!is_unique[v][NOT_INVITED]) {
        is_unique[u][INVITED] = 0;
      }

      // ================================================================
      // 2. If u is NOT INVITED:
      // ================================================================
      // We choose whichever is larger for child v
      if (dp[v][INVITED] == dp[v][NOT_INVITED]) {
        // A TIE! We could choose either -> automatically NOT unique!
        dp[u][NOT_INVITED] += dp[v][INVITED];
        is_unique[u][NOT_INVITED] = 0;
      } else if (dp[v][INVITED] > dp[v][NOT_INVITED]) {
        dp[u][NOT_INVITED] += dp[v][INVITED];
        // Inherit child v's uniqueness:
        if (!is_unique[v][INVITED]) {
          is_unique[u][NOT_INVITED] = 0;
        }
      } else { // dp[v][NOT_INVITED] > dp[v][INVITED]
        dp[u][NOT_INVITED] += dp[v][NOT_INVITED];
        // Inherit child v's uniqueness:
        if (!is_unique[v][NOT_INVITED]) {
          is_unique[u][NOT_INVITED] = 0;
        }
      }
    }
  }
}


namespace algorithms::onlinejudge::advanced_topics::party_at_Hali_Bula
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
        while(stdin_read(N) && N) {

          person_to_id.clear();
          unique_person_counter = 0;

          vvi tree(N);
          std::string big_boss;
          stdin_read(big_boss);
          int _ = get_id(big_boss);
          for(int i = 1; i < N; ++i) {
            std::string person, boss;
            stdin_read(person, boss);
            int p_id = get_id(person);
            int b_id = get_id(boss);
            tree[b_id].push_back(p_id);
          }
          vvi dp(N, vi(2, 0));
          vvi is_unique(N, vi(2, 1));
          root = get_id(big_boss);
          dfs(root, -1, tree, dp, is_unique);

          int max_guests = 0;
          bool unique_answer = false;

          if (dp[root][INVITED] == dp[root][NOT_INVITED]) {
            // Tie at the root -> CANNOT BE UNIQUE!
            max_guests = dp[root][INVITED];
            unique_answer = false;
          } else if (dp[root][INVITED] > dp[root][NOT_INVITED]) {
            max_guests = dp[root][INVITED];
            unique_answer = is_unique[root][INVITED];
          } else {
            max_guests = dp[root][NOT_INVITED];
            unique_answer = is_unique[root][NOT_INVITED];
          }

          std::cout << max_guests << " " << (unique_answer ? "Yes" : "No") << "\n";
        }
    }
}