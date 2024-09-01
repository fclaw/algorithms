#include <vector>


namespace algorithms::graph::leetcode::snake
{

using grid = std::vector<std::vector<int>>;

    /**
     * https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations
     * In an n * n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). 
     * The grid has empty cells represented by zeros and blocked cells represented by ones. 
     * The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
     * In one move the snake can:
     * Move one cell to the right if there are no blocked cells there. 
     * This move keeps the horizontal/vertical position of the snake as it is.
     * Move down one cell if there are no blocked cells there. 
     * This move keeps the horizontal/vertical position of the snake as it is.
     * Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. 
     * In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c). */
    int minimumMoves(const grid& g) 
    {
        return 0;
    }
}