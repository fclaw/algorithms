/*
───────────────────────────────────────────────────────────────
🧳 UVa 110 Meta-Loopless Sorts, https://onlinejudge.org/external/1/110.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM OVERVIEW: META-LOOPLESS SORTS (Insertion Sort Decision Tree)
 * ============================================================================
 * Generates the complete Pascal-style decision tree for an Insertion Sort.
 * 
 * CORE STRATEGY:
 * We maintain a sequence of currently `sorted_letters` and determine where to
 * place the `curr_letter` by comparing it from RIGHT to LEFT against the 
 * sorted sequence.
 *
 * This right-to-left traversal maps perfectly to a 3-phase structural block:
 * 1. The initial `if` 
 * 2. The intermediate `else if` statements 
 * 3. The fallback `else`
 *
 * EXAMPLE STATE:
 * --------------
 * sorted_letters: [a, b]  (Length = 2)
 * curr_letter:    'c'
 *
 * EXPLICIT 3-BRANCH LOGIC:
 * ------------------------
 * [ PHASE 1 ] The "if" Branch (Append to End)
 *      Logic:  Compare against the VERY LAST element (sorted_letters.back()).
 *      Code:   `if b < c then`
 *      Action: Insert 'c' at the end -> [a, b, c]
 * 
 * [ PHASE 2 ] The "else if" Branches (Insert in the Middle)
 *      Logic:  Loop backward from the second-to-last element down to the first
 *              (j = size - 2 down to 0).
 *              If the current element is greater than `sorted_letters[j]`,
 *              it belongs immediately after it (at index j + 1).
 *      Code:   `else if a < c then` (when j = 0)
 *      Action: Insert 'c' at j + 1  -> [a, c, b]
 *
 * [ PHASE 3 ] The "else" Branch (Prepend to Beginning)
 *      Logic:  If it is not greater than ANY element, it must be the absolute
 *              smallest. No comparison needed.
 *      Code:   `else`
 *      Action: Insert 'c' at index 0 -> [c, a, b]
 *
 * IMPLEMENTATION DETAILS & OPTIMIZATIONS:
 * ---------------------------------------
 * - Immutable State Backtracking: `sorted_letters` is passed BY VALUE. Since 
 *   N <= 8, copying small vectors is lightning fast and implicitly handles the
 *   backtracking "un-do" step. No manual vector.erase() is needed!
 * - Fast I/O: Output is accumulated into `result` BY REFERENCE rather than
 *   calling std::cout at every leaf node, resulting in extremely fast execution.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;


std::string join(const std::vector<int>& indices) {
  std::string result = "";

  for (size_t i = 0; i < indices.size(); ++i) {
    // Convert integer index to letter
    char letter = 'a' + indices[i];
    result += letter;

    // Only add a comma if this is NOT the last element
    if (i < indices.size() - 1) {
      result += ",";
    }
  }

  return result;
}

std::string makeVars(const std::vector<int>& indices) { return join(indices); }

std::string makeWriteln(const std::vector<int>& indices) {
  std::string writeln = "writeln(";
  writeln += makeVars(indices);
  writeln += ")";
  return writeln;
}

std::string makeReadln(const std::vector<int>& indices) {
  std::string readln = "readln(";
  readln += makeVars(indices);
  readln += ");";
  return readln;
}


void write_if_else(const vi& letters, size_t i, std::string indent, vi sorted_letters, std::string& result) {
  // base case
  if(i == letters.size()) {
    result += indent + makeWriteln(sorted_letters) + "\n";
    return;
  }

  auto letter = std::string(1, 'a' + letters[i]);
  
  // if branch
  auto back_letter = std::string(1, 'a' + sorted_letters.back());
  auto if_branch = "if " + back_letter + " < " + letter + " then\n";
  auto if_sorted_letters = sorted_letters;
  if_sorted_letters.push_back(letters[i]);
  result += indent + if_branch;
  write_if_else(letters, i + 1, indent + "  ", if_sorted_letters, result);
    
  // if else branch 
  for(int j = sorted_letters.size() - 2; j >= 0; --j) {
    auto cmp_letter = std::string(1, 'a' + sorted_letters[j]);
    std::string else_if_branch = "else if " + cmp_letter + " < " + letter + " then\n";
    auto else_if_sorted_letters = sorted_letters;
    else_if_sorted_letters.insert(else_if_sorted_letters.begin() + j + 1, letters[i]);
    result += indent + else_if_branch;
    write_if_else(letters, i + 1, indent + "  ", else_if_sorted_letters, result);
  }

  // else branch
  std::string else_branch = "else\n";
  auto else_sorted_letters = sorted_letters;
  else_sorted_letters.insert(else_sorted_letters.begin(), letters[i]);
  result += indent + else_branch;
  write_if_else(letters, i + 1, indent + "  ", else_sorted_letters, result);
}


namespace algorithms::onlinejudge::strings::meta_loopless_sort
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        int t_cases;
        bool is_first = true;

        while_read(t_cases);
        std::cin.ignore();
        while(t_cases--) {

          if(!is_first) std::cout << std::endl;
          else is_first = false;

          int N;
          while_read(N);

          std::string program = {};
          vi letters(N);
          std::iota(letters.begin(), letters.end(), 0);

          program += "program sort(input,output);\n";
          program += "var\n";
          program += makeVars(letters);
          program += " : integer;\n";
          program += "begin\n";
          std::string indent = "  ";
          program += indent + makeReadln(letters);
          std::string if_else_body = "";
          vi tmp = {};
          int start = letters.front();
          letters.erase(letters.begin());
          write_if_else(letters, 0, indent, {start}, if_else_body);
          program += "\n" + if_else_body;
          program += "end.";
          printf("%s\n", program.c_str());
          std::cin.ignore();
        }
    }
}