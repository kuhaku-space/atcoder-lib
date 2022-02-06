#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A"
#include "graph/dijkstra_fibonacci.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m, r;
    cin >> n >> m >> r;
    Graph<int> g(n);
    g.input_edge(m, true);

    auto dist = dijkstra(g, r, Inf);
    rep(i, n) {
        if (dist[i] != Inf)
            co(dist[i]);
        else
            co("INF");
    }

    return 0;
}