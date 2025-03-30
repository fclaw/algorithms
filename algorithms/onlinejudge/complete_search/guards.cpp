#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
#include <numeric>
#include <unordered_set>



typedef std::vector<int> vi;
typedef std::unordered_set<int> si;

void draw_grid(int SIZE, vi guards = {}) {
    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            if (!guards.empty() && c < guards.size() && guards[c] == r)
                std::cout << " G ";  // Guard
            else
                std::cout << " . ";  // Empty cell
        }
        std::cout << "\n";
    }
}

namespace algorithms::onlinejudge::complete_search::guards
{
    /** https://onlinejudge.org/external/100/10094.pdf, 
     * his problem is like the n-queens chess problem, but must find/use the pattern! */
    int SIZE;
    const int MAX_SIZE = 1000;
    const size_t MAX_BIT = 2 * MAX_SIZE - 1;
    vi guards;
    bool is_solution;
    std::bitset<MAX_BIT> rw, ld, rd;
    bool checkPlacement(int r, int c) 
    { return !rw.test(r) && !ld.test(r - c + MAX_SIZE - 1) && !rd.test(r + c); }
    void bits_set(int r, int c, bool flag) 
    { rw.set(r, flag); ld.set(r - c + MAX_SIZE - 1, flag); rd.set(r + c, flag); }
    void bits_reset() { rw.reset(); ld.reset(); rd.reset(); }
    bool isSpecial(int n) { return (n % 6 == 2 || n % 6 == 3); }
    void backtrack(int c, int prev, vi& local)
    {
        if(is_solution) return;
        if(c == SIZE)
        {
            guards = local;
            is_solution = true;
            return;
        }

        int start = prev >= SIZE ? (!(SIZE % 2) ? 0 : 1) : prev;
        for(int r = start; r < SIZE; r++)
          if(checkPlacement(r, c))
          {
              bits_set(r, c, true);
              local.push_back(r);
              backtrack(c + 1, r + 2, local);
              local.pop_back();
              bits_set(r, c, false);
          }
    }
    void generateSpecialLayout(int SIZE) 
    {
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
       
        while(std::cin >> SIZE)
        {
            bits_reset();
            is_solution = false;
            if(isSpecial(SIZE))
              generateSpecialLayout(SIZE);
            else 
            {
                int r = !(SIZE % 2) ? 1 : 0;
                vi local = {r};
                bits_set(r, 0, true);
                backtrack(1, r + 2, local);
            }
            if(guards.empty()) printf("Impossible\n");
            else
            {
                std::string ans =
                std::accumulate(
                    guards.begin(),
                    guards.end(),
                    std::string(), 
                    [](std::string& s, int n) 
                    { return s + (s.empty() ? "" : " ") + std::to_string(n + 1); });
                std::cout << ans << std::endl;
                std::cout << "SIZE: " << SIZE << "\n";
                draw_grid(SIZE, guards);
            }
        }
    }
}