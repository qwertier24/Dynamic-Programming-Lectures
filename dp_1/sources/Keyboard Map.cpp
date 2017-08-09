#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < n; i++)
#define FOR(i, n) for(int i = 1; i <= n; i++)

typedef long long ll;
typedef pair<int,int> pii;
#define fi first
#define se second

#ifdef LOCAL
#define err(x) cerr << #x << ":" << x << endl
#else
#define err(x)
#endif

#define N 5010
#define M 3010
ll g[N], h[N], f[N][M];
int a[N];
struct Queue {
    int q[N];
    int fr, rr;
}q[M];
#define ldb long double
long double getk(int j, int k, int l) {
    ldb x1 = j, y1 = f[j][l] - g[j] + j * (ldb)h[j],
        x2 = k, y2 = f[k][l] - g[k] + k * (ldb)h[k];
    return (y2 - y1) / (x2 - x1);
}
int main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    FOR (i, n) {
        scanf("%d", &a[i]);
        g[i] = g[i-1] + i*a[i];
        h[i] = h[i-1] + a[i];
    }
    FOR (i, n) {
        FOR (j, m) {
            // FOR (k, i-1) {
            //     f[i][j] = min(f[k][j-1] + g[i] - g[k] - k*(h[i] - h[k]));
            // }
            {
                Queue &q = ::q[j-1];
                while (q.rr > q.fr && getk(q.q[q.fr], q.q[q.fr+1], j-1) <= h[i]) {
                    q.fr++;
                }
                int k = q.q[q.fr];
                f[i][j] = f[k][j-1] + g[i] - g[k] - k*(h[i] - h[k]);
            }
            {
                Queue &q = ::q[j];
                while (q.rr > q.fr &&
                       getk(q.q[q.rr-1], q.q[q.rr], j) >= getk(q.q[q.rr], i, j)) {
                    q.rr--;
                }
                q.q[++q.rr] = i;
            }
            // printf("%d %d %lld\n", i, j, f[i][j]);
        }
    }
    printf("%lld\n", f[n][m]);
    return 0;
}
