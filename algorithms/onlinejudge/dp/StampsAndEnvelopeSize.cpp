/*
───────────────────────────────────────────────────────────────
🧳 UVa 242 Stamps and Envelope Size, https://onlinejudge.org/external/2/242.pdf, rt: s
───────────────────────────────────────────────────────────────
Verdict: Accepted | Runtime: 0.100s

   Algorithmic Summary:
   
   1. The Reachability DP (Subproblem State):
      We define 'check_reachability(postage, stamps_left, stamps)' as a top-down 
      memoized function. It returns true if we can make exactly 'postage' using 
      at most 'stamps_left' stamps.
      
      State transitions:
         check_reachability(postage, S_left) = OR_{s in stamps} (check_reachability(postage - s, S_left - 1))
      
      Since the maximum postage value is bounded by (max_pockets * max_denomination) 
      which is typically small (<= 1000), a 2D cache array of size 11 x 1001 is 
      both highly memory-efficient and fast to query.

   2. Sequential Coverage Scan:
      For each stamp set, we incrementally test 'postage = 1, 2, 3, ...' until 
      we find a postage value that is unreachable. The maximum consecutive 
      reachable value is our 'curr_max_coverage'.

   3. Lexicographical Tie-Breaking:
      When two sets yield the same maximum coverage, we compare them in reverse 
      order (from the largest denomination down to the smallest):
        - Prefer the set with fewer denominations.
        - If sizes are equal, compare the largest elements. The set with the 
          strictly smaller largest element is preferred.
        - If they are equal, compare the second-largest, and so on.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vb = std::vector<bool>;



int cache[11][1001];


bool check_reachability(int postage, int stamps_left, const vi& stamps) {

  if(stamps_left >= 0 && 
     postage == 0) {
    return (bool)(cache[stamps_left][postage] = 1);
  }

  if(stamps_left == 0) {
    return (bool)(cache[stamps_left][postage] = 0);
  }

  if(~cache[stamps_left][postage]) {
    return (bool)cache[stamps_left][postage];
  }

  bool is_reachable = false; 
  for(int s : stamps) {
    if(postage >= s) {
      is_reachable |= check_reachability(postage - s, stamps_left - 1, stamps);
    }
  }

  return (cache[stamps_left][postage] = (int)is_reachable);
}

// Corrected tie-breaker comparison
bool is_preferred(const vi& best, const vi& curr) {
  if (curr.size() < best.size()) {
    return true;
  } else if (curr.size() == best.size()) {
    int S = (int)curr.size();
    for (int i = S - 1; i >= 0; --i) {
      if (curr[i] > best[i]) {
        return false;
      } else if (curr[i] < best[i]) {
        return true; // Fixed: immediately return true if smaller
      }
    }
    return true;
  } else {
    return false;
  }
}


namespace algorithms::onlinejudge::dp::stamps_and_envelope_size
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
        
        int pockets, S, D;
        while(std::cin >> pockets && pockets) {
          std::cin >> S;
          vvi set(S);
          for(int i = 0; i < S; ++i) {
            std::cin >> D;
            vi denominations(D);
            for(int i = 0; i < D; ++i) {
              std::cin >> denominations[i];
            }
            std::sort(denominations.begin(), denominations.end());
            set[i] = denominations;
          }

          int max_coverage = 0;
          vi collection;
            
          for(const auto& col : set) {
            std::memset(cache, -1, sizeof cache);
            int M = pockets * col.back();
            bool can_extend = true;
            int curr_max_coverage = 0;
            for(int postage = 1; postage <= M; ++postage) {
              can_extend &= check_reachability(postage, pockets, col);
              if(!can_extend) {
                break;
              }
              curr_max_coverage = postage;
            }
            if(max_coverage < curr_max_coverage) {
              max_coverage = curr_max_coverage;
              collection = col;
            } else if(max_coverage == curr_max_coverage) {
              if((!collection.empty() && 
                 is_preferred(collection, col)) || 
                 collection.empty()) {
                collection = col;
              }
            }
          }
         
          std::stringstream ss;
          for (int d : collection) {
            ss << std::setw(3) << d; // Enforces a width of 3 for each number
          }
          std::string col = ss.str();
          // Print the final formatted line
          // "%3d" right-aligns the max_coverage value with a width of 3
          std::printf("max coverage = %3d :%s\n", max_coverage, col.c_str());
        }
    }
}