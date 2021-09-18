#include "lib/template/template.hpp"

struct Tree {
    int64_t V, logV;
    vector<vector<int64_t>> data;
    vector<int64_t> depth;
    vector<vector<int64_t>> parent;

    Tree(int64_t v) : V(v), logV(0) {
        while (V > (1LL << logV)) ++logV;
        data = vector<vector<int64_t>>(V);
        depth = vector<int64_t>(V);
        parent = vector<vector<int64_t>>(logV, vector<int64_t>(V));
    }

    void init(int64_t r) {
        struct node {
            int64_t v, p, d;
        };
        stack<node> st;
        st.push(node{r, -1, 0});
        while (!st.empty()) {
            auto [v, p, d] = st.top();
            st.pop();
            depth[v] = d;
            parent[0][v] = p;
            for (auto i : data[v]) {
                if (i == p) continue;
                st.push(node{i, v, d + 1});
            }
        }
    }

    void build(int64_t r = 0) {
        this->init(r);
        for (int64_t k = 0; k < logV - 1; ++k) {
            for (int64_t v = 0; v < V; ++v) {
                if (parent[k][v] < 0)
                    parent[k + 1][v] = -1;
                else
                    parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    void add_edge(int64_t a, int64_t b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
    }

    int64_t lca(int64_t u, int64_t v) {
        if (depth[u] > depth[v]) swap(u, v);
        for (int64_t k = 0; k < logV; ++k) {
            if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
        }
        if (u == v) return u;

        for (int64_t k = logV - 1; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int64_t get_depth(int64_t a) { return depth[a]; }
    int64_t get_parent(int64_t a) { return parent[0][a]; }

    int64_t get_ancestor(int64_t a, int64_t d) {
        for (int64_t k = 0; d; d >>= 1, ++k) {
            if (d & 1) a = parent[k][a];
        }
        return a;
    }
};
