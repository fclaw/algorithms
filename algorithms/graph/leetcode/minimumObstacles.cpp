#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>


namespace algorithms::graph::leetcode::minimum_obstacles
{

struct cell_hash {
    size_t operator()(const std::pair<int, int>& p) const
    {
        // Hash the first element
        size_t first_hash = std::hash<int>{}(p.first);
        // Hash the second element
        size_t second_hash = std::hash<int>{}(p.second);
        // Combine the two hash values
        return first_hash ^ (second_hash + 0x9e3779b9 + (first_hash << 6) + (second_hash >> 2));
    }
};

using grid = std::vector<std::vector<int>>;
using cell = std::pair<int, int>;
using state = std::pair<int, cell>;
using vi = std::unordered_set<cell, cell_hash>;
using queue = std::priority_queue<state, std::vector<state>, std::greater<state>>;

    /**
     * https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner
     * You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
     * 0 represents an empty cell,
     * 1 represents an obstacle that may be removed.
     * You can move up, down, left, or right from and to an empty cell.
     * Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) 
     * to the lower right corner (m - 1, n - 1) */
    const int EMPTY = 0;
    const int OBSTACLE = 1;
    int M, N;
    vi visited;
    std::vector<std::pair<int, int>> dirs = 
    { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int y, int x)
    { return y >= 0 && y < M && x >= 0 && x < N; }
    int bfs(const grid& g, queue& q)
    {
        int ans = 0;
        while(!q.empty())
        {
            state s = q.top();
            q.pop();
            int c_r = s.second.first;
            int c_c = s.second.second;
            int cnt = s.first;
            if(c_r == M - 1 && 
               c_c == N - 1)
            {
                ans = cnt;
                break;
            }
            
            for(auto d : dirs)
            {
                int r = c_r + d.first;
                int c = c_c + d.second;
                if(!checkBoundary(r, c))
                  continue;
                
                if(auto it = visited.find({r, c}); 
                   it != visited.end())
                  continue;

                visited.insert({r, c});
                int p = g[r][c] == OBSTACLE ? cnt + 1 : cnt;
                q.push({p, {r, c}});
            }
        }
        return ans;
    }
    int minimumObstacles(const grid& g) 
    {
        M = g.size();
        N = g[0].size();
        queue q;
        q.push({0, {0, 0}});
        visited.insert({0, 0});
        return bfs(g, q);
    }
}