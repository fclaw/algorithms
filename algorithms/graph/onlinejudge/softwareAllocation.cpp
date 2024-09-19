#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "../edmonds_karp.cpp"


namespace algorithms::graph::onlinejudge::sa
{

typedef std::tuple<char, int, std::vector<int>> app;
namespace mf = algorithms::graph::mf;


    /**
     *  modelling graph flow problem where vertices are applications (1 .. 26), computers (27 .. 36) 
     *  and two special vertices source (0) and sink (37).
     * Then, we link apps to computers as mentioned int he problem description. We link source
     * s to all apps and link all computers to sink t. All edges in this flow graph are directed edges.
     * The problem says that there can be more than one (say, X) users bringing in a particular
     * app A in a given day. Thus, we set the edge weight (capacity) from source s to a particular
     * app A to X. The problem also says that each computer can only be used once. Thus, we
     * set the edge weight from each computer B to sink t to 1. The edge weight between apps to
     * computers isset to ∞. With this arrangement at hand, if there is a flow from an app A to a computer
     * B and finally to sink t, that flow corresponds to one matching between that particular app A and computer B.
     * Once we have this flow graph, we can pass it to our Edmonds Karp’s implementation
     * shown earlier to obtain the Max Flow mf. If mf is equal to the number of applications
     * brought in that day, then we have a solution, i.e. if we have X users bringing in app A, then
     * X different paths (i.e. matchings) from A to sink t must be found by the Edmonds Karp’s
     * algorithm (and similarly for the other apps). 
     * The actual app → computer assignments can be found by simply checking the backward
     * edges from computers (vertices 27 - 36) to apps (vertices 1 -26). A backward edge (computer
     * → app) in the residual matrix res will contain a value +1 if the corresponding forward edge
     * (app → computer) is selected in the paths that contribute to the Max Flow mf. This is also
     * the reason why we start the flow graph with directed edges from apps to computers only */
    const int source = 0;
    const int sink = 37;
    const int inf = 5 * 1e+05;
    int appToVertex(char app) { return (int)app - 64; }
    int vertexToApp(int v) { return (char)(v + 64); }
    int compToVertex(int comp) { return comp + 27; }
    std::string canAllocateApps(const std::vector<app>& apps) 
    {
        mf::MAX_V = 38;
        mf::residual_graph.resize(mf::MAX_V);
        for(auto& x : mf::residual_graph)
          x.resize(mf::MAX_V);

        for(int i = 0; i < mf::MAX_V; i++)
          for(int j = 0; j < mf::MAX_V; j++)
            mf::residual_graph[i][j] = 0;

        for(auto a : apps)
        {
            char app;
            int w;
            std::vector<int> xs;
            std::tie(app, w, xs) = a;
            mf::residual_graph[source][appToVertex(app)] = w;
            for(int x : xs)
            {
                mf::residual_graph[appToVertex(app)][compToVertex(x)] = inf;
                mf::residual_graph[compToVertex(x)][sink] = 1;
            }
        }

        mf::source = 0;
        mf::sink = 37;
        mf::edmonds_karp();

        std::string ans(10, '_');

        for(int i = 27; i < mf::MAX_V; i++)
          for(int j = 1; j < 27; j++)
            if(mf::residual_graph[i][j] == 1)
              ans[i - 27] = vertexToApp(j);

        bool isAll = true;
        for(auto t : apps)
        {
            auto cnt = std::count(ans.begin(), ans.end(), std::get<0>(t));
            isAll &= (cnt == std::get<1>(t));
        }

        return isAll ? ans : "!";
    }
}
