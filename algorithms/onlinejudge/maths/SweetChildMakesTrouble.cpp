/*
───────────────────────────────────────────────────────────────
🧳 UVa 10497 Sweet Child Makes Trouble, the pattern ≈ Fibonacci, https://onlinejudge.org/external/104/10497.pdf, 
   https://oeis.org/A000166: Subfactorial or rencontres numbers, or derangements: number of permutations of n elements with no fixed points,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>



namespace bg = algorithms::onlinejudge::maths::utility::big_integer;

using ull = unsigned long long;
using v_bg = std::vector<bg::bigint>;


constexpr int MAX_THINGS = 800;

struct Article { int idx; };

using v_article = std::vector<Article>;

ull memo[21][1 << 20];


ull backtrack(int pos, int used, const v_article& articles) {
  if(__builtin_popcount(used) == (int)articles.size()) {
    return 1;
  }

  if(~memo[pos][used]) {
    return memo[pos][used];
  }

  ull ways = 0;
  for(auto& a : articles) {
    if(!(used & (1 << a.idx)) && a.idx != pos)
      ways += backtrack(pos + 1, used | (1 << a.idx), articles);
  }
  return memo[pos][used] = ways;
}


namespace algorithms::onlinejudge::maths::sweet_child_makes_trouble
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

        v_bg things(MAX_THINGS + 1);
        things[0] = bg::bigint(1);
        things[1] = bg::bigint(0);
        for(int i = 2; i <= MAX_THINGS; i++) {
          things[i] = (i - 1) * (things[i - 1] + things[i - 2]);
        }

        int n_things;
        while(scanf("%d", &n_things) == 1 && n_things != -1) {
        //   v_article articles(things);
        //   for(int i = 0; i < things; i++) {
        //     articles[i].idx = i + 1;
        //   }
        //   std::memset(memo, -1, sizeof(memo));
        //   printf("%llu\n", backtrack(1, 0, articles));
          printf("%s\n", things[n_things].getRawRep().c_str());
        }
    }
}