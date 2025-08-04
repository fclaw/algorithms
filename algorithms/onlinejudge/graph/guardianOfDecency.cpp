
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 12083 Guardian of Decency, MIS, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;

struct Person
{
    int height;
    std::string music;
    std::string sport;
};

using v_person = std::vector<Person>;

bool is_match(
  const Person& male, 
  const Person& female) {
  int height_diff = std::abs(male.height - female.height);
  return height_diff <= 40 &&
         male.music == female.music &&
         male.sport != female.sport;
}

namespace algorithms::onlinejudge::graph::guardian_of_decency
{
    /** https://onlinejudge.org/external/120/12083.pdf */
    int t_cases, group;
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
          while_read(group);
          v_person male_group;
          v_person female_group;
          for(int idx = 0; idx < group; idx++) {
            std::string gender;
            Person person;
            while_read(person.height);
            while_read(gender);
            while_read(person.music);
            while_read(person.sport);
            if(gender == "M")
              male_group.push_back(person);
            else female_group.push_back(person);
          }

          int L_SIZE = male_group.size();
          int R_SIZE = female_group.size();
          mcmb::vvi graph(L_SIZE);
          for(int i = 0; i < L_SIZE; ++i) {
            for(int j = 0; j < R_SIZE; ++j) {
              auto male = male_group[i];
              auto female = female_group[j];
              // whether an edge can be built
              if(is_match(male, female)) {
                graph[i].push_back(j);
              }
            }
          }

          int max_matches = 0;
          mcmb::kuhn kuhn_s(R_SIZE);
          for(int male_id = 0; male_id < L_SIZE; ++male_id) {
            kuhn_s.visited.assign(L_SIZE, false);
            bool is_matched = mcmb::try_kuhn(male_id, graph, kuhn_s);
            if(is_matched) max_matches++;
          }

          std::cout << (L_SIZE + R_SIZE - max_matches) << std::endl;
        }
    }
}