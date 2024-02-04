#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>
#include "data_structure/bit_vector.hpp"
#include "segment_tree/monoid.hpp"

template <class T, class M, int L = 30>
struct wavelet_matrix_monoid {
  private:
    using U = typename M::value_type;

  public:
    wavelet_matrix_monoid() = default;
    template <class Value>
    wavelet_matrix_monoid(const std::vector<T> &v, const std::vector<Value> &u) : length(v.size()) {
        assert(v.size() == u.size());
        std::vector<int> l(length), r(length), ord(length);
        std::iota(ord.begin(), ord.end(), 0);
        for (int level = L - 1; level >= 0; level--) {
            matrix[level] = bit_vector(length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < length; i++) {
                if ((v[ord[i]] >> level) & 1) {
                    matrix[level].set(i);
                    r[right++] = ord[i];
                } else {
                    l[left++] = ord[i];
                }
            }
            mid[level] = left;
            matrix[level].build();
            ord.swap(l);
            for (int i = 0; i < right; i++) ord[left + i] = r[i];
            cs[level].resize(length + 1);
            cs[level][0] = M::id;
            for (int i = 0; i < length; i++) cs[level][i + 1] = M::op(cs[level][i], u[ord[i]]);
        }
    }

    U range_sum(int r, T x) const { return range_sum(0, r, x); }

    U range_sum(int l, int r, T x) const {
        for (int level = L - 1; level >= 0; level--)
            std::tie(l, r) = succ((x >> level) & 1, l, r, level);
        return cs[0][matrix[0].rank(false, r)] - cs[0][matrix[0].rank(false, l)];
    }

    U rect_sum(int l, int r, T upper) const {
        U res = 0;
        for (int level = L - 1; level >= 0; level--) {
            bool f = (upper >> level) & 1;
            if (f)
                res += cs[level][matrix[level].rank(false, r)] -
                       cs[level][matrix[level].rank(false, l)];
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    U rect_sum(int l, int r, T lower, T upper) const {
        return rect_sum(l, r, upper) - rect_sum(l, r, lower);
    }

  private:
    int length;
    bit_vector matrix[L];
    int mid[L];
    std::vector<U> cs[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {matrix[level].rank(f, l) + mid[level] * f,
                matrix[level].rank(f, r) + mid[level] * f};
    }
};
