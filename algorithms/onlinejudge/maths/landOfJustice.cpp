/*
───────────────────────────────────────────────────────────────
🧳 UVa 10499 The Land of Justice, rt: s
───────────────────────────────────────────────────────────────
 *
 *
 * --- Mathematical Analysis ---
 *
 * The core insight of this problem is that profit is generated exclusively from the
 * NEW surface area created when the sphere is cut into N pieces. The selling price
 * is based on the total surface area of all sold pieces.
 *
 * Let R = the radius of the sphere.
 * Let N = the number of pieces the sphere is divided into.
 *
 *
 * STEP 1: Define the Cost Price
 *
 * The businessman buys a single, solid sphere. The cost is its surface area.
 * Cost Price = Surface Area of a Sphere = 4 * π * R²
 *
 *
 * STEP 2: Define the Selling Price
 *
 * The selling price is the sum of the surface areas of all N pieces. To find this,
 * let's first determine the surface area of a single piece (a wedge), which consists
 * of a curved part and two flat, semi-circular faces.
 *
 *   a) Area of the curved part of one piece:
 *      The original sphere's surface area (4πR²) is divided equally among N pieces.
 *      Curved Area per piece = (4 * π * R²) / N
 *
 *   b) Area of the flat parts of one piece:
 *      Each cut creates two new semi-circular faces. A single wedge-shaped piece has
 *      two such flat faces. Two semi-circles of radius R form one full circle.
 *      Flat Area per piece = 2 * Area(Semi-circle) = Area(Circle) = π * R²
 *
 *   c) Total surface area of ONE piece:
 *      Area_one_piece = (Curved Area) + (Flat Area)
 *      Area_one_piece = (4πR² / N) + πR²
 *
 *   d) Total Selling Price (Revenue):
 *      This is the area of one piece multiplied by the number of pieces, N.
 *      Selling Price = N * Area_one_piece
 *      Selling Price = N * [ (4πR² / N) + πR² ]
 *      Selling Price = 4πR² + NπR²
 *
 *
 * STEP 3: Calculate the Profit Percentage
 *
 * The standard formula for profit percentage is:
 * Profit % = ( (Selling Price - Cost Price) / Cost Price ) * 100%
 *
 * Substitute the expressions from Step 1 and 2:
 * Profit % = ( (4πR² + NπR²) - 4πR² ) / ( 4πR² ) * 100%
 *
 *
 * STEP 4: Simplify the Expression
 *
 * The '4πR²' terms in the numerator cancel out:
 * Profit % = ( NπR² ) / ( 4πR² ) * 100%
 *
 * The 'πR²' terms cancel out, revealing that the profit is independent of the sphere's size:
 * Profit % = ( N / 4 ) * 100%
 * Profit % = N * 25%
 *
 *
 * EDGE CASE: N = 1
 *
 * If N=1, no cuts are made. The sphere is bought and sold as is.
 * Cost Price = 4πR²
 * Selling Price = 4πR²
 * Profit = 0%
 * Our formula only applies for N > 1, as the logic is based on creating new surfaces.
 *
 *
 * FINAL ALGORITHM:
 * For any given N > 1, the profit is N * 25%.
 * For N = 1, the profit is 0%.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;


namespace algorithms::onlinejudge::maths::land_of_justice
{
    /** https://onlinejudge.org/external/104/10499.pdf */
    int n;
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
        
        while(scanf("%d", &n) == 1 && n > 0) {
          printf("%lld%%\n", n == 1 ? 0 : (static_cast<ll>(n) * 100) / 4);
        } 
    }
}