/*
───────────────────────────────────────────────────────────────
🧳 UVa 10150 Doublets, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bfs.cpp"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <queue>


typedef std::vector<std::string> vs;


const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";



void change_letter(
  const std::string& s,
  std::queue<std::string>& queue,
  const std::unordered_set<std::string>& dictionary,
  std::unordered_map<std::string, std::string>& parent, 
  std::unordered_set<std::string>& used) {
  int S = (int)s.size();
  for(int i = 0; i < S; ++i)
    for(char c : alphabet)
      if(c != s[i]) {
        auto new_s = s;
        new_s[i] = c;
        if(dictionary.count(new_s) && 
           !used.count(new_s)) {
          parent[new_s] = s;
          queue.push(new_s);
          used.insert(new_s);
        }
      }
}

bool is_two_words(const std::string& s) {
    size_t pos = s.find(' ');
    if (pos == std::string::npos) return false;                 // No space
    if (s.find(' ', pos + 1) != std::string::npos) return false; // More than one space
    if (pos == 0 || pos == s.size() - 1) return false;          // One part is empty
    return true;
}


namespace algorithms::onlinejudge::graph::doublets
{
    /** https://onlinejudge.org/external/101/10150.pdf */
    int is_first = true;
    void run_bfs(
      const std::string& source, 
      const std::string& sink,
      std::unordered_set<std::string>& dictionary) {
      
      std::unordered_map<std::string, std::string> parent;
      std::unordered_set<std::string> used;
      std::queue<std::string> queue;
      queue.push(source);
      used.insert(source);
      while(!queue.empty()) {
        std::string s = queue.front(); queue.pop();
        if(s == sink) break;
        change_letter(s, queue, dictionary, parent, used);
      }
      
      std::vector<std::string> path;
      std::string step = sink;
      while(!step.empty()) {
        path.push_back(step);
        step = parent[step];
      }

      if(!is_first) std::cout << std::endl;
      else is_first = false;
      if(path.size() > 1) {
        auto it = path.rbegin();
        for(; it != path.rend(); ++it)
          std::cout << *it << std::endl;
      } else printf("No solution.\n");
    }
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
        
        std::string line;
        std::unordered_set<std::string> dictionary;
        while(std::getline(std::cin, line)) {
          if(line.empty()) continue;
          if(!is_two_words(line)) 
            dictionary.insert(line);
          else {
            size_t pos = line.find(' ');
            std::string source = line.substr(0, pos);
            std::string sink = line.substr(pos + 1, line.size());
            run_bfs(source, sink, dictionary);
          } 
        }
    }
}