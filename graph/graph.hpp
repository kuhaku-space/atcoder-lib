#include "_base.hpp"

template <class T>
struct Graph {
    struct edge {
        int from, to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const edge &rhs) const { return rhs < *this; }
    };

    int V;
    vector<vector<edge>> edges;

    Graph(int v) : V(v) { edges = vector<vector<edge>>(V); }

    auto &operator[](int i) { return edges[i]; }
    const auto &operator[](int i) const { return edges[i]; }
    auto begin() { return edges.begin(); }
    const auto begin() const { return edges.begin(); }
    auto end() { return edges.end(); }
    const auto end() const { return edges.end(); }

    int size() const { return V; }

    void add_edge(int a, int b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
    }
    void add_edges(int a, int b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
        edges[b].push_back(edge{b, a, d});
    }
};
