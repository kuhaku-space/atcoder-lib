#include "template/template.hpp"

/**
 * @brief 行列ライブラリ
 *
 * @tparam T 要素の型
 */
template <class T>
struct Matrix {
    Matrix() = default;
    Matrix(int x) : v(x, std::vector<T>(x)) {}
    Matrix(int x, int y) : v(x, std::vector<T>(y)) {}
    Matrix(const std::vector<std::vector<T>> &_v) : v(_v) {}

    const auto &operator[](int i) const { return this->v[i]; }
    auto &operator[](int i) { return this->v[i]; }
    const auto begin() const { return this->v.begin(); }
    auto begin() { return this->v.begin(); }
    const auto end() const { return this->v.end(); }
    auto end() { return this->v.end(); }

    Matrix &operator+=(const Matrix &rhs) {
        assert(this->v.size() == rhs.v.size());
        assert(this->v[0].size() == rhs.v[0].size());
        for (int i = 0; i < this->v.size(); ++i) {
            for (int j = 0; j < this->v[0].size(); ++j) this->v[i][j] += rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator-=(const Matrix &rhs) {
        assert(this->v.size() == rhs.v.size());
        assert(this->v[0].size() == rhs.v[0].size());
        for (int i = 0; i < this->v.size(); ++i) {
            for (int j = 0; j < this->v[0].size(); ++j) this->v[i][j] -= rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator*=(const Matrix &rhs) {
        assert(this->v[0].size() == rhs.v.size());
        int x = this->v.size(), y = rhs.v[0].size(), z = rhs.v.size();
        std::vector<std::vector<T>> tmp(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int k = 0; k < z; ++k) {
                for (int j = 0; j < y; ++j) tmp[i][j] += this->v[i][k] * rhs.v[k][j];
            }
        }
        std::swap(this->v, tmp);
        return *this;
    }

    Matrix operator-() const {
        std::vector<std::vector<T>> tmp(this->v);
        for (auto &v : tmp)
            for (auto &x : v) x = -x;
        return Matrix(tmp);
    }

    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix &rhs) const { return Matrix(*this) -= rhs; }
    Matrix operator*(const Matrix &rhs) const { return Matrix(*this) *= rhs; }

    std::vector<T> operator*(const std::vector<T> &rhs) {
        assert(this->v[0].size() == rhs.size());
        int x = this->v.size(), y = this->v[0].size();
        std::vector<T> res(x);
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) res[i] += this->v[i][j] * rhs[j];
        }
        return res;
    }

    T det() const {
        assert(this->v.size() == this->v[0].size());
        std::vector<std::vector<T>> u(v);
        int n = u.size();
        T ans = 1;
        for (int i = 0; i < n; ++i) {
            if (u[i][i] == T(0)) {
                for (int j = i + 1; j < n; ++j) {
                    if (u[j][i] != T(0)) {
                        std::swap(u[j], u[i]);
                        ans *= -1;
                        break;
                    }
                }
                if (u[i][i] == T(0)) return T(0);
            }
            ans *= u[i][i];
            T t = T(1) / u[i][i];
            for (int j = i; j < n; ++j) u[i][j] *= t;
            for (int k = i + 1; k < n; ++k) {
                if (u[k][i] == T(0)) continue;
                ans *= u[k][i];
                t = T(1) / u[k][i];
                for (int j = i; j < n; ++j) u[k][j] = u[k][j] * t - u[i][j];
            }
        }
        return ans;
    }

    Matrix pow(std::int64_t k) const {
        assert(this->v.size() == this->v[0].size());
        int n = this->v.size();
        Matrix res(n, n), mul(this->v);
        res.unit_matrix();
        for (; k > 0; k >>= 1) {
            if (k & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    void unit_matrix() {
        assert(this->v.size() == this->v[0].size());
        int n = this->v.size();
        for (int i = 0; i < n; ++i) {
            this->v[i].assign(n, T(0));
            this->v[i][i] = T(1);
        }
    }

    Matrix transposed() const {
        int x = this->v[0].size(), y = this->v.size();
        std::vector<std::vector<T>> res(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                res[i][j] = this->v[j][i];
            }
        }
        return Matrix(res);
    }

    void print_debug() const {
        for (auto u : this->v) {
            std::cerr << "[";
            for (auto x : u) std::cerr << x << ", ";
            std::cerr << "]" << std::endl;
        }
    }

  private:
    std::vector<std::vector<T>> v;
};
