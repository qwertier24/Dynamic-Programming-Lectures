#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < n; i++)
#define FOR(i, n) for(int i = 1; i <= n; i++)

typedef long long ll;
typedef pair<int,int> pii;
#define first fi
#define second se

#ifdef LOCAL
#define err(x) cerr << #x << ":" << x << endl
#else
#define err(x)
#endif

#define N 2010

char s[N];
ll f[N][N], g[N][N];
ll m;
#define INF (1ll<<60)
int main() {
#ifdef QWERTIER
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  scanf("%s", s+1);
  scanf("%lld", &m);
  int n = strlen(s+1);
  FOR (len, n) {
    FOR (l, n - len + 1) {
      int r = l + len - 1;
      if (l == r || (l + 1 == r && s[l] == s[r])) {
        f[l][r] = 0;
        g[l][r] = 1;
      } else {
        if (s[l] == s[r]) {
          f[l][r] = f[l+1][r-1];
          g[l][r] = g[l+1][r-1];
          if (g[l][r] >= INF) {
            g[l][r] = INF;
          }
        } else {
          f[l][r] = min(f[l][r-1], f[l+1][r]) + 1;
          if (f[l][r-1] + 1 == f[l][r]) {
            g[l][r] += g[l][r-1];
            if (g[l][r] >= INF) {
              g[l][r] = INF;
            }
          }
          if (f[l+1][r] + 1 == f[l][r]) {
            g[l][r] += g[l+1][r];
            if (g[l][r] >= INF) {
              g[l][r] = INF;
            }
          }
        }
      }
    }
  }
  if (g[1][n] < m) {
    puts("NONE");
    return 0;
  }
  int l = 1, r = n;
  string ans;
  while (l <= r) {
    if (s[l] == s[r]) {
      ans += s[l];
      l++;
      r--;
    } else {
      if (s[l] < s[r]) {
        if (f[l+1][r] + 1 == f[l][r]) {
          if (g[l+1][r] < m) {
            m -= g[l+1][r];
            ans += s[r];
            r--;
          } else {
            ans += s[l];
            l++;
          }
        } else {
          ans += s[r];
          r--;
        }
      } else {
        if (f[l][r-1] + 1 == f[l][r]) {
          if (g[l][r-1] < m) {
            m -= g[l][r-1];
            ans += s[l];
            l++;
          } else {
            ans += s[r];
            r--;
          }
        } else {
          ans += s[l];
          l++;
        }
      }
    }
  }
  if ((n + f[1][n]) % 2 == 1) {
    for (int i = int(ans.size())-2; i >= 0; i--)
      ans += ans[i];
  } else {
    for (int i = int(ans.size())-1; i >= 0; i--)
      ans += ans[i];
  }
  cout << ans << endl;
  return 0;
}
