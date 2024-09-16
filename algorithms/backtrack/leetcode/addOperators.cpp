#include <vector>
#include <string>
#include <unordered_map>


namespace algorithms::backtrack::leetcode::add_operators
{


using ll = long long;
using expressions = std::vector<std::string>;
using ev = std::unordered_map<std::string, ll>;

    /**
     * https://leetcode.com/problems/expression-add-operators
     * Given a string num that contains only digits and an integer target, 
     * return all possibilities to insert the binary operators '+', '-', and/or '*' 
     * between the digits of num so that the resultant expression evaluates to the target value.
     * Note that operands in the returned expressions should not contain leading zeros. 
     * Hints: Since the question asks us to find all of the valid expressions, 
     * we need a way to iterate over all of them (complete search is inevitable) 
     * We can keep track of the expression string and evaluate it at the very end. But that would take a lot of time. 
     * Can we keep track of the expression's value as well so as to avoid the evaluation at the very end of recursion? 
     * consideration about multiplication operation:  
     * We simply need to keep track of the last operand in our expression and 
     * reverse it's effect on the expression's value while considering the multiply operator. */
    const std::vector<std::string> op = {"+", "-", "*"};
    expressions ans = {};
    ev evals;
    std::pair<ll, int> findOp(const std::string& exp)
    {
        ll p = std::string::npos;
        int j = 0;
        int k = exp.size();
        while(--k >= 0)
        {
            if(exp[k] == '+')
            {
                p = k;
                j = 0;
                break;
            }
            if(exp[k] == '-')
            {
                p = k;
                j = 1;
                break;
            }
            if(exp[k] == '*')
            {
                p = k;
                j = 2;
                break;
            }
        }
        return {p, j};
    }
    ll evaluate(int i, std::string exp)
    {
        if(auto it = evals.find(exp); 
           it != evals.end())
          return (*it).second;

        int p = exp.find_last_of(op[i]);
        ll res = 0;
        if(p == std::string::npos)
          res = std::stol(exp);
        else 
        {
            auto x = std::stol(exp.substr(p + 1));
            auto tmp = exp;
            exp.erase(p);
            auto eval = (*evals.find(exp)).second;
            if(op[i] == "+") res = eval + x;
            if(op[i] == "-") res = eval - x;
            if(op[i] == "*")
            {
                auto r = findOp(exp);
                ll prev = r.first;
                int j = r.second;
                if(prev == std::string::npos)
                  res = eval * x;
                else 
                {
                    int v = x * std::stol(exp.substr(prev + 1));
                    exp.erase(prev);
                    exp += op[j] + std::to_string(v);
                    if(j == 0) res = evaluate(0, exp);
                    if(j == 1) res = evaluate(1, exp);
                    if(j == 2) res = evaluate(2, exp);
                }
            }
        }
        return res;
    }
    void backtrack(const std::string& num, int i, int j, std::string exp, ll target)
    {
        int S = num.size();
        if(i == S) return;
        std::string local = exp;
        local += num.substr(i, 1);

        ll e = evaluate(j, local);
        evals[local] = e;
        
        if(i == S - 1 && e == target)
        {
           ans.push_back(local);
           return;
        }
        // 4 branches, one for each operation
        for(int k = 0; k < op.size(); k++)
          backtrack(num, i + 1, k, local + op[k], target);
        // no operation branch
        auto s = local.substr(local.find_last_of(op[j]) + 1);
        // determine whether a number has a leading zero
        if(s.front() != '0') backtrack(num, i + 1, j, local, target);
    }

    expressions addOperators(const std::string& num, int target) 
    { backtrack(num, 0, 0, {}, (ll)target); return ans; }
}