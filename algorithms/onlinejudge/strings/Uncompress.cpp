/*
───────────────────────────────────────────────────────────────
🧳 UVa 245 Uncompress, https://onlinejudge.org/external/2/245.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <list>
#include <iterator>
#include <algorithm> // for std::all_of
#include <cctype> // for std::isspace, std::isalpha, std::isdigit
#include <bits/stdc++.h>



using vs = std::vector<std::string>;
using container = std::list<std::string>;

auto empty = std::string();

vs breakIntoPieces(const std::string& line) {
  vs pieces;
  std::string current = empty;

  for (int i = 0; i < (int)line.length(); ++i) {
    char c = line[i];

    if (std::isalpha(c)) {
      if (!current.empty() && 
          !std::isalpha(current.back())) {
        pieces.push_back(current); 
        current = empty;
      }
      current += c;
    } else if (std::isdigit(c)) {
      if (!current.empty() && 
          !std::isdigit(current.back())) {
        pieces.push_back(current); 
        current = empty;
      }
      current += c;
    } else {
      // It's a separator (space, comma, -, ', etc.)
      if (!current.empty()) 
        pieces.push_back(current);
       pieces.push_back(std::string(1, c)); // Each symbol is its own piece
       current = empty;
      }
    }
  if (!current.empty()) 
    pieces.push_back(current);
  return pieces;
}

/**
 * ============================================================================
 * THE O(1) RE-LINKING STRATEGY (std::list Move-to-Front)
 * ============================================================================
 * The Uncompress algorithm requires frequent "Move-to-Front" operations. 
 * While a std::vector would require O(N) to shift all elements after an 
 * access, a std::list allows us to re-order the "dictionary" in O(1) time 
 * once the target node is located.
 * 
 * NAVIGATION:
 * Because the problem uses 1-based indexing from the MOST RECENT word, 
 * we use a reverse_iterator starting at rbegin().
 * 
 * THE ADVANCED CONVERSION:
 * Using `it.base()` is a subtle way to convert our "search cursor" back into 
 * a standard iterator suitable for the `erase` and `push_back` operations. 
 * Since std::list iterators are not invalidated by moves (unlike vectors), 
 * this approach is both memory-safe and architecturally elegant.
 * 
 * DICTIONARY STACK:
 * In this implementation, the "Back" of the list represents the "Top" of the 
 * MTF stack (the most recently used word).
 * ============================================================================
 */


container::const_iterator getIterator(const container& words, int target) {
//   std::cout << "getIterator: target = " << target << std::endl;
  auto it = words.rbegin();
  return std::advance(it, target), it.base();
}

void pushFront(container& words, container::const_iterator it) {
  auto el = *it;
  words.erase(it); // constant time operation in list
  words.push_back(el); // Move to the end of the list (most recently used)
}

bool is_integer(const std::string& s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool isOnlyLetters(const std::string& str) {
  return std::all_of(str.begin(), str.end(), 
    [](unsigned char c) {
      return std::isalpha(c);
    });
}


std::string gluePieces(const vs& pieces) {
  std::string result;
  for(const auto& piece : pieces)
    result += piece;
  return result;
}

void processPieces(vs& pieces, container& dictionary) {
  for(auto& piece : pieces) {
    if(is_integer(piece)) {
        int index = std::stoi(piece);
        auto it = getIterator(dictionary, index);
        piece = *it; // Replace the piece with the actual word from the dictionary
        pushFront(dictionary, it);
    }
    else if(isOnlyLetters(piece)) {
      dictionary.push_back(piece);
    }
  }
}


namespace algorithms::onlinejudge::strings::uncompress
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

        container dictionary;
        std::string line;
        while(std::getline(std::cin, line) && line != "0") {
          // 1 break
          vs pieces = breakIntoPieces(line);
          // 2 process each piece
          processPieces(pieces, dictionary);
          // 3 restore the original word with placeholders replaces if any
          std::cout << gluePieces(pieces) << std::endl;
        }
    }
}