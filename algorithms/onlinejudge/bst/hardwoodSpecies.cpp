#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>


typedef std::unordered_map<std::string, int> msi; 
typedef std::vector<std::pair<std::string, double>> vp;

namespace algorithms::onlinejudge::bst::hardwood_species
{
    // https://onlinejudge.org/external/102/10226.pdf, 
    // use hashing for a better performance
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        std::cin.ignore();
        std::cin.ignore();
        while(tc--)
        {
            msi species;
            std::string tree;
            int N = 0;
            while(std::getline(std::cin, tree), !tree.empty())
            { ++species[tree]; ++N; }
            
            vp frequencies;
            for(auto it : species)
              frequencies.push_back({it.first, it.second});

            std::sort(frequencies.begin(), frequencies.end());

            for(auto p : frequencies)
              std::cout << p.first << " " << std::setprecision(4) << std::fixed << p.second / N * 100.0 << std::endl;

            if(tc) std::cout << std::endl;
        }
    }
}