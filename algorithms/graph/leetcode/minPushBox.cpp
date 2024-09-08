#include <vector>
#include <optional>
#include <queue>
#include <string>

namespace algorithms::graph::leetcode::push_box
{

enum Pos { Left, Up, Right, Down };

using grid = std::vector<std::vector<std::string>>;
using cell = std::pair<int, int>;
using vi = std::vector<std::vector<std::vector<bool>>>;
using dist = std::vector<std::vector<std::vector<int>>>;
using state = std::pair<Pos, cell>;

    /**
     * https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location
     * A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
     * The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
     * Your task is to move the box 'B' to the target position 'T' under the following rules:
     * The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
     * The character '.' represents the floor which means a free cell to walk.
     * The character '#' represents the wall which means an obstacle (impossible to walk there).
     * There is only one box 'B' and one target cell 'T' in the grid.
     * The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. 
     * This is a push. The player cannot walk through the box.
     * Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1. 
     * hints: We represent the search state as (player_row, player_col, box_row, box_col).
     * You need to count only the number of pushes. Then inside of your BFS check if the box could be pushed (in any direction) 
     * given the current position of the player */
    const int inf = 5 * 1e+05;
    const std::string BOX = "B";
    const std::string WORKER = "S";
    const std::string DEST = "T";
    const std::string EMPTY = ".";
    const std::string OBS = "#";
    const int D = 4;
    int M, N;
    std::vector<std::pair<int, int>> dirs = 
    { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int y, int x)
    { return y >= 0 && y < M && x >= 0 && x < N; }
    vi visited;
    dist distance;
    std::optional<cell> posToCell(Pos p, const cell& box)
    {
        std::optional<cell> pos = std::nullopt;
        int r = box.first;
        int c = box.second;
        if(p == Left && c - 1 >= 0)
          pos = {r, c - 1};
        if(p == Up && r - 1 >= 0) 
          pos = {r - 1, c};
        if(p == Right && c + 1 < N)
          pos = {r, c + 1};   
        if(p == Down && r + 1 < M)
          pos = {r + 1, c};
        return pos;
    }
    std::optional<cell> move(const grid& g, Pos p, const cell& box)
    {
        std::optional<cell> pos = std::nullopt;
        int r = box.first;
        int c = box.second;
        if(p == Left && 
           c + 1 < N && 
           g[r][c + 1] != OBS)
          pos = {r, c + 1};
        if(p == Up && 
           r + 1 < M && 
           g[r + 1][c] != OBS)
          pos = {r + 1, c};
        if(p == Right && 
           c - 1 >= 0 &&
           g[r][c - 1] != OBS)
          pos = {r, c - 1};
        if(p == Down && 
           r - 1 >= 0 && 
           g[r - 1][c] != OBS)
          pos = {r - 1, c};
        return pos;
    }
    bool bfs_worker(const grid& g, Pos pos, const cell& box, const cell& worker) 
    {
        bool canReach = false;
        auto target = posToCell(pos, box); // target cell
        if(target.has_value())
        {
            cell t = target.value();
            std::vector<std::vector<bool>> visited = 
            std::vector<std::vector<bool>>(M, std::vector<bool>(N, false));
            std::queue<cell> q;
            q.push(worker);
            visited[worker.first][worker.second] = true;
            while(!q.empty())
            {
                cell u = q.front();
                q.pop();
                if(u == t)
                {
                    canReach = true;
                    break;
                }
                for(auto d : dirs)
                {
                    int r = u.first + d.first;
                    int c = u.second + d.second;
                    if(!checkBoundary(r, c) ||
                       (r == box.first && 
                       c == box.second) ||
                       g[r][c] == OBS ||
                       visited[r][c])
                      continue;
                    visited[r][c] = true;
                    q.push({r, c}); 
                }
            }
        }
        return canReach;
    }
    void bfs(const grid& g, std::queue<state>& q, const cell& target)
    {
        bool finished = false;
        while(!q.empty() && !finished)
        {
            auto v = q.front();
            q.pop();
            Pos curr_pos = v.first;
            cell box = v.second;
            if(box == target)
            {
                finished = true;
                break;
            }
            for(int i = 0; i < D; i++)
            {
                if((Pos)i == curr_pos)
                  continue;
                auto wp = posToCell(curr_pos, box);
                if(wp.has_value())
                {
                    cell t = wp.value();
                    if(bfs_worker(g, (Pos)i, box, t))
                    {
                        auto mp = move(g, (Pos)i, box);
                        if(mp.has_value())
                        {
                            cell p = mp.value();
                            if(!visited[(Pos)i][p.first][p.second])
                            {
                                visited[(Pos)i][p.first][p.second] = true;
                                distance[(Pos)i][p.first][p.second] =
                                distance[curr_pos][box.first][box.second] + 1;
                                q.push({(Pos)i, p});
                            }
                        }
                    }
                }
            }

            auto mp = move(g, curr_pos, box);
            if(mp.has_value())
            {
                cell p = mp.value();
                if(!visited[curr_pos][p.first][p.second])
                {
                    visited[curr_pos][p.first][p.second] = true;
                    distance[curr_pos][p.first][p.second] =
                      distance[curr_pos][box.first][box.second] + 1;
                    q.push({curr_pos, p});
                }
            }
        }
    }
    int minPushBox(const grid& g) 
    {
        M = g.size();
        N = g[0].size();
        visited = vi(D, std::vector<std::vector<bool>>(M, std::vector<bool>(N, false)));
        distance = dist(D, std::vector<std::vector<int>>(M, std::vector<int>(N, inf)));
        std::queue<state> q;
        cell target;
        cell box;
        cell worker;
        for(int r = 0; r < M; r++)
          for(int c = 0; c < N; c++)
          {
            if(g[r][c] == BOX) box = {r, c};
            if(g[r][c] == WORKER) worker = {r, c};
            if(g[r][c] == DEST) target = {r, c};
          }
        for(int wp = 0; wp < D; wp++)
        {
            if(bfs_worker(g, (Pos)wp, box, worker))
            {
                q.push({(Pos)wp, box});
                visited[wp][box.first][box.second] = true;
                distance[wp][box.first][box.second] = 0;
            }
        }

        int moves = inf;
        bfs(g, q, target);
        for(int pw = 0; pw < D; pw++)
          moves = std::min(moves, distance[pw][target.first][target.second]);
        return moves == inf ? -1 : moves;
    }
}