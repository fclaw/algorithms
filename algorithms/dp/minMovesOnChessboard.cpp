#include <tuple>
#include <vector>
#include <iostream>
#include <iomanip>

using MinMovesOfPiDp = std::vector<std::vector<int>>;

void printMinMovesOfPiDp(MinMovesOfPiDp dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::dp
{
    /*
       In the game of chess a Knight can move 2.5 steps a( square that can be reached by moving two squares horizontally 
       and one square vertically, or two squares vertically and one square horizontally). 
       A King, can move only one step (either horizontally, vertically or diagonally).
       We have designed a special piece that can move either like a knight or like a king.
       call it Pi.
      
      Given that Pi on a particular cell, and you want ot move ti ot another
      cell then what si the minimum number of moves it takes Pi go from source to destination. 
      Write a function that accepts source and destination cells and 
      return the minimum number of moves it will take Pi to move from source to destination cell.
    */
   int minMovesOfPiDp(std::tuple<int, int> source, std::tuple<int, int> dest)
   {
       int source_x, source_y, dest_x, dest_y;
       std::tie(source_x, source_y) = source;
       std::tie(dest_x, dest_y) = dest;
       MinMovesOfPiDp dp(8, std::vector<int>(8, -1));

       dp[source_y][source_x] = 1;

       for (int i = 0; i < 8; i++)
         for (int j = 0; j < 8; j++)
         {
            if(i == source_y && j == source_x)
              continue;  
            int move1 = i - 2 >= 0 && j - 1 >= 0 ? 1 + dp[i - 2][j - 1] : 0;
            int move2 = i - 2 >= 0 && j + 1 < 8 ? 1 + dp[i - 2][j + 1] : 0;
            int move3 = i - 1 >= 0 && j + 2 < 8 ? 1 + dp[i - 1][j + 2] : 0; 
            int move4 = i + 1 < 8 && j + 2 < 8 ? 1 + dp[i + 1][j + 2] : 0;
            int move5 = i + 2 < 8 && j + 1 < 8 ? 1 + dp[i + 2][j + 1] : 0;
            int move6 = i + 2 < 8 && j - 1  >= 0 ? 1 + dp[i + 2][j - 1] : 0;
            int move7 = i + 1 < 8 && j - 2 >= 0 ? 1 + dp[i + 1][j - 2] : 0;
            int move8 = i - 1 >= 0 && j - 2 >= 0 ? 1 + dp[i - 1][j - 2] : 0;

            dp[i][j] += std::min(move1, std::min(move2, std::min(move3, std::min(move4, std::min(move5, std::min(move6, std::min(move7, move8)))))));
         }
        
       printMinMovesOfPiDp(dp);

       return dp[dest_y][dest_x];
   }
}