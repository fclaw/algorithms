#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>




typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;


namespace algorithms::onlinejudge::complete_search::wedding
{
    /** https://onlinejudge.org/external/106/10662.pdf, 3 nested loops  */
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        // The first line consists of three integers T, R, H 
        // indicating the number of travel agencies, restaurants and hotels, respectively. 
        int M, K, N;
        while(std::cin >> M >> K >> N)
        {
            vi travel_agencies(M), restaurants(K), hotels(N);
            vvb rest_to_hotel(K, vb(N, false)), hotel_to_ta(N, vb(M, false)), ta_to_rest(M, vb(K, false));

            int v;
            for(int i = 0; i < M; i++)
              for(int j = 0; j <= K; j++)
              {
                  std::cin >> v;
                  if(j == 0)
                    travel_agencies[i] = v;
                  else ta_to_rest[i][j - 1] = (v == 1);
              }


            for(int i = 0; i < K; i++)
              for(int j = 0; j <= N; j++)
              {
                 std::cin >> v;
                 if(j == 0) 
                  restaurants[i] = v;
                else rest_to_hotel[i][j - 1] = (v == 1);
            }

            for(int i = 0; i < N; i++)
              for(int j = 0; j <= M; j++)
              {
                  std::cin >> v;
                  if(j == 0)
                    hotels[i] = v;
                  else hotel_to_ta[i][j - 1] = (v == 1); 
              }

              int expenses = INT32_MAX;
              int travel_agency_idx, restaurant_idx, hotel_idx;
              for(int m = 0; m < M; m++)
                for(int k = 0; k < K; k++)
                  for(int n = 0; n < N; n++)
                    if(!ta_to_rest[m][k] && 
                       !rest_to_hotel[k][n] && 
                       !hotel_to_ta[n][m])
                    {
                        int sum = travel_agencies[m] + restaurants[k] + hotels[n]; 
                        if(expenses > sum)
                        {
                            expenses = sum;
                            travel_agency_idx = m;
                            restaurant_idx = k;
                            hotel_idx = n;
                        }
                    }

               if(expenses != INT32_MAX) 
                 printf("%d %d %d:%d\n", travel_agency_idx, restaurant_idx, hotel_idx, expenses);
               else printf("Don't get married!\n");  
        }
    }
}