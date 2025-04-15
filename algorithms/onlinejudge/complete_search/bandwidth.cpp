#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <sstream>
#include <utility>
#include <cctype>
#include <unordered_set>






typedef std::vector<int> vi;
typedef std::vector<std::pair<int, vi>> vpivi;


int charToIndex(char ch)  { return ch - 'A'; }

char indexToChar(int idx) { return idx + 'A'; }

namespace algorithms::onlinejudge::complete_search::bandwidth
{
    /** https://onlinejudge.org/external/1/140.pdf, 
     * max n is just 8, use next permutation; 
     * the algorithm inside next permutation is iterative */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        std::string in, cleaned;

        while(std::getline(std::cin, in) && in != "#")
        {
            cleaned.clear();
            // Remove all spaces
            for (char c : in)
              if(!isspace(c)) cleaned += c;

            std::unordered_set<int> real_vertices;
            vpivi graph;

            std::istringstream ss(cleaned);
            std::string token;
            
            while (std::getline(ss, token, ';')) 
            {
                if (token.empty()) continue;
            
                char node = token[0];
                int from = charToIndex(node);
                real_vertices.insert(from);
                std::vector<int> neighbors;
            
                for (size_t i = 2; i < token.size(); ++i)
                  if(std::isalpha(token[i]))
                  {
                      int neigh = charToIndex(token[i]);
                      real_vertices.insert(neigh);
                      neighbors.push_back(neigh);
                  }
            
                graph.emplace_back(from, neighbors);
            }

            vi ordering(real_vertices.begin(), real_vertices.end());
            std::sort(ordering.begin(), ordering.end());

            vi min_ordering;
            int min_bandwidth = INT32_MAX;
            do
            {
                // The bandwidth of the ordering is then defined as the maximum of the individual bandwidths
                int bandwidth = INT32_MIN;
                for(auto& p : graph)
                  for(int neigh : p.second)
                  {
                     auto it_p = std::find(ordering.begin(), ordering.end(), p.first);
                     auto it_n = std::find(ordering.begin(), ordering.end(), neigh);
                     int d = std::abs(std::distance(it_p, it_n));
                     bandwidth = std::max(bandwidth, d);
                  }
    
                // If more than one ordering produces the same bandwidth, then choose the smallest
                // in lexicographic ordering, that is the one that would appear first in an alphabetic listing.
                if(bandwidth == min_bandwidth)
                  min_ordering = std::min(min_ordering, ordering);
                else if(bandwidth < min_bandwidth)
                { min_ordering = ordering; min_bandwidth = bandwidth; }
    
            }
            while(std::next_permutation(ordering.begin(), ordering.end()));
    
            std::string s;
            for(int idx : min_ordering)
              if(real_vertices.count(idx))
              { s += indexToChar(idx); s += " "; }
    
            printf("%s-> %d\n", s.c_str(), min_bandwidth);
        }
    }
}