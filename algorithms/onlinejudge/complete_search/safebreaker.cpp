#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <sstream>
#include <tuple>
#include <unordered_set>






typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef std::vector<std::tuple<std::string, int, int>> vtsii;

const int MAX = 9999;


void generateNumberWithLeadingZeros(vs& numbers) 
{
    for (int num = 0; num <= MAX; num++)
    {
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << num;
        numbers.push_back(ss.str());
    }
}


namespace algorithms::onlinejudge::complete_search::safebreaker
{
    /** https://onlinejudge.org/external/2/296.pdf, 
     * try all 10000 possible codes, 4 nested loops, 
     * use similar solution as ‘Master-Mind’ game  */
    bool trySelect(const std::string& guess, const std::string& cand, int old_c, int old_m, int& mask) 
    {
        int new_c = old_c, new_m = old_m;
        int used = 0;
        for(int i = 0; i < 4; i++)
          for(int j = 0; j < 4; j++)
          {
              bool right = (guess[i] == cand[j] && i == j && new_c > 0);
              bool misplaced = (guess[i] == cand[j] && i != j && new_m > 0);
              if((right || misplaced) && !(used & (1 << i)))
              { i == j ? --new_c : --new_m; used |= (1 << i); }

              if(old_c == 0 && old_m == 0 && guess[i] == cand[j])
                return false;
          }
        return !((old_c != 0 && new_c > 0) || (old_m != 0 && new_m > 0));
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        vs numbers;
        generateNumberWithLeadingZeros(numbers);
        
        int tc;
        std::cin >> tc;
        while(tc--)
        {
            int N;
            std::cin >> N;
            std::cin.ignore();
            vtsii guesses;
            std::string in;
            for(int i = 0; i < N; i++)
            {
                std::getline(std::cin, in);
                std::stringstream ss(in);
                std::string guess;
                int c, m; // correct, misplaced
                // Read the first part (string before space)
                ss >> guess;
                // Read the fraction part (after space) and split by '/'
                char slash;
                ss >> c >> slash >> m;
                // Return the tuple
                guesses.push_back(std::make_tuple(guess, c, m));
            }

            vs candidates;
            for(auto cand : numbers)
            {
                bool isValidCand = true;
                int used = 0;
                for(auto& [guess, c, m] : guesses)
                  isValidCand &= trySelect(guess, cand, c, m, used);
                if(isValidCand) candidates.push_back(cand);
            }
            if(debug_mode) dbg(candidates);
        }
    }
}