#include <vector>
#include <cstdio>
#include <numeric>
#include <iostream>

namespace algorithms::backtrack::onlinejudge::cd
{
    // https://onlinejudge.org/external/6/624.pdf
    /**
     * You have a long drive by car ahead. You have a tape recorder, but unfortunately your best music is on
     * CDs. You need to have it on tapes so the problem to solve is: you have a tape N minutes long. How
     * to choose tracks from CD to get most out of tape space and have as short unused space as possible.
     * Assumptions:
     * • number of tracks on the CD does not exceed 20
     * • no track is longer than N minutes
     * • tracks do not repeat
     * • length of each track is expressed as an integer number
     * • N is also integer
     * Program should find the set of tracks which fills the tape best and print it in the same sequence as
     * the tracks are stored on the CD
     */
    int SIZE;
    int CAPACITY;
    int length;
    int songs;
    void backtrack(const std::vector<int>& cd, int i, int l, int s)
    {
        if(l > CAPACITY) return;

        if(length < l)
        {
            length = l;
            songs = s;
        }

        if(i >= SIZE) return;
        
        backtrack(cd, i + 1, l + cd[i], s | (1 << i));
        backtrack(cd, i + 1, l, s);
    }
}

namespace cd = algorithms::backtrack::onlinejudge::cd;

void submit()
{
    int capacity, s, v;
    while(std::cin >> capacity)
    {
        std::cin >> s;
        std::vector<int> cd;
        for(int i = 0; i < s; i++)
            std::cin >> v,
            cd.push_back(v);
        cd::CAPACITY = capacity;
        cd::SIZE = s;
        cd::length = cd::songs = 0;
        cd::backtrack(cd, 0, 0, 0);
        for(int i = 0; i < cd::SIZE; i++)
            if(cd::songs & (1 << i))
            printf("%d ", cd[i]);
        printf("sum:%d\n", cd::length);
    }
}