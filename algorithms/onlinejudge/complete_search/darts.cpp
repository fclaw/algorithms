#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <algorithm>



typedef  long long ll;
typedef std::vector<int> vi;
typedef std::unordered_set<ll> sll;


namespace algorithms::onlinejudge::complete_search::darts
{
    /** https://onlinejudge.org/external/7/735.pdf */
    ll mkMask(int i, int j, int k, bool isSort)
    {
        if(!isSort) return ((ll)i << 40) | ((ll)j << 20) | k;
        std::vector<int> v = {i, j, k};
        std::sort(v.begin(), v.end());
        return ((ll)v[0] << 40) | ((ll)v[1] << 20) | v[2];
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int INIT;
        const int REGION = 20;
        const int SIZE = 62;
        const int BULLS_EYE = 50;
        const int TARGET = 0;
        while(std::cin >> INIT && INIT > 0)
        {

            vi dartboard(SIZE); // 62
            dartboard[61] = BULLS_EYE;
            for(int i = 1; i <= REGION; i++)
            {
                dartboard[i] = i;
                dartboard[REGION + i] = 2 * i;
                dartboard[2 * REGION + i] = 3 * i;
            }

            int comb = 0;
            int cnt = 0;
            sll used_comb;
            sll used_idx;
            for(int i = 0; i < SIZE; i++) // first dart
              for(int j = 0; j < SIZE; j++) // second dart
                for(int k = 0; k < SIZE; k++) // third dart
                {
                    int first = dartboard[i];
                    int second = dartboard[j];
                    int third = dartboard[k];
                    int score = first + second + third;
                    if(score > INIT) continue;
                    if(INIT - score == TARGET)
                    {
                        ll comb_mask = mkMask(first, second, third, true);
                        if(!used_comb.count(comb_mask))
                        { comb++; used_comb.insert(comb_mask); }
                        ll idx_mask = mkMask(first, second, third, false);
                        if(!used_idx.count(idx_mask))
                        { used_idx.insert(idx_mask); cnt++; }

                    }
                }
            if(comb == 0) printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n", INIT);    
            else printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\nNUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n", INIT, comb, INIT, cnt); 
            printf("**********************************************************************\n");       
        }
        printf("END OF OUTPUT\n");
    }
}