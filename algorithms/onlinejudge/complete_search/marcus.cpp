#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>



namespace algorithms::onlinejudge::complete_search::marcus
{

typedef std::vector<std::string> vs;
typedef std::vector<std::tuple<int, int, std::string>> dir;


    /** https://onlinejudge.org/external/104/10452.pdf, 
     * at each pos, Indy can go forth/left/right; try all */
    const std::string GODS_NAME = "IEHOVA#";
    const char start = '@';
    const char finish = '#';
    const std::string forth = "forth";
    const std::string right = "right";
    const std::string left = "left";
    bool isFinished;
    dir dirs = {{0, -1, left}, {0, 1, right}, {-1, 0, forth}};
    int M, N; 
    vs path;
    bool checkBoundary(int r, int c) { return r >= 0 && r < M && c >= 0 && c < N; }
    void backtrack(const vs& grid, int r, int c, int idx, vs& curr_path)
    {
        if(idx == GODS_NAME.size())
        {
            path = curr_path; 
            isFinished = true;
            return;
        }

        for(auto d : dirs)
        {
            int next_r = r + std::get<0>(d);
            int next_c = c + std::get<1>(d);
            if(!checkBoundary(next_r, next_c) ||
               (grid[next_r][next_c] != GODS_NAME[idx]))
              continue;
              
            curr_path.push_back(std::get<2>(d));
            backtrack(grid, next_r, next_c, idx + 1, curr_path);
            curr_path.pop_back();
            if(isFinished) return;
        }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            path = {};
            isFinished = false;
            std::cin >> M >> N;
            vs grid(M);
            for(int i = 0; i < M; i++)
              std::cin >> grid[i];

            int c;
            for(int i = 0; i < N; i++)
              if(grid.back()[i] == start) c = i;
              
            std::string word;
            vs curr_path;
            backtrack(grid, M - 1, c, 0, curr_path);
            for(int i = 0; i < path.size(); i++)
            { std::cout << path[i]; if(i != path.size() - 1) std::cout << " "; }
            std::cout << std::endl;
        }  
    }
}