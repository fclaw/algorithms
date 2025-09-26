/*
───────────────────────────────────────────────────────────────
🧳 UVa 10183 How many Fibs?, get the number of Fibonaccis when generating them; BigInteger, https://onlinejudge.org/external/101/10183.pdf, rt: s
───────────────────────────────────────────────────────────────
 * The problem asks us to count how many Fibonacci numbers fall within a given
 * range [a, b], where a and b are very large numbers.
 *
 * The strategy is to pre-compute a large number of Fibonacci numbers and store
 * them in a sorted list. For each query [a, b], we can then use binary search
 * to efficiently find the indices of the first Fibonacci number >= a and the
 * first Fibonacci number > b. The difference in these indices gives the count.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>


namespace bg = algorithms::onlinejudge::maths::utility::big_integer;


const int MAX = 500;
using map = std::map<bg::bigint, int>;



namespace algorithms::onlinejudge::maths::how_many_fibs
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

        map fibs_count;
        std::vector<bg::bigint> fibs(MAX + 1);
        // fibs[0] = bg::bigint("0");
        fibs[1] = bg::bigint("1");
        fibs[2] = bg::bigint("2");
        fibs_count[bg::bigint("1")] = 0;
        fibs_count[bg::bigint("2")] = 1;
        for (int i = 3; i <= MAX; i++) {
          fibs[i] = fibs[i - 1] + fibs[i - 2];
          fibs_count[fibs[i]] = fibs_count[fibs[i - 1]] + 1;
        }

        std::string from, to;
        while (std::cin >> from >> to) {
          if(from == "0" && to == "0") break;
          auto low = std::lower_bound(fibs.begin(), fibs.end(), bg::bigint(from));
          auto up = std::upper_bound(fibs.begin(), fibs.end(), bg::bigint(to));
          printf("%d\n", fibs_count[*(up)] - fibs_count[*low]);
        }
    }
}