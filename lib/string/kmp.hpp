#include "template/template.hpp"

/**
 * @brief KMP法
 * @details 構築 $O(|S|)$
 * @see https://snuke.hatenablog.com/entry/2014/12/01/235807
 *
 * @tparam Container
 */
template <class Container>
struct KMP {
  private:
    Container t;
    std::vector<int> data;

  public:
    KMP(const Container &_t) : t(_t), data(_t.size() + 1) {
        data[0] = -1;
        int j = -1;
        for (int i = 0; i < t.size(); ++i) {
            while (j >= 0 && t[i] != t[j]) j = data[j];
            if (t[i + 1] == t[++j]) data[i + 1] = data[j];
            else data[i + 1] = j;
        }
    }

    /**
     * @brief 検索
     *
     * @param s 対象列
     * @return std::vector<int>
     */
    std::vector<int> search(const Container &s) {
        int n = s.size(), m = t.size();
        std::vector<int> res(n);
        int i = 0, j = 0;
        while (i + j < n) {
            if (j < m && t[j] == s[i + j]) {
                ++j;
                res[i + j - 1] = j;
                continue;
            }
            i += j - data[j];
            j = max(data[j], int(0));
        }
        return res;
    }
};
