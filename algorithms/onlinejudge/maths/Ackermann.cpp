/*
───────────────────────────────────────────────────────────────
🧳 UVa 371 Ackermann Functions, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;

std::unordered_map<ll, ll> memo;


ll do_ackermann(ll n) {
  if(memo.find(n) != memo.end()) return memo.at(n);
  if(n <= 0) return 0;
  if(n == 1) return 0;
  if(n % 2 == 0) 
    return memo[n] = 1 + do_ackermann(n / 2);
  return memo[n] = 1 + do_ackermann(3 * n + 1);
}

namespace algorithms::onlinejudge::maths::Ackermann
{
    /** https://onlinejudge.org/external/3/371.pdf */
    int n, m;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while(while_read(n, m) && n && m) {
          int start = std::min(n, m);
          int end = std::max(n, m);
          ll max_seq = 0;
          int max_seq_num = start;
          for(int curr_num = start; curr_num <= end; ++curr_num) {
            ll seq = curr_num == 1 ? 3 : do_ackermann(curr_num);
            if(seq > max_seq) {
              max_seq = seq;
              max_seq_num = curr_num;
            }
          }
        printf("Between %d and %d, %d generates the longest sequence of %d values.\n", start, end, max_seq_num, (int)max_seq);
        }
    }
}