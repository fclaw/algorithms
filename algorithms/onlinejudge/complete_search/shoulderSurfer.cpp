#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>




typedef std::vector<char> vc;
typedef std::vector<vc> vvc;
typedef std::unordered_set<std::string> ss;


namespace algorithms::onlinejudge::complete_search::shoulder_surfer
{
    /** https://onlinejudge.org/external/12/1262.pdf, 
     * LA 4845, Daejeon10, sort the columns in the
     * two 6 × 5 grids first so that 
     * we can process common passwords in lexicographic order; 
     * backtracking; 
     * important: skip two similar passwords */
    const int ROW = 6;
    const int COL = 5;
    int K;
    bool k_pass_found;
    std::string pass;
    ss passwords;
    void backtrack(const vvc& chars, int c, int& k, std::string& local)
    {
        if(k_pass_found) return;
        if(c == COL)
        {
            if(!passwords.count(local) && ++k == K)
            { pass = local; k_pass_found = true; }
            else passwords.insert(local);
            return;
        }

        for(char ch : chars[c])
        {
            local.push_back(ch);
            backtrack(chars, c + 1, k, local);
            local.pop_back();
        } 
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc;
        std::cin >> tc;
        while(tc--)
        {
            pass = {};
            passwords.clear();
            k_pass_found = false;
            std::cin >> K;
            vvc f_grid(COL), s_grid(COL);
            std::string s;
            for (int i = 0; i < 2 * ROW; i++) 
            {
                std::cin >> s;
                for (int j = 0; j < COL; j++)
                  if (i < ROW) f_grid[j].push_back(s[j]);
                  else s_grid[j].push_back(s[j]);
            }

            // Sort each column
            for (int j = 0; j < COL; j++)
              std::sort(f_grid[j].begin(), f_grid[j].end()),
              std::sort(s_grid[j].begin(), s_grid[j].end());


            vvc options(COL);
            for (int c = 0; c < COL; ++c) 
            {
                std::unordered_set<char> in_first(f_grid[c].begin(), f_grid[c].end());
                std::unordered_set<char> in_both;
                for (char ch : s_grid[c])
                  if (in_first.count(ch))
                    in_both.insert(ch); // Only collect shared letters
              
                vc unique_sorted(in_both.begin(), in_both.end());
                std::sort(unique_sorted.begin(), unique_sorted.end());
                options[c] = std::move(unique_sorted);
            }

            s.clear();
            int k = 0;
            backtrack(options, 0, k, s);
            if(k_pass_found) std::cout << pass << std::endl; else printf("NO\n");
        }
    }
}