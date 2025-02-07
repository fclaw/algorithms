#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>

typedef std::vector<std::string> vs;

namespace algorithms::adhoc::card
{
    /** https://onlinejudge.org/external/106/10646.pdf 
     * In this game, the value of a card is defined as the value of the card face if the card face shows a
     * number between 2 and 9, otherwise the value is 10. Initially there is a pile consisting of 52 cards with
     * card faces down. Take the top 25 cards of the pile in the hand. Set Y = 0. 
     * Then execute three times the following steps together:
     * • Take the top card of the cards of the pile and determine its value.
     * • Let the card value be X. Add X to Y .
     * • Put this card and the top (10 − X) cards of the pile away.
     * At last put the 25 remaining cards in your hand on top of the pile. The task is to determine the
     * Y -th card from the pile, counted from the bottom. */
    const size_t CARDS = 52;
    const size_t TOP_DECK = 25;
    const size_t BOTTOM_DECK = 27;
    const size_t R = 3;

    int determineValue(const std::string& card)
    { 
        int v = std::atoi(&card[0]);
        return v != 0 ? v : 10;
    }  
   
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc;
        std::cin >> tc;
        while(tc--)
        {
            std::string card;
            vs top_deck = vs(TOP_DECK);
            vs bottom_deck = vs(BOTTOM_DECK); 

            for(int i = 0; i < BOTTOM_DECK; i++)
              std::cin >> card,
              bottom_deck[i] = card;

            for(int i = 0; i < TOP_DECK; i++)
              std::cin >> card,
              top_deck[i] = card;

            int y = 0;
            int r = 0;
            auto ptr = --top_deck.end();
            // TD 4S 8C 7D JH 8H 7S KH 8S 2C 2S QH    6D 3H 3C KC 6S AS 5C 3S    QC AC JC 4C 6H
            // 1 round: QC AC JC 4C 6H
            // 2 round: 6D 3H 3C KC 6S AS 5C 3S
            // 3 round: QH
            // left: TD 4S 8C 7D JH 8H 7S KH 8S 2C 2S, y = 19
            while(r++ < R)
            {
                auto curr = *ptr;
                int x = determineValue(*ptr);
                y += x;
                ptr -= (11 - x);
                cout << "card: " << curr << ", y: " << y << ", next: " << *ptr << "\n";
            }

            std::cout << bottom_deck[y] << std::endl;  
        }
    }
}