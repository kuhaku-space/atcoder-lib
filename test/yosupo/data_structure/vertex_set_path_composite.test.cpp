#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include "math/modint.hpp"
#include "segment_tree/segment_tree.hpp"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

using Mint = ModInt<>;

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<pair<Mint, Mint>> a(n);
    cin >> a;
    HLD hld(n);
    hld.input_edges(0);
    hld.build();
    using M = Affine<Mint>;
    using RM = Rev<M>;
    segment_tree<M> st1(n);
    segment_tree<RM> st2(n);
    rep (i, n) {
        st1.set(hld.get(i), a[i]);
        st2.set(hld.get(i), a[i]);
    }
    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            int p, a, b;
            cin >> p >> a >> b;
            st1.set(hld.get(p), {a, b});
            st2.set(hld.get(p), {a, b});
        } else {
            int u, v, x;
            cin >> u >> v >> x;
            auto l = M::id, r = M::id;
            auto f = [&](int u, int v) {
                l = M::op(st1.prod(u, v), l);
            };
            auto g = [&](int u, int v) {
                r = RM::op(st2.prod(u, v), r);
            };
            int lca = hld.lca(u, v);
            hld.for_each(lca, u, f);
            hld.for_each_edge(lca, v, g);
            auto ans = RM::op(l, r);
            co(ans.first * x + ans.second);
        }
    }

    return 0;
}