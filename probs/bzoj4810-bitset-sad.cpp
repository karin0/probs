#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define go(e_,s_) for(Edge *e_=(s_);e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define crep(...) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define oper operator
#define daze << '\n'
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p;*this>>p;if(c=='.'){int y=0,k=0;for(c=gc();isdigit(c);c=gc())y=y*10+(c-'0'),++k;x=(double)y/p_[k-1];if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 100003;

int n, m, a[N], bel[N];
struct Query {
    int op, l, r, x;
    bool *ans;
    bool operator < (const Query &rh) const {
        return bel[l] < bel[rh.l] || (bel[l] == bel[rh.l] && r < rh.r);
    }
} qwq[N];
bool ans[N];
int l, r, cnt[N], mx;
std::bitset<100001> s1, s2;
void ins(cint x) {
    if (++cnt[x] == 1) s1.set(x), s2.set(mx - x);
}
void del(cint x) {
    if (--cnt[x] == 0) s1.reset(x), s2.reset(mx - x);
}
int main() {
    io >> n >> m;
    int sz = sqrt(3 * (double)n * n / m);
    int c = 0;
    rep (i, 1, n) {
        io >> a[i];
        mx = std::max(mx, a[i]);
        if (++c > sz) bel[i] = bel[i - 1] + 1, c = 1;
        else bel[i] = bel[i - 1];
    }
    rep (i, 1, m) {
        Query &q = qwq[i];
        io >> q.op >> q.l >> q.r >> q.x;
        q.ans = &ans[i];
        mx = std::max(mx, q.x);
    }
    std::sort(qwq + 1, qwq + m + 1);
    l = r = 1;
    ins(a[l = r = 1]);
    rep (i, 1, m) {
        const Query &q = qwq[i];
        while (l < q.l) del(a[l++]);
        while (l > q.l) ins(a[--l]);
        while (r < q.r) ins(a[++r]);
        while (r > q.r) del(a[r--]);
        int x = q.x;
        if (q.op == 1)
            *q.ans = x == 0 || (s1 & s1 << x).any();
        else if (q.op == 2)
            *q.ans = (!(x & 1) && s1.test(x >> 1)) || (s1 & s2 >> (mx - x)).any();
        else for (int d = 1; d * d <= x; ++d) if (x % d == 0 && s1.test(d) && s1.test(x / d)) {
            *q.ans = true;
            break;
        }
    }
    rep (i, 1, m)
        io << (ans[i] ? "yuno\n" : "yumi\n");
}


