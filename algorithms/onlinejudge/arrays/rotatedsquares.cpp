#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>


const int R = 4;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
#define loop(x, s, n) for(int x = s; x < n; x++)

namespace algorithms::onlinejudge::arrays::rotated_squares
{

    // https://onlinejudge.org/external/108/10855.pdf, string array, 90 clockwise rotation
    void rotate(vvi& matrix)
    {
        int n = matrix.size();
        loop(i, 0, n / 2)
          loop(j, i, n - i - 1)
          {
             int temp = matrix[i][j];
             matrix[i][j] = matrix[n - j - 1][i];
             matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
             matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
             matrix[j][n - i - 1] = temp;
          }
    }
    int search(const vvi& parent, const vvi& child, int p_s, int c_s) 
    {
        int matches = 0;
        loop(i, 0, p_s)
          loop(j, 0, p_s)
          {
              if(parent[i][j] == child[0][0] &&
                 p_s - i >= c_s && 
                 p_s - j >= c_s)
              {
                  bool isIn = true;
                  loop(k, 0, c_s && isIn)
                    loop(l, 0, c_s && isIn)
                      if(parent[i + k][j + l] != child[k][l])
                      { isIn = false; break; }
                  if(isIn) { ++matches; }    
              }
          }
        return matches;  
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int n, m;
        while(true)
        {
            std::cin >> n >> m;

            if(n == 0 && m == 0) break;

            vvi parent = vvi(n, vi(n));
            vvi child = vvi(m, vi(m));

            char s;
            loop(i, 0, n)
              loop(j, 0, n)
                std::cin >> s,
                parent[i][j] = (int)s;

                
            loop(i, 0, m)
              loop(j, 0, m)
                std::cin >> s,
                child[i][j] = (int)s;

            vi ans = vi(R, 0);
            loop(i, 0, R)
            {
                int res = search(parent, child, n, m);
                ans[i] = res;
                rotate(child);
            }

            /**
             * The solutions of the different problems appear in successive lines. For each problem the output consists
             * of a line with four integers, which are the number of times each rotation of the small square appears in
             * the big square. The first number corresponds to the number of appearances of the small square without
             * rotations, the second to the appearances of the square rotated 90 degrees (clockwise), the third to the
             * square rotated 180 degrees, and the fourth to the square rotated 270 degrees.
            */
            loop(i, 0, R) std::cout << ans[i] << (i != R - 1 ? " " : "");
            std::cout << std::endl;
        }        
    }
}