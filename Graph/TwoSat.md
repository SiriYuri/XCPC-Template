k-SAT (k > 2) 是 NP-Hard 的     
对于 2-SAT, 按照依赖条件建边后, 判断 x 和 $\neg$ x 是否在一个 SCC 内, 是则误解, 否则贪心的选择更靠近叶子的, 也就是 SCC 标号更小的
$O(n + m)$   
如果要判断是否只有唯一解, 就需要在 tarjan 之后, 对每个 i, 判断 i 是否能到达 $\neg$ i, 或者 $\neg$ i 能否到达 i, 如果是, 说明一定要选择更靠近叶子的那个, 这个 i 只有唯一解   
是 $O(n ^ 2)$ 的
```cpp
struct TwoSat {
    int n;
    std::vector<std::vector<int>> e;
    std::vector<bool> ans;
    
    TwoSat(int n) : n(n), e(2 * n + 2), ans(n + 1) {}
    
    void add(int u, bool f, int v, bool g) {
        e[2 * u + !f].emplace_back(2 * v + g);
        e[2 * v + !g].emplace_back(2 * u + f);
    }
    
    bool work() {
        std::vector<int> id(2 * n + 2, -1), dfn(2 * n + 2, -1), low(2 * n + 2, -1);
        std::vector<int> stk;
        int now = 0, cnt = 0;
        
        auto tarjan = [&](auto self, int u) -> void {
            stk.emplace_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    self(self, v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };

        for (int i = 2; i <= 2 * n + 1; ++i) {
            if (dfn[i] == -1) {
                tarjan(tarjan, i);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false; 
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
};
```
