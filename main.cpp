// #define DBG_MACRO_NO_WARNING

// #include "algorithms/onlinejudge/maths/bafana.cpp"
// #include <chrono>
// #include <iomanip>
// #include <bits/stdc++.h>
// #include <sys/resource.h>

// long get_memory_usage() {
//     struct rusage usage;
//     getrusage(RUSAGE_SELF, &usage);
//     return usage.ru_maxrss; // This returns memory in kilobytes (KB)
// }


// int main(int argc, char* argv[])
// {

//     // std::ios_base::sync_with_stdio(false);
//     // std::cin.tie(NULL);

//     std::optional<char*> file = std::nullopt;
//     bool debug_mode = true;
//     if(argc > 1) file = std::make_optional(argv[1]);

//     // Measure memory before algorithm starts
//     long mem_before = get_memory_usage();
//     auto start = std::chrono::system_clock::now();
//     // algorithm starts
//     algorithms::onlinejudge::maths::bafana::submit(file, debug_mode);
//     // algorithm ends
//     auto end = std::chrono::system_clock::now();
//     auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//     // Measure memory after algorithm ends
//     long mem_after = get_memory_usage();
//     std::cout << std::endl << "Time: " <<  std::fixed << std::setprecision(1) << (double)elapsed.count() / 1000 << "s, ";
//     std::cout << "Memory usage: " << (mem_after - mem_before) / 1024 << "Mb\n";
// }


#include <bits/stdc++.h>


template<typename... Args>
bool while_read(Args&... args) { return (... && static_cast<bool>(std::cin >> args)); }


namespace algorithms::onlinejudge::maths::bafana
{
    /** https://onlinejudge.org/external/118/11805.pdf */
    int t_cases, n, k, p, t_case = 1;
    void submit()
    {
       
        while_read(t_cases);
        while(t_cases--) {
          while_read(n, k, p);
          int last_player = (p % n + k) % n;
          printf("Case %d: %d\n", t_case++, last_player == 0 ? n : last_player);
        }  
    }
}

namespace bafana = algorithms::onlinejudge::maths::bafana;

int main() { bafana::submit(); }