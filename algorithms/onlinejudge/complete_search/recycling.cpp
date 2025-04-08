#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::unordered_map<char, int> mci;

namespace algorithms::onlinejudge::complete_search::recycling
{
    /** https://onlinejudge.org/external/1/154.pdf, 3 nested loops  */
    mci bins = {{'r', 0}, {'o', 1}, {'y', 2}, {'g', 3}, {'b', 4}};
    mci wastes = {{'P', 0}, {'G', 1}, {'A', 2}, {'S', 3}, {'N', 4}};
    int findBest(const vvi& allocations)
    { 
        vi start = {0, 1, 2, 3, 4};
        int S = allocations.size();
        vi diff_xs(S, INT32_MAX);
        do
        {
            int idx = -1;
            int diff = 0;
            for(int i = 0; i < S; i++)
            {
                int local = 0;
                vi xs = allocations[i];
                for(int j = 0; j < xs.size(); j++)
                  if(start[j] != xs[j]) local++; 
                if(local == 0) idx = i;
                diff += local;
            }
            if(idx != -1) diff_xs[idx] = diff;
        }
        while(std::next_permutation(start.begin(), start.end()));
        return 1 + std::min_element(diff_xs.begin(), diff_xs.end()) - diff_xs.begin();
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        std::string l;
        vvi allocations;
        while(std::getline(std::cin, l) && l != "#")
        {
            if(l == "e" || l == "ecclesiastical")
            { 
                std::cout << findBest(allocations) << std::endl;
                allocations.clear(); 
            }
            else
            {
                vi tmp(5);
                for(int i = 0; i < l.length(); i += 4)
                {
                    std::string sub = l.substr(i, 3);
                    auto idx = sub.front();
                    auto w = sub.back();
                    tmp[bins[idx]] = wastes[w];
                }
                allocations.push_back(tmp);
            }
        }
    }
}