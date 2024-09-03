#include <vector>
#include <queue>

namespace algorithms::graph::leetcode::snake
{

using grid = std::vector<std::vector<int>>;
using vi = std::vector<std::vector<std::vector<bool>>>;
using dist = std::vector<std::vector<std::vector<int>>>;
using cell = std::pair<int, int>;
using state = std::pair<cell, int>;


    /**
     * https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations
     * In an n * n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). 
     * The grid has empty cells represented by zeros and blocked cells represented by ones. 
     * The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
     * In one move the snake can:
     * Move one cell to the right if there are no blocked cells there. 
     * This move keeps the horizontal/vertical position of the snake as it is.
     * Move down one cell if there are no blocked cells there. 
     * This move keeps the horizontal/vertical position of the snake as it is.
     * Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. 
     * In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c)
     * hint: The state of the BFS is the position (x, y) along with a binary value that specifies if the position is horizontal or vertical. */
    enum Pos { H = 0, V = 1 };
    const int inf = 5 * 1e+05;
    const int Empty = 0;
    const int Block = 1;
    int M, N;
    vi visited;
    dist distance;
    bool checkBoundary(int y, int x)
    { return y >= 0 && y < M && x >= 0 && x < N; }
    bool checkHorizontalRightMove(const grid& g, const state& s) 
    {
        int y = s.first.first;
        int x = s.first.second + 1; // head
        return checkBoundary(y, x) && !visited[H][y][x] && g[y][x] == Empty;
    }
    bool checkVerticalRightMove(const grid& g, const state& s) 
    {
        int head_y = s.first.first;
        int head_x = s.first.second + 1;
        int tail_y = s.first.first - 1;
        int tail_x = s.first.second + 1;
        return 
          checkBoundary(head_y, head_x) &&
          checkBoundary(tail_y, tail_x) && 
          !visited[V][head_y][head_x] && 
          !visited[V][tail_y][tail_x] && 
          g[head_y][head_x] == Empty &&
          g[tail_y][tail_x] == Empty;
    }
    bool checkHorizontalDownMove(const grid& g, const state& s)
    {
        int head_y = s.first.first + 1;
        int head_x = s.first.second;
        int tail_y = s.first.first + 1;
        int tail_x = s.first.second - 1;
        return 
          checkBoundary(head_y, head_x) &&
          checkBoundary(tail_y, tail_x) && 
          !visited[H][head_y][head_x] && 
          !visited[H][tail_y][tail_x] &&
          g[head_y][head_x] == Empty && 
          g[tail_y][tail_x] == Empty;
    }
    bool checkVerticalDownMove(const grid& g, const state& s) 
    {
        int y = s.first.first + 1;
        int x = s.first.second;
        return checkBoundary(y, x) && !visited[V][y][x] && g[y][x] == Empty;
    }
    bool checkClockwiseMove(const grid& g, const state& s) 
    {
        int y = s.first.first + 1;
        int x = s.first.second - 1;
        int aux_below_y = s.first.first + 1;
        int aux_below_x = s.first.second;
        return 
          checkBoundary(y, x) &&
          checkBoundary(aux_below_y, aux_below_x) && 
          !visited[V][y][x] &&
          g[y][x] == Empty &&
          g[aux_below_y][aux_below_x] == Empty;
    }
    bool checkCounterClockwiseMove(const grid& g, const state& s) 
    {
        int y = s.first.first - 1;
        int x = s.first.second + 1;
        int aux_right_y = s.first.first;
        int aux_right_x = s.first.second + 1;
        return 
          checkBoundary(y, x) && 
          checkBoundary(aux_right_y, aux_right_x) && 
          !visited[H][y][x] &&
          g[y][x] == Empty && 
          g[aux_right_y][aux_right_x] == Empty;
    }
    void bfs(const grid& g, std::queue<state> q)
    {
        while(!q.empty())
        {
            state s = q.front();
            q.pop();
            int curr_y = s.first.first;
            int curr_x = s.first.second;
            int p = s.second;
            if(p == H && checkHorizontalRightMove(g, s))
            {
                //  If the snake is horizontal, move the head to (r, c + 1)
                int y = curr_y;
                int x = curr_x + 1; // head
                visited[H][y][x] = true;
                distance[H][y][x] = distance[p][curr_y][curr_x] + 1;
                q.push({{y, x}, H});

            } //... 
            if(p == V && checkVerticalRightMove(g, s))
            {
                // If the snake is vertical, you can move both the head and tail to the next column in one step. 
                // Head to (r, c + 1), tail to (r - 1, c + 1)
                int head_y = curr_y;
                int head_x = curr_x + 1;
                int tail_y = curr_y - 1;
                int tail_x = curr_x + 1;
                visited[V][head_y][head_x] = 
                visited[V][tail_y][tail_x] = true;
                distance[V][head_y][head_x] = distance[p][curr_y][curr_x] + 1;
                q.push({{head_y, head_x}, V});

            } //...
            if(p == H && checkHorizontalDownMove(g, s))
            {
                // If the snake is horizontal, you can move both the head and tail to the next row in one step. 
                // Head to (r + 1, c), tail to (r + 1, c - 1)
                int head_y = curr_y + 1;
                int head_x = curr_x;
                int tail_y = curr_y + 1;
                int tail_x = curr_x - 1;
                visited[H][head_y][head_x] = 
                visited[H][tail_y][tail_x] = true;
                distance[H][head_y][head_x] = distance[p][curr_y][curr_x] + 1;
                q.push({{head_y, head_x}, H});

            } //...
            if(p == V && checkVerticalDownMove(g, s))
            {
                 // If the snake is vertical, move the head to (r + 1, c)
                 int y = curr_y + 1;
                 int x = curr_x;
                 visited[V][y][x] = true;
                 distance[V][y][x] = distance[p][curr_y][curr_x] + 1;
                 q.push({{y, x}, V});

            } //...
            if(p == H && checkClockwiseMove(g, s))
            {
                 // Move the head to (r + 1, c - 1)
                 int y = curr_y + 1;
                 int x = curr_x - 1;
                 int aux_y = curr_y + 1;
                 int aux_x = curr_x;
                 visited[V][y][x] = true;
                 distance[V][y][x] = distance[p][curr_y][curr_x] + 1;
                 q.push({{y, x}, V});                 

            } //...
            if(p == V && checkCounterClockwiseMove(g, s))
            {
                 // Move the head to (r - 1, c + 1)
                 int y = curr_y - 1;
                 int x = curr_x + 1;
                 int aux_y = curr_y;
                 int aux_x = curr_x + 1;
                 visited[H][y][x] = true;
                 distance[H][y][x] = distance[p][curr_y][curr_x] + 1;
                 q.push({{y, x}, H});
            } //...
        }
    }
    int minimumMoves(const grid& g) 
    {
        M = g.size();
        N = g[0].size();
        std::queue<state> q;
        visited = vi(2, std::vector<std::vector<bool>>(M, std::vector<bool>(N, false))); // 2 cells occupied
        distance = dist(2, std::vector<std::vector<int>>(M, std::vector<int>(N, inf))); // only head cell counts
        q.push({{0, 1}, H});
        visited[H][0][0] = true;
        visited[H][0][1] = true;
        distance[H][0][1] = 0;
        bfs(g, q);
        int ans = distance[H][M - 1][N - 1];
        return ans != inf ? ans : -1;
    }
}