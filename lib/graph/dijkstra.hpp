#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    dist[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist)) p_que.emplace(i.to, e.dist + i.dist);
        }
    }
    return dist;
}
