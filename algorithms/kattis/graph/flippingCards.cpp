/*
───────────────────────────────────────────────────────────────
🧳 Flipping Cards, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../aux.h"
#include "../../onlinejudge/graph/tools/mcbm.cpp"
#include "../../onlinejudge/debug.h"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;


struct Card
{
    int front_pic;
    int back_pic;
};

using v_card = std::vector<Card>;
using map_picture = std::unordered_map<int, int>;


namespace algorithms::kattis::graph::flipping_cards
{
    /** https://open.kattis.com/problems/flippingcards */
    int t_cases, cards_n;
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
          int pic_id = 0;
          while_read(cards_n);
          v_card cards(cards_n);
          map_picture pictures;
          for(int card_id = 0; card_id < cards_n; ++card_id) {
            Card card;
            while_read(card.back_pic);
            while_read(card.front_pic);
            cards[card_id] = card;
            if(!pictures.count(card.back_pic)) {
              pictures[card.back_pic] = pic_id++;
            }
            if(!pictures.count(card.front_pic)) {
              pictures[card.front_pic] = pic_id++;
            }
          }

          int L_SIZE = cards_n;
          int R_SIZE = pic_id;

          mcmb::vvi graph(L_SIZE);
          for(int card_id = 0; card_id < L_SIZE; ++card_id) {
            Card card = cards[card_id];
            if(pictures.count(card.back_pic)) {
              int pic_id = pictures[card.back_pic];
              graph[card_id].push_back(pic_id);
            }
            if(pictures.count(card.front_pic)) {
              int pic_id = pictures[card.front_pic];
              graph[card_id].push_back(pic_id);
            }
          }

          int matched_cards = 0;
          mcmb::kuhn kuhn_s(R_SIZE);
          for(int card_id = 0; card_id < L_SIZE; ++card_id) {
            kuhn_s.visited.assign(L_SIZE, false);
            bool is_matched = mcmb::try_kuhn(card_id, graph, kuhn_s);
            if(is_matched) matched_cards++;
          }
          std::cout << (matched_cards == cards_n ? "possible" : "impossible") << std::endl;
        }
    }
}