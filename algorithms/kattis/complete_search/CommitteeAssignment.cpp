/*
───────────────────────────────────────────────────────────────
🧳  Committee Assignment, https://open.kattis.com/problems/committeeassignment, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;

int N, M;


void backtrack(int member, const vi& feud_list, vi& committees_so_far, int& min_committees) {
 
    if(member == N) {
      min_committees = std::min(min_committees, (int)committees_so_far.size());
      return;
    }

    // branch-and-bound
    if((int)committees_so_far.size() >= min_committees) {
      return;
    }

    // create new committee
    int committee = (1 << member);
    committees_so_far.push_back(committee);
    backtrack(member + 1, feud_list, committees_so_far, min_committees);
    committees_so_far.pop_back();

    // assign member to an exiting committee
    for(int& c : committees_so_far) {
      int list = feud_list[member];
      if((c & list) == 0) {
        c |= (1 << member);
        backtrack(member + 1, feud_list, committees_so_far, min_committees);
        c &= ~(1 << member);
      }
    }

}

int get_min_required_committees(const vi& feud_list) {

  vi committees_so_far;
  int min_committees = N;
  backtrack(0, feud_list, committees_so_far, min_committees);
  return min_committees;
}

namespace algorithms::kattis::complete_search::committee_assignment
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

        while(std::cin >> N >> M && N) {
          int idx = 0;
          vi feud_list(N);
          std::string name_1, name_2;
          std::unordered_map<std::string, int> name_to_idx;
          for(int i = 0; i < M; ++i) {
            std::cin >> name_1 >> name_2;
            if(auto it = name_to_idx.find(name_1);
               it == name_to_idx.end()) {
              name_to_idx[name_1] = idx++;
            }
            if(auto it = name_to_idx.find(name_2);
               it == name_to_idx.end()) {
              name_to_idx[name_2] = idx++;
            }

            int name_1_idx = name_to_idx.at(name_1);
            int name_2_idx = name_to_idx.at(name_2);

            feud_list[name_1_idx] |= (1 << name_2_idx);
            feud_list[name_2_idx] |= (1 << name_1_idx);
          }
 
          printf("%d\n", get_min_required_committees(feud_list));
        }
    }
}