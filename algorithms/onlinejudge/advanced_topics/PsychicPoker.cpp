/*
───────────────────────────────────────────────────────────────
🧳 UVa 131 The Psychic Poker Player, https://onlinejudge.org/external/1/131.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct Card {
  int rank;   // 2..14 (where T=10, J=11, Q=12, K=13, A=14)
  char suit;  // 'C', 'D', 'H', 'S'
  // 1. Required equality operator
  bool operator == (const Card& other) const {
    return rank == other.rank && suit == other.suit;
  }

  // Operator < comparing rank first, then suit as a tie-breaker
  bool operator < (const Card& other) const {
   return std::tie(this->rank, this->suit) < std::tie(other.rank, other.suit);
  }

};

// 2. Specializing std::hash for Card
namespace std {
    template <>
    struct hash<Card> {
        size_t operator()(const Card& card) const {
            int suit_id = 0;
            if (card.suit == 'D') suit_id = 1;
            else if (card.suit == 'H') suit_id = 2;
            else if (card.suit == 'S') suit_id = 3;

            // Perfect hash formula: maps every card uniquely to 0..51
            return (card.rank - 2) * 4 + suit_id;
        }
    };
}

using v_card = std::vector<Card>;
using vi = std::vector<int>;


// Map card character to numerical rank (2..14)
int parse_rank(char c) {
    if (c >= '2' && c <= '9') return c - '0';
    if (c == 'T') return 10;
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    if (c == 'A') return 14;
    return 0;
}

// Evaluates a 5-card hand and returns its rank from 1 (best) to 9 (worst)
int evaluate_hand(v_card hand) {
    // 1. Sort hand by rank ascending
    std::sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
        return a.rank < b.rank;
    });

    // 2. Check for Flush (all 5 cards have the same suit)
    bool is_flush = true;
    for (int i = 1; i < 5; ++i) {
        if (hand[i].suit != hand[0].suit) {
            is_flush = false;
            break;
        }
    }

    // 3. Check for Straight
    // High Straight (e.g. 10, J, Q, K, A)
    bool is_straight = (hand[4].rank - hand[0].rank == 4) &&
                       (hand[1].rank == hand[0].rank + 1) &&
                       (hand[2].rank == hand[0].rank + 2) &&
                       (hand[3].rank == hand[0].rank + 3);

    // Low Straight Ace-Low (A, 2, 3, 4, 5 -> parsed as 2, 3, 4, 5, 14)
    if (hand[0].rank == 2 && hand[1].rank == 3 && hand[2].rank == 4 && 
        hand[3].rank == 5 && hand[4].rank == 14) {
        is_straight = true;
    }

    // 4. Count rank frequencies
    std::map<int, int> counts;
    for (const auto& card : hand) {
        counts[card.rank]++;
    }

    // Collect frequencies and sort descending (e.g. [4, 1], [3, 2], [2, 2, 1], etc.)
    vi freqs;
    for (auto const& p : counts) {
        freqs.push_back(p.second);
    }
    std::sort(freqs.rbegin(), freqs.rend());

    // 5. Hierarchy Evaluation (from best 1 to worst 9)
    if (is_straight && is_flush) return 1; // straight-flush
    if (freqs == vi{4, 1}) return 2; // four-of-a-kind
    if (freqs == vi{3, 2}) return 3; // full-house
    if (is_flush)                       return 4; // flush
    if (is_straight)                    return 5; // straight
    if (freqs == vi{3, 1, 1}) return 6; // three-of-a-kind
    if (freqs == vi{2, 2, 1}) return 7; // two-pairs
    if (freqs == vi{2, 1, 1, 1}) return 8; // one-pair
    
    return 9; // highest-card
}

std::string rank_to_string(int rank) {
    static const std::vector<std::string> rank_names = {
        "",                 // 0 (unused)
        "straight-flush",   // 1
        "four-of-a-kind",   // 2
        "full-house",       // 3
        "flush",            // 4
        "straight",         // 5
        "three-of-a-kind",  // 6
        "two-pairs",        // 7
        "one-pair",         // 8
        "highest-card"      // 9
    };

    if (rank >= 1 && rank <= 9) {
        return rank_names[rank];
    }
    return "highest-card";
}

void backtrack(v_card& hand, const v_card& deck, int i, int j, int& max_hand) {
  int curr_max_hand = evaluate_hand(hand);
  max_hand = std::min(max_hand, curr_max_hand);

  if(i == (int)hand.size() || 
     max_hand == 1) {
    return;
  }

  // hold
  backtrack(hand, deck, i + 1, j, max_hand);
  // exchange
  Card old = hand[i];
  hand[i] = deck[j];
  backtrack(hand, deck, i + 1, j + 1, max_hand);
  hand[i] = old;
}


int get_max_hand(v_card hand, const v_card& deck) {

  int max_hand = INT32_MAX;
  std::sort(hand.begin(), hand.end());
  do {
    backtrack(hand, deck, 0, 0, max_hand);
  } while(std::next_permutation(hand.begin(), hand.end()));

  return max_hand;
}

std::string card_to_string(const v_card& cards, const std::unordered_map<Card, std::string>& card_to_str) {
  std::string str;
  for(auto card : cards) {
    str += card_to_str.at(card) + " ";
  }
  str.pop_back();
  return str;
}

namespace algorithms::onlinejudge::advanced_topics::psychic_poker_player
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

        std::string str;
        while(std::getline(std::cin, str)) {
          std::stringstream ss(str);
          v_card hand;
          v_card deck;
          int i = 0;
          std::string raw;
          std::unordered_map<Card, std::string> card_to_str;
          while(ss >> raw) {
            char rank = raw.front();
            char suit = raw.back();
            Card card = {parse_rank(rank), suit};
            if(i < 5) {
              hand.push_back(card);
            } else {
              deck.push_back(card);
            }
            card_to_str[card] = raw;
            ++i;
          }

          std::string s_hand = card_to_string(hand, card_to_str);
          std::string s_deck = card_to_string(deck, card_to_str);
          int max_hand = get_max_hand(hand, deck);
          printf("Hand: %s Deck: %s Best hand: %s\n", s_hand.c_str(), s_deck.c_str(), rank_to_string(max_hand).c_str());
        }
    }
}