#include <bits/stdc++.h>
#include "avl.h"

// There are totally four cases which will violate the balancing of a node
// Case 1 : Insertion at the left subtree of the left child of the node --> Rebalance by right rotation
// Case 2 : Insertion at the right subtree of the right child of the node --> Rebalance by left rotation
// Case 3 : Insertion at the left subtree of the right child of the node --> Rebalance by left right rotation
// Case 4 : Insertion at the right subtree of the left child of the node --> Rebalance by right left rotation

template<typename T>
avlTree<T>::avlTree(const T& val){
    insert(val);
}

template<typename T>
avlTree<T>::avlTree(const std::vector<T> &arr){
    for(T e : arr) insert(e);
}

template<typename T>
void avlTree<T>::leftRotation(avlNode **node){
    avlNode *rightChild = (*node)->right;
    (*node)->right = rightChild->left;
    rightChild->left = *node;
    (*node)->height = getHeight(node);
    rightChild->height = getHeight(&rightChild);
    *node = rightChild;
}

template<typename T>
void avlTree<T>::rightRotation(avlNode **node){
    avlNode *leftChild = (*node)->left;
    (*node)->left = leftChild->right;
    leftChild->right = *node;
    //Update height
    (*node)->height = getHeight(node);
    leftChild->height = getHeight(&leftChild);
    *node = leftChild;
}

template<typename T>
void avlTree<T>::leftrightRotation(avlNode **node){
    // Reduce the problem into the form of case 1
    leftRotation(&(*node)->left);
    rightRotation(node);
}

template<typename T>
void avlTree<T>::rightleftRotation(avlNode **node){
    // Reduce the problem into the form of case 2
    rightRotation(&(*node)->right);
    leftRotation(node);
}

template<typename T>
int avlTree<T>::getHeight(avlNode **node){
    if (*node == nullptr) return 0;
    else return std::max(getHeight(&(*node)->left), getHeight(&(*node)->right)) + 1;
}

template<typename T>
void avlTree<T>::insert(avlNode** node, const T& val){
    if (*node == nullptr) {
        avlNode* newNode = new avlNode(val);
        *node = newNode;
        return;
    }
    if (val >= (*node)->data) insert(&(*node)->right, val);
    else insert(&(*node)->left, val);
    balance(node);
}

template<typename T>
void avlTree<T>::balance(avlNode** node){
    if (*node == nullptr) return;

    if (getHeight(&(*node)->left) - getHeight(&(*node)->right) > 1){
        // The left node is deeper or in other words, the new node was inserted at the left child
        if (getHeight(&((*node)->left->left)) >= getHeight(&((*node)->left->right)))
            // The left subtree is deeper or in other words, 
            // the new node was inserted at the left subtree of the left child
            rightRotation(node);
            // The right subtree is deeper or in other words,
            // the new node was inserted at the right subtree of the left child
        else leftrightRotation(node);
    }

    else if (getHeight(&(*node)->right) - getHeight(&(*node)->left) > 1){
        if (getHeight(&((*node)->right->right)) >= getHeight(&((*node)->right->left)))
            leftRotation(node);
        else {
            rightleftRotation(node);
        }
    }

    (*node)->height = getHeight(node);
}

template<typename T>
void avlTree<T>::lvTranv(avlNode** node){
    avlNode* temp = *node;
    std::list<avlNode*> queue;
    queue.push_back(temp);
    while (queue.size()){
        temp = queue.front();
        queue.pop_front();
        if (temp->left) queue.push_back(temp->left);
        if (temp->right) queue.push_back(temp->right);
        std::cout << "Parent : " << temp->data << std::endl;
        if (temp->left) std::cout << "Left child : " << temp->left->data << std::endl;
        if (temp->right) std::cout << "Rigth child : " << temp->right->data << std::endl;
    }
}

template <typename T>
bool avlTree<T>::find(avlNode** node, const T& val){
    if (*node == nullptr) return false;
    if (val == (*node)->data) return true;
    else if (val > (*node)->data) return find(&(*node)->right, val);
    else return find(&(*node)->left, val);
}

template<typename T>
void avlTree<T>::remove(avlNode** node, const T& val){
    avlNode* pre = nullptr;
    avlNode* cur = *node;

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
        avlNode* temp = cur->right;
        while (temp->left) temp = temp->left;
        T val = temp->data;
        // If its is the smallest in the right subtree then it either has no child or 1 right child
        // Because if it has 2 children or 1 left child then it is not the smallest
        remove(node, val);
        cur->data = val;
    }

    balance(node);

}

template <typename T>
void avlTree<T>::remove(const T& val){
    remove(&root, val);
}

template<typename T>
void avlTree<T>::insert(const T& val){
    insert(&root, val);
}

template <typename T>
bool avlTree<T>::find(const T& val){
    return find(&root, val);
}

template<typename T>
void avlTree<T>::lvTranv(){
    lvTranv(&root);
}

