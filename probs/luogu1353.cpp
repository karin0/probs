/*
奶牛们打算通过锻炼来培养自己的运动细胞，作为其中的一员，贝茜选择的运动方式是每天进行N(1 <= N <= 10,000)分钟的晨跑。在每分钟的开始，贝茜会选择下一分钟是用来跑步还是休息。

贝茜的体力限制了她跑步的距离。更具体地，如果贝茜选择在第i分钟内跑步，她可以在这一分钟内跑D_i(1 <= D_i <= 1,000)米，并且她的疲劳度会增加1。不过，无论何时贝茜的疲劳度都不能超过M(1 <= M <= 500)。如果贝茜选择休息，那么她的疲劳度就会每分钟减少1，但她必须休息到疲劳度恢复到0为止。在疲劳度为0时休息的话，疲劳度不会再变动。晨跑开始时，贝茜的疲劳度为0。

还有，在N分钟的锻炼结束时，贝茜的疲劳度也必须恢复到0，否则她将没有足够的精力来对付这一整天中剩下的事情。

请你计算一下，贝茜最多能跑多少米。

输入输出格式

输入格式：
第1行: 2个用空格隔开的整数：N 和 M

第2..N+1行: 第i+1为1个整数：D_i

输出格式：
输出1个整数，表示在满足所有限制条件的情况下，贝茜能跑的最大距离
f(t, h) <- 第 t 分钟末疲劳度为 h 可已跑的最大距离
f(t, h) = max{ h + 1 > mh ? -INF : f(t - 1, h + 1), f(t - 1, h) + d[i]}
*/
#include <cstdio>
#include <algorithm>
#define MAXN 10005
#define MAXM 505
#define INF 2099999999

int n, mh;
int d[MAXN], f[MAXN][MAXM][2];
int main() {
    scanf("%d%d", &n, &mh);
    for (int t = 1; t <= n; ++t)
        scanf("%d", d + t);
    f[1][0][0] = 0;
    f[1][1][1] = d[1];
    f[1][0][1] = -INF;
    f[1][1][0] = -INF;
    for (int t = 2; t <= n; ++t) {
        for (int h = 0; h <= std::min(t, mh); ++h) {
            f[t][h][1] = std::max((h == 0) ? -INF : f[t - 1][h - 1][1], (h == 1) ? f[t - 1][0][0] : -INF) + d[t];
            f[t][h][0] = std::max((h == mh) ? -INF : std::max(f[t - 1][h + 1][0], f[t - 1][h + 1][1]), (h == 0) ? f[t - 1][0][0] : -INF);
        }
    }
    printf("%d\n", f[n][0][0]);
    return 0;
}
