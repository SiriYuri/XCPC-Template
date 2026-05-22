返回 [最短路, 前驱节点, 路径数]
```cpp
auto dijk = [&] (int root) -> auto {
    std::vector<i64> dis(n + 1, inf<i64>), pre(n + 1, -1), cnt(n + 1);
    std::priority_queue<std::pair<i64, i64>, std::vector<std::pair<i64, i64>>, std::greater<std::pair<i64, i64>>> pq;
    dis[root] = 0;
    cnt[root] = 1;
    pq.emplace(0, root);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dis[u]) {
            continue;
        }
        for (auto [to, w] : edge[u]) {
            if (dis[to] > dis[u] + w) {
                dis[to] = dis[u] + w;
                pre[to] = u;
                cnt[to] = cnt[u];
                pq.emplace(dis[to], to);
            } else if (dis[to] == dis[u] + w) {
                cnt[to] += cnt[u];
            }
        }
    }
    return std::make_tuple(dis, pre, cnt);
};
```
