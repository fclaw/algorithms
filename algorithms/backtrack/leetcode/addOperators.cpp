#include <vector>
#include <string>
#include <chrono>
#include <thread>


namespace algorithms::backtrack::leetcode::add_operators
{


using ll = long long;
using expressions = std::vector<std::string>;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

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
    expressions ans;
    std::pair<ll, ll> evaluate(const int& i, const int& eval, const int& prev_eval, const std::string& exp)
    {
        int p = exp.find_last_of(op[i]);
        auto res = std::pair<ll, ll>();
        if(p == std::string::npos)
        {
            res.first = std::stol(exp);
            res.second = res.first;
        }
        else 
        {
            auto x = std::stol(exp.substr(p + 1));
            if(op[i] == "+") res = {eval + x, x};
            if(op[i] == "-") res = {eval - x, -x};
            if(op[i] == "*") res = {eval - prev_eval + x * prev_eval, x * prev_eval};
        }
        return res;
    }
    void backtrack(const std::string& num, int i, int j, int eval, int prev_eval, std::string exp, const ll& target)
    {
        int S = num.size();
        if(i == S) return;

        auto r = evaluate(j, eval, prev_eval, exp);   
        if(i == S - 1 && r.first == target)
        {
           ans.push_back(exp);
           return;
        }
        // 4 branches, one for each operation
        for(int k = 0; k < op.size() && i + 1 < S; k++)
          backtrack(num, i + 1, k, r.first, r.second, exp + op[k] + num.substr(i + 1, 1), target);
        // no operation branch
        auto s = exp.substr(exp.find_last_of(op[j]) + 1);
        // determine whether a number has a leading zero
        if(s.front() != '0') backtrack(num, i + 1, j, eval, prev_eval, exp + num.substr(i + 1, 1), target);
    }

    expressions addOperators(const std::string& num, int target) 
    { ans.reserve(10000); backtrack(num, 0, 0, 0, 0, num.substr(0, 1), (ll)target); return ans; }
}