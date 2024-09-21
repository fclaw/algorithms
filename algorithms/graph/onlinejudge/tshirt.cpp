#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include "../edmonds_karp.cpp"


namespace algorithms::graph::onlinejudge::t_shirt
{

enum T_SHIRT { XXL = 1, XL, L, M, S, XS };
typedef std::vector<std::vector<T_SHIRT>> graph;
namespace mf = algorithms::graph::mf;

    /** https://onlinejudge.org/external/110/11045.pdf 
     * assignment problem; but actually the input constraint is actually small enough for recursive backtracking) */
    int volunteerToVertex(int v) { return v + 7; }
    bool canBeDistributedFairly(int t_shirt_w, int v, const graph& g)
    {
        mf::MAX_V = v + 8;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = 0;

        for(int i = 1; i < 7; i++)
          mf::residual_graph[0][i] = t_shirt_w;
        
        for(int i = 0; i < v; i++)
          for(T_SHIRT t : g[i])
             mf::residual_graph[(int)t][volunteerToVertex(i)] = 1,
             mf::residual_graph[volunteerToVertex(i)][mf::MAX_V - 1] = 1;

        mf::source = 0;
        mf::sink = mf::MAX_V - 1;
        mf::edmonds_karp();

        return mf::max_flow == v;
    }
}

namespace ts = algorithms::graph::onlinejudge::t_shirt;

ts::T_SHIRT toTShirt(std::string s)
{
    ts::T_SHIRT res;
    if(s == "XXL") res = ts::XXL;
    if(s == "XL") res = ts::XL;
    if(s == "L") res = ts::L;
    if(s == "M") res = ts::M;
    if(s == "S") res = ts::S;
    if(s == "XS") res = ts::XS;
    return res;
}

int submit_ts()
{
    int TC;
    scanf("%d", &TC);
    while(--TC >= 0)
    {
        int t_shirts_c, v;
        scanf("%d %d", &t_shirts_c, &v);
        ts::graph g;
        for(int i = 0; i < v; i++)
        {
            std::string s1, s2;
            std::cin >> s1 >> s2;
            std::vector<ts::T_SHIRT> sizes;
            sizes.push_back(toTShirt(s1));
            sizes.push_back(toTShirt(s2));
            g.push_back(sizes);
        }
        bool ans = ts::canBeDistributedFairly(t_shirts_c / 3, v, g);
        printf("%s\n", ans ? "YES" : "NO");
    }
    return 0;
}