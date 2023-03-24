#include <bits/stdc++.h>
using namespace std;
#define MXSZ 300008
typedef struct Cat {
    int a, b;
    Cat(int x, int y) : a(x), b(y){};
    Cat(){};
    inline bool operator<(const Cat &C) const {
        return b != C.b ? b < C.b : a < C.a;
    };

} Cat;
int N, M;
int a[MXSZ], b[MXSZ];
Cat cats[MXSZ];
int ba_srt[MXSZ];
pair<int, int> a_srt[MXSZ];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];
    for (int i = 0; i < N; i++) a_srt[i] = make_pair(a[i], i), cats[i].a = a[i], cats[i].b = b[i];

    sort(cats, cats + N);
    sort(a_srt, a_srt + N);

    for (int i = 0; i < M; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, l, r;
            cin >> x >> l >> r;
            auto itl = lower_bound(cats, cats + N, Cat(l, x));
            auto itr = upper_bound(cats, cats + N, Cat(r, x));
            cout << itr - itl << '\n';
        } else if (op == 2) {
            int k;
            cin >> k;
            auto ita = lower_bound(a_srt, a_srt + N, make_pair(a[k], k));

            assert(ita->first == a[k] && ita->second == k);
            auto itb = upper_bound(a_srt, a_srt + N, make_pair(a[k], N + 87));
            assert(itb != a_srt + N);
            int k2 = itb->second;
            auto itsrc = lower_bound(cats, cats + N, Cat(a[k], b[k]));
            auto itdst = lower_bound(cats, cats + N, Cat(a[k2], b[k2]));

            if (itsrc->b != itdst->b) {
                swap(itsrc->a, itdst->a);
            }
            swap(ita->second, itb->second);
            swap(a[k], a[k2]);
        } else {
            assert(0);
        }
    }
}