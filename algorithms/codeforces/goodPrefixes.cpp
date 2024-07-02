#include <vector>
#include <iostream>

namespace algorithms::codeforces
{
    // https://codeforces.com/problemset/problem/1985/C
    /*
      Alex thinks some array is good if there exists some element that can be represented as the sum of all other elements (the sum of all other elements is 0
      if there are no other elements). For example, the array [1,6,3,2] is good since 1+3+2=6
      Furthermore, the array [0] is also good. However, the arrays [1,2,3,4] and [1] are not good.
      Alex has an array 𝑎(1), 𝑎(2), .. , 𝑎(n). Help him count the number of good non-empty prefixes of the array 𝑎.
    */
    int countGoodPrefixes(std::vector<int> xs) 
    {
         int n = xs.size();
         long long int prefixSum = xs[0];
         int currMax = xs[0];
         int ptr = 1;
         int res = xs[0] == 0 ? 1 : 0;

         while(ptr < n)
         {
            if(xs[ptr] > currMax)
            {
                if(xs[ptr] == prefixSum)
                  res++;
                currMax = xs[ptr];
            }
            else
              if(currMax == prefixSum - currMax + xs[ptr])
                res++;
            prefixSum += xs[ptr];
            ptr++;
         }

         return res;
    } 

    int main()
    {
         int n;
         std::cin >> n;
         while(n > 0)
         {
             int s;
             std::cin >> s;
             std::vector<int> xs(s);
             for (int i = 0; i < s; i++)
             {
                int x;
                std::cin >> x;
                xs[i] = x;
             }
             std::cout << countGoodPrefixes(xs) << std::endl;
             n--;
         };
         
         return 0;
    }
}