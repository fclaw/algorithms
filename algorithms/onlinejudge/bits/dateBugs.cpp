#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <bitset>
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::bits::date_bugs
{

const size_t MAX_YEAR = 10000;
typedef std::vector<std::bitset<MAX_YEAR>> vb;

    // https://onlinejudge.org/external/7/700.pdf, can be solved with bitset
    // it may also be solved by pure mathematical approach mainly 
    // The Chinese Remainder Theorem (CRT) or 
    // incremental search with LCM is more efficient when dealing with large numbers.
    const int MAX_RECORDS = 20;
    void submit(std::optional<char*> file)
    {
        if(file.has_value())
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
       
        /**
         * The input file contains several test cases, in which the actual year has to be calculated. The description
         * of each case starts with a line containing an integer n (1 ≤ n ≤ 20), the number of computers. Then,
         * there is one line containing three integers yi, ai, bi for each computer (0 ≤ ai ≤ yi < bi < 10000). 
         * yi is the year the computer displays, bi is the year in which the bug happens 
         * (i.e. the first year which can’t be displayed by this computer) and ai 
         * is the year that the computer displays instead of bi 
         * */
        int machines, c = 0;
        while(true)
        {
            std::cin >> machines;
            if(!machines) break;
            int actual_year;
            vb machines_years;
            machines_years.reserve(machines);
            while(machines--)
            {
                // year – The actual year, which we are trying to determine. 
                // It may or may not match the displayed year on a given machine.
                int year; 
                //  The year that is displayed instead of B due to a bug. 
                // If the machine were functioning correctly, it would show B when the actual year is Y.
                int wrong_year;
                // 	B – The first year in which the bug was detected (i.e., when a machine first started displaying the wrong year).
                int detected_year;
                scanf("%d %d %d", &year, &wrong_year, &detected_year);
                int diff = detected_year - wrong_year;
                std::bitset<MAX_YEAR> years;
                for(int y = year; y < MAX_YEAR; y += diff)
                  years.set(y);
                machines_years.push_back(years);
            }

            std::bitset<MAX_YEAR> tmp = machines_years[0];
           
            for(int i = 1; i < machines_years.size() && !tmp.none(); i++)
              tmp &= machines_years[i];
            
            actual_year = tmp._Find_first();
              
            //For each test case, output the line ‘Case #k:’, where k is the number of the situation. Then, output
            // the line ‘The actual year is z.’, where z is the smallest possible year (satisfying all computers and
            // being greater or equal to u = max(sum i from 1 to n ai). 
            // If there is no such year less than 10000, output ‘Unknown bugs detected.’.
            if(actual_year == MAX_YEAR) printf("Case #%d:\nUnknown bugs detected.\n\n", ++c);
            else printf("Case #%d:\nThe actual year is %d.\n\n", ++c, actual_year);
        }
    }
}