#pragma once

#include <numeric>


namespace algorithms::onlinejudge::graph::tools::tree
{
    template<typename T = int>
    T def = std::numeric_limits<T>::max();
    template<typename T = int>
    struct Tree
    {
        int node;
        T val;
        Tree* left = nullptr; 
        Tree* right = nullptr;
        Tree() {
          this->node = -1;
          this->val = def<T>;
        }
        Tree(T val, int node = -1) {
        this->node = node;
        this->val = val;
        }
    };
}