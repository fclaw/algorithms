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
typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;


namespace algorithms::onlinejudge::greedy::commando_war
{
    /**  */
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

        size_t N, c = 1;
        while(std::cin >> N && N)
        {
            vpii troops(N);
            size_t brief_t, job_t;
            for(size_t i = 0; i < N; i++)
              scanf("%zu %zu\n", &brief_t, &job_t),
              troops[i] = { brief_t, job_t };
            
            auto cmp = 
              [](const pii& x, const pii& y) 
              { return x.second > y.second || 
                       (x.second == y.second && x.first < y.first); };
            std::sort(troops.begin(), troops.end(), cmp);

            // We simulate briefing each commando one by one, and track
            // the maximum of (total briefing time so far + their job time),
            // since jobs start only after briefing and run in parallel.
            size_t curr_brief_t = 0;
            size_t min_t = 0;
            for(size_t i = 0; i < N; i++) {
              curr_brief_t += troops[i].first;
              min_t = std::max(min_t, curr_brief_t + troops[i].second);
            }
            printf("Case %zu: %zu\n", c++, min_t);
        }
    }
}