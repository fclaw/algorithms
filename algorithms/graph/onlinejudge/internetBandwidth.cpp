#include <string>
#include <vector>
#include "../edmonds_karp.cpp"


namespace algorithms::graph::onlinejudge::ib
{

typedef std::vector<std::tuple<int, int, int>> graph;
namespace mf = algorithms::graph::mf;

    /** https://onlinejudge.org/external/8/820.pdf */
    int calculateBandwidth(int v, int source, int sink, const graph& g)
    {
        mf::MAX_V = v;
        mf::source = source;
        mf::sink = sink;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = 0;  

        for(auto t : g)
        {
            int from = std::get<0>(t);
            int to = std::get<1>(t);
            int w = std::get<2>(t);
            mf::residual_graph[from][to] = w;
            mf::residual_graph[to][from] = w;
        }

        mf::edmonds_karp();

        return mf::max_flow;
    }
}