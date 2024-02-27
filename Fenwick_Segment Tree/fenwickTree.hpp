#include <vector>
#include <iostream>


class fenwickTree {
    std::vector<long long> __fenwickTree;

    public:
        fenwickTree(const std::vector<long long> &v) : __fenwickTree(v.size() + 1, 0) {
            for (size_t idx = 1; idx < __fenwickTree.size(); idx++) {
                __fenwickTree[idx] += v[idx - 1];
                if (idx + (idx & -idx) < __fenwickTree.size()) {
                    __fenwickTree[idx + (idx & -idx)] += __fenwickTree[idx];
                }
            }
        }
        void display() {
            for (long long e : __fenwickTree) std::cout << e << " ";
            std::cout << std::endl;
        }

        void updatePoint(unsigned long long idx, long long val) {
            idx++;
            for (; idx < __fenwickTree.size(); idx += idx & -idx) {
                __fenwickTree[idx] += val;
            }
        }

        long long queryPrefix(unsigned long long idx) {
            long long sum = 0;
            idx++;
            for (; idx; sum +=__fenwickTree[idx], idx -= idx & -idx);
            return sum;
        }

        long long queryPoint(unsigned long long idx) {
            return queryPrefix(idx) - queryPrefix(idx - 1);
        }

        long long queryInterval(unsigned long long l, unsigned long long r) {
            assert(r < __fenwickTree.size() && "Right interval out of range");
            assert(l >= 0 && "Left interval should be positive");
            return queryPrefix(r) - queryPrefix(l - 1);
        }
};

class fenwickTree_ {
    std::vector<long long> __suffixArr;
    std::vector<long long> __suffixArr_;
    std::vector<long long> __fenwickTree;
    std::vector<long long> __fenwickTree_;

    // 
    std::vector<long long> init(const std::vector<long long> &v) {
        std::vector<long long> tree(v.size() + 1);
        for (size_t idx = 1; idx < v.size() + 1; idx++) {
                tree[idx] += v[idx - 1];
                if (idx + (idx & -idx) < v.size() + 1) {
                    tree[idx + (idx & -idx)] += tree[idx];
            }
        }
        return tree;
    }

    long long queryPrefix(std::vector<long long> tree, unsigned long long idx) {
        long long sum = 0;
        // idx++; 
        // Since we ald r++ and l++ before pass them in so we do not idx++ again otherwise
        // the idx will out of vector size when we deal with right end point
        for (; idx; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }

    void updateTree_(size_t idx, long long val) {
        idx++;
        long long val_ = idx * val;
        for (; idx < __fenwickTree.size(); idx += idx & -idx) {
            __fenwickTree[idx] += val, __fenwickTree_[idx] += val_;
        }
    }

    void updateTree(size_t l, size_t r, long long val) {
        updateTree_(l, val);
        updateTree_(r + 1, -val);
    }

    public:
        fenwickTree_(const std::vector<long long> &v) : __fenwickTree(v.size() + 1, 0),
                                                        __fenwickTree_(v.size() + 1, 0), 
                                                        __suffixArr(v.size(), 0), 
                                                        __suffixArr_(v.size(), 0) {
            __suffixArr[0] = __suffixArr_[0] = v[0];
            for (size_t idx = 1; idx < v.size(); idx++) {
                __suffixArr[idx] = v[idx] - v[idx - 1];
                __suffixArr_[idx] = (idx + 1) * __suffixArr[idx];
            }
            __fenwickTree = init(__suffixArr);
            __fenwickTree_ = init(__suffixArr_);
        }

        long long queryInterval(unsigned long long l, unsigned long long r) {
            r++, l++; //  To adjust the algorithm for zero-indexed
            return (r + 1) * queryPrefix(__fenwickTree, r) - l * queryPrefix(__fenwickTree, l - 1) -
                   (queryPrefix(__fenwickTree_, r) - queryPrefix(__fenwickTree_, l - 1));
        }

        long long queryPrefix(unsigned long long idx) {
            return queryInterval(0, idx);
        }

        long long queryPoint(unsigned long long idx) {
            return queryInterval(idx, idx);
        }

        void updateInterval(size_t l, size_t r, long long val) {
            for (size_t idx = l; idx < r + 1; idx++) {
                if (idx != __suffixArr.size() - 1) {
                    __suffixArr[idx + 1] -=val;
                }
                __suffixArr[idx] += val;
                __suffixArr_[idx] = (idx + 1) * __suffixArr[idx];
            }
            updateTree(l, r, val);
        }

        void updatePoint(size_t idx, long long val) {
            updateInterval(idx, idx, val);
        }

        std::vector<long long> getOriginArr() {
            std::vector<long long> original(__suffixArr.size());
            original[0] = __suffixArr[0];
            for (size_t idx = 1; idx < __suffixArr.size(); idx++) {
                original[idx] = __suffixArr[idx] + original[idx - 1];
            }
            for (auto e : original) std::cout << e << " ";
            return original;
        }

        
        void display() {
            std::cout << "Suffix Array : " << std::endl;
            for (long long e : __suffixArr) std::cout << e << " ";
            std::cout << std::endl;
            std::cout << "Suffix Array_ : " << std::endl;
            for (long long e : __suffixArr_) std::cout << e << " ";
            std::cout << std::endl;
            std::cout << "Fenwick Tree : " << std::endl;
            for (long long e : __fenwickTree) std::cout << e << " ";
            std::cout << std::endl;
            std::cout << "Fenwick Tree_ : " << std::endl;
            for (long long e : __fenwickTree_) std::cout << e << " ";
            std::cout << std::endl;
        }


};


