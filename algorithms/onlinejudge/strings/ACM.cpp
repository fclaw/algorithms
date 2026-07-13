/*
───────────────────────────────────────────────────────────────
🧳 UVa 11048 Automatic correction of misspellings, https://onlinejudge.org/external/110/11048.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




bool check_replace_or_swap(const std::string& A, const std::string& B) {
    int mismatches = 0;
    int first_mismatch = -1;

    for (size_t i = 0; i < A.length(); ++i) {
        if (A[i] != B[i]) {
            mismatches++;
            if (first_mismatch == -1) first_mismatch = i;
        }
    }

    // 1. One letter is wrong (Replace)
    if (mismatches == 1) return true;

    // 2. Adjacent swap check
    if (mismatches == 2) {
        int idx = first_mismatch;
        // Check if swapping A[idx] and A[idx+1] makes it equal to B
        if (idx + 1 < (int)A.length() && A[idx] == B[idx+1] && A[idx+1] == B[idx]) {
            return true;
        }
    }

    return false;
}


bool check_insert_delete(const std::string& A, const std::string& B) {
    // Let 'L' be the longer string, 'S' be the shorter string
    const std::string& L = (A.length() > B.length()) ? A : B;
    const std::string& S = (A.length() > B.length()) ? B : A;

    size_t i = 0, j = 0;
    int mismatches = 0;

    while (i < S.length() && j < L.length()) {
        if (S[i] != L[j]) {
            mismatches++;
            if (mismatches > 1) return false;
            j++; // Skip the extra character in the longer string
        } else {
            i++; j++;
        }
    }
    return true;
}


namespace algorithms::onlinejudge::strings::acm
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

        int n_words, n_queries;
        std::string word, query;
        std::map<std::string, int> dictionary;
        while(std::cin >> n_words) {
          for(int i = 0; i < n_words; ++i) {
            std::cin >> word;
            dictionary.insert({word, i}); 
          }

          std::cin >> n_queries;
          while(n_queries--) {
            std::cin >> query;
            if(dictionary.find(query) != dictionary.end()) {
              printf("%s is correct\n", query.c_str());
            } else {
              std::string target_w;
              int min_idx = INT32_MAX;
              for(auto p : dictionary) {
                std::string word = p.first;
                int idx = p.second;
                int w_length = word.length();
                int q_length = query.length();
                if(std::abs(w_length - q_length) > 1) {
                  continue;
                }

                if (w_length == q_length) {
                  // CASE 1: Same length. Check for:
                  // - Exactly 1 mismatch (Replace)
                  // - OR Exactly 1 adjacent swap
                  bool res = check_replace_or_swap(query, word);
                  if(res) {
                    if(target_w.empty() || 
                       min_idx > idx) {
                      target_w = word;
                    }
                    min_idx = std::min(min_idx, idx);
                  }
                }
                else {
                  // CASE 2: Lengths differ by 1. Check for:
                  // - Exactly 1 missing/extra letter (Insert/Delete)
                  bool res = check_insert_delete(query, word);
                  if(res) {
                    if(target_w.empty() || 
                       min_idx > idx) {
                      target_w = word;
                    }
                    min_idx = std::min(min_idx, idx);
                  }
                }
              }

              if(!target_w.empty()) {
                printf("%s is a misspelling of %s\n", query.c_str(), target_w.c_str()); 
              } else {
                printf("%s is unknown\n", query.c_str());  
              }
            }
          }
      }
    }
}