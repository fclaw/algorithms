#include <vector>
#include <cstdio>
#include <iostream>

namespace algorithms::codeforces
{
    /*
      https://codeforces.com/problemset/problem/1472/B
      Alice and Bob received candies from their parents. 
      Each candy weighs either 1 gram or 2 grams. 
      Now they want to divide all candies among themselves fairly 
      so that the total weight of Alice's candies is equal to the total weight of Bob's candies.
      Check if they can do that. Note that candies are not allowed to be cut in half.
      speak generally, can candies be shared out fairly among k people.
      there are similarities to https://leetcode.com/problems/fair-distribution-of-cookies
    */
     bool canBeSharedOutFairly(int n, std::vector<int> weighs)
     {
          int sum = 0;
          int c2 = 0;
          int c1 = 0;
          for(auto w : weighs)
          {
          }
          return false;
     }

     int main()
     {
        int TS;
        scanf("%d", &TS);
        while(TS-- > 0)
        {
            int N;
            scanf("%d", &N);
            std::vector<int> xs(N);
            for (int i = 0; i < N; i++)
              scanf("%d", &xs[i]);
              
            auto ans = canBeSharedOutFairly(N, xs) ? "YES" : "NO";
            printf("%s\n", ans);
          }
          return 0;
     }
}