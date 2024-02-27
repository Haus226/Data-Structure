#include <bits/stdc++.h>
#include "bst.h"

template <typename T>
binTree<T>::binTree(const std::vector<T> &arr){
    for(T e: arr) insert(e);
}

template <typename T>
binTree<T>::binTree(const T& val){
    insert(val);
}

template<typename T>
void binTree<T>::insert(binNode **node, const T& val){
    if (*node == nullptr) {
        binNode* newNode = new binNode(val);
        *node = newNode;
        return;
    }
    if (val >= (*node)->data) insert(&(*node)->right, val);
    else insert(&(*node)->left, val);
}

template <typename T>
void binTree<T>::insert(const T& val) {
    insert(&root, val);
}

template<typename T>
void binTree<T>::remove(binNode **node, const T& val){
    binNode* pre = nullptr;
    binNode* cur = *node;

    // We should ensure that the node is not nullptr first
    while (cur && cur->data != val) {
        pre = cur;
        if (cur->data < val) cur = cur->right;
        else if (cur->data > val) cur = cur->left;
    }

    if (cur == nullptr) {        
        std::cout << "No such element exists.." << std::endl;
        return;
    }


    // Case 1 : No children
    if ((not cur->left) && (not cur->right)){
        if (cur == pre->left) pre->left = nullptr;
        else pre->right = nullptr;
    }

    // Case 2 : 1 child
    if (cur->left) pre->left = cur->left;
    else pre->right = cur->right;
    
    // Case 3 : 2 children
    if (cur->left && cur->right){
        // Or finding the most right node in the left subtree which > all left nodes but < all right nodes
        binNode* temp = cur->right;
        while (temp->left) temp = temp->left;
        T data = temp->data;
        // If its is the smallest in the right subtree then it either has no child or 1 right child
        // Because if it has 2 children or 1 left child then it is not the smallest
        remove(node, data);
        cur->data = data;
    }

}

template <typename T>
void binTree<T>::remove(const T& val){
    remove(&root, val);
}

template<typename T>
void binTree<T>::lvTranv(binNode **node){
    binNode* temp = *node;
    std::list<binNode*> queue;
    queue.push_back(temp);
    while (queue.size()){
        temp = queue.front();
        queue.pop_front();
        if (temp->left) queue.push_back(temp->left);
        if (temp->right) queue.push_back(temp->right);
        std::cout << temp->data << std::endl;
    }
}

template <typename T>
void binTree<T>::lvTranv(){
    lvTranv(&root);
}

template <typename T>
bool binTree<T>::find(binNode **node, const T& val){
    if (*node == nullptr) return false;
    if (val == (*node)->data) return true;
    else if (val > (*node)->data) return find(&(*node)->right, val);
    else return find(&(*node)->left, val);
}

template <typename T>
bool binTree<T>::find(const T& val){
    return find(&root, val);
}



