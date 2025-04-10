#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef std::vector<char> vc;
typedef std::vector<vc> vvc;


namespace algorithms::onlinejudge::complete_search::largest_square
{
    /** https://onlinejudge.org/external/109/10908.pdf, 4 nested loops, square, not too hard  */
    int M, N, Q;
    int getSquare(const vvc& grid, int r, int c) 
    {
        int square = INT32_MIN;
        char origin = grid[r][c];
        int L = std::min(std::min(c, N - 1 - c), std::min(r, M - 1 - r)) + 1;
        for(int s = 1; s < L; s++)
        {
            bool isFails = false;
            for(int i = r - s; i <= r - s + 2 * s && !isFails; i++)
              for(int j = c - s; j <= c - s + 2 * s; j++)
                if(grid[i][j] != origin)
                { isFails = true; break; }
            if(!isFails) square = s; else break; 
        }
        return 2 * square + 1; 
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int tc;
        std::cin >>  tc;
        while(tc--)
        {
            std::cin >> M >> N >> Q;
            vvc grid(M, vc(N));
            for(int r = 0; r < M; r++)
              for(int c = 0; c < N; c++)
                std::cin >> grid[r][c];
            
            printf("%d %d %d\n", M, N, Q);
            for(int q = 0; q < Q; q++)
            {
                int r, c;
                std::cin >> r >> c;
                std::cout << getSquare(grid, r, c) << std::endl;
            }   
        }  
    }
}