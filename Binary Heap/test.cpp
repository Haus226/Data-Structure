#include <bits/stdc++.h>
#include "binHeap.hpp"
using namespace std;

int main(int argc, char **argv) {
    // random_device rd;
    // mt19937 gen(rd());
    // std::uniform_int_distribution<int> rand(1, 1000);
    // vector<int> v, q;
    // for (int i = 0; i < 15; i++) {
    //     v.push_back(rand(gen));
    // }
    vector<int> v = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> t;
    binHeap p(v, std::greater<int>()), q(v, std::greater<int>());
    p.update(1, 100);
    p.meld(q);
    p.sort();
    p.print();

    for (int i = 0; i < v.size() * 2; i++) {
        t.push_back(p.pop());
    }
    cout << "Sorted : " << is_sorted(t.begin(), t.end(), std::greater<int>()) << endl;

    // cout << "Sorted : " << is_sorted(q.begin(), q.end(), std::greater<int>()) << endl;


    // random_device rd;
    // mt19937 gen(rd());
    // std::uniform_int_distribution<int> rand;
    // vector<int> v, q;
    // for (int i = 0; i < 100000; i++) {
    //     v.push_back(rand(gen));
    // }
    // binHeap p(v);
    // for (int i = 0; i < 100000; i++) {
    //     q.push_back(p.pop());
    // }
    // cout << is_sorted(q.begin(), q.end()) << endl;
}