/*
───────────────────────────────────────────────────────────────
🧳 UVa 10817 Headmaster’sHeadache, https://onlinejudge.org/external/108/10817.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




struct Applicant
{
   int salary;
   vi subjects;
};


int cache[101][1 << 16];

int dp(int idx, int N, int taught_subjects, const std::vector<Applicant>& applicants) {

  if(__builtin_popcount(taught_subjects) == 2 * N) {
    return (cache[idx][taught_subjects] = 0);
  }

  if(idx == (int)applicants.size()) {
    return Inf;
  }

  if(~cache[idx][taught_subjects]) {
    return cache[idx][taught_subjects];
  }

  int best = dp(idx + 1, N, taught_subjects, applicants);

  Applicant app = applicants[idx];
  bool can_hired = false;
  int new_taught_subject = taught_subjects;
  for(int s : app.subjects) {
    int bit = 1 << 2 * s;
    if(!(new_taught_subject & bit)) {
      new_taught_subject |= bit;
      can_hired = true;
    } else {
      int bit = 1 << (2 * s + 1);
      if(!(new_taught_subject & bit)) {
        new_taught_subject |= bit;
        can_hired = true;
      }
    }
  }

  if(can_hired) {
    best = std::min(best, app.salary + dp(idx + 1, N, new_taught_subject, applicants));
  }

  return (cache[idx][taught_subjects] = best);

}

int get_min_cost(int taught_subjects, int N, const std::vector<Applicant>& applicants) {
  std::memset(cache, -1, sizeof cache);
  return dp(0, N, taught_subjects, applicants);
}


namespace algorithms::onlinejudge::advanced_topics::headmaster_s_headache
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

        int n_subjects, n_teachers, n_applicants;
        while(stdin_read(n_subjects, n_teachers, n_applicants) && 
              (n_subjects && n_teachers && n_applicants)) {
          std::cin.ignore();
          int budget = 0;
          int taught_subjects = 0;
          for(int i = 0; i < n_teachers; ++i) {
            std::string s;
            std::getline(std::cin, s);
            std::stringstream ss(s);
            int salary;
            ss >> salary;
            budget += salary;
            int s_idx;
            while(ss >> s_idx) {
              --s_idx;
              if(taught_subjects & (1 << (2 * s_idx))) {
                taught_subjects |= (1 << (2 * s_idx + 1));
              } else {
               taught_subjects |= (1 << (2 * s_idx)); 
              }
            }
          }
          std::vector<Applicant> applicants(n_applicants);
          for(int i = 0; i < n_applicants; ++i) {
            std::string s;
            std::getline(std::cin, s);
            std::stringstream ss(s);
            ss >> applicants[i].salary;
            int s_idx;
            while(ss >> s_idx) {
              --s_idx;
              applicants[i].subjects.push_back(s_idx);
            }
          }
          printf("%d\n", budget + get_min_cost(taught_subjects, n_subjects, applicants));
        }
    }
}