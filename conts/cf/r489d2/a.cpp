#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#define forn(__e,__u) for(Edge *__e=__u->e;__e;__e=__e->e)
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO{static cint L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(cchar ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,cchar end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(cchar*st,cchar end='\n'){while(*st)pc(*st++);if(end)pc(end);}void pd(cint x){pc('0'+x);pc('\n');}}io;

int a[100003];
int main() {
    static int i, x, f;
    int n = io;
    re (i, 0, n) {
        a[i] = io;
        if (a[i] == 0)
            f = 1;
    }
    std::sort(a, a + n);
    int *end = std::unique(a, a + n);
    io.print((int)(end - a - f));

    return 0;
}

