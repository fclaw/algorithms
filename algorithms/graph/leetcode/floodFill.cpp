#include <vector>
#include <queue>

// https://leetcode.com/problems/flood-fill
/**
 * An image is represented by an m x n integer grid image 
 * where image[i][j] represents the pixel value of the image.
 * You are also given three integers sr, sc, and color. 
 * You should perform a flood fill on the image starting from the pixel image[sr][sc].
 * To perform a flood fill, consider the starting pixel, 
 * plus any pixels connected 4-directionally to the starting pixel of the same color 
 * as the starting pixel, plus any pixels connected 4-directionally 
 * to those pixels (also with the same color), and so on. 
 * Replace the color of all of the aforementioned pixels with color.
 * Return the modified image after performing the flood fill
 */
namespace algorithms::graph::leetcode::flood_fill
{

using matrix = std::vector<std::vector<int>>;
using vi = std::vector<std::tuple<int, int, bool>>;
using iq = std::queue<std::pair<int, int>>;

    int m;
    int n;
    std::vector<std::pair<int, int>> dirs = 
      { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    bool checkBoundary(int r, int c) 
      { return r >= 0 && r < m && c >= 0 && c < n; }
    bool isVisited(vi visited, int r, int c) 
    {
        bool ok = false;
        for(auto t : visited)
        {
            int x, y;
            bool s;
            std::tie(x, y, s) = t;
            if(s && r == x && c == y)
            {
                ok = true;
                break;
            }
        }
        return ok;
    }
    void setVisited(vi& visited, int r, int c) 
    {
        for(auto& t : visited)
        {
            int x, y;
            bool s;
            std::tie(x, y, s) = t;
            if(r == x && c == y)
            {
                t = {x, y, true};
                break;
            }
        }
    }
    void bfs(matrix& img, iq& queue, int prev, int clr, vi& visited)
    {
        while(!queue.empty())
        {
            auto cell = queue.front();
            queue.pop();
            for(auto dr : dirs)
            {
                int x = cell.first;
                int y = cell.second;
                int r = x + dr.first;
                int c = y + dr.second;
                if(checkBoundary(r, c) && 
                   img[r][c] == prev &&
                   !isVisited(visited, r, c))
                {
                    queue.push({r, c});
                    setVisited(visited, r, c);
                    img[r][c] = clr;
                }
            }
        }
    }
    matrix floodFill(matrix& image, int sr, int sc, int colour) 
    {
        m = image.size();
        n = image[0].size();
        vi visited;
        int prev = image[sr][sc];
        image[sr][sc] = colour;
        for(int r = 0; r < m; r++)
          for(int c = 0; c < n; c++)
          {
            if(r == sr && c == sc)
              visited.push_back({r, c, true});
            else if (image[r][c] == prev)
              visited.push_back({r, c, false});
          }
        
        iq queue;
        queue.push({sr, sc});
        bfs(image, queue, prev, colour, visited);
        return image;
    }
}