#pragma once

#include <bits/stdc++.h>

template<typename F>
inline void loop(size_t n, F&& f) {
  for(size_t i = 0; i < n; ++i)
    std::forward<F>(f)(i);
}

// Overloading the >> operator for std::pair<int, int>
template<typename T1, typename T2>
std::istream& operator >> (std::istream& is, std::pair<T1, T2>& p) { return is >> p.first >> p.second; }

template<typename... Args>
bool while_read(Args&... args) { return (... && static_cast<bool>(std::cin >> args)); }


// --- RECOMMENDED ALTERNATIVE: Specialize std::hash ---
// This is often considered cleaner because you don't need to specify
// the hasher every time you declare a map.
// This specialization needs to be in the std namespace.
namespace std {
    template<typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        size_t operator()(const std::pair<T1, T2>& p) const {
            // Use the same robust combination logic.
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
}

template<typename T1, typename T2>
std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) 
{ return os << "{ " << p.first << ", " << p.second << "}"; }
