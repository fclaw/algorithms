#include <cstdio>

namespace algorithms::onlinejudge::dp
{
    /* 
      https://onlinejudge.org/external/114/11420.pdf
      Given the value of n and s, your job is to find out in how many ways they can be secured.
    */
    int waysToSecureDrawers(int n, int s)
    {
        return 0;
    }

    /*
     Each line contains two integers n and s(1 ≤ n ≤ 65, 0 ≤s ≤ 65). 
     Here n is the total number of drawers and s is 
     the number of drawers that needs to be secured.
     Input is terminated by a line containing two negative numbers. 
     This input should not be processed.
    */
    void submit_uva_11420()
    {
        int n, s;
        while(true)
        {
            scanf("%d %d", &n, &s);
            if(n == -1 && s == -1)
              break;
            int ans = waysToSecureDrawers(n, s);
            printf("%d\n", ans);
        }
    }
}