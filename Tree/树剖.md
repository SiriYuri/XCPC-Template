```cpp
namespace HLD {
    int n, cur;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;

    void init(int _n) {
        n = _n;
        siz.assign(n + 1, 0);
        top.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        parent.assign(n + 1, 0);
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        seq.assign(n + 1, 0);
        adj.assign(n + 1, {});
        cur = 1;
    }

    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }

    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto &v : adj[u]) {
            top[v] = (v == adj[u][0] ? top[u] : v);
            dfs2(v);
        }
        out[u] = cur;
    }

    void work(int root = 1) {
        top[root] = root;
        dep[root] = 1;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    int kthAncester(int u, int k) {
        if (!k) {
            return u;
        }
        if (dep[u] <= k) {
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }

    bool isAncester(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    int rootedParent(int root, int u) {
        std::swap(root, u);
        if (root == u) {
            return u;
        }
        if (!isAncester(root, u)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), root, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }

    int rootedSize(int root, int u) {
        if (root == u) {
            return n;
        }
        if (!isAncester(u, root)) {
            return siz[u];
        }
        return n - siz[rootedParent(root, u)];
    }

    int rootedLca(int root, int u, int v) {
        return lca(root, u) ^ lca(root, v) ^ lca(u, v);
    }
};
```
