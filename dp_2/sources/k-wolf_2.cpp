#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 1, i##_ED = n; i <= i##_ED; i++)
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

LL dp[20][2][10010];
int vis[20][2][10010];
int K;
bool check(int suf, int x) {
  for (int i = 0; i + 1 < K && suf / 10 > 0; i++) {
    if (suf % 10 == x)
      return false;
    suf /= 10;
  }
  return true;
}
int newsuf(int suf, int x) {
  suf = suf * 10 + x;
  if (suf / 100000 == 1)
    (suf %= 10000) += 10000;
  return suf;
}
vector<int> dig;
LL dfs(int cur, int lim, int suf) {
  if (cur == -1)
    return 1;

  if (!lim && vis[cur][lim][suf])
    return dp[cur][lim][suf];
  vis[cur][lim][suf] = 1;

  LL &res = dp[cur][lim][suf];
  res = 0;
  REP (i, 10) {
    if (lim && i > dig[cur])
      break;
    if (check(suf, i))
      res += dfs(cur-1, lim&(i==dig[cur]), newsuf(suf, i));
  }
  // printf("%d %d %d %d %I64d\n", cur, lim, suf, pre0, res);
  return res;
}
LL calc(LL n) {
  dig.clear();
  while (n) {
    dig.push_back(n%10);
    n /= 10;
  }
  LL res = 0;
  REP (i, dig.size()) {
    FOR (j, 9)
      if (i+1 != dig.size() || j <= dig.back())
        res += dfs(i-1, (i+1 == dig.size() && j==dig.back()), 10+j);
  }
  return res;
}

int main() {
#ifdef QWERTIER
  freopen("in.txt", "r", stdin);
#endif
  LL L, R;
  while (cin >> L >> R >> K) {
    memset(vis, 0, sizeof(vis));
    cout << calc(R) - calc(L-1) << endl;
  }
  return 0;
}
