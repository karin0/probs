#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
    #define ccccc(x) std::cerr << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
    #define ccccc(x) 0
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){static char c;for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static char c;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char c){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=c;}template<class T>void print(T x,const char end='\n'){static char c[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=c;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=c)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;

typedef long long ll;

const int N = 2001;
int n, h, f[N];
struct A {
    int a, b, s;
    bool operator < (const A &rh) const {
        return s < rh.s;
    }
} a[N];
int main() {
    static int i, j, k;
    n = io;
    rep (i, 1, n) {
        f[0] += (a[i].a = io);
        a[i].s = a[i].a + (a[i].b = io);
    }
    h = io;
    std::sort(a + 1, a + n + 1);
    rep (i, 1, n)
        f[i] = -1;
    rep (i, 1, n) {
        per (j, k, 0)
            if (f[j] + a[i].b >= h)
                f[j + 1] = std::max(f[j + 1], f[j] - a[i].a);
        if (f[k + 1] >= 0)
            ++k;
    }
    io.print(k);

    return 0;
}
