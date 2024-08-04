#include <vector>
#include <cstdio>
#include <numeric>

namespace algorithms::backtrack::uv
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
    void rec(std::vector<int> cd, int start, int c, std::vector<int>& songs, bool& finished)
    {
        
    }
    std::vector<int> fillCd(std::vector<int> cd, int capacity)
    {
        SIZE = cd.size();
        std::vector<int> songs;
        bool finished = false;
        rec(cd, 0, capacity, songs, finished);
        return songs;
    }

    void submit_uv_624()
    {
        int capacity, n;
        scanf("%d %d", &capacity, &n);
        std::vector<int> cd(n);
        for(int i = 0; i < n; i++)
          scanf("%d", &cd[i]);
        auto xs = fillCd(cd, capacity);
        int res = std::reduce(xs.begin(), xs.end());
        std::string ans;
        for(auto x : xs)
        {
          ans += std::to_string(x);
          ans += " ";
        }
        ans += "sum:" + std::to_string(res);
        printf("%s", ans.c_str());
    }
}