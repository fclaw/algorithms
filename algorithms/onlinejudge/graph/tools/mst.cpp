#include "dfs.cpp"


namespace algorithms::onlinejudge::graph::tools
{
    template <typename T = Unit, typename W = int>
    struct WNode
    {
        int node;
        W weight;
        T value;
    };

    template <typename T, typename W>
    using WGraph = std::vector<std::vector<WNode<T, W>>>;
}