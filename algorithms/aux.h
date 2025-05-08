#pragma once

#include <iostream>

template<typename F>
inline void loop(size_t n, F&& f)
{
    for (size_t i = 0; i < n; ++i)
      std::forward<F>(f)(i);
}

template<typename... Args>
bool while_read(Args&... args) { return (... && static_cast<bool>(std::cin >> args)); }