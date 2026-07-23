/*
───────────────────────────────────────────────────────────────
🧳 UVa 263 Number Chains, https://onlinejudge.org/external/2/263.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;

struct Link
{
    std::string minuend;
    std::string subtrahend;
    std::string diff;
};

using v_link = std::vector<Link>;


std::string remove_leading_zeros(const std::string& s) {
    if (s.empty()) return s;
    
    // Find the first character that is not '0'
    size_t first_non_zero = s.find_first_not_of('0');
    
    if (first_non_zero == std::string::npos) {
        return "0"; // If the string is all zeros (e.g., "000"), return a single "0"
    }
    
    return s.substr(first_non_zero);
}

Link mklink(ll num) {
  auto minuend = std::to_string(num);
  auto subtrahend = std::to_string(num);
  std::sort(minuend.begin(), minuend.end(), std::greater<char>());
  std::sort(subtrahend.begin(), subtrahend.end());
  // remove leading zeros if any
  subtrahend = remove_leading_zeros(subtrahend);
  auto diff = std::to_string(std::atoll(minuend.c_str()) - std::atoll(subtrahend.c_str()));
  return {minuend, subtrahend, diff}; 
}

v_link build_chain(ll num) {

  Link init = mklink(num);
  v_link chain = {init};

  std::string last;
  std::unordered_set<std::string> in_chain;
  do {
    auto diff = chain.back().diff;
    in_chain.insert(diff);
    Link link = mklink(std::atoll(diff.c_str()));
    chain.push_back(link);
    last = link.diff;
  } while(in_chain.find(last) == in_chain.end());

  return chain;
}


namespace algorithms::onlinejudge::strings::number_chains
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

        ll num;
        while(std::cin >> num && num) {
          v_link chain = build_chain(num);
          printf("Original number was %lld\n", num);
          for(Link link : chain) {
            printf("%s - %s = %s\n", link.minuend.c_str(), link.subtrahend.c_str(), link.diff.c_str());
          }
          printf("Chain length %d\n\n", (int)chain.size());
        }
    }
}