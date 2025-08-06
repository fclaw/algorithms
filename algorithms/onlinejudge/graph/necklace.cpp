 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 10054 The Necklace, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/eulerian.cpp"
#include <bits/stdc++.h>



namespace eulerian = algorithms::onlinejudge::graph::tools::eulerian;


struct Bead
{
    int index;
    int origin_index;
    int left_clr;
    int right_clr;
};


bool can_chain(const Bead& lhs, const Bead& rhs) { 
  return lhs.right_clr == rhs.left_clr && (lhs.origin_index != rhs.origin_index);
}
Bead swap(const Bead& bead) { 
  Bead swapped = bead;
  swapped.left_clr = bead.right_clr;
  swapped.right_clr = bead.left_clr;
  swapped.origin_index = bead.index;
  return swapped;
}


using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using v_bead = std::unordered_map<int, Bead>;


namespace algorithms::onlinejudge::graph::necklace
{
    /** https://onlinejudge.org/external/100/10054.pdf */
    int t_cases, t_case = 1, beads_n;
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
          while_read(beads_n);
          v_bead beads;
          int ext = 0;
          for(int bead_idx = 0; bead_idx < beads_n; ++bead_idx) {
            Bead bead;
            while_read(bead.left_clr);
            while_read(bead.right_clr);
            bead.index = bead_idx;
            bead.origin_index = bead_idx;
            beads[bead_idx] = bead;
            if(bead.left_clr != bead.right_clr) {
              Bead swapped = swap(bead);
              swapped.index = beads_n + ext++;
              beads[swapped.index] = swapped;
            }
          }
 
          int ext_beads_n = beads_n + ext;
          vvi necklace(beads_n);
          for(int bead_i = 0; bead_i < beads_n; ++bead_i) {
            for(int bead_j = 0; bead_j < ext_beads_n; ++bead_j) {
              if(bead_i != bead_j) {
                if(can_chain(beads[bead_i], beads[bead_j])) {
                  int bead_i_idx = beads[bead_i].index;
                  int bead_j_idx = beads[bead_j].index;
                  necklace[bead_i_idx].push_back(bead_j_idx);
                }
              }
            }
          }
        }
    }
}