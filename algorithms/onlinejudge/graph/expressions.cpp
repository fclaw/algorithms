 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 11234 Expressions, rt: s
 ───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: Parsing Postfix Expressions with a Balance Counter
 * =====================================================================================
 *
 * The core challenge of this problem is to convert a linear postfix expression string
 * into a hierarchical expression tree. This requires a robust parsing strategy.
 *
 * A simple backtracking or guessing approach fails because it's difficult to
 * determine the boundary between the left and right subexpressions for an operator.
 * The solution is a deterministic, single-pass parsing technique based on a
 * fundamental property of valid binary postfix expressions.
 *
 * --- The Fundamental Property ---
 *
 * In any valid binary postfix expression, the number of operands is always exactly
 * one greater than the number of operators.
 *   - `ab+`      -> 2 operands, 1 operator
 *   - `ab+c*`    -> 3 operands, 2 operators
 *
 * This property arises from the structure of the corresponding expression tree, where
 * every operator is an internal node with two children, and every operand is a leaf.
 *
 * --- The Balance-Counter Trick ---
 *
 * We can exploit this property to find the precise split point between the left and
 * right subtrees for any given operator. The algorithm works as follows:
 *
 * 1.  Let the full expression be `[LEFT_EXPR][RIGHT_EXPR][OPERATOR]`. The root of
 *     our tree is the final `OPERATOR`. Our task is to parse the prefix
 *     `[LEFT_EXPR][RIGHT_EXPR]`.
 *
 * 2.  We scan this prefix string BACKWARDS (from right to left), maintaining a
 *     `balance` counter initialized to 0.
 *       - If we see an OPERAND (lowercase), we increment `balance`.
 *       - If we see an OPERATOR (uppercase), we decrement `balance`.
 *
 * 3.  The FIRST time `balance` becomes +1, we have found the end of a complete,
 *     self-contained subexpression. This subexpression is the RIGHT child of our
 *     root operator.
 *
 *    Example Trace on "ab+cd-*":
 *      - Root is `*`. Prefix to parse is `ab+cd-`.
 *      - Scan backwards from `-`:
 *        - `char='-'`: operator, balance = -1
 *        - `char='d'`: operand,  balance = 0
 *        - `char='c'`: operand,  balance = 1  --> STOP!
 *
 * 4.  The split point is the index where the balance became +1.
 *       - Right Subexpression: "cd-"
 *       - Left Subexpression:  "ab+"
 *
 * This function is then called recursively on the left and right substrings to
 * build the entire tree in a top-down, deterministic fashion. It's a classic
 * example of a recursive descent parser.
 *
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>


namespace tree = algorithms::onlinejudge::graph::tools::tree;


int find_split_point(const std::string& exp) {
  int balance = 0;
  for(int i = exp.size() - 2; i >= 0; --i) {
    if(std::islower(exp[i])) {
      // operand
      balance++;
    } else {
      // operator
      balance--;
    }
    if(balance == 1) return i; // found the split point
  }
  return -1; // should never happen if the expression is valid
}


tree::Tree<char>* built_tree(const std::string& exp) {
  tree::Tree<char>* root = new tree::Tree<char>(exp.back());
  if (exp.size() == 1) {
    // Leaf node
    return root;
  }
  int split_point = find_split_point(exp);
  root->left = built_tree(exp.substr(0, split_point));
  root->right = built_tree(exp.substr(split_point, exp.size() - 1 - split_point));
  return root;
}


std::string do_levelorder(tree::Tree<char>* tree) {
  if(!tree) return {};
  std::string levelorder_s;
  std::queue<tree::Tree<char>*> q;
  q.push(tree);
  while(!q.empty()) {
    tree::Tree<char>* node = q.front(); q.pop();
    levelorder_s += node->val;
    if(node->left) q.push(node->left);
    if(node->right) q.push(node->right);
  }
  std::reverse(levelorder_s.begin(), levelorder_s.end());
  return levelorder_s;
}


namespace algorithms::onlinejudge::graph::expressions
{
    /** https://onlinejudge.org/external/112/11234.pdf */
    int t_cases;
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
        
        while_read(t_cases);
        while(t_cases--) {
          std::string expression;
          while_read(expression);
          tree::Tree<char>* tree = built_tree(expression);
          std::string levelorder_s = do_levelorder(tree);
          std::cout << levelorder_s << std::endl;
        }
    }
}