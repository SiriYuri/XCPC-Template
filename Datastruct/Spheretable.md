```cpp
template<typename T, typename Opt> 
struct SphereTable { // SphereTable<int, Opt> st(a, Opt());
    int n, m;
    std::vector<int> log;
    std::vector<std::vector<T>> st;
    Opt opt;

    SphereTable(const std::vector<T> &a, Opt(o)) : opt(o) {
        n = a.size() - 1;
        log.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            log[i] = log[i >> 1] + 1;
        }
        m = log[n] + 1;
        st.assign(m, std::vector<T> (n + 1));
        st[0] = a;
        for (int j = 1; j < m; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                st[j][i] = opt(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int k = log[r - l + 1];
        return opt(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

struct Opt {
    int operator () (const int &x, const int &y) const {
        return std::max(x, y);
    }
};
```
