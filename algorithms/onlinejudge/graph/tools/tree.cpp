#pragma once


namespace algorithms::onlinejudge::graph::tools::tree
{
    template<typename T = int>
    struct Tree
    {
        int node;
        T val;
        Tree* left = nullptr; 
        Tree* right = nullptr;
        Tree(T val, int node = -1) {
        this->node = node;
        this->val = val;
        }
    };
}