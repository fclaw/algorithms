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


namespace algorithms::onlinejudge::greedy::bus_driver
{
    /** https://onlinejudge.org/external/113/11389.pdf, load balancing */
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

        int N, d, r;
        while(std::cin >> N >> d >> r && N && d && r)
        {
            vi m_routes(N);
            vi e_routes(N);
            for(int i = 0; i < N; i++)
              std::cin >> m_routes[i];
            for(int i = 0; i < N; i++)
              std::cin >> e_routes[i];
           
            std::sort(m_routes.begin(), m_routes.end());
            std::sort(e_routes.begin(), e_routes.end(), std::greater<int>()); 
            int overwork = 0;
            for(int i = 0; i < N; i++)
              if(m_routes[i] + e_routes[i] > d)
                overwork += (m_routes[i] + e_routes[i]) - d;
            std::cout << (ll)(r * overwork) << std::endl;
        }
    }
}