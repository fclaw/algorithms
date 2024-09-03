#include <vector>
#include <string>

namespace algorithms::backtrack::leetcode::invalid_parentheses
{


    /**
     * https://leetcode.com/problems/remove-invalid-parentheses
     * Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses 
     * to make the input string valid.
     * Return a list of unique strings that are valid with the minimum number of removals. 
     * You may return the answer in any order. 
     * hints: Since we do not know which brackets can be removed, we try all the options! We can use recursion
     * In the recursion, for each bracket, we can either use it or remove it.
     * Recursion will generate all the valid parentheses strings but we want the ones with the least number of parentheses deleted.
     * We can count the number of invalid brackets to be deleted and only generate the valid strings in the recursion. */
    std::vector<std::string> removeInvalidParentheses(std::string s)
    {
        return {};    
    }
}