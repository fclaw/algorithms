#include <cmath>
#include <cstdio>

namespace algorithms::codeforces
{
    // https://codeforces.com/problemset/problem/1872/A
    /*
       You have two vessels with water. The first vessel contains 𝑎
       grams of water, and the second vessel contains 𝑏 grams of water. 
       Both vessels are very large and can hold any amount of water.

       You also have an empty cup that can hold up to 𝑐 grams of water.
       In one move, you can scoop up to 𝑐 grams of water from any vessel and pour it into the other vessel. 
       Note that the mass of water poured in one move does not have to be an integer.

       What is the minimum number of moves required to make the masses of water in the vessels equal? 
       Note that you cannot perform any actions other than the described moves.
       Tags: complete search, greedy, math, *800
    */
     
     int stepsToMakeVolEqual(int f, int s, int c) 
     { 
          float r = std::abs(f - s) / (2 * c);
          float fr = r - (int)r;
          return fr != 0 ? r + 1 : r;
     }

     void submit_1872_a()
     {
        int TS;
        scanf("%d", &TS);
        while(TS-- > 0)
        {
            int f_v, s_v, s;
            scanf("%d %d %d", &f_v, &s_v, &s);
            auto ans = stepsToMakeVolEqual(f_v, s_v, s);
            printf("%d\n", ans);
        }
     }

}