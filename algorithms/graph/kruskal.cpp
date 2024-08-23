#include <vector>

namespace algorithms::graph::kruskal
{

using graph = std::vector<std::pair<int, std::pair<int, int>>>;
using edge = std::pair<int, std::pair<int, int>>;

class UnionFind
{
private:
  std::vector<int> link;
  std::vector<int> size;
  /**
   * The function find returns the representative for an element x. 
   * The representative can be found by following the chain that begins at x
   * The time complexity of the function find is O(log n) assuming that the length of each chain is O(log n). 
   * In this case, the functions same and unite also work in O(log(n)) time.
   */
  int find(int x) 
  { 
      while(x != link[x]) 
        x = link[x];
      return x; 
  }
public:
  UnionFind(int el)
  {
      link.resize(el + 1);
      size.resize(el + 1);
      for(int i = 1; i <= el; i++)
      {
          link[i] = i;
          size[i] = 1;
      }
  }
  // The function same checks whether elements a and b belong to the same set
  bool same(int x, int y) 
  { return find(x) == find(y); }
  // The function unite joins the sets that contain elements a and b (the elements have to be in different sets). 
  // The function first finds the representatives of the sets and then connects the smaller set to the larger set
  // The function unite makes sure that the length of each chain is O(log n) by connecting the smaller set to the larger set.
  void unite(int x, int y) 
  {
       int first = find(x);
       int second = find(y);
       if(size[first] > size[second])
       {
          size[first] += size[second];
          link[second] = first;
       }
       else if(first < second)
       {
          size[second] += size[first];
          link[first] = second;
       }
  }
};

   /**
    * The initial spanning tree only contains the nodes of the graph and does not contain any edges. 
    * Then the algorithm goes through the edges ordered by their weights, 
    * and always adds an edge to the tree if it does not create a cycle.
    * The algorithm maintains the components of the tree. 
    * Initially, each node of the graph belongs to a separate component. 
    * Always when an edge is added to the tree, two components are joined. 
    * Finally, all nodes belong to the same component, and a minimum spanning tree has been found
    * A short note on implementation:
    * When implementing Kruskal’s algorithm, it is convenient to use the edge list representation of the graph. 
    * The first phase of the algorithm sorts the edges in the list in O(m * log(m)) time. 
    *  After this, the second phase of the algorithm builds the minimum spanning tree as follows:
    *   for(...) <- goes through edges
    *    if(!same(node1, node2)) union(node1, node2)
    * The loop goes through the edges in the list and always processes an edge a–b where a and b are two nodes. 
    * Two functions are needed: the function same determines if a and b are in the same component, 
    * and the function unite joins the components that contain a and b.
    * The problem is how to efficiently implement the functions same and unite. 
    * One possibility is to implement the function same as a graph traversal and check if we can get from node a to node b. 
    * However, the time complexity of such a function would be O(n + m) and the resulting algorithm would be slow, 
    * because the function same will be called for each edge in the graph.
    * We will solve the problem using a union-find structure that implements both functions in O(log n) time. 
    * Thus, the time complexity of Kruskal’s algorithm will be O(m log n) after sorting the edge list.
    */
   int spanning_tree(int v, const graph& g)
   {
       graph edges = g;
       std::sort(edges.begin(), edges.end());
       int mst = 0;
       UnionFind uf(v);    
       for(auto e : edges)
       {
           int x = e.second.first;
           int y = e.second.second;
           if(!uf.same(x, y))
           {
              uf.unite(x, y);
              mst += e.first;
           }
       }
       return mst;
   }
}

