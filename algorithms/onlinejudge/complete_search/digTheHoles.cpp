#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <unordered_map>
#include <array>



/** There are 6 coins of different colors Red, Green, Blue, Yellow, Orange, Violet */
enum Colour 
{ 
    B = 1 << 0,
    G = 1 << 1,
    O = 1 << 2,
    R = 1 << 3,
    V = 1 << 4,
    Y = 1 << 5
};

typedef std::vector<Colour> vc;
typedef std::vector<std::tuple<uint32_t, int, int>> vtiii;


uint32_t packColours(const vc& colours) 
{
    uint32_t mask = 0;
    for (int i = 0; i < 4; ++i)
      mask |= (static_cast<uint32_t>(colours[i]) << (6 * i));
    return mask;
}

std::unordered_map<char, Colour> map = {{'B', B}, {'G', G}, {'O', O}, {'R', R}, {'V', V}, {'Y', Y}};

namespace algorithms::onlinejudge::complete_search::dig_the_holes
{
    /**  https://onlinejudge.org/external/114/11412.pdf, next permutation, find one possibility from 6!  */
    bool validate(uint32_t perm, uint32_t guess, int r, int m) 
    { 
        int right = 0;
        std::array<int, 6> count_perm{}, count_guess{};
    
        for (int i = 0; i < 4; ++i) 
        {
            Colour c1 = static_cast<Colour>((perm >> (6 * i)) & 0b111111);
            Colour c2 = static_cast<Colour>((guess >> (6 * i)) & 0b111111);
    
            if (c1 == c2) ++right;
            else 
            {
                // Count for misplaced matching
                count_perm[__builtin_ctz(c1)]++;
                count_guess[__builtin_ctz(c2)]++;
            }
        }
    
        if (right != r) return false;
    
        // Count misplaced: sum of min overlaps where not in right position
        int misplaced = 0;
        for (int i = 0; i < 6; ++i)
          misplaced += std::min(count_perm[i], count_guess[i]);
    
        return misplaced == m;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc;
        std::cin >> tc;
        std::cin.ignore();
        std::cin.ignore();
        while(tc--)
        {
            std::unordered_set<uint32_t> used;
            vc start = {B, G, O, R, V, Y};
            bool isValid = false;
            vtiii guesses;
            std::string in;
            while(std::getline(std::cin, in) && !in.empty())
            {
                std::string s = in.substr(0, 4);
                vc g;
                for(char c : s) g.push_back(map[c]);
                guesses.push_back({packColours(g), in[5] - '0', in[7] - '0'});
            }
            do
            {
                vc perm;
                std::copy_n(start.begin(), 4, std::back_inserter(perm));
                uint32_t mask = packColours(perm);
                if(used.count(mask)) continue;
                used.insert(mask);
                bool isPermValid = true;
                for(auto& [guess, r, m] : guesses)
                  isPermValid &= validate(mask, guess, r, m);
                isValid |= isPermValid;
                if(isValid) break;
                  
            }while(std::next_permutation(start.begin(), start.end()));
            std::cout << (isValid ? "Possible" : "Cheat") << std::endl;
        }
    }
}