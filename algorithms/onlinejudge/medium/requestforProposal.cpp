#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <string>


namespace algorithms::onlinejudge::easy::request_for_proposal
{
    // https://onlinejudge.org/external/101/10141.pdf, solvable with one linear scan
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
             
        int case_number = 0;
        bool first_case = true;
        while (true) 
        {
            int n, p;
            if (scanf("%d %d", &n, &p) != 2) break;  // Read n and p, exit on failure
        
            if (n == 0 && p == 0) break;  // Termination condition
        
            std::cin.ignore();  // Ignore the newline after numbers

            if (!first_case) std::cout << std::endl;  // Print a blank line between test cases
            first_case = false;

            // Read `n` requirement lines (ignored for now)
            std::string dummy;
            for (int i = 0; i < n; ++i) std::getline(std::cin, dummy);

            std::string best_proposal;
            double best_price = std::numeric_limits<double>::max();
            int best_met_requirements = -1;

            // Read `p` proposals
            for (int i = 0; i < p; ++i) 
            {
                std::string proposal_name;
                std::getline(std::cin, proposal_name);  // Read full proposal name
                
                double price;
                int r;
                scanf("%lf %d", &price, &r);
                std::cin.ignore();  // Ignore newline

                // Read `r` requirement lines (ignored)
                for (int j = 0; j < r; ++j) std::getline(std::cin, dummy);

                // Select the best proposal based on requirements first, then price
                if (r > best_met_requirements || 
                    (r == best_met_requirements && 
                     price < best_price)) 
                {
                    best_proposal = proposal_name;
                    best_price = price;
                    best_met_requirements = r;
                }
            }

            std::cout << "RFP #" << ++case_number << std::endl;
            std::cout << best_proposal << std::endl;  
        }
    }
}