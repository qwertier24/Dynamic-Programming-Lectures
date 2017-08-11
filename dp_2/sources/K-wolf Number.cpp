#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 1, ##i_ED = n; i <= ##i_ED; i++)
#define REP(i, n) for(int i = 0, i##_ED = n; i < i##_ED; i++)
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
typedef long long LL;

LL dp[20][2][10010][2];
int vis[20][2][100010][2];
LL dfs(int cur, int lim, int suf, int pre0) {
  if (vis[cur][lim][suf][pre0])
    return dp[cur][lim][suf][pre0];
  if (lim == 0) {
    REP (i, 10) {
    }
  }
}
LL calc(LL n, int k) {
}

int main() {
#ifdef QWERTIER
  freopen("in.txt", "r", stdin);
#endif
  LL L, R, K;
  while (cin >> L >> R >> K) {
    memset(dp, 0, sizeof(dp));
    printf("%d\n", calc(R, K) - calc(L, K-1));
  }
  return 0;
}
