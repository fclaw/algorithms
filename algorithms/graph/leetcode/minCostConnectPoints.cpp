#include <vector>

namespace algorithms::graph::leetcode::kruskal
{

using points = std::vector<std::vector<int>>;
using graph = std::vector<std::pair<int, std::pair<int, int>>>;

class DSU { 
    int* parent; 
    int* rank; 
public: 
    DSU(int n) 
    { 
        parent = new int[n]; 
        rank = new int[n]; 
  
        for (int i = 0; i < n; i++) { 
            parent[i] = -1; 
            rank[i] = 1; 
        } 
    } 
  
    // Find function 
    int find(int i) 
    { 
        if (parent[i] == -1) 
            return i; 
  
        return parent[i] = find(parent[i]); 
    } 
  
    // Union function 
    void unite(int x, int y) 
    { 
        int s1 = find(x); 
        int s2 = find(y); 
  
        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) { 
                parent[s1] = s2; 
            } 
            else if (rank[s1] > rank[s2]) { 
                parent[s2] = s1; 
            } 
            else { 
                parent[s2] = s1; 
                rank[s1] += 1; 
            } 
        } 
    } 
};

    /**
     *  https://leetcode.com/problems/min-cost-to-connect-all-points
     *  You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
     *  The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, 
     *  where |val| denotes the absolute value of val.
     *  Return the minimum cost to make all points connected.
     *  All points are connected if there is exactly one simple path between any two points.
     *  Hint: Connect each pair of points with a weighted edge, the weight being the manhattan distance between those points.
     *  the task simply comes down to finding MST on a graph
     */
    int V;
    int minCostConnectPoints(const points& ps)
    {
        int n = ps.size();
        V = ps.size();
        graph edges;
        for(int i = 0; i < n; i++)
          for(int j = i + 1; j < n; j++)
          {
               int w = 
                 std::abs(ps[i][0] - ps[j][0]) +
                 std::abs(ps[i][1] - ps[j][1]);
               edges.push_back({w, {i, j}});
          }

       std::sort(edges.begin(), edges.end());
       int mst = 0;
       DSU uf(V);
       for(auto e : edges)
       {
           int x = e.second.first;
           int y = e.second.second;
           if(uf.find(x) != uf.find(y))
           {
              uf.unite(x, y);
              mst += e.first;
           }
       }
       return mst;
    }
}