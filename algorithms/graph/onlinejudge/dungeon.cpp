#include <vector>
#include <string>
#include <queue>

namespace algorithms::graph::onlinejudge::dungeon_master
{

using maze = std::vector<std::vector<std::string>>;
using dir = std::vector<std::pair<int, int>>;
using vi = std::vector<std::vector<std::vector<bool>>>;
using dist = std::vector<std::vector<std::vector<int>>>;
using el = std::tuple<int, int, int>;

    /**
     * https://onlinejudge.org/external/5/532.pdf
     * You are trapped in a 3D dungeon and need to find the quickest way out! The dungeon is composed
     * of unit cubes which may or may not be filled with rock. It takes one minute to move one unit north,
     * south, east, west, up or down. You cannot move diagonally and the maze is surrounded by solid rock
     * on all sides. Is an escape possible? If yes, how long will it take? */
    const std::string obstacle = "#";
    const std::string free = ".";
    const std::string start = "S";
    const std::string end = "E";
    const int inf = 5 * 1e+05;
    int M, N, L;
    bool finished = false;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < M && c >= 0 && c < N; }
    void bfs(const std::vector<maze>& m, std::queue<el>& q, vi& visited, dist& ds) 
    {
        while(!q.empty() && 
              !finished)
        {
            int l, x, y;
            auto v = q.front();
            q.pop();
            std::tie(l, x, y) = v;

            if(m[L - 1][x][y] == end)
            {
                finished = true;
                break;
            }

            for(auto d : dirs)
            {
                int next_x = x + d.first;
                int next_y = y + d.second;
                bool canMove = checkBoundary(next_x, next_y);
                if(!canMove || 
                   visited[l][next_x][next_y] || 
                   m[l][next_x][next_y] == obstacle)
                  continue;
                if(l + 1 < L && 
                   (m[l + 1][next_x][next_y] == free || 
                    m[l + 1][next_x][next_y] == end))
                {
                    visited[l + 1][next_x][next_y] = true;
                    ds[l + 1][next_x][next_y] = ds[l][x][y] + 2;
                    q.push({l + 1, next_x, next_y});
                }
                visited[l][next_x][next_y] = true;
                ds[l][next_x][next_y] = ds[l][x][y] + 1;
                q.push({l, next_x, next_y});
            }
        }      
    }
    int canEscape(int r, int c, const std::vector<maze>& m)
    {
        M = r;
        N = c;
        L = m.size();
        vi visited(L, std::vector<std::vector<bool>>(M, std::vector<bool>(N, false)));
        dist distance(L, std::vector<std::vector<int>>(M, std::vector<int>(N, inf)));
        std::queue<el> q;
        int sx, sy;
        for(int i = 0; i < M; i++)
          for(auto j = 0; j < N; j++)
            if(m[0][i][j] == start)
            {
                sx = i;
                sy = j;
                break;
            }

        int ex, ey;
        for(int i = 0; i < M; i++)
          for(auto j = 0; j < N; j++)
            if(m[L - 1][i][j] == end)
            {
                ex = i;
                ey = j;
                break;
            }
         
        distance[0][sx][sy] = 0;
        visited[0][sx][sy] = true; 
        q.push({0, sx, sy});
        bfs(m, q, visited, distance);
        return distance[L - 1][ex][ey];
    }
}