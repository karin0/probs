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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}char*gs(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return x+1;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p;*this>>p;if(c=='.'){int y=0,k=0;for(c=gc();isdigit(c);c=gc())y=y*10+(c-'0'),++k;x=(double)y/p_[k-1];if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 10003;

struct Point {
    double x, y;
    Point() {}
    Point(const Point &a, const Point &b) : x(b.x - a.x), y(b.y - a.y) {}
    double operator * (const Point &rh) const {
        return x * rh.y - y * rh.x;
    }
    bool operator < (const Point &rh) const {
        return x < rh.x || (x == rh.x && y < rh.y);
    }
    double norm() const {
        return x * x + y * y;
    }
} a[N], b[N];
typedef Point Vec;
double solve(cint n) {
    std::sort(a + 1, a + n + 1);
    int c = 0;
    rep (i, 1, n) {
        const Point &p = a[i];
        while (c > 1 && Vec(b[c - 1], b[c]) * Vec(b[c - 1], p) < 0)
            --c;
        b[++c] = a[i];
    }
    int t = c;
    per (i, n - 1, 1) {
        const Point &p = a[i];
        while (c > t && Vec(b[c - 1], b[c]) * Vec(b[c - 1], p) < 0)
            --c;
        b[++c] = a[i];
    }
    if (n > 1) --c;
    double ans = sqrt(Vec(b[c], b[1]).norm());
    re (i, 1, c)
        ans += sqrt(Vec(b[i], b[i + 1]).norm());
    ccc(ans);
    return ans;
};
int main() {
    int n = io;
    // int n;
    // scanf("%d", &n);
    rep (i, 1, n) {
        io >> a[i].x >> a[i].y;
        // scanf("%lf%lf", &a[i].x, &a[i].y);
    }
    // printf("%.2f\n", solve(n));
    io << io(solve(n), 2) daze; 
}


