#include "dfs.cpp"


namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::tools::wg
{
    template <typename T = tools::Unit, typename W = int>
    struct WNode
    {
        int node;
        W weight;
        T value;
    };

    template <typename T, typename W>
    using WGraph = std::vector<std::vector<WNode<T, W>>>;
}