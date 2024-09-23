#include <vector>
#include <tuple>
#include <cstdio>
#include <unordered_set>
#include "../edmonds_karp.cpp"

namespace algorithms::graph::onlinejudge::pt
{

typedef int capacity;
typedef std::tuple<int, int, capacity> node;
typedef std::vector<std::tuple<int, int, capacity>> graph;
typedef std::vector<std::pair<int, capacity>> regulators;
namespace mf = algorithms::graph::mf;

const int inf = 5 * 1e+05;

    /** https://onlinejudge.org/external/103/10330.pdf 
     * max flow with vertex capacities
     * there is a Network Flow variant where the capacities are not just defined along the
     * edges but also on the vertices. To solve this variant, we can use vertex splitting technique
     * which (unfortunately) doubles the number of vertices in the flow graph. A weighted graph
     * with a vertex weight can be converted into a more familiar one without vertex weight by
     * splitting each weighted vertex v to v(in) and v(out), reassigning its incoming/outgoing edges to
     * v(in)/v(out), respectively and finally putting the original vertex v’s weight as the weight of edge
     * v(in) → v(out). Now with all weights defined on edges, we can run Edmonds Karp’s as per normal. */
    int determineMaxPower(int V, const graph& g, const regulators& source, const std::vector<int>& regs_sink)
    {
        mf::MAX_V = V;
        mf::source = 0;
        mf::sink = V - 1;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = 0;

        for(node t : g)
        {
            int from = std::get<0>(t);
            int to = std::get<1>(t);
            capacity cap = std::get<2>(t);
            mf::residual_graph[from][to] = cap;
        }

        for(auto p : source) 
          mf::residual_graph[mf::source][p.first] = p.second;
        for(int i = 0; i < regs_sink.size(); i++) 
          mf::residual_graph[regs_sink[i]][mf::sink] = inf;

        mf::edmonds_karp();

        return mf::max_flow;
    }
}

namespace pt = algorithms::graph::onlinejudge::pt;

void submit_pt()
{
    int cap_n; // the number of regulators
    while((bool)scanf("%d", &cap_n) == 1)
    {
        std::vector<int> caps(cap_n + 1);
        for(int i = 1; i <= cap_n; i++)
            scanf("%d", &caps[i]);

        int e;
        scanf("%d", &e);
        pt::graph g;
        while(--e >= 0)
        {
            int from, to, c;
            scanf("%d %d %d", &from, &to, &c);
            g.push_back({from, to, c});
        }
        
        int in, out;
        scanf("%d %d", &in, &out);
        pt::regulators regs;
        std::vector<int> regs_sink;
        std::unordered_set<int> regs_taken;
        int start = cap_n;
        for(int i = 0; i < in + out; i++)
        {
            int r;
            scanf("%d", &r);
            regs_taken.insert(r);
            if(i < in) 
            {
                int to = ++start;
                for(auto& t : g)
                if(std::get<0>(t) == r)
                   std::get<0>(t) = to;
                g.push_back({r, to, caps[r]});    
                regs.push_back({r, caps[r]});
            }
            if(i >= in) regs_sink.push_back(r);
        }

        // split the regulator=-sink vertex into v(int)/v(out)
        for(int i = 0; i < regs_sink.size(); i++)
        {
            int from = regs_sink[i];
            int to = ++start;
            for(auto& t : g)
              if(std::get<0>(t) == from)
                 std::get<0>(t) = to;
            g.push_back({from, to, caps[from]});
            regs_sink[i] = to;
        }

        // all regulators except for ones incident to either source or sink
        for(int i = 1; i <= cap_n; i++)
          if(regs_taken.find(i) == 
             regs_taken.end())
          {
               int v = ++start;
                for(auto& t : g)
                 if(std::get<0>(t) == i)
                    std::get<0>(t) = v;
                 g.push_back({i, v, caps[i]});
          }    

        int pw = pt::determineMaxPower(start + 2, g, regs, regs_sink);
        printf("%d\n", pw);
    }
}