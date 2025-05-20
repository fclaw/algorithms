 #include "../debug.h"
 #include "../../aux.h"
 
 #include <optional>
 #include <iostream>
 #include <cstdio>
 #include <vector>
 #include <algorithm>
 #include <numeric>
 #include <stdexcept>
 #include <cstring>
 #include <bitset>
 #include <unordered_map>
 #include <unordered_set>
 #include <string>
 #include <sstream>
 
 
 
 
 
 struct Block
 {
     int l;
     int m;
 };
 
 std::ostream& operator << 
   (std::ostream& out, const Block& b) 
   { return out << "{" << b.l << ", "  << b.m << "}"; }
 
 bool operator < (const Block& bl, const Block& br) { return bl.l > br.l || (bl.l == br.l && bl.m > br.m); }
 
 typedef std::vector<int> vi;
 typedef std::vector<Block> vblock;
 
 
 namespace algorithms::onlinejudge::dp::tiling_up_blocks
 {
     /** https://onlinejudge.org/external/11/1196.pdf, LA 2815, Kaohsiung03; sort all the blocks in increasing L[i], then we get the classical LIS problem */
     void submit(std::optional<char*> file, bool debug_mode)
     {
         if (file.has_value())
           // Attempt to reopen stdin with the provided file
           if (std::freopen(file.value(), "r", stdin) == nullptr) {
             // If freopen fails, throw an exception with a more detailed error message
             std::string name = file.value();
             std::string errorMessage = 
               "Failed to open file: " + name +
               " with error: " + std::strerror(errno);
             throw std::ios_base::failure(errorMessage);
           }
        
         int n;
         while(while_read(n) && n)
         {
              vblock vblock(n);
              int l, m;
              loop(n, [&vblock, &l, &m](int i) { while_read(l, m); vblock[i] = {l, m}; } );
              std::sort(vblock.begin(), vblock.end());

              int s = (int)vblock.size();
              vi dp = vi(s, 1);
              for(int i = 1; i < s; ++i)
                for(int j = i - 1; j >= 0; --j)
                  if(vblock[i].l <= vblock[j].l && 
                    vblock[i].m <= vblock[j].m)
                    dp[i] = std::max(dp[i], 1 + dp[j]);
              std::cout << *std::max_element(dp.begin(), dp.end()) << std::endl;
         }
         std::cout << "*" << std::endl;
     }
 }