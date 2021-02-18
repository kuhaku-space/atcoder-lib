#include "_base.hpp"

struct prime_number {
    const int sz = 1 << 22;
    bitset<1 << 22> is_not_prime;
    vector<int64_t> data;

    prime_number() { init(); }

    void init() {
        is_not_prime[0] = is_not_prime[1] = true;
        for (int64_t i = 2; i < sz; ++i) {
            if (!is_not_prime[i]) {
                data.emplace_back(i);
                for (int64_t j = 2; i * j < sz; ++j) {
                    is_not_prime[i * j] = true;
                }
            }
        }
    }

    bool is_prime(int64_t n) {
        assert(n >= 0);
        if (n < sz) return !is_not_prime[n];
        for (auto i : data) {
            if (i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    // 素因数分解
    vector<pair<int64_t, int64_t>> prime_factorization(int64_t n) {
        vector<pair<int64_t, int64_t>> res;

        for (auto i : data) {
            int64_t cnt = 0;
            for (; n % i == 0; n /= i) cnt++;
            if (cnt) res.emplace_back(i, cnt);
            if (n < i * i) break;
        }
        if (n != 1) res.emplace_back(n, 1);

        return res;
    }

    int64_t pow_int(int64_t x, int64_t n) {
        assert(n >= 0);
        int64_t res = 1;
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= x;
            x *= x;
        }
        return res;
    }

    // 約数列挙
    vector<int64_t> divisors(int64_t n) {
        auto v = prime_factorization(n);

        vector<int64_t> res, a, b, cp;
        res.emplace_back(1);
        for (auto p : v) {
            cp.resize(res.size());
            copy(res.begin(), res.end(), cp.begin());
            a.resize(res.size());
            for (int64_t k = 1; k <= p.second; ++k) {
                int64_t t = pow_int(p.first, k);
                for (int64_t i = 0; i < a.size(); ++i) a[i] = cp[i] * t;
                merge(res.begin(), res.end(), a.begin(), a.end(),
                      back_inserter(b));
                swap(res, b);
                b.clear();
            }
        }

        return res;
    }

    // 因数分解列挙
    vector<vector<int64_t>> factorization(int64_t n) {
        vector<vector<int64_t>> res;

        auto f = [&](auto self, vector<int64_t> v, int64_t a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };

        f(f, vector<int64_t>(), n);
        return res;
    }
};
prime_number pn;
