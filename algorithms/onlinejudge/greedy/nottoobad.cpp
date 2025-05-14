#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <cmath>





typedef std::vector<std::string> vs;
typedef std::vector<int> vi;
typedef std::pair<int, vi> pivi;
typedef std::unordered_map<std::string, vi> mapsvi;


mapsvi build_prefix_map(const vs& dictionary) {
    mapsvi prefix_map;
    int n = dictionary.size();
    for (int i = 0; i < n; ++i) {
        const std::string& word = dictionary[i];
        std::string prefix = {};
        for (char ch : word) {
            prefix += ch;
            prefix_map[prefix].push_back(i);
        }
    }
    // Optional: sort each list by word length (ascending)
    for (auto& [prefix, indices] : prefix_map) {
        std::sort(indices.begin(), indices.end(), [&](int a, int b) {
            return dictionary[a].size() < dictionary[b].size();
        });
    }
    return prefix_map;
}


namespace algorithms::onlinejudge::greedy::nottoobad
{
    /** https://onlinejudge.org/external/106/10602.pdf */
    int tc, n;
    pivi backtrack(std::string w, int i, mapsvi& prefix_map, const vs& dictionary, std::unordered_set<int>& used, int n_components, bool& finished)
    {
        if (w.empty() || finished) return {INT32_MAX, {}};
        if((int)used.size() == n_components) 
        { finished = true; return {0, {}}; }
    
        used.insert(i);
        int min_steps = INT32_MAX;
        vi best_path;
        for (int idx : prefix_map[w])
        {
            if(used.count(idx)) continue;
            std::string next = dictionary[idx];
            int diff = (int)next.length() - (int)w.length();
            auto [steps, path] = backtrack(next, idx, prefix_map, dictionary, used, n_components, finished);
            used.erase(idx);
            if (steps != INT32_MAX && 
                diff + steps < min_steps)
            {
                min_steps = diff + steps;
                best_path = path;
                best_path.insert(best_path.begin(), idx);
            }
            if(finished) break;
        }
    
        // Try deleting last character (free operation)
        std::string prefix = w;
        prefix.pop_back();
        auto [steps, path] = backtrack(prefix, i, prefix_map, dictionary, used, n_components, finished);
        if(steps < min_steps)
        { min_steps = steps; best_path = path; }
        return {min_steps, best_path};
    }
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
        std::cin >> tc;
        while(tc--)
        {
            std::cin >> n;
            vs dictionary(n);
            loop(n, [&dictionary](int i) { std::cin >> dictionary[i]; } );
            std::sort(dictionary.begin(), dictionary.end());

            mapsvi prefix_map = build_prefix_map(dictionary);

            std::unordered_set<int> used;
            int min_steps = 0;
            vi min_path;
            // trying all words and find minimum
            for(int i = 0; i < n; i++)
              if(!used.count(i))
              {
                std::unordered_set<int> mask;
                int n_components = prefix_map[std::string(1, dictionary[i].front())].size();
                bool finished = false;
                auto [steps, path] = backtrack(dictionary[i], i, prefix_map, dictionary, mask, n_components, finished);
                steps = steps == INT32_MAX ? 0 : steps;
                path.insert(path.begin(), i);        // ⬅️ ensure start word is included
                for (int idx : path) used.insert(idx);  // ⬅️ now we safely update `used`
                min_steps += (int)dictionary[i].length() + steps;
                min_path.insert(min_path.end(), path.begin(), path.end());
              }
            std::cout << min_steps << std::endl;
            for(int idx : min_path) { std::cout << dictionary[idx] << std::endl; }
        }  
    }
}