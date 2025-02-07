#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;

namespace algorithms::onlinejudge::skiena::voting
{
    /** https://onlinejudge.org/external/101/10142.pdf
     * Australian ballots require that the voter rank the candidates in order of choice. Initially only the first
     * choices are counted and if one candidate receives more than 50% of the vote, that candidate is elected. If
     * no candidate receives more than 50%, all candidates tied for the lowest number of votes are eliminated.
     * Ballots ranking these candidates first are recounted in favour of their highest ranked candidate who
     * has not been eliminated. This process continues [that is, the lowest candidate is eliminated and each
     * ballot is counted in favour of its ranked non-eliminated candidate] until one candidate receives more
     * than 50% of the vote or until all candidates are tied */
    const int inf = 5 * (int)1e+05;
    const size_t N = 1000;
    std::pair<int, int> getBoundaries(const vi& xs, vi& eliminated)
    {
        int j;
        for(int i = 0; i < xs.size(); i++)
          if(eliminated[i] == -1) { j = i; break; }

        int max_idx = j;
        int min_idx = j;  

        for(int i = 0; i < xs.size(); i++)
        {
            if(i == j) continue;
            if(xs[i] > xs[max_idx]) max_idx = i;
            if(xs[i] < xs[min_idx] && eliminated[i] == -1) 
            { min_idx = i; eliminated[i] = 0; }
        }
        return {max_idx, min_idx};
    }

    // after the n-th round there are 3 cases:
    // 1 one of candidates manages to gather votes greater the the set threshold
    // 2 the round ends up in a complete tie
    // 3 one of candidates who has the least votes is out of contention and be chucked off the election
    // only cases 3 provides for the counting going on
    vs vote(const vs& candidates, vvi& ballots, int threshold) 
    {
        vs ans;
        bool finished = false;
        while(!finished)
        {
        }
        return ans;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int n;
            scanf("%d", &n);
            std::cin.ignore();
            vs candidates = vs(n);
            std::string c;
            for(int j = 0; j < n; j++)
            {
                std::getline(std::cin, c);
                candidates[j] = c;
            }

            vvi ballots = vvi(N, vi(n));
            
            std::string line;
            int threshold = 0;
            while (std::getline(std::cin, line) && 
                   !line.empty()) 
            { // Read until empty line
               std::stringstream ss(line);
               vi ballot;
               int rank;
               while (ss >> rank)
                 ballot.push_back (--rank);  // Store 0-based indices
               ballots.push_back(ballot);
               ++threshold;
            }
          
            ballots.resize(threshold + 1);

            threshold = threshold / 2 + 1;
            vs ans = vote(candidates, ballots, threshold);
            for(int i = 0; i < ans.size(); i++)
            {
                std::cout << ans[i];
                if(i < ans.size() - 1)
                  std::cout << std::endl;
            }
            if(tc) std::cout << std::endl;
        }
    }
}