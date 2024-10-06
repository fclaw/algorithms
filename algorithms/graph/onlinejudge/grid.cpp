/** https://onlinejudge.org/external/109/10913.pdf, s: r, c, neg left, stat; t: down/left/right
 * 1. You can only move left, right or down
 * 3. You can never move outside the grid
 * 4. You can not step on a cell more than once
 * 5. Every cell has an integer associated with it
 * 6. You have to make sure the sum of integers of the path is maximized
 * 7. You can step on at most k negative integers from source to destination  
* */

#include <vector>
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>

namespace algorithms::graph::onlinejudge::grid_walking
{

#define loop(x, s, n) for(int x = s; x < n; x++)
typedef std::vector<std::pair<int, int>> dirs; 
typedef std::vector<std::vector<int>> matrix;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::vector<vvvi> vvvvi;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;

const int inf = 5 * 1e+05;

    /** You can only move left, right or down. 
     * (i, j − 1) is left of (i, j), 
     * (i, j + 1) is right of (i, j), 
     * (i + 1, j) is down of (i, j) */
    dirs ds = { {0, 1}, /* left */ {0, -1}, /* right */  {1, 0} /* down */ };
    int N, K;
    bool finished = false; 
    bool checkBoundary(int r, int c) 
    { return r >= 0 && r < N && c >= 0 && c < N; }
    // You have to make sure the sum of integers of the path is maximized
    // how to convert to DAG? 
    int backtrack(const matrix& mtx, int r, int c, int k, int d, vvb& visited, vvvvi& memo)
    {
        if(k > K) return -inf;

        if(r == N - 1 && c == N - 1)
          return mtx[r][c];


        int &local_max = memo[r][c][k][d];
        if(~local_max) return memo[r][c][k][d];

        local_max = -inf; 
        loop(i, 0, ds.size())
        {
            int n_r = r + ds[i].first;
            int n_c = c + ds[i].second;
            if(checkBoundary(n_r, n_c) &&
               !visited[n_r][n_c])
            {
                visited[n_r][n_c] = true; // lock
                int res = backtrack(mtx, n_r, n_c, k + (int)(mtx[n_r][n_c] < 0), i, visited, memo);
                if(res != -inf) local_max = std::max(local_max, mtx[r][c] + res);
                visited[n_r][n_c] = false; // release
            }
        }
        return memo[r][c][k][d] = local_max;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int n, k, c = 1;
        while(std::cin >> n >> k)
        {
            if(n == 0 && k == 0) break;
            matrix mtx;
            vi xs;
            N = n;
            K = k;
            int x;
            loop(i, 0, n)
            {
              loop(j, 0, n)
                std::cin >> x,
                xs.push_back(x);  
              mtx.push_back(xs);
              xs.clear();
            }

            vvb visited(n, vb(n, false));
            visited[0][0] = true;
            vvvvi memo(n, vvvi(n, vvi(k + 1, vi(ds.size(), -1))));
            int max_sum = backtrack(mtx, 0, 0, (int)(mtx[0][0] < 0), 0, visited, memo);
            std::string ans = max_sum != -inf ? std::to_string(max_sum) : "impossible";
            printf("Case %d: %s\n", c++, ans.c_str());
        }
    }
}