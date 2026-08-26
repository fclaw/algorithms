/*
───────────────────────────────────────────────────────────────
🧳 UVa 11212 Editing a Book, https://onlinejudge.org/external/112/11212.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "../maths/utility/permutations.cpp"
#include <bits/stdc++.h>


constexpr int MAX_FAC = 9;

using vi = std::vector<int>;

namespace perm = algorithms::onlinejudge::maths::utility::permutations;


vi fact(MAX_FAC + 1, 1);

void precompute_fac() { 
  for(int i = 1; i < MAX_FAC + 1; ++i) {
    fact[i] = fact[i - 1] * i;
  }
}

struct State
{
    vi permutation;
    int operations;
};

int get_min_cut_paste_operations(const vi& paragraph) {

  int SIZE = (int)paragraph.size();
  vi dist_s(fact[SIZE] + 1, INT32_MAX);
  std::queue<State> queue;

  // init
  vi source = paragraph;
  std::sort(source.begin(), source.end());
  int source_idx = (int)perm::getPermutationIndex(source);
  int target_idx = (int)perm::getPermutationIndex(paragraph);
  queue.push({source, 0});
  dist_s[source_idx] = 0;

  int min_cut_paste_operation = 0;

  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    vi curr_perm = state.permutation;
    int op_so_far = state.operations;
    int curr_perm_idx = perm::getPermutationIndex(curr_perm);

    if(curr_perm_idx == target_idx) {
      min_cut_paste_operation = op_so_far;
      break;
    }
    
    if(op_so_far > 2) {
      continue;
    }


    // i = start of cut, j = end of cut (inclusive)
    for (int i = 0; i < SIZE; ++i) {
      for (int j = i; j < SIZE; ++j) {
        // 1. Create remaining vector without [i .. j]
        vi remaining;
        remaining.insert(remaining.end(), curr_perm.begin(), curr_perm.begin() + i);
        remaining.insert(remaining.end(), curr_perm.begin() + j + 1, curr_perm.end());

        // 2. Try inserting [i .. j] into all valid positions k
        // (Avoid inserting back at position 'i' since that produces the identical array)
        for (int k = 0; k <= (int)remaining.size(); ++k) {
          if (k == i) continue; // Skip no-op
          vi next_perm = remaining;
          next_perm.insert(next_perm.begin() + k, curr_perm.begin() + i, curr_perm.begin() + j + 1);
          int next_perm_idx = perm::getPermutationIndex(next_perm);
          if(dist_s[next_perm_idx] == INT32_MAX) {
            dist_s[next_perm_idx] = 1 + op_so_far;
            queue.push({next_perm, 1 + op_so_far});
          }
        }
      }
    }
  }

  //
  if(dist_s[target_idx] != INT32_MAX) {
    return min_cut_paste_operation;
  } else {
    std::queue<State> queue;
    vi dist_t(fact[SIZE] + 1, INT32_MAX);
    queue.push({paragraph, 0});
    dist_t[target_idx] = 0;

    while(!queue.empty()) {
      State state = queue.front(); queue.pop();
      vi curr_perm = state.permutation;
      int op_so_far = state.operations;
      int curr_perm_idx = perm::getPermutationIndex(curr_perm);

      if(dist_s[curr_perm_idx] != INT32_MAX) {
        min_cut_paste_operation = dist_s[curr_perm_idx] + op_so_far;
        break;
      }
    
      if(op_so_far > 2) {
        continue;
      }


      // i = start of cut, j = end of cut (inclusive)
      for (int i = 0; i < SIZE; ++i) {
        for (int j = i; j < SIZE; ++j) {
          // 1. Create remaining vector without [i .. j]
          vi remaining;
          remaining.insert(remaining.end(), curr_perm.begin(), curr_perm.begin() + i);
          remaining.insert(remaining.end(), curr_perm.begin() + j + 1, curr_perm.end());

          // 2. Try inserting [i .. j] into all valid positions k
          // (Avoid inserting back at position 'i' since that produces the identical array)
          for (int k = 0; k <= (int)remaining.size(); ++k) {
            if (k == i) continue; // Skip no-op
            vi next_perm = remaining;
            next_perm.insert(next_perm.begin() + k, curr_perm.begin() + i, curr_perm.begin() + j + 1);
            int next_perm_idx = perm::getPermutationIndex(next_perm);
            if(dist_t[next_perm_idx] == INT32_MAX) {
              dist_t[next_perm_idx] = 1 + op_so_far;
              queue.push({next_perm, 1 + op_so_far});
            }
          }
        }
      }
    }

    /**
     * 🧠 MEET-IN-THE-MIDDLE DEDUCTION (Halim Case 3):
     * ------------------------------------------------
     * 1. Theoretical Diameter for N <= 9:
     *    It is mathematically proven that ANY permutation of length N <= 9 
     *    can be sorted in AT MOST 5 cut-and-paste operations (Max distance <= 5).
     * 
     * 2. Bidirectional Search Coverage:
     *    - Forward BFS from Source (s) explores all states at depth <= 2.
     *    - Backward BFS from Target (t) explores all states at depth <= 2.
     *    - Therefore, any path of length 0, 1, 2, 3, or 4 will GUARANTEE an 
     *      intersection (v in both sets) since 2 + 2 = 4.
     * 
     * 3. Deduction by Elimination:
     *    If no intersection is found, then:
     *        Distance > 4  AND  Distance <= 5  ===>  Distance MUST BE EXACTLY 5!
     * 
     * ⚡ PERFORMANCE BENEFIT:
     * -----------------------
     * This avoids having to expand BFS to depth 3 (which would require generating 
     * O(N^3 * N^3 * N^3) ≈ 10^7 states), keeping the search blazing fast in O(N^6)!
     */
    if(min_cut_paste_operation == INT32_MAX) {
      min_cut_paste_operation = 5;
    }
  }
  return min_cut_paste_operation;
}


namespace algorithms::onlinejudge::advanced_topics::editing_book
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
        
        precompute_fac();

        int n_paragraphs, t_case = 1;
        while(std::cin >> n_paragraphs && 
              n_paragraphs) {    
          vi paragraph(n_paragraphs);
          for(int i = 0; i < n_paragraphs; ++i) {
            std::cin >> paragraph[i];
          }
          printf("Case %d: %d\n", t_case++, get_min_cut_paste_operations(paragraph));
        }
    }
}