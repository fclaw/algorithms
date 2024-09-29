#include <vector>
#include <unordered_set>
#include <cassert>
#include <cstdio>
#include "../edmonds_karp.cpp"

namespace algorithms::graph::onlinejudge::sabotage
{

typedef std::vector<std::vector<int>> adj_matrix;
typedef std::vector<int> vv;
typedef std::unordered_set<int> sv;
typedef std::vector<std::pair<int, int>> vp;
namespace mf = algorithms::graph::max_flow;

    /** https://onlinejudge.org/external/104/10480.pdf */
    void performEdmondsKarp(int V, int capital, int major, const adj_matrix& graph) 
    {
        mf::MAX_V = V;
        mf::source = capital;
        mf::sink = major;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = graph[i][j];

        mf::edmonds_karp();
    }

    /** dfs based function to find all reachable vertices from s. 
     *  The function marks visited[i] as true if i is reachable from s. 
     *  The initial values in visited[] must be false. 
     * We can also use BFS to find reachable vertices */
    void reachableVertices(int V, int s, sv& visited)
    {
        visited.insert(s);
        for (int i = 0; i < V; i++)
          if(mf::residual_graph[s][i] && 
             visited.find(i) == visited.end())
            reachableVertices(V, i, visited);
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(freopen(file.value(), "r", stdin) != NULL);

        int vertices, edges;
        while(true)
        {
            std::cin >> vertices >> edges;
            if(vertices == 0 && edges == 0) break;
            ++vertices;
            adj_matrix graph = adj_matrix(vertices, vv(vertices));
            for(int i = 0; i < edges; i++)
            {
                int from, to, w;
                std::cin >> from >> to >> w;
                --from; --to;
                graph[from][to] = w;
                graph[to][from] = w;
            }
            
            int capital = 0, major = 1;
            performEdmondsKarp(vertices, capital, major, graph);

            sv visited;
            reachableVertices(vertices, capital, visited);

            vp ans;
            for(auto v : visited)
              for(int i = 0; i < vertices; i++)
                 if(auto it = visited.find(i); 
                    it == visited.end() &&
                    graph[v][i])
                ans.push_back({v, i});

            for(auto p : ans) printf("%d %d\n", ++p.first, ++p.second);
            cout << std::endl;
        }
    }
}