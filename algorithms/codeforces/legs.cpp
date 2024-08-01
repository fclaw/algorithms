#include <cstdio>


namespace algorithms::codeforces
{
    void submit_1996_a()
    {
        int TC;
        scanf("%d", &TC);
        while(--TC >= 0)
        {
            int legs;
            scanf("%d", &legs);
            int cows = legs / 4;
            int chickens = (legs % 4) / 2;
            printf("%d\n", cows + chickens);
        }
    }
}