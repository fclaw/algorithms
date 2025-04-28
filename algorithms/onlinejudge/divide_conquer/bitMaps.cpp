#include "../debug.h"
#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <cctype>






typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int, int> pii;
typedef std::vector<std::pair<pii, pii>> vppii;


vppii splitRegion(const pii& tl, const pii& br) 
{
    return
     {{{tl.first, tl.second}, {(tl.first + br.first) / 2, (tl.second + br.second) / 2 }},
      {{tl.first, (tl.second + br.second) / 2 + 1}, {(tl.first + br.first) / 2, br.second}},
      {{(tl.first + br.first) / 2 + 1, tl.second}, {br.first, (tl.second + br.second) / 2 }},
      {{(tl.first + br.first) / 2 + 1, (tl.second + br.second) / 2 + 1}, {br.first, br.second }}};
}

std::string print(const std::string& s)
{
    std::string tmp;
    for(int i = 0; i < (int)s.size(); i++)
    {
        if(i % 50 == 0) 
          tmp += '\n';
        tmp += s[i];
    }
    return tmp;
}

namespace algorithms::onlinejudge::divide_conquer::bit_maps
{
    /** https://onlinejudge.org/external/1/183.pdf, simple exercise of Divide and Conquer */
    int R, C;
    std::string T;
    const std::string D = "D";
    const std::string B = "B";
    enum Region { Zeros, Ones, Mixed };
    Region test(const vvi& bitmap, const pii& tl, const pii& br) 
    {
        int size = (br.first - tl.first + 1) * (br.second - tl.second + 1);
        int zeros = 0, ones = 0;
        bool isMixed = false;
        // Iterate through the rows and columns defined by the segment
        for(int r = tl.first; r <= br.first && !isMixed; ++r)
          for(int c = tl.second; c <= br.second && !isMixed; ++c)
          {
             if(bitmap[r][c] == 1) ones++;
             else zeros++;
             if(zeros > 0 && ones > 0) 
             { isMixed = true; break; }
          } 

        if(isMixed) return Mixed; 
        else if(size == ones) return Ones;
        else return Zeros; 
    }
    std::string transformBtoD(const vvi& bitmap, const pii& tl, const pii& br)
    {
        if(tl.first > br.first || 
           tl.second > br.second) 
          return {};

        Region reg = test(bitmap, tl, br);
        if(reg == Ones) return std::to_string(Ones);
        if(reg == Zeros) return std::to_string(Zeros);
       
        std::string s = D;
        vppii ps = splitRegion(tl, br);
        // divide into 4 parts (top-left, top-right, bottom-left, bottom-right)
        for(const auto& [p_tl, p_br] : ps)
          s += transformBtoD(bitmap, p_tl, p_br);
        return s;
    }
    void transformDtoB(const std::string& bitmap_d, int& idx, const pii& tl, const pii& br, std::string& bitmap)
    {
        if(tl.first > br.first || 
           tl.second > br.second || 
           idx > (int)bitmap_d.size())
          return;

        // Base case: If the character at bitmap_d[idx] is '0' or '1', fill the region with that value
        if (bitmap_d[idx] == Zeros + '0' || 
            bitmap_d[idx] == Ones + '0')
        {
           // Fill region tl to br with bitmap_d[idx] ('0' or '1')
           // This would mean that for each cell within this region, we should fill the value
           // Depending on your data structure, this would involve filling the bitmap or storing the result.
           // Simply return the filled segment
           for(int r = tl.first; r <= br.first; ++r)
             for(int c = tl.second; c <= br.second; ++c)
               bitmap[r * C + c] = bitmap_d[idx];
           idx++;
           return;
        }

        idx++;
        vppii ps = splitRegion(tl, br);
        for(const auto& [p_tl, p_br] : ps)
          transformDtoB(bitmap_d, idx, p_tl, p_br, bitmap);
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        while(std::cin >> T >> R >> C)
          if(T == B)
          {
             vvi bitmap(R, vi(C));
             char c;
             for(int i = 0; i < R; i++)
               for(int j = 0; j < C; j++)
                 std::cin >> c,
                 bitmap[i][j] = (int)(c - '0');
             printf("%s%4d%4d%s\n", D.c_str(), R, C, print(transformBtoD(bitmap, {0, 0}, {R - 1, C - 1})).c_str());
          }  
          else
          {
             std::string bitmap_d;
             std::cin >> bitmap_d;
             std::string bitmap;
             bitmap.resize(R * C);
             int idx = 0;
             transformDtoB(bitmap_d, idx, {0, 0}, {R - 1, C - 1}, bitmap);
             printf("%s%4d%4d%s\n", B.c_str(), R, C, print(bitmap).c_str()); 
          }
    }
}