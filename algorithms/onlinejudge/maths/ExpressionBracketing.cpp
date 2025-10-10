/*
───────────────────────────────────────────────────────────────
🧳 UVa 10312 Expression Bracketing, https://onlinejudge.org/external/103/10312.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;
namespace bg = algorithms::onlinejudge::maths::utility::big_integer;



constexpr int MAX_LENGTH = 26;

namespace algorithms::onlinejudge::maths::expression_bracketing
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

        std::vector<bg::bigint> s_catalans = arithmetics::super_catalans_all_bigint(MAX_LENGTH);
        std::vector<bg::bigint> catalans = arithmetics::catalan_all_bigint(MAX_LENGTH);


        int n_letters;
        while(scanf("%d", &n_letters) == 1) {
          std::cout << (s_catalans[n_letters - 1] - catalans[n_letters - 1]) << std::endl;
        }
    }
}