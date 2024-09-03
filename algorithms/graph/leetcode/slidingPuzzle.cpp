#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

namespace algorithms::graph::leetcode::sliding_puzzle
{

using board = std::vector<std::vector<int>>;
using state = std::string;
using node = std::tuple<int, state>;
using dist = std::unordered_map<std::string, int>;

    /**
     * https://leetcode.com/problems/sliding-puzzle/?envType=problem-list-v2&envId=breadth-first-search
     * On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. 
     * A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
     * The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
     * Given the puzzle board board, return the least number of moves required so that the state of the board is solved. 
     * If it is impossible for the state of the board to be solved, return -1 
     * Perform a breadth-first-search, where the nodes are the puzzle boards and 
     * edges are if two puzzle boards can be transformed into one another with one move.
     * the final arrangement: 1, 2, 3, 4, 0, 5 */
    const int R = 2;
    const int C = 3;
    const std::string touchstone = "123450";
    const std::vector<int> shifts = {-1 /* left */ , 1 /* right */ , 3 /* down */, -3 /* up */};
    bool checkBoundary(int i) { return i >= 0 && i < R * C; }
    dist distance;
    std::string origin;
    std::vector<std::pair<int, std::string>> generateStates(int idx, state s) 
    {
        std::vector<std::pair<int, std::string>> acc;
        state tmp;
        for(auto shift : shifts)
          if(checkBoundary(idx + shift))
          {
              if(idx == 2 && idx + shift == 3 || 
                 idx == 3 && idx + shift == 2)
                continue;
              tmp = s;
              std::swap(tmp[idx], tmp[idx + shift]);
              acc.push_back({idx + shift, tmp});
          }
        return acc;
    }
    void bfs(std::queue<node>& q) 
    {
        while(!q.empty())
        {
            int idx;
            state s;
            node n = q.front();
            q.pop();
            std::tie(idx, s) = n;
            for(auto x : generateStates(idx, s))
            {
                if(distance.find(x.second) != 
                   distance.end())
                  continue;
                distance[x.second] = distance[s] + 1;
                q.push({x.first, x.second});
            }
        }
    };
    int slidingPuzzle(const board& b)
    {
        state s = "";
        for(int r = 0; r < R; r++)
          for(int c = 0; c < C; c++)
            s += std::to_string(b[r][c])[0];

        std::queue<node> q;
        int zero_idx = std::find(s.begin(), s.end(), '0') - s.begin();
        q.push({zero_idx, s});
        distance[s] = 0;
        bfs(q);
        auto path = distance.find(touchstone);
        return path == distance.end() ? -1 : (*path).second;
    }
}