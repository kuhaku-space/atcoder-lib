#include "data_structure/radix_heap.hpp"
#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    radix_heap_dijkstra<_edge> p_que;
    dist[s] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist)) p_que.push(_edge{i.to, e.dist + i.dist});
        }
    }
    return dist;
}