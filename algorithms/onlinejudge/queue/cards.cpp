#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>


typedef std::vector<int> vi;
typedef std::queue<int> qi;


namespace algorithms::onlinejudge::queue::cards
{
    
    /** https://onlinejudge.org/external/109/10935.pdf */
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int N;
        while(true)
        {
            std::cin >> N;
            if(N == 0) break;

            vi discarded_cards;
            qi deck;
            for(int i = 1; i <= N; i++)
              deck.push(i);
           
            // Throw away the top card and move the
            // card that is now on the top of the deck to
            // the bottom of the deck.
            while(deck.size() != 1)
            {
                int x = deck.front();
                discarded_cards.push_back(x);
                deck.pop();
                int y = deck.front();
                deck.pop();
                deck.push(y);
            }

            cout << "Discarded cards:";
            if(discarded_cards.size() > 0) std::cout << " ";
            for(int i = 0; i < discarded_cards.size(); i++)
            {
                std::cout << discarded_cards[i];
                if(i != discarded_cards.size() - 1)
                  std::cout << ", ";
            }
            std::cout << std::endl;
            std::cout << "Remaining card: " << deck.front() << std::endl;    
        }
    }
}