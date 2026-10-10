/*
───────────────────────────────────────────────────────────────
🧳 UVa 1252 Twenty Questions, https://onlinejudge.org/external/12/1252.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





constexpr int MAX_FEATURES = 11;


enum Feature_Status { NO = 0, YES = 1 };


int count_objects(int mask, const vi& objects) {
  
  int counter = 0;
  for(int o : objects) {
    if((o & mask) == mask) {
      counter++;
    }
  }
  return counter;
}

int dp(int features_mask, int answers_mask, int features_n, const vi& objects, std::unordered_map<ii, int>& cache) {

  // --------------------------------------------------------------------
  // BASE CASE: If <= 1 object remains, it is uniquely identified!
  // --------------------------------------------------------------------
  if (count_objects(answers_mask, objects) <= 1) {
    return 0;
  }

   ii key = std::make_pair(features_mask, answers_mask);
   if(auto it = cache.find(key); 
      it != cache.end()) {
     return it->second;
   }

    int best = Inf;
    for(int feature = 0; feature < features_n; ++feature) {
      int bit = 1 << feature;
      if(!(features_mask & bit)) {
        int new_features_mask = features_mask | bit;
         // try NO
        int no_mask = answers_mask | (1 << (2 * feature + NO));
        int cnt_no = count_objects(no_mask, objects); // apply mask to count objects
        int yes_mask = answers_mask | (1 << (2 * feature + YES));
        int cnt_yes = count_objects(yes_mask, objects);
        // PRUNING: Only ask this question if it actually splits the candidates!
        // (If everyone has 'yes' or everyone has 'no', asking it gives 0 info).
        if(cnt_no > 0 && 
           cnt_yes > 0) {
          // Worst-case answer for this specific question (MAX):
          int no_branch = dp(new_features_mask, no_mask, features_n, objects, cache);
          int yes_branch = dp(new_features_mask, yes_mask, features_n, objects, cache);
          int worst_case = 1 + std::max(no_branch, yes_branch);
          // We choose the question that minimizes the worst case (MIN):
          best = std::min(best, worst_case);
        }
      }
    }
  
  return (cache[key] = best);
}


int get_max_questions(int features_n, const vi& objects) {
  std::unordered_map<ii, int> cache;
  return dp(0, 0, features_n, objects, cache);
}


namespace algorithms::onlinejudge::advanced_topics::twenty_questions
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

        int features_n, objects_n;
        while(stdin_read(features_n, objects_n) &&
              (features_n && objects_n)) {
          vi objects(objects_n);
          for(int o = 0; o < objects_n; ++o) {
            std::string s;
            stdin_read(s);
            int tmp = 0;
            for(int i = 0; i < (int)s.size(); ++i) {
              if(s[i] == '0') {
                tmp |= (1 << (2 * i + NO));
              } else {
                tmp |= (1 << (2 * i + YES)); 
              }
            }
            objects[o] = tmp;
          }
          printf("%d\n", get_max_questions(features_n, objects));
        }
    }
}