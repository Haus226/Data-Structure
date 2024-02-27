#pragma once
#include <vector>

template <typename T>
class binTree{
    private:
        struct binNode
        {
            T data;
            binNode *left = nullptr;
            binNode *right = nullptr;
            explicit binNode(const T &data) : data(data) {}
        };
        binNode *root = nullptr;

        void insert(binNode **node, const T& val);
        void remove(binNode **node, const T& val);
        bool find(binNode **node, const T& val);
        void lvTranv(binNode **node);
    public:
        binTree(const std::vector<T> &arr);
        binTree(const T& data);
        void insert(const T& val);
        void remove(const T& val);
        bool find(const T& val);
        void lvTranv();
};

#include "bst.tpp"