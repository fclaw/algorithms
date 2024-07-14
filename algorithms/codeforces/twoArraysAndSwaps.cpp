#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <iostream>

namespace algorithms::codeforces
{
      /*
        https://codeforces.com/problemset/problem/1353/B
        You are given two arrays 𝑎 and 𝑏 both consisting of 𝑛
        positive (greater than zero) integers. You are also given an integer 𝑘.
        In one move, you can choose two indices 𝑖 and 𝑗 (1 <= i, j <= n)
        and swap a(i) and b(j).
        Note that 𝑖 and 𝑗 can be equal or different.
        Swap 𝑎(2) with 𝑏(2) or swap 𝑎(3) and 𝑏(9) both are acceptable moves.
        Your task is to find the maximum possible sum you can obtain in the array 𝑎
        if you can do no more than (i.e. at most) 𝑘 such moves (swaps).
      */
      int maxFromKSwaps(std::vector<int> xs, std::vector<int> ys, int k)
      {
           std::sort(xs.begin(), xs.end());
           std::sort(ys.begin(), ys.end(), std::greater<int>());
           
           int n = xs.size();
           int m = ys.size();
           int i, j = 0;

           while(j < m && i < n && k > 0)
           {
               while(j < m && ys[j] < xs[i])
               {
                   i++;
                   j++;
               }

               if(j == m)
                 break;

               int tmp = xs[i];
               xs[i] = ys[j];
               ys[j] = tmp; 
               i++;
               j++;
               k--;
           };

          return std::accumulate(xs.begin(), xs.end(), 0);
      }

      std::vector<int> readVector(int n)
      {
          std::vector<int> xs(n);
          int v;
          for (int i = 0; i < n; i++)
            scanf("%d", &xs[i]);
          return xs;
      }

      void submit_1353_B()
      {
          int TC;
          scanf("%d", &TC);
          while(--TC >= 0)
          {
              int n, k;
              scanf("%d %d\n", &n, &k);
              
              auto xs = readVector(n);
              auto ys = readVector(n);

              auto ans = maxFromKSwaps(xs, ys, k);
              printf("%d\n", ans);
          }
      }
}
