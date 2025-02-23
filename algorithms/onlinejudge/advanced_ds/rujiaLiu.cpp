#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>

typedef std::vector<int> vi;
typedef std::unordered_map<int, vi> mivi;

namespace algorithms::onlinejudge::advanced_ds::rujia_liu
{
    /** https://onlinejudge.org/external/119/11991.pdf, use the idea of an Adj List */
    
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int K, N;
        while(std::cin >> K >> N && K && N)
        {
            mivi adjList;
            int v, k;
            for(int i = 0; i < K; i++)
            { std::cin >> v; adjList[--v].push_back(i); }

            for(int j = 0; j < N; j++)
            {
                std::cin >> k >> v;
                --v;
                --k;
                std::cout << (adjList.find(v) != adjList.end() && k < adjList[v].size() ? adjList[v][k] + 1 : 0) << std::endl;
            }
        }
    }
}