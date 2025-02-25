#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "../../advanced_ds/unionFind.cpp"


namespace ad = algorithm::advanced_ds;


typedef std::vector<int> vi;
typedef std::unordered_map<int, std::pair<int, vi>> mip;
typedef std::unordered_map<int, int> mi;

namespace algorithms::onlinejudge::advanced_ds::brain
{
    /** https://onlinejudge.org/external/105/10507.pdf, disjoint sets simplifies this problem */
    const size_t MAX = 26;
    int getInt(char c) { return c - 'A'; }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(std::cin >> N && N)
        {
            int C;
            std::cin >> C;
            std::string l;
            mi years;
            ad::UnionFind brain(MAX);
            std::cin >> l;
            int rep = brain.findSet(getInt(l.front()));
            for(auto a : l) 
            { 
                brain.unionSet(rep, getInt(a)); 
                years[getInt(a)] = 0; 
            }
            
            mip nodes;
            while(C--)
            {
                std::cin >> l;
                int from = getInt(l.front());
                int to = getInt(l.back());
                nodes[from].second.push_back(to);
                nodes[to].second.push_back(from);
            }

            bool isResolved = true;
            while(isResolved)
            {
                isResolved = false;
                for(auto n : nodes)
                {
                    if(brain.isSameSet(n.first, rep))
                      continue;
                    int cnt = n.second.first;
                    for(auto c : n.second.second)
                      if(brain.isSameSet(c, rep)) cnt++;
                    if(cnt == 3)
                    {
                        int year = 0;
                        for(auto c : n.second.second)
                          year = std::max(year, years[c]);
                        years[n.first] = year + 1;
                        brain.unionSet(rep, n.first);
                        isResolved = true;
                    }
                }
            }
            
            if(years.size() == N)
            {
                int max_year = 0;
                for(auto y : years)
                  if(y.second > max_year)
                    max_year = y.second;
                printf("WAKE UP IN, %d, YEARS\n", max_year);
            }
            else printf("THIS BRAIN NEVER WAKES UP\n");
        }
    }
}