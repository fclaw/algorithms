#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <set>
#include <vector>



typedef std::multiset<int> msi;
typedef std::vector<std::pair<int, int>> vp;

namespace algorithms::onlinejudge::bst::lemmings
{
    // https://onlinejudge.org/external/9/978.pdf, simulation, use multiset
    void fightDuel(int& green, int& blue) 
    {
        if(green == blue) { green = 0; blue = 0; }
        else if(green > blue) { green -= blue; blue = 0; }
        else { blue -= green; green = 0; }
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);

        int tc;
        std::cin >> tc;
        while(tc--)
        {
            msi greens, blues;
            int battlefields, gN, bN;
            scanf("%d %d %d\n", &battlefields, &gN, &bN);
            int power;
            for(int i = 0; i < gN; i++)
            { std::cin >> power; greens.insert(power); }
            for(int i = 0; i < bN; i++)
            { std::cin >> power; blues.insert(power); }

            /** Imagine a war with 2 battlefields and a green army with powers 20 10 and a blue army with powers 10 10 15
             * The first round will have 20 vs 15 in battlefield 1 and 10 vs 10 in battlefield 2. 
             * After these battles, green race will still have a power 5 lemming (that won on
             * battlefield 1) and blue race will have one with power 10 (that did not fight). 
             * The ones in battlefield 2 died, since they both had the same power. 
             * After that comes a second round, and only battlefield 1 will have a fight, being 5 vs 10. 
             * The blue lemming wins, killing the last green soldier and giving the victory do the blue race */
            while(!greens.empty() &&
                  !blues.empty())
            {
                int b = 0;
                vp fights;
                // assignment to battlefields
                while(b++ < battlefields && 
                      !greens.empty() && 
                      !blues.empty())
                {
                    // ...
                    auto green_it = greens.find(*greens.rbegin());  // Find the last (largest) element
                    auto blue_it = blues.find(*blues.rbegin());    // Find the last (largest) element
                    
                    int green_warrior = *green_it;
                    int blue_warrior = *blue_it;
                    
                    fights.push_back({green_warrior, blue_warrior});
                    
                    greens.erase(green_it);  // Erase safely using iterator
                    blues.erase(blue_it);
                }

                // aftermath of a dual between green and blue (fightDuel)
                // and retrieval of winners to their armies
                for(auto it : fights) // ..
                {
                    int g = it.first;
                    int b = it.second;
                    fightDuel(g, b);
                    if(g != 0) greens.insert(g);
                    if(b != 0) blues.insert(b);
                }

            }
            
            if(greens.empty() && blues.empty())
              std::cout << "green and blue died\n";
            else if(blues.empty())
            {
                std::cout << "green wins\n";
                for(auto it = greens.rbegin(); 
                    it != greens.rend(); 
                    it++)
                  std::cout << *it << std::endl;
            }
            else
            {
                std::cout << "blue wins\n";
                for(auto it = blues.rbegin(); 
                    it != blues.rend(); 
                    it++)
                  std::cout << *it << std::endl; 
            }
            std::cout << std::endl;
        }
    }
}