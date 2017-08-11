#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = 0; i < n; i++)
#define MP make_pair
#define FI first
#define SE second
#define VI vector<int>
#define CLR(x) memset(x, 0, sizeof(x))
#define SZ(x) (x.size())
#ifdef QWERTIER
#define err(x) cerr<<x<<endl;
#else
#define err(x)
#endif

#define MOD 1000000007
typedef long long LL;

LL f[50][2][2][2], g[50][2][2][2];
void add(LL &x, LL dx) {
  x += dx;
  x %= MOD;
}
LL query(int x, int y, int k) {
  if (x == 0 || y == 0 || k == 0)
    return 0;
  x--;
  y--;
  k--;
  memset(f, 0, sizeof(f));
  memset(g, 0, sizeof(g));
  // (0..x) ^ (0..y) <= k
  for (int di = 0; di <= 30; di++) {
    for (int dx = 0; dx <= 1; dx++) {
      for (int dy = 0; dy <= 1; dy++) {
        for (int dk = 0; dk <= 1; dk++) {
          for (int cx = 0; cx <= 1; cx++) {
            for (int cy = 0; cy <= 1; cy++) {
              int ck = cx ^ cy;
              if (cx == 1 && dx == 1 && !((x>>di)&1))continue;
              if (cy == 1 && dy == 1 && !((y>>di)&1))continue;
              if (ck == 1 && dk == 1 && !((k>>di)&1))continue;

              if (di > 0) {
                add(f[di][dx][dy][dk], f[di-1][dx&(cx==((x>>di)&1))][dy&(cy==((y>>di)&1))][dk&(ck==((k>>di)&1))]);
                add(g[di][dx][dy][dk], g[di-1][dx&(cx==((x>>di)&1))][dy&(cy==((y>>di)&1))][dk&(ck==((k>>di)&1))]);
                add(g[di][dx][dy][dk], (ck<<di)*f[di-1][dx&(cx==((x>>di)&1))][dy&(cy==((y>>di)&1))][dk&(ck==((k>>di)&1))]%MOD);
              } else {
                add(f[di][dx][dy][dk], 1);
                add(g[di][dx][dy][dk], ck);
              }
              //printf("%d %d %d %d %I64d %I64d\n", di, dx, dy, dk, f[di][dx][dy][dk], g[di][dx][dy][dk]);
            }
          }
        }
      }
    }
  }
  return (g[30][1][1][1] + f[30][1][1][1]) % MOD;
}
int main() {
#ifdef QWERTIER
  freopen("in.txt", "r", stdin);
#endif
  int Q;
  scanf("%d", &Q);
  while (Q--) {
    int x1, y1, x2, y2, k;
    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
    printf("%I64d\n", ((query(x2,y2,k)-query(x1-1,y2,k)-query(x2,y1-1,k)+query(x1-1,y1-1,k)) % MOD + MOD)%MOD);
  }
  return 0;
}
