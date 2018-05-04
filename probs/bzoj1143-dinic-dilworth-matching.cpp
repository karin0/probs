#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <queue>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; // return s == t ? EOF : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(p = b, 1, L, stdout);
        *p++ = c;
    }
    template<class T>
    void print(T x, const bool nl = true) {
        static char c[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (nl)
            pc('\n');
    }
    void ps(const char *st, const bool nl = true) {
        while (*st)
            pc(*st++);
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 103, M = 10003, inf = 0x7f7f7f7f;
namespace g {
    struct Node {
        int d;
        struct Edge *e, *c;
    } g[N * 2], *s, *t;
    struct Edge {
        Node *v;
        Edge *e, *r;
        int c;
        Edge() {}
        Edge(Node *_u, Node *_v, const int _c) : v(_v), e(_u->e), c(_c) {
            _u->e = this;
        }
        void *operator new (size_t) {
            static Edge pool[(M + N * 2) * 2], *curr = pool;
            return curr++;
        }
    };
    int n;
    inline void arc(Node *const u, Node *const v, const int c) {
        new Edge(u, v, c);
        new Edge(v, u, 0);
        (u->e->r = v->e)->r = u->e;
    }
    bool bfs() {
        static Node *u, *v;
        std::queue<Node *> q;
        for (u = g + 1; u <= g + n; ++u)
            u->c = u->e, u->d = 0;
        s->d = 1;
        q.push(s);
        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (Edge *e = u->e; e; e = e->e) if (e->c > 0 && !(v = e->v)->d) {
                v->d = u->d + 1;
                if (v == t)
                    return true;
                q.push(v);
            }
        }
        return false;
    }
    int dfs(Node *const u, int lim = inf) {
        if (u == t || lim == 0)
            return lim; // ****
        int res = 0, f;
        Node *v;
        for (Edge *&e = u->c; e; e = e->e) if (e->c > 0 && ((v = e->v)->d == u->d + 1) && (f = dfs(v, std::min(e->c, lim))) > 0) {  // *****
            e->c -= f;
            e->r->c += f;
            lim -= f;
            res += f;
            if (lim == 0)
                return res;
        }
        return res;
    }
    int dinic() {
        static int res;
        for (res = 0; bfs(); res += dfs(s));
        return res;
    }
}

std::bitset<N> f[N];
int main() {
    static int i, j, k, n, m;
    n = io;
    m = io;
    g::n = n * 2 + 2;
    g::s = &g::g[g::n];
    g::t = g::s - 1;
    re (i, 0, m) {
        j = io;
        f[j].set((int)io);
    }
    rep (k, 1, n) rep (i, 1, n) if (f[i].test(k))
        f[i] |= f[k];
    rep (i, 1, n) rep (j, 1, n) if (f[i].test(j))
        g::arc(&g::g[i], &g::g[n + j], 1);
    rep (i, 1, n) {
        g::arc(g::s, &g::g[i], 1);
        g::arc(&g::g[n + i], g::t, 1);
    }
    io.print(n - g::dinic());

    io.flush();
    return 0;
}
