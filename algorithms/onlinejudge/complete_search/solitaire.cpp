#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef std::pair<int, int> pii;
typedef std::vector<pii> vpii;


namespace algorithms::onlinejudge::complete_search::solitaire
{
    /** https://onlinejudge.org/external/105/10503.pdf
    ==========================================
    COMPLEXITY ANALYSIS & PRUNING STRATEGY
    ==========================================

    1. **Full Search Complexity**
    - The naive approach generates all permutations of up to 13 elements.
    - Worst-case: 13! = 6,227,020,800 (billions of states), which is infeasible.

    2. **Where Pruning Helps**
    - **Partial Placement Pruning**: If a piece cannot legally be placed, we backtrack early.
    - **Symmetry Reductions**: Skip redundant cases where rotations/mirrors produce the same state.
    - **Constraint-Based Cuts**: If a state violates known constraints (e.g., edge-matching in puzzles), abandon the branch early.

    3. **Effective Complexity Estimate**
    - With aggressive pruning, the branching factor drops significantly.
    - Instead of O(n!), we estimate O(c^n) where c ≈ 2.5 to 4.
    - For n = 13, this gives O(4^13) ≈ 67 million, which is feasible.

    4. **How to Measure Pruning Efficiency?**
    - Count recursive calls and compare with 13!.
    - Measure execution time across different input sizes.
    - Check how many branches are skipped due to constraints.

    By leveraging pruning, we significantly reduce the problem size, making the search feasible!
    */
    // N - the number of spaces
    // M = the number of pieces
    int N, M;
    bool ans;
    void backtrack(const vpii& pieces, pii last, pii curr, int mask, int s)
    {
        if(s == N)
          if(curr.second == last.first)
          { ans = true; return; }
        
        for(int i = 0; i < M; i++)
        {
            if((mask & (1 << i)))
              continue;
            if(pieces[i].first == curr.second)
              backtrack(pieces, last, pieces[i], mask | (1 << i), s + 1);
            pii tmp;
            tmp.first = pieces[i].second;
            tmp.second = pieces[i].first;
            if(tmp.first == curr.second)
              backtrack(pieces, last, tmp, mask | (1 << i), s + 1);
        }     
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        while(true)
        {
            ans = false;
            std::cin >> N;
            if(!N) break;
            std::cin >> M;
            pii fp;
            pii lp;
            scanf("%d %d\n", &fp.first, &fp.second);
            scanf("%d %d\n", &lp.first, &lp.second);
            vpii pieces(M);
            pii p;
            for(int i = 0; i < M; i++)
            { std::cin >> p.first >> p.second; pieces[i] = p; }
            backtrack(pieces, lp, fp, 0, 0);
            std::cout << (ans ? "YES" : "NO") << std::endl;
        }
    }
}