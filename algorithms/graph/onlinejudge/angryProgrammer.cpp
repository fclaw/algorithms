#include <vector>
#include <tuple>
#include <cstdio>
#include <unordered_map>
#include <cassert>
#include "../edmonds_karp.cpp"

namespace algorithms::graph::onlinejudge::angry_programmer
{

typedef int cost;
typedef std::tuple<int, int, cost> edge;
typedef std::vector<edge> graph;
typedef std::vector<std::vector<std::pair<int, int>>> adj;

namespace mf = algorithms::graph::max_flow;

   /** Minimum Cut problem
    *  Let’s define an s-t cut C = (S-component, T-component) as a partition of V ∈ G such that
    *  source s ∈ S-component and sink t ∈ T-component.
    * The by-product of computing Max Flow is Min Cut! 
    * After Max Flow algorithm stops, we run graph traversal (DFS/BFS)
    * from source s again. All reachable vertices from source s using positive weighted edges in 
    * the residual graph belong to the S-component. All other unreachable vertices belong to the T-component (i.e. vertex 1 and 3). 
    * All edges connecting the S-component to the T-component belong to the cut-set of C */
   void performEdmondsKarp(int V, int director, int server, const graph& g)
   {
        mf::MAX_V = V;
        mf::source = director;
        mf::sink = server;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = 0;
        
        for(edge t : g)
        {
            int from = std::get<0>(t);
            int to = std::get<1>(t);
            cost c = std::get<2>(t);
            mf::residual_graph[from][to] = c;
        }

        mf::edmonds_karp();
   }
}

typedef std::unordered_map<int, std::pair<int, int>> mc;
namespace ap = algorithms::graph::onlinejudge::angry_programmer;

void submit_ap(std::optional<char*> file)
{
    if(file.has_value())
      assert(freopen(file.value(), "r", stdin) != NULL);
    int vertices, w;
    while(true)
    {
        std::cin >> vertices >> w;
        if(vertices == 0 && w == 0) break;
        
        int server = vertices - 1;
        int director = 0;
        mc machines;
        int c = vertices - 2;
        while(--c >= 0)
        {
            int i, cost;
            std::cin >> i >> cost;
            if(cost > 0) 
              machines.insert({--i, {vertices++, cost}});
        }

        int directConnection = INT32_MAX;
        ap::graph graph;
        while(--w >= 0)
        {
            int from, to, w;
            std::cin >> from >> to >> w;
            --from; --to;
            if(from == director && 
               to == server)
                directConnection = w;

            if(auto it = machines.find(from); 
               it != machines.end())
            {
                int aux = (*it).second.first;
                int cost = (*it).second.second;
                graph.push_back({from, aux, cost});
                 graph.push_back({aux, from, cost});
                graph.push_back({aux, to, w});
                graph.push_back({to, aux, w});       
            }
            else
              graph.push_back({from, to, w});
              graph.push_back({to, from, w});
        }

        ap::performEdmondsKarp(vertices, director, server, graph);
        printf("%d\n", ap::mf::max_flow);
    }
}
