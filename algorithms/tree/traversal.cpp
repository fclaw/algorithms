#include <vector>
#include <unordered_map>

using Tree = std::unordered_map<int, std::vector<int>>;

namespace algorithms::tree
{
    void dfs(Tree tree, int node, int prev, void (*process)(int))
    {
        // process(node); pre-order:first process the root node,then traverse the left subtree,then traverse the right subtree

        // a typical way to traverse a tree is to start a depth-first search at an arbitrary node. 
        // The following recursive function can be used:
        for (auto x : tree[node])
          if(x != prev) dfs(tree, x, node, process);

        process(node); // post-order: first traverse the left subtree, then traverse the right subtree, then process the root node  
    }
}