#include <string>
#include <vector>
#include "../edmonds_karp.cpp"


namespace algorithms::graph::onlinejudge::ib
{

typedef std::vector<std::tuple<int, int, int>> graph;
namespace mf = algorithms::graph::max_flow;

    /** https://onlinejudge.org/external/8/820.pdf */
    int calculateBandwidth(int v, int source, int sink, const graph& g)
    {
        mf::MAX_V = v;
        mf::source = source;
        mf::sink = sink;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

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

namespace ib = algorithms::graph::onlinejudge::ib;

int submit_ib()
{
    int v, source, sink, c, tc = 1, from, to, w;
    while(scanf("%d", &v), (bool)v)
    {
        scanf("%d %d %d", &source, &sink ,&c);
        --source;
        --sink;
        ib::graph g;
        while(--c >= 0)
          scanf("%d %d %d", &from, &to, &w),
          g.push_back({--from, --to, w});

        int ans = ib::calculateBandwidth(v, source, sink, g);

        printf("Network %d\n", tc++);
        printf("The bandwidth is %d.\n\n", ans);
    }
    return 0;
}