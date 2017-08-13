#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<map>
#include<set>
#include<vector>
#include<string>
#include<queue>
#include<iostream>
#define REP(i, n) for(int i = 0, ed_##i = n; i < ed_##i; i++)
#define FOR(i, n) for(int i = 1, ed_##i = n; i <= ed_##i; i++)
#define bit(x) (1 << (x))
#define bitl(x) (1LL << (x))
#define sqr(x) ((x) * (x))
#define sz(x) ((int)(x.size()))
#define cnti(x) (__builtin_popcount(x))
#define cntl(x) (__builtin_popcountll(x))
#define clzi(x) (__builtin_clz(x))  // Leading zeros
#define clzl(x) (__builtin_clzll(x))
#define ctzi(x) (__builtin_ctz(x))
#define ctzl(x) (__builtin_ctzll(x))

#ifdef QWERTIER
#define err(x) cerr << #x << " : " << x << endl
#else
#define err(x)
#endif

typedef long long LL;
using namespace std;

typedef pair<int,int> pii;
#define MP make_pair

#define MOD 1000000007
#define N 16

inline int _1(int i, int j) {
  return (i >> j) & 1;
}
inline int _1(int i) {
  return 1 << i;
}

#define maxN 16
#define maxM 16

inline void addMod(int &x, int dx) {
  x += dx;
  x %= MOD;
}

int f[N+1][N+1];  // not considering rows and columns
void pre_calc() {
  map<int, int> dp[2];
  FOR (m, maxM) {
    REP (i, 2) {
      dp[i].clear();
    }
    int cur = 0, lst = 1;
    dp[cur][0] = 1;

    FOR (i, maxN) {
      REP (j, m) {
        swap(cur, lst);
        dp[cur].clear();
        for (map<int, int>::iterator it = dp[lst].begin(); it != dp[lst].end(); ++it) {
          int s = it->first,
              v = it->second;
          if (j && !_1(s, j) && _1(s, j - 1)) {
            addMod(dp[cur][s ^ _1(j-1)], v);
          }
          addMod(dp[cur][s ^ _1(j)], v);
        }
      }
      addMod(f[i][m], dp[cur].count(0)?dp[cur][0]:0);
    }
  }
}

int g[N+1], gg[N+1];  // only considering the rows
int h[N+1][N+1];  // considering the rows and columns
void calc() {
  FOR (n, maxN) {
    REP (S, (1 << (n - 1))) {
      FOR (m, maxM) {
        gg[m] = 1;
        int lst = 0, f = 1;
        FOR (i, n - 1) {
          if ((S >> (i-1)) & 1) {
            f *= -1;
            gg[m] = gg[m] * (LL) ::f[i-lst][m] % MOD;
            lst = i;
          }
        }
        gg[m] = gg[m] * (LL) ::f[n-lst][m] % MOD;
      }
      FOR (m, maxM) {
        g[m] = gg[m];
        FOR (i, m - 1) {
          addMod(g[m], -(g[i] * (LL)gg[m-i]) % MOD);
        }
        if (cnti(S) & 1) {
          addMod(h[n][m], -g[m]);
        } else {
          addMod(h[n][m], g[m]);
        }
      }
    }
  }
}

int main() {
#ifdef QWERTIER
  freopen("in.txt", "r", stdin);
#endif
  pre_calc();
  calc();
  int n, m;
  while (scanf("%d%d", &n, &m) != EOF) {
    printf("%d\n", (h[n][m] + MOD) % MOD);
  }
  return 0;
}
