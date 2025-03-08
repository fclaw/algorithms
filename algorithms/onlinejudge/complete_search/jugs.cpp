#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
#include <set>




typedef std::vector<int> vi;
typedef std::set<std::pair<int, int>> sii;

namespace algorithms::onlinejudge::complete_search::jugs
{
    /** https://onlinejudge.org/external/5/571.pdf, 
     * solution can be suboptimal, add flag to avoid cycling */
    int capacity_a;
    int capacity_b;
    int target;
    vi ans;
    enum Action { FillA, PourAB, EmptyA, FillB, PourBA, EmptyB };
    int min_steps;  // Track the shortest path
    void backtrack(int curr_a, int curr_b, vi& seq, sii& visited, Action last)
    {
        // Stop if we already found a shorter solution
        if(seq.size() >= min_steps) return;

        // Stop if both jugs are full (early stopping)
        if(curr_a == capacity_a && 
           curr_b == capacity_b) return;

        // If target is reached
        if(curr_b == target) 
        {
            if(seq.size() < min_steps) 
            { min_steps = seq.size(); ans = seq; }
            return;
        }

       // avoid visiting the already explored states
       if (visited.count({curr_a, curr_b})) return;
       visited.insert({curr_a, curr_b});

        for(int i = FillA; i <= EmptyB; i++)
        {
            if(i == last) continue;
            if(curr_a == 0 && i == FillA)
            {
                seq.push_back(FillA);
                backtrack(capacity_a, curr_b, seq, visited, FillA);
                seq.pop_back();
            }
      
            if (i == PourAB && 
                curr_a > 0 && 
                curr_b < capacity_b)
            {
              int diff = std::min(curr_a, capacity_b - curr_b);
              int next_a = curr_a - diff;
              int next_b = curr_b + diff;
              
              seq.push_back(PourAB);
              backtrack(next_a, next_b, seq, visited, PourAB);
              seq.pop_back();
            }
         
            if(curr_a > 0 && i == EmptyA)
            { 
                seq.push_back(EmptyA);
                backtrack(0, curr_b, seq, visited, EmptyA);
                seq.pop_back();
            }

            if(curr_b == 0 && i == FillB)
            {
                seq.push_back(FillB);
                backtrack(curr_a, capacity_b, seq, visited, FillB);
                seq.pop_back();
            }
        
            if (i == PourBA && 
                curr_b > 0 && 
                curr_a < capacity_a) {
              int diff = std::min(curr_b, capacity_a - curr_a);
              int next_a = curr_a + diff;
              int next_b = curr_b - diff;
              
              seq.push_back(PourBA);
              backtrack(next_a, next_b, seq, visited, PourBA);
              seq.pop_back();
          }
         
            if(curr_b > 0 && i == EmptyB)
            {
               seq.push_back(EmptyB);
               backtrack(curr_a, 0, seq, visited, EmptyB);
               seq.pop_back();
            }
        }
    }

    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        while(std::cin >> 
              capacity_a >>
              capacity_b >> 
              target)
        {
            min_steps = std::numeric_limits<int>::max();
            ans = {};
            sii visited;
            vi seq;
            backtrack(0, 0, seq, visited, FillA);
            for(int a : ans)
              if(a == FillA)
                std::cout << "fill A" << std::endl;
              else if(a == FillB)
                std::cout << "fill B" << std::endl;
              else if(a == PourAB)
                std::cout << "pour A B" << std::endl;
              else if(a == PourBA)
                std::cout << "pour B A" << std::endl;
              else if(a == EmptyA)
                std::cout << "empty A" << std::endl;
              else std::cout << "empty B" << std::endl;
            std::cout << "success" << std::endl;  
        }
    }
}