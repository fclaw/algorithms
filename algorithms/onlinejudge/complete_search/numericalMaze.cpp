#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <algorithm>



typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::unordered_set<int> si;
typedef std::unordered_map<int, si> misi;
typedef std::vector<std::pair<int, int>> vpii;


namespace algorithms::onlinejudge::complete_search::maze
{
    /** https://onlinejudge.org/external/8/868.pdf, try row 1 to N; 4 ways; some constraints */
    int R, C;
    const size_t SIZE = 30;
    bool solution_found;
    const int SOURCE_ROW = 1;
    std::bitset<SIZE * SIZE> visited;  // For 20x20
    inline bool is_visited(int r, int c) { return visited[r * SIZE + c]; }
    inline void set_visited(int r, int c) { visited.set(r * SIZE + c); }
    inline void clear_visited(int r, int c) { visited.reset(r * SIZE + c); }
    vpii ds = { {0, 1}, /* right */ {0, -1}, /* left */ {1, 0}, /* down */ {-1, 0} /* up */};
    bool checkBoundary(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; }
    void backtrack(const vvi& maze, int c_r, int c_c, int target, int curr, si& sinks)
    {
        if(c_r == R) return;
        if(c_r == R - 1 && 
           ((maze[c_r][c_c] == target) ||  // successfully reached target
            (maze[c_r][c_c] == 1) ||       // start of next sequence
            (curr < target)))
        {
            if(!solution_found) 
              solution_found = true; 
            sinks.insert(c_c); 
            return; 
        }

        for(auto d : ds)
        {
            int r = c_r + d.first;
            int c = c_c + d.second;
            if(!checkBoundary(r, c) || 
               is_visited(r, c))
              continue;

            set_visited(r, c);

            if(curr == target && maze[r][c] == 1)
              backtrack(maze, r, c, target + 1, 1, sinks);
            if(maze[r][c] == curr + 1)
              backtrack(maze, r, c, target, maze[r][c], sinks);

            clear_visited(r, c);  
        }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        std::cin.ignore();
        while(tc--)
        {
            scanf("%d %d\n", &R, &C);
            vvi maze;
            vi sources;
            for(int i = 0; i < R; i++)
            {
                vi row(C);
                for(int j = 0; j < C; j++)
                  std::cin >> row[j];
                maze.push_back(row);  
            }
          
            for(int i = 0; i < C; i++)
              if(maze[0][i] == 1)
                sources.push_back(i);

            misi solutions;
            for(int s : sources) 
            {
                si sinks;
                solution_found = false;
                set_visited(0, s);
                backtrack(maze, 0, s, 1, 1, sinks);
                visited.reset();
                if(solution_found)
                { solutions[s] = sinks; solution_found = false; }
            }

            int source = INT32_MAX, sink = INT32_MAX;
            for (const auto& [start, sinks] : solutions) 
            {
                int min_sink = *std::min_element(sinks.begin(), sinks.end());
                if (start < source || 
                    (start == source &&
                     min_sink < sink))
                { source = start; sink = min_sink; }
            }
            std::cout << SOURCE_ROW << " " << source + 1 << std::endl;
            std::cout << R << " " << sink + 1 << std::endl;
            if(tc > 0) std::cout << std::endl;
        }
    }
}