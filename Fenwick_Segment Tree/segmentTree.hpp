#include <vector>
#include <cmath>
#include <cstdint>
#include <iostream>

class segmentTree {
    private:
        struct segmentTreeNode {
            long long l, r;
            long long q, lazy;
        };
        std::vector<segmentTreeNode> __segmentTree;

        void build(long long x, long long y, long long p, const std::vector<long long> &v) {
            __segmentTree[p].l = x, __segmentTree[p].r = y;
            if (x == y) {
                __segmentTree[p].q = v[x];
                return;
            }
            long long m = x + ((y - x) >> 1);
            build(x, m, p * 2 + 1, v), build(m + 1, y, p * 2 + 2, v);
            __segmentTree[p].q = __segmentTree[p * 2 + 1].q + __segmentTree[p * 2 + 2].q;
        }

        void pushdownUpdate(long long p) {
            if (__segmentTree[p].lazy) {
                __segmentTree[p * 2 + 1].q += __segmentTree[p].lazy * (__segmentTree[p * 2 + 1].r - __segmentTree[p * 2 + 1].l + 1);
                __segmentTree[p * 2 + 2].q += __segmentTree[p].lazy * (__segmentTree[p * 2 + 2].r - __segmentTree[p * 2 + 2].l + 1);
                __segmentTree[p * 2 + 1].lazy += __segmentTree[p].lazy;
                __segmentTree[p * 2 + 2].lazy += __segmentTree[p].lazy;
                __segmentTree[p].lazy = 0;
            }
        }

        void update(long long x, long long y, long long delta, long long p) {
            if (x <= __segmentTree[p].l && y >= __segmentTree[p].r) {
                __segmentTree[p].q += delta * ((__segmentTree[p].r - __segmentTree[p].l) + 1);
                __segmentTree[p].lazy += delta;
                return;
            }
            pushdownUpdate(p);
            long long m = __segmentTree[p].l + ((__segmentTree[p].r - __segmentTree[p].l) >> 1);
            if (x <= m) update(x, y, delta, p * 2 + 1);
            if (y > m) update(x, y, delta, p * 2 + 2);
            __segmentTree[p].q = __segmentTree[p * 2 + 1].q + __segmentTree[p * 2 + 2].q;
        }

        long long query(long long x, long long y, long long p) {
            if (x <= __segmentTree[p].l && y >= __segmentTree[p].r) return __segmentTree[p].q;
            pushdownUpdate(p);  
            // pushdownSet(p);
            long long ans = 0;  
            long long m = __segmentTree[p].l + ((__segmentTree[p].r - __segmentTree[p].l) >> 1);
            if (x <= m) ans += query(x, y, p * 2 + 1);
            if (y > m) ans += query(x, y, p * 2 + 2);
            return ans;
        }

        // Set the given interval to specific value instead of just update by some delta
        // = instead of += since we are set the value which does not need to know how much is the 
        // total change
        // void pushdownSet(long long p) {
            // if (__segmentTree[p].lazy) {
            //     __segmentTree[p * 2 + 1].q = __segmentTree[p].lazy * (__segmentTree[p * 2 + 1].r - __segmentTree[p * 2 + 1].l + 1);
            //     __segmentTree[p * 2 + 2].q = __segmentTree[p].lazy * (__segmentTree[p * 2 + 2].r - __segmentTree[p * 2 + 2].l + 1);
            //     __segmentTree[p * 2 + 1].lazy = __segmentTree[p].lazy;
            //     __segmentTree[p * 2 + 2].lazy = __segmentTree[p].lazy;
            //     __segmentTree[p].lazy = 0;
            // }
        // }

        // long long set(long long x, long long y, long long val, long long p) {
        //     if (x <= __segmentTree[p].l && y >= __segmentTree[p].r) {
        //         __segmentTree[p].lazy = val;
        //         __segmentTree[p].q = (y - x + 1) * val;
        //         return;
        //     }
        //     pushdownSet(p);   
        //     long long m = x + ((y - x) >> 1);
        //     if (x <= m) set(x, y, val, p * 2 + 1);
        //     if (y > m) set(x, y, val, p * 2 + 2);
        //     __segmentTree[p].q = __segmentTree[p * 2 + 1].q + __segmentTree[p * 2 + 2].q;
        // }

    public:
        segmentTree(const std::vector<long long> &v) {
            __segmentTree = std::vector<segmentTreeNode>(static_cast<std::int64_t>(2 * pow(2, ceil(log2(v.size()))) - 1));
            build(0, v.size() - 1, 0, v);
        }

        void show() {
            for (auto &e : __segmentTree) {
                std::cout << "Left, Right : " << e.l << " " << e.r << std::endl;
                std::cout << "Sum, Lazy : " << e.q << " " << e.lazy << std::endl;
            }
        }
        long long queryInterval(int l, int r) { return query(l, r, 0); }
        long long queryPrefix(unsigned long long idx) { return query(0, idx, 0); }
        void updateInterval(int l, int r, int delta) { update(l, r, delta, 0); }
        void updatePoint(unsigned long long idx, long long delta) {update(idx, idx, delta, 0); }

};