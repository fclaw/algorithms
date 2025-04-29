#include "../debug.h"
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <tuple>





typedef long long ll;
typedef std::tuple<int, int, int> tii;
typedef std::vector<tii> vpii;

namespace algorithms::onlinejudge::greedy::shoemaker
{
    /**    */
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
        std::cin.ignore();
        while(tc--)
        {
            int N;
            std::cin >> N;
            vpii jobs(N);
            int t, p;
            for(int i = 0; i < N; i++)
            {
                std::cin >> t >> p;
                jobs[i] = {i + 1, p, t};
            }
            // prioritize  by weigh: the more weigh the earlier a job should be picked up
            auto cmpByWeigh = 
              [](const tii& jobi, const tii& jobj)
              {
                 ll left = (ll)(std::get<1>(jobi) * std::get<2>(jobj));
                 ll right = (ll)(std::get<1>(jobj) * std::get<2>(jobi));
                 if(left == right)
                   return std::get<0>(jobi) < std::get<0>(jobj);
                 return left > right;
              };
            std::sort(jobs.begin(), jobs.end(), cmpByWeigh);
            std::string schedule;
            for(const tii& tpl : jobs)
              schedule += std::to_string(std::get<0>(tpl)) + " ";
            schedule.pop_back();
            std::cout << schedule << std::endl;
            if(tc) std::cout << std::endl;
        }
    }
}