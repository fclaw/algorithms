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
    std::ostream& operator << 
    (std::ostream& out, const WNode<T, W>& node) 
    { return out << "{n: " << node.node << ", w: "  << node.weight << "}"; }

    template <typename T = tools::Unit, typename W = int>
    using WGraph = std::vector<std::vector<WNode<T, W>>>;

    template <typename T = tools::Unit, typename W = int>
    WNode<T, W> mkWNode(int n, W w, T v = tools::Unit{}) { return {n, w, v}; }
}