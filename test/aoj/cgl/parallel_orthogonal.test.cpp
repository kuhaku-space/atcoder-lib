#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_A"
#include <iostream>
#include "geometry/geometry.hpp"

int main(void) {
    int q;
    std::cin >> q;
    while (q--) {
        Point<double> a, b, c, d;
        std::cin >> a >> b >> c >> d;
        Line l(a, b), r(c, d);
        if (parallel(l, r)) std::cout << 2 << std::endl;
        else if (orthogonal(l, r)) std::cout << 1 << std::endl;
        else std::cout << 0 << std::endl;
    }

    return 0;
}
