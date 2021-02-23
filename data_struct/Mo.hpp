#include "_base.hpp"

template <class F, class G>
struct Mo {
    vector<int64_t> left, right, order;
    bitset<1 << 20> v;
    int width, nl, nr, ptr;
    F add;
    G del;

    Mo(int n, F f, F g)
        : add(f), del(g), width((int)sqrt(n)), nl(0), nr(0), ptr(0), v() {}

    void insert(int l, int r) {
        left.push_back(l);
        right.push_back(r);
    }

    void build() {
        order.resize(left.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            if (left[a] / width != left[b] / width) return left[a] < left[b];
            return right[a] < right[b];
        });
    }

    int process() {
        if (ptr == order.size()) return -1;
        const auto id = order[ptr];
        while (nl > left[id]) distribute(--nl);
        while (nr < right[id]) distribute(nr++);
        while (nl < left[id]) distribute(nl++);
        while (nr > right[id]) distribute(--nr);
        return order[ptr++];
    }

    inline void distribute(int idx) {
        v.flip(idx);
        if (v[idx])
            add(idx);
        else
            del(idx);
    }
};