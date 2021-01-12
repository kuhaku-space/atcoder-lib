#include "_base.hpp"

template <class T>
struct Graph {
    struct edge {
        int64_t from, to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }

        bool operator>(const edge &rhs) const { return dist > rhs.dist; }

        edge &operator+=(const edge &rhs) {
            to = rhs.to;
            dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) { return edge(*this) += rhs; }
    };

    int64_t V;
    vector<T> dist;
    vector<vector<edge>> edges;

    Graph(int64_t v) : V(v) {
        edges = vector<vector<edge>>(V);
        dist = vector<T>(V, numeric_limits<T>::max());
    }

    void add_edge(int64_t a, int64_t b, T d = 1, bool is_dual = false) {
        edges[a].push_back(edge{a, b, d});
        if (is_dual) edges[b].push_back(edge{b, a, d});
    }
};