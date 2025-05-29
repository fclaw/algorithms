#define DBG_MACRO_NO_WARNING

#include "algorithms/onlinejudge/dp/exactChange.cpp"
#include <chrono>
#include <iomanip>
#include <bits/stdc++.h>


int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::optional<char*> file = std::nullopt;
    bool debug_mode = true;
    if(argc > 1) file = std::make_optional(argv[1]);

    auto start = std::chrono::system_clock::now();
    // algorithm starts
    algorithms::onlinejudge::dp::exact_change::submit(file, debug_mode);
    // algorithm ends
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << std::endl << "time: " <<  std::fixed << std::setprecision(1) << (double)elapsed.count() / 1000 << "s\n";
}


// #include <iostream>
// using namespace std;

// int main() {
//     cout << "1\n";
//     for (int t = 0; t < 1; ++t) {
//         cout << "10000\n";           // price
//         cout << "40\n";             // number of coins
//         for (int i = 0; i < 40; ++i) {
//             cout << (100 * ((i % 5) + 1)) << "\n";  // e.g., 100, 200, 300, 400, 500
//         }
//         cout << "\n";
//     }
//     return 0;
// }