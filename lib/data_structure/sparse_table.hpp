#pragma once
#include "internal/internal_bit.hpp"
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief スパーステーブル
 *
 * @tparam M モノイド
 */
template <class M>
struct sparse_table {
  private:
    using T = typename M::value_type;

  public:
    sparse_table(const std::vector<T> &v) : _size(v.size()), lookup(v.size() + 1), data() {
        int b = std::max(1, internal::countr_zero(internal::bit_ceil(_size)));
        data.emplace_back(v);
        for (int i = 1; i < b; ++i) data.emplace_back(_size + 1 - (1 << i));
        for (int i = 1; i < b; ++i) {
            for (int j = 0; j + (1 << i) <= _size; ++j) {
                data[i][j] = M::op(data[i - 1][j], data[i - 1][j + (1 << (i - 1))]);
            }
        }
        for (int i = 3; i <= _size; ++i) lookup[i] = lookup[(i + 1) >> 1] + 1;
    }

    T prod(int l, int r) const {
        assert(0 <= l && l < r && r <= _size);
        int b = lookup[r - l];
        return M::op(data[b][l], data[b][r - (1 << b)]);
    }

  private:
    int _size;
    std::vector<int> lookup;
    std::vector<std::vector<T>> data;
};
