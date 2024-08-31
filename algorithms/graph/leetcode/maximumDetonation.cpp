#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::bombs_detonation
{

using graph = std::vector<std::vector<int>>;
using point = std::pair<int, int>;

    /**
     * https://leetcode.com/problems/detonate-the-maximum-bombs
     * You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. 
     * This area is in the shape of a circle with the center as the location of the bomb.
     * The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. 
     * xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, 
     * whereas ri denotes the radius of its range.
     * You may choose to detonate a single bomb. When a bomb is detonated, 
     * it will detonate all bombs that lie in its range. 
     * These bombs will further detonate the bombs that lie in their ranges.
     * Given the list of bombs, return the maximum number of bombs that can be detonated 
     * if you are allowed to detonate only one bomb. 
     * hints: 
     *   Bombs are nodes and are connected to other bombs in their range by directed edges.
     *   Run a Depth First Search (DFS) from every node, and all the nodes it reaches are the bombs that will be detonated.
     * */
    int S;
    std::vector<bool> visited;
    int max_detonation = 0;
    bool isAffected(const point& pivot, const point& t, int radius)
    {
        int dx = std::abs(pivot.first - t.first);
        int dy = std::abs(pivot.second - t.second);
        return radius * radius >= dx * dx + dy * dy; 
    }
    void bfs(const graph& g, int i) 
    {
        std::queue<int> q;
        q.push(i);
        visited[i] = true;
        int max = 1;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(auto v : g[u])
            {
                if(visited[v]) continue;
                max++;
                visited[v] = true;
                q.push(v);
            }
        }
        max_detonation = std::max(max_detonation, max);
    }
    int maximumDetonation(const std::vector<std::vector<int>>& bombs)
    {
        S = bombs.size();
        graph g(S);
        for(int i = 0; i < S; i++)
        {
            std::vector<int> affected;
            for(int j = 0; j < S; j++)
            {
                point p = {bombs[i][0], bombs[i][1]};
                point t = {bombs[j][0], bombs[j][1]};
                int r = bombs[i][2];
                if(i != j && isAffected(p, t, r))
                  affected.push_back(j);
            }
            g[i] = affected;
        }

        for(int i = 0; i < S; i++) 
        {
            visited = std::vector<bool>(S, false);
            if(!visited[i]) bfs(g, i);
        }
        return max_detonation;
    }
}