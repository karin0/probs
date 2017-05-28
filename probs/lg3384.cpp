// Luogu 3384
// 树链剖分模板
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) ((x) + (((y) - (x)) >> 1))
const int MAXN = 100010;

int n, root, mod;

// Graph
int adj[MAXN], n_val[MAXN];
int e_to[MAXN], e_next[MAXN], e_last = 0;
void add_edge(int u, int v) {
    ++e_last; // u -> v
    e_to[e_last] = v;
    e_next[e_last] = adj[u];
    adj[u] = e_last;

    ++e_last; // v -> u
    e_to[e_last] = u;
    e_next[e_last] = adj[v];
    adj[v] = e_last;
}

int tr_pos[MAXN];
// Segment Tree
int st[4 * MAXN], lazy[4 * MAXN];
void build(int k, int l, int r) {
    if (l == r) {
        st[k] = n_val[tr_pos[k]];
    } else {
        int mid = MID(l, r);
        build(LC(k), l, mid);
        build(RC(k), mid + 1, r);
        st[k] = st[LC(k)] + st[RC(k)];
    }
}
void unlazy(int k, int l, int r) {
    lazy[LC(k)] = lazy[RC(k)] = lazy[k];
    int mid = MID(l, r);
    st[LC(k)] += lazy[k] * (mid - l + 1);
    st[RC(k)] += lazy[k] * (r - mid);
    lazy[k] = -1;
}
void update(int k, int l, int r, int tl, int tr, int d) { // add d to it
    if (tr < l || r < tl) return;
    if (tl <= l && r <= tr) {
        lazy[k] += d; // nodes in the subtrees need to be added d.
        st[k] += d * (r - l + 1); // itself is processed, so we trust all nodes we meet..
        st[k] %= mod;
    } else {
        if (lazy[k] != -1) unlazy(k, l, r);
        int mid = MID(l, r);
        update(LC(k), l, mid, tl, tr, d);
        update(RC(k), mid + 1, r, tl, tr, d);
        st[k] = (st[LC(k)] + st[RC(k)]) % mod; // Ensure st[k] is trustable
    }
}
int query(int k, int l, int r, int tl, int tr) {
    if (tr < l || r < tl) return 0;
    if (tl <= l && r <= tr) {
        return st[k];
    } else {
        if (lazy[k] != -1) unlazy(k, l, r);
        int mid = MID(l, r);
        return query(LC(k), l, mid, tl, tr) + query(RC(k), mid + 1, r, tl, tr);
    }
} 
void st_init() {
    memset(lazy, -1, sizeof(lazy));
    build(1, 1, n);
}
// Tree with HLD
int fa[MAXN], hson[MAXN], depth[MAXN], size[MAXN];
int htop[MAXN], hld[MAXN],  hld_last = 0; // tr_pos[MAXN];
void dfs1(int u, int deep) {
    int hson_size = -1;
    depth[u] = deep;
    size[u] = 1; // numbers of *already found* nodes in subtree(u)
    
    int v;
    for (int e = adj[u]; e; e = e_next[e]) {
        v = e_to[e];
        if (v != fa[u]) {
            fa[v] = u;
            dfs1(v, deep + 1);
            size[u] += size[v]; // as subtree(v) is completely found
            if (size[v] > hson_size) {
                hson_size = size[v];
                hson[u] = v;
            }
        }
    }
} // u is leaf <=> hson[u] == 0 <=> size[u] == 1
void dfs2(int u, int top) {
    htop[u] = top;
    hld[u] = ++hld_last;
    tr_pos[hld_last] = u;
    if (hson[u]) dfs2(hson[u], u);
    
    int v;
    for (int e = adj[u]; e; e = e_next[e]) {
        v = e_to[e];
        if (v != fa[u] && v != hson[u]) {
            dfs2(v, v);
        }
    }
}
void update_path(int x, int y, int z) { // path(x, y)
    while (htop[x] != htop[y]) {
        if (depth[x] > depth[y]) std::swap(x, y); // To assume dep[x] < dep[y]
        update(1, 1, n, hld[htop[y]], hld[y], z);
        y = fa[htop[y]];
    }
    if (depth[x] > depth[y]) std::swap(x, y); // To assume dep[x] < dep[y]
    update(1, 1, n, hld[x], hld[y], z);
}
int query_path(int x, int y) {
    int res = 0;
    while (htop[x] != htop[y]) {
        if (depth[x] > depth[y]) std::swap(x, y);
        res += query(1, 1, n, hld[htop[y]], hld[y]);
        y = fa[htop[y]];
    }
    if (depth[x] > depth[y]) std::swap(x, y); // To assume dep[x] < dep[y]
    res += query(1, 1, n, hld[x], hld[y]);
    return res;
}



void hld_init() {
    dfs1(root, 0);
    dfs2(root, root);
    st_init();
}
int main() {
    int q;
    int x, y, z;
    scanf("%d%d%d%d", &n, &q, &root, &mod);
    for (int i = 1; i <= n; ++i ) {
        scanf("%d", n_val + i);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
    }
    hld_init();
    int oper;
    while (q--) {
        scanf("%d", &oper);
        if (oper == 1) { // Add z to value of each node in path(x, y)
            scanf("%d%d%d", &x, &y, &z);
            update_path(x, y, z);
        } else if (oper == 2) { // Query sum of values of nodes in path(x, y)
            scanf("%d%d", &x, &y);
            printf("%d\n", query_path(x, y));
        } else if (oper == 3) { // Add z to value of each node in sub-tree(x)
            scanf("%d%d", &x, &z);
            update(1, 1, n, hld[x], hld[x] + size[x] - 1, z); // as hld[] is continous in a sub-tree
        } else { // Query sum of values of nodes in sub-tree(x)
            scanf("%d", &x);
            printf("%d\n", query(1, 1, n, hld[x], hld[x] + size[x] - 1)); // as hld[] is continous in a sub-tree
        }
    }
}
