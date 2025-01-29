#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>


namespace algorithms::onlinejudge::easy::division_nlogonia
{
    // https://onlinejudge.org/external/114/11498.pdf
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int n, d_x, d_y;
        while(scanf("%d", &n), n != 0)
        {
            int x, y;
            scanf("%d %d", &d_x, &d_y);
            while(n--)
            {
                scanf("%d %d", &x, &y);
                // the word ‘divisa’ (means border in Portuguese) if the residence 
                // is on one of the border lines (North-South or East-West);
                // North-South, d_x == x, // East-West, d_y == y
                if(d_x == x || d_y == y) printf("divisa\n");
                // ‘NO’ (means NW in Portuguese) if the residence is in Northwestern Nlogonia;
                else if(x < d_x && y > d_y) printf("NO\n");
                // ‘NE’ if the residence is in Northeastern Nlogonia;
                else if(x > d_x && y > d_y) printf("NE\n");
                // ‘SE’ if the residence is in Southeastern Nlogonia;
                else if(x > d_x && y < d_y) printf("SE\n");
                // ‘SO’ (means SW in Portuguese) if the residence is in Southwestern Nlogonia.
                else printf("SO\n");
            }
        }
    }
}