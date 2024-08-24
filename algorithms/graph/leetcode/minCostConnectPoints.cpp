#include <vector>

namespace algorithms::graph::leetcode::kruskal
{

using points = std::vector<std::vector<int>>;
using graph = std::vector<std::pair<int, std::pair<int, int>>>;

    /**
     *  https://leetcode.com/problems/min-cost-to-connect-all-points
     *  You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
     *  The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, 
     *  where |val| denotes the absolute value of val.
     *  Return the minimum cost to make all points connected.
     *  All points are connected if there is exactly one simple path between any two points.
     */
    int minCostConnectPoints(const points& ps) 
    {
        return 1;
    }
}