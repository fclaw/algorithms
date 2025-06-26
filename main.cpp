#define DBG_MACRO_NO_WARNING

#include "algorithms/onlinejudge/graph/robot.cpp"
#include <chrono>
#include <iomanip>
#include <bits/stdc++.h>


int main(int argc, char* argv[])
{

    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);

    std::optional<char*> file = std::nullopt;
    bool debug_mode = true;
    if(argc > 1) file = std::make_optional(argv[1]);

    auto start = std::chrono::system_clock::now();
    // algorithm starts
    algorithms::onlinejudge::graph::robot::submit(file, debug_mode);
    // algorithm ends
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << std::endl << "time: " <<  std::fixed << std::setprecision(1) << (double)elapsed.count() / 1000 << "s\n";
}