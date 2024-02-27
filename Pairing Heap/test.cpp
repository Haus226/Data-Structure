#include <bits/stdc++.h>
#include "pairingHeap.hpp"

using namespace std;

int main() {
    // using T = std::pair<int, std::string>;
    // auto f = [](std::pair<int, std::string> &a, std::pair<int, std::string> &b) {return a.second < b.second;};
    // PairingHeap<T, decltype(f)> heap(f);
    // Node<T> *p = new Node(std::make_pair(5, std::string("Oscar")));
    // heap.push(p);
    // p = new Node(std::make_pair(3, std::string("Cindy")));
    // heap.push(p);
    // p = new Node(std::make_pair(4, std::string("Batman")));
    // heap.push(p);

    // auto q = heap.pop();
    // std::cout << q.first << " " << q.second <<std::endl;
    // q = heap.pop();
    // std::cout << q.first << " " << q.second <<std::endl;
    // q = heap.pop();
    // std::cout << q.first << " " << q.second <<std::endl;

    vector<int> v = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> t;
    PairingHeap p(v, std::greater<int>()), q(v, std::greater<int>());
    // p.update(1, 100);
    p.meld(q);
    // p.print();

    for (int i = 0; i < v.size() * 2; i++) {
        t.push_back(p.pop());
    }
    for (int i : t) cout << i << " ";
    cout << endl;
    cout << "Sorted : " << is_sorted(t.begin(), t.end(), std::greater<int>()) << endl;


    // using T = int;
    // PairingHeap<T> p, q, h;
    // Node<T> *t = new Node(2);
    // p.push(t);
    // t = new Node(7);
    // p.push(t);
    // t = new Node(6);
    // Node<T> *f = t;
    // h.push(t);
    // t = new Node(9);
    // h.push(t);
    // p.push(h);
    // t = new Node(4);
    // q.push(t);
    // t = new Node(5);
    // q.push(t);
    // p.push(q);
    // p.decrease(f, 1);
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
    // std::cout << p.pop() << std::endl;
}