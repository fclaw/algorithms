#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include <vector>


typedef std::stack<char> sc;
typedef std::vector<std::string> vs;

namespace algorithms::onlinejudge::stack::anagrams
{
    
    /** https://onlinejudge.org/external/7/732.pdf, 
     * use stack to simulate the process
     * This is a backtracking problem, as you need to explore 
     * all valid sequences of operations that match the given constraints. */
    vs sequences;
    int N;
    const char PUSH = 'i';
    const char POP = 'o';
    void backtrack(const std::string& source, const std::string& target, std::string& tmp, sc& stack, std::string& op, int i, int j)
    {
        if(tmp == target)
        {
            sequences.push_back(op);
            return;
        }

        if(i < N)
        {
            stack.push(source[i]);
            op.push_back(PUSH);
            backtrack(source, target, tmp, stack, op, i + 1, j);
            // arguments are passed by reference thus the state is sharable
            // the state must be reverted in order not to interfere with other recursive calls
            op.pop_back();
            stack.pop();
        }
        
        if(!stack.empty())
        {
            char c = stack.top();
            // to prevent the unchecked growth of calls and run into TLE 
            if(c == target[j])
            {
                stack.pop();
                tmp.push_back(c);
                op.push_back(POP);
                backtrack(source, target, tmp, stack, op, i, j + 1);
                // arguments are passed by reference thus the state is sharable
                // the state must be reverted in order not to interfere with other recursive calls
                op.pop_back();
                tmp.pop_back();
                stack.push(c);
            }
        }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        std::string source, target;
        while(std::cin >> source >> target)
        {
            std::string tmp;
            sc stack;
            std::string op;
            N = source.size();
            backtrack(source, target, tmp, stack, op, 0, 0);
            std::cout << "[" << std::endl;
            for(auto str : sequences)
            {
                for(int i = 0; i < str.size(); i++)
                { std::cout << str[i]; if(i < str.size() - 1) std::cout << " "; }
                std::cout << std::endl;  
            }
            std::cout << "]" << std::endl;
            sequences.clear();
        }
    }
}