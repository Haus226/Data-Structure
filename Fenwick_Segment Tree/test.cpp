#include <bits/stdc++.h>
using namespace std;
#include "segmentTree.hpp"
#include "fenwickTree.hpp"

int main(int argc, char** argv) {
    mt19937 gen(14);
    uniform_int_distribution<long long> randint(-100000, 1000000);
    int size = 1e3;
    cout << "Size : " << size  << endl;
    int verbose = 0;
    vector<long long> v(size);
    for (size_t i = 0; i < v.size(); i++) {
        v[i] = randint(gen);
        // v[i] = i + 1;
    }
    if (verbose) {
        for (size_t i = 0; i < size; i++) {
            cout << v[i] << " ";
        }
    }
    cout << endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    segmentTree s(v);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
  
    begin = std::chrono::steady_clock::now();
    fenwickTree t(v);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    begin = chrono::steady_clock::now();
    fenwickTree_ _(v);
    end = chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;



    // Check whether the same : 
    // for (size_t idx = 0; idx < v.size(); idx++) {
    //     if (verbose) {
    //         cout << "Idx : " << idx << endl;
    //         cout << "Segment Tree query Prefix : " << s.queryPrefix(idx) << endl;
    //         cout << "Fenwick Tree_ query Prefix : " << _.queryPrefix(idx) << endl;
    //         cout << "Fenwick Tree query Prefix : " << t.queryPrefix(idx) << endl;
    //     }
    //     assert(s.queryPrefix(idx) == _.queryPrefix(idx));
    //     assert(_.queryPrefix(idx) == t.queryPrefix(idx));
    //     assert(t.queryPrefix(idx) == s.queryPrefix(idx));
    //     for (size_t jdx = idx + 1; jdx < v.size(); jdx++) {
    //     if (verbose) {
    //         cout << "Jdx : " << jdx << endl;        
    //         cout << "Segment Tree query Interval : " << s.queryInterval(idx, jdx) << endl;
    //         cout << "Fenwick Tree_ query Interval : " << _.queryInterval(idx, jdx) << endl;
    //         cout << "Fenwick Tree query Interval : " << t.queryInterval(idx, jdx) << endl;
    //     }
    //         assert(s.queryInterval(idx, jdx) == _.queryInterval(idx, jdx));
    //         assert(_.queryInterval(idx, jdx) == t.queryInterval(idx, jdx));
    //         assert(t.queryInterval(idx, jdx) == s.queryInterval(idx, jdx));
    //     }
    // }
    cout << "Query Interval : Segment, Fenwick_, Fenwick : " << endl;

    begin = chrono::steady_clock::now();
    for (size_t idx = 0; idx < v.size(); idx++) {
        for (size_t jdx = idx + 1; jdx < v.size() ; jdx++) {
            // cout << idx << " " << jdx << endl;
            // cout << "Segement : " << s.queryInterval(idx, jdx) << endl;
            // cout << "Accumulate : " << accumulate(v.begin() + idx, v.begin() + jdx + 1, 0) << endl;
            // cout << v[jdx] << endl;
            assert(s.queryInterval(idx, jdx) == accumulate(v.begin() + idx, v.begin() + jdx + 1, 0ll));

        }
    }
    end = chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    begin = chrono::steady_clock::now();
    for (size_t idx = 0; idx < v.size(); idx++) {
        for (size_t jdx = idx + 1; jdx < v.size() ; jdx++) {
            assert(_.queryInterval(idx, jdx) == accumulate(v.begin() + idx, v.begin() + jdx + 1, 0));
            // _.queryInterval(idx, jdx);
        }
    }
    end = chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

    begin = chrono::steady_clock::now();
    for (size_t idx = 0; idx < v.size(); idx++) {
        for (size_t jdx = idx + 1; jdx < v.size() ; jdx++) {
            // t.queryInterval(idx, jdx);
            assert(t.queryInterval(idx, jdx) == accumulate(v.begin() + idx, v.begin() + jdx + 1, 0));

        }
    }
    end = chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;


    // _.getOriginArr();
    cout << "Exit..." << endl;


}