#include <cassert>
#include <optional>
#include <iostream>

namespace contest::codeforces::contest2033::A
{

enum Player {  Sakurako = 1, Kosuke };

    std::string playerToString(Player p) 
    {
        std::string s;
        if(p == Sakurako) s = "Sakurako";
        if(p == Kosuke) s = "Kosuke";
        return s;
    }

    int makeMove(int r, int i) 
    { 
        int shift = 2 * r - 1;
        if(r % (int)Kosuke == 0) shift = shift * (-1);
        return i + shift;
    }
    Player determineWinner(int boundary) 
    {
        int i = 0, r = 1;
        while(std::abs(i) <= boundary) { i = makeMove(r, i); ++r; }
        --r;
        return r % (int)Kosuke == 0 ? Kosuke : Sakurako;
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        int tc;
        std::cin >> tc;
        while(--tc >= 0)
        {
            int boundary;
            std::cin >> boundary;
            Player p = determineWinner(boundary);
            printf("%s\n", playerToString(p).c_str());
        }
    }
}