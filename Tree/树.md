```cpp
namespace Tree {
    int n;
    std::vector<int> dep, parent, maxdep, len1, len2, p1, p2, up;
    std::vector<std::vector<std::pair<int, int>>> edge;

    void init(int _n) {
        n = _n;
        dep.assign(n + 1, 0);
        parent.assign(n + 1, 0);
        maxdep.assign(n + 1, 0);
        len1.assign(n + 1, 0);
        len2.assign(n + 1, 0);
        p1.assign(n + 1, 0);
        p2.assign(n + 1, 0);
        up.assign(n + 1, 0);
        edge.assign(n + 1, std::vector<std::pair<int, int>>());
    }

    void work(int root = 1) {
        dfs1(root, 0);
        dfs2(root, 0);
        dfs3(root, 0);
    }

    void addEdge(int u, int v, int w = 1) {
        edge[u].emplace_back(v, w);
        edge[v].emplace_back(u, w);
    }

    void dfs1(int p, int fa) {
        maxdep[p] = dep[p];
        for (auto [c, w] : edge[p]) {
            if (c != fa) {
                dep[c] = dep[p] + 1;
                parent[c] = p;
                dfs1(c, p);
                maxdep[p] = std::max(maxdep[p], maxdep[c]);
            }
        }
    }

    void dfs2(int p, int fa) {
        for (auto [c, w] : edge[p]) {
            if (c != fa) {
                dfs2(c, p);
                int x = len1[c] + w;
                if (x > len1[p]) {
                    len2[p] = len1[p];
                    p2[p] = p1[p];
                    len1[p] = x;
                    p1[p] = c;
                } else if (x > len2[p]) {
                    len2[p] = x;
                    p2[p] = c;
                }
            }
        }
    }

    void dfs3(int p, int fa) {
        for (auto [c, w] : edge[p]) {
            if (c != fa) {
                if (p1[p] == c) {
                    up[c] = std::max(up[p], len2[p]) + w;
                } else {
                    up[c] = std::max(up[p], len1[p]) + w;
                }
                dfs3(c, p);
            }
        }
    }

    int furthest(int p) {
        return std::max(len1[p], up[p]);
    }

    int radius, center, diam; // 中心, 直径, 半径
    void getCenter() { 
        center = 1; 
        for (int i = 1; i <= n; i++) {
            if (std::max(len1[i], up[i]) < std::max(len1[center], up[center])) {
                center = i;
            }
        }
        radius = std::max(len1[center], up[center]); 
        diam = len1[center] + up[center] + 1;    
    }

    int rem, cog; // 重心
    std::vector<bool> vis;
    
    int dfs4(int p) {
        vis[p] = 1;
        int s = 1, res = 0;
        for (auto [c, w] : edge[p]) {
            if (vis[c]) continue;
            int t = dfs4(c);
            res = std::max(res, t);
            s += t;
        }
        res = std::max(res, n - s);
        if (res < rem) {
            rem = res;
            cog = p;
        }
        return s;
    }

    void getCog() {
        vis.assign(n + 1, 0);
        rem = std::numeric_limits<int>::max() >> 1;
        cog = 1;
        dfs4(1);
    }
};
```
