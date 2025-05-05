#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>






typedef long long ll;
typedef std::vector<int> vi;


namespace algorithms::onlinejudge::greedy::shopaholic
{
    /** https://onlinejudge.org/external/113/11369.pdf */
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

        int tc;
        std::cin >> tc;
        while(tc--)
        {
            size_t N;
            std::cin >> N;
            vi articles(N);
            for(size_t i = 0; i < N; i++)
              std::cin >> articles[i];
            std::sort(articles.begin(), articles.end(), std::greater<int>());

            size_t max_discount = 0;
            size_t i = -1, j = (N - N % 3) - 1;
            while(N > 2 && (i += 3) <= j)
              max_discount += articles[i];
            std::cout << max_discount << std::endl;
        }  
    }
}