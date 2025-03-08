#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <set>



typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::set<int> si;

namespace algorithms::onlinejudge::complete_search::hamiltonian_cycle
{
    /** https://onlinejudge.org/external/7/775.pdf, 
     backtracking suﬃces because the search space cannot be that big; 
     in a dense graph, it is more likely to have a Hamiltonian cycle, so we can prune early; 
     we do NOT have to find the best one like in TSP problem */
    int V;
    si ans;
    bool isFinished;
    void backtrack(const vvi& graph, int v, si& seq)
    {
        if(!seq.empty() && 
           v == *seq.begin() && 
           seq.size() < V || 
           isFinished) 
          return;

        if(!seq.empty() && 
           v == *seq.begin() &&
           seq.size() == V)
        { 
            ans = seq; 
            isFinished = true;
            return; 
        }

        for(auto u : graph[v])
        {
            if(seq.count(v)) 
              continue;
            seq.insert(v);
            backtrack(graph, u, seq);
            seq.erase(v);
        }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(std::cin >> V)
        {
            isFinished = false;
            ans = {};
            std::string l;
            vvi adjList(V);
            while(std::getline(std::cin, l))
            {
                if(l == "%") break;
                std::stringstream ss(l);
                int from, to;
                while(ss >> from >> to)
                {
                    --from; --to;
                    adjList[from].push_back(to);
                    adjList[to].push_back(from);
                }
            }
            si seq;
            backtrack(adjList, 0, seq);
            if(!ans.empty())
            {
                for(auto v : ans)
                { std::cout << v + 1 << " "; }
                std::cout << 1 << std::endl;
            }
            else std::cout << "N" << std::endl;
        }
    }
}