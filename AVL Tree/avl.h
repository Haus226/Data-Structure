#pragma once
#include <bits/stdc++.h>

template <typename T>
class avlTree {
    public:
        void insert(const T& val);
        void remove(const T& val);
        bool find(const T& val);
        void lvTranv();
        explicit avlTree(const T& val);
        avlTree(const std::vector<T> &arr);
    private:
        struct avlNode
        {
            T data;
            avlNode *left = nullptr;
            avlNode *right = nullptr;
            int height = 1;
            explicit avlNode(const T& val) : data(val) {}
        };

        avlNode *root = nullptr;
        void leftRotation(avlNode **node);
        void rightRotation(avlNode **node);
        void leftrightRotation(avlNode **node);
        void rightleftRotation(avlNode **node);
        int getHeight(avlNode **node);
        void insert(avlNode **node, const T& val);
        void balance(avlNode **node);
        void remove(avlNode **node, const T& val);
        bool find(avlNode **node, const T& val);
        void lvTranv(avlNode **node);
};

#include "avl.tpp"
