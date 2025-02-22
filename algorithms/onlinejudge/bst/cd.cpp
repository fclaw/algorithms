#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <set>




namespace algorithms::onlinejudge::bst::cd
{
    // https://onlinejudge.org/external/118/11849.pdf, 
    // use set to pass the time limit, better: use hashing!
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        int K, N;
        while(true)
        {
            scanf("%d %d\n", &K, &N);
            if(K == 0 && N == 0) break;
            std::set<int> disks;
            int disk;
            while(K--)
            {
                scanf("%d\n", &disk);
                disks.insert(disk);
            }

            int matches = 0;
            while(N--)
            {
                scanf("%d\n", &disk);
                if(disks.find(disk) != disks.end()) matches++;
            }
            printf("%d\n", matches);
        }   
    }
}