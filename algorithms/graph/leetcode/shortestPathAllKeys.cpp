#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <queue>

namespace algorithms::graph::leetcode::shortest_path_all_keys
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

using grid = std::vector<std::string>;
using cell = std::pair<int, int>;
using dir = std::vector<std::pair<int, int>>;
using vi = std::vector<std::vector<bool>>;
using dist = std::vector<std::vector<int>>;
using memo = std::unordered_map<cell, std::unordered_map<int, int>, cell_hash>;

    /**
     * https://leetcode.com/problems/shortest-path-to-get-all-keys
     * You are given an m x n grid grid where:
     * '.' is an empty cell.
     * '#' is a wall.
     * '@' is the starting point.
     * Lowercase letters represent keys.
     * Uppercase letters represent locks.
     * You start at the starting point and one move consists of walking one space in one of the four cardinal directions. 
     * You cannot walk outside the grid, or walk into a wall. 
     * If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.
     * For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of 
     * the first k letters of the English alphabet in the grid. 
     * This means that there is exactly one key for each lock, and one lock for each key; 
     * and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
     * Return the lowest number of moves to acquire all keys. If it is impossible, return -1. */
    const int inf = 5 * 1e+05;
    const char PLAYER = '@';
    const char WALL = '#';
    const char EMPTY = '.';
    int M, N, K = 0;
    dir dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    bool checkBoundary(int r, int c)
    { return r >= 0 && r < M && c >= 0 && c < N; }
    bool isLock(const char& c) { return std::isalpha(c) && std::isupper(c); }
    int keyToInt(const char& key) { return (int)key - 97; }
    int lockToInt(const char& lock) { return (int)lock - 65; }
 
    int bfs(const grid& g, const cell& source, const cell& sink, int obtained_keys)
    {
        dist distance = dist(M, std::vector<int>(N, inf));
        vi visited = vi(M, std::vector<bool>(N, false));
        std::queue<cell> q;
        visited[source.first][source.second] = true;
        distance[source.first][source.second] = 0;
        q.push(source);
        bool finished = false;
        while(!q.empty() && !finished)
        {
            auto v = q.front();
            q.pop();
            int c_r = v.first;
            int c_c = v.second;
            if(v.first == sink.first && 
               v.second == sink.second)
            {
                finished = true;
                break;
            }
            for(auto d : dirs)
            {
                int r = c_r + d.first;
                int c = c_c + d.second;
                if(!checkBoundary(r, c) ||
                   g[r][c] == WALL ||
                   visited[r][c] ||
                   (isLock(g[r][c]) &&
                    !(obtained_keys & (1 << lockToInt(g[r][c])))))
                  continue;

                visited[r][c] = true;
                distance[r][c] = distance[c_r][c_c] + 1;
                q.push({r, c});
            }
        }
        return distance[sink.first][sink.second];
    }
    int calculateMinPath(const grid& g, const cell& source, const std::unordered_map<int, cell>& keys, int mask, memo& mt) 
    {
        if(mask == ((1 << K) - 1))
            return 0;

        if(auto it_f = mt.find(source); it_f != mt.end())
          if(auto it_s = (*it_f).second.find(mask); 
             it_s != (*it_f).second.end())
            return (*it_s).second;

        int path = inf;
        for(int k = 0; k < K; k++)
        {
            if((mask & (1 << k)))
              continue;
            auto it = keys.find(k);
            if(auto it = keys.find(k); it != keys.end())
            {
                int res = bfs(g, source, (*it).second, mask);
                if(res != inf)
                  path = std::min(path, res + calculateMinPath(g, (*it).second, keys, (mask | (1 << k)), mt));
            }
        }
        return mt[source][mask] = path;
    }
    int shortestPathAllKeys(const grid& g)
    {
        M = g.size();
        N = g[0].size();
        std::unordered_map<int, cell> keys;
        cell player; // player's initial position
        for(int r = 0; r < M; r++)
          for(int c = 0; c < N; c++)
          {
             if(std::isalpha(g[r][c]) && 
                std::islower(g[r][c]))
            {
               K++;
               keys[keyToInt(g[r][c])] = {r, c};
            }
             if(g[r][c] == PLAYER)
               player = {r, c};  
          }
        memo mt;
        int ans = calculateMinPath(g, player, keys, 0, mt);
        return ans == inf ? -1 : ans;
    }
}