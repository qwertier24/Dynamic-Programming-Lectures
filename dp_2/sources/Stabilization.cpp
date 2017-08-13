#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<map>
#include<set>
#include<vector>
#include<string>
#include<queue>
#include<iostream>
#define REP(i,n) for(int i=0; i<n; i++)
#define FOR(i,n) for(int i=1; i<=n; i++)

typedef long long LL;
using namespace std;

typedef pair<int,int> pii;
#define MP make_pair

void print(int x) {
  for (int i = 31; i >= 0; i--)
    printf("%d", (x>>i)&1);
  puts("");
}

#define N 100010
#define D 20

LL sum[1<<D];
int ldig[1<<D], hdig[1<<D], a[N], f[D][D], g[D][D];
LL h[D];
int n;

pair<LL,int> brute() {
  pair<LL,int> ans = MP(1ll<<60, 0);
  for (int i = 0; i < (1<<20); i++) {
    LL sum = 0;
    FOR (j, n) {
      a[j] ^= i;
    }
    FOR (j, n-1) {
      sum += abs(a[j+1] - a[j]);
    }
    FOR (j, n) {
      a[j] ^= i;
    }
    ans = min(ans, MP(sum ,i));
  }
  return ans;
}
int main(){
#ifdef QWERTIER
  freopen("in.txt","r",stdin);
#endif
  int T;
  scanf("%d", &T);
  REP (i, (1<<20)) {
    for (int j = 0; j < 20; j++) {
      if ((i>>j)&1) {
        ldig[i] = j;
        break;
      }
    }
    for (int j = 19; j >= 0; j--) {
      if ((i>>j)&1) {
        hdig[i] = j;
        break;
      }
    }
  }
  while (T--) {
    scanf("%d", &n);
    FOR (i, n) {
      scanf("%d", &a[i]);
    }
    sum[0] = 0;
    memset(h, 0, sizeof(h));
    memset(f, 0, sizeof(f));
    memset(g, 0 ,sizeof(g));
    FOR (i, n - 1) {
      if (a[i+1] == a[i])
        continue;
      sum[0] += abs(a[i+1] - a[i]);
      int x = max(a[i+1], a[i]), y = min(a[i+1], a[i]);
      for (int j = 0; j < 20; j++) {
        if (j >= hdig[x ^ y])
          break;
        if (((x >> j) & 1) && !((y >> j) & 1)) {
          f[hdig[x ^ y]][j]++;
        } else if (!((x >> j) & 1) && ((y >> j) & 1)) {
          g[hdig[x ^ y]][j]++;
        }
      }
      h[hdig[a[i+1] ^ a[i]]] += (x - y) - (1 << hdig[a[i+1] ^ a[i]]);
    }
    pair<LL, int> ans(sum[0], 0);
    REP (S, (1<<20)) {
      if (!S) {
        continue;
      }
      sum[S] = sum[S ^ (1<<ldig[S])];
      for (int i = 19; i >= 0; i--) {
        if (i == ldig[S]) {
          sum[S] -= h[ldig[S]] * 2;
          break;
        } else if ((S >> i) & 1) {
          sum[S] += 1ll * f[i][ldig[S]] * (1ll << (ldig[S]+1));
          sum[S] -= 1ll * g[i][ldig[S]] * (1ll << (ldig[S]+1));
        } else {
          sum[S] -= 1ll * f[i][ldig[S]] * (1ll << (ldig[S]+1));
          sum[S] += 1ll * g[i][ldig[S]] * (1ll << (ldig[S]+1));
        }
      }
      if (MP(sum[S], S) <= ans) {
        ans = MP(sum[S], S);
      }
    }
    cout << ans.second << ' ' << ans.first << endl;
  }
  return 0;
}
