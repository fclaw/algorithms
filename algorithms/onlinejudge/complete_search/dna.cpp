#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>



typedef std::vector<std::string> vs;

namespace algorithms::onlinejudge::complete_search::dna
{
    /** https://onlinejudge.org/external/119/11961.pdf,
     * there are at most 4^10 possible DNA strings; moreover,
     * the mutation power is at most K ≤ 5 so the search space is much smaller;
     * sort the output and then remove duplicates */
    int N, K;
    std::vector<char> els = {'A', 'G', 'C', 'T'};
    void backtrack(std::string& dna, int d, int mask, vs& mutations)
    {
        if(d == K)
        { mutations.push_back(dna); return; }

        for(int i = 0; i < dna.size(); i++)
          if(!(mask & (1 << i)))
            for(int k = 0; k < els.size(); k++)
            {
                char tmp = dna[i];
                dna[i] = els[k];
                backtrack(dna, d + 1, mask | (1 << i), mutations);
                dna[i] = tmp;
            }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            scanf("%d %d", &N, &K);
            std::string dna;
            std::cin >> dna;
            vs mutations = {dna};
            backtrack(dna, 0, 0, mutations);
            std::sort(mutations.begin(), mutations.end());
            mutations.erase(std::unique(mutations.begin(), mutations.end()), mutations.end());
            std::cout << mutations.size() << std::endl;
            for(auto m : mutations) std::cout << m << std::endl;
        }
    }
}