#include <cstdio>
#include <vector>
#include <algorithm>

using arr = std::vector<int>;

namespace algorithms::onlinejudge::greedy
{
    // https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2267
    /* 
       The input contains several test cases. 
       The first line of each test case contains two integers between 1 and 20000 inclusive, 
       indicating the number n of heads that the dragon has, and the number m of knights in the kingdom. 
       The next n lines each contain an integer, and give the diameters of the dragon’s heads, in centimetres. 
       The following m lines each contain an integer, and specify the heights of the knights of Loowater, also in centimetres.
       The last test case is followed by a line containing ‘0 0’.
       In order to chop off a head, a knight must be at least as tall as the diameter of the head.
       The knights’ union demands that for chopping off a head, a knight must be paid a wage 
       equal to one gold coin for each centimetre of the knight’s height
    */
    int canDragonHeadsBeChoppedOff(arr xs, arr ys) 
    {

        // sort the arrays in an increasing order
        std::sort(xs.begin(), xs.end());
        std::sort(ys.begin(), ys.end());

        int n = xs.size();
        int m = ys.size();
        int i, j, reward = 0;

        while(i < n && j < m)
        {
            // select the knights until one greater then current 
            // dragon head is found
            while (xs[i] > ys[j] && j < m) j++;
            
            if(j == m)
              break;

            reward += ys[j];
            i++;
            j++;
        };

        return i < n ? -1 : reward;
    }
    
    void canLoowaterBeSaved() 
    {

        int N, M;
        while(true)
        {
            scanf("%d %d", &N, &M);
            if(N == 0 && N == 0)
              break;

            arr dragonHeads(N);
            arr knightsHeights(M);
            
            int i = 0;
            while(i < N)
            {
                int x;
                scanf("%d", &x);
                dragonHeads.push_back(x);
                i++;
            };

            int j = 0;
            while(j < M)
            {
                int x;
                scanf("%d", &x);
                knightsHeights.push_back(x);
                j++;
            };

            int ans = canDragonHeadsBeChoppedOff(dragonHeads, knightsHeights);
            if(ans != -1)
              printf("%d\n", ans);
            else 
              printf("%s", "Loowater is doomed!\n"); 
        }
    }
}