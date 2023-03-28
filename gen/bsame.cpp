#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "testlib.h"
using namespace __gnu_pbds;
using namespace std;

// const int R = 1000000000;
void gen_uni(vector<int> &v, int n, int r) {
    if (r < 2e6 || n * 10 > r) {
        for (int i = 1; i <= r; i++) {
            v.push_back(i);
        }
        shuffle(v.begin(), v.end());
        v.resize(n);
        return;
    }
    while ((int)v.size() < n) {
        for (int i = 0; i < n + 10000; i++) {
            v.push_back(rnd.next(1, r));
        }
        sort(v.begin(), v.end());
        auto res = unique(v.begin(), v.end());
        v.resize(min((int)distance(v.begin(), res), n));
        shuffle(v.begin(), v.end());
    }
}
void gen_color(vector<int> &v, int n, int r, int gszl, int gszr) {
    while ((int)v.size() < n) {
        int i = 0;
        while (i < n) {
            int color = rnd.next(1, r);
            for (int j = rnd.next(gszl, gszr); j && i < n; --j) v.push_back(color), i++;
        }
        v.resize(n);
    }
    shuffle(v.begin(), v.end());
}
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ord_set;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int ops[4];
    ops[1] = atoi(argv[3]);
    ops[2] = atoi(argv[4]);
    ops[3] = atoi(argv[5]);
    int R = atoi(argv[6]);
    int gpszl = atoi(argv[7]);
    int gpszr = atoi(argv[8]);
    assert(R >= N);
    assert(gpszl <= N);
    assert(gpszl <= gpszr);
    printf("%d %d\n", N, M);
    vector<int> a, b;

    gen_uni(a, N, R);
    gen_color(b, N, R, gpszl, gpszr);

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    printf("%d", a[0]);
    for (int i = 1; i < N; i++) printf(" %d", a[i]);
    printf("\n");
    printf("%d", b[0]);
    for (int i = 1; i < N; i++) printf(" %d", b[i]);
    printf("\n");

    unordered_map<int, ord_set> batree;
    map<int, int> amap;
    int minL = 1;
    int maxR = R;
    for (int i = 0; i < N; i++) {
        batree[b[i]].insert(a[i]);
        amap[a[i]] = i;
    }

    for (int i = 0; i < M;) {
        int op = rnd.next(1, 3);
        while (!ops[op]) op = rnd.next(1, 3);
        if(i + 20 >= M) op = 1;
        if (op == 1) {
            int x = b[rnd.next(0, N - 1)];
            int l = rnd.next(minL, maxR);
            int r = rnd.next(minL, maxR);
            if (r < l) swap(l, r);
            if (rnd.next(1,30) == 1) x = rnd.next(1, R);
            printf("%d %d %d %d\n", op, x, l, r);
            i++;
        } else if (op == 2) {
            int x = b[rnd.next(0, N - 1)];
            auto itx = batree[x].begin();
            int ts = rnd.next(1,(int)batree[x].size());
            int h = 0;
            for(;h<ts && i<M-20;h++,i++){
                if(itx == batree[x].end() || next(amap.find(*itx)) == amap.end()) break;
                auto it = amap.find(*itx);
                int k = it->second;
                auto itn = next(it);
                assert(it != amap.end() && it != amap.end());
                int h = itn->second;
                batree[b[k]].erase(a[k]);
                batree[b[h]].erase(a[h]);
                auto ins = batree[b[k]].insert(a[h]);
                batree[b[h]].insert(a[k]);
                swap(it->second, itn->second);
                swap(a[k], a[h]);
                printf("%d %d\n", op, k);
                itx = next(ins.first);
            }
        } else if (op == 3) {
            int x = b[rnd.next(0, N - 1)];
            int h = 0;
            int ts = rnd.next(1, (int)batree[x].size());
            for(;h<ts && i<M-20;h++,i++){
                int s = rnd.next(0, 1);
                int t = rnd.next(0, 1);
                printf("%d %d %d %d\n", op, x, s, t);
                int newv;
                if (t)
                    newv = amap.rbegin()->first + 1;
                else
                    newv = amap.begin()->first - 1;
                if (s) {
                    int ind = amap[*batree[x].rbegin()];
                    amap.erase(*batree[x].rbegin());
                    a[ind] = newv;
                    batree[x].erase(batree[x].rbegin());
                    batree[x].insert(newv);
                    amap[newv] = ind;
                } else {
                    int ind = amap[*batree[x].begin()];
                    amap.erase(*batree[x].begin());
                    a[ind] = newv;
                    batree[x].erase(batree[x].begin());
                    batree[x].insert(newv);
                    amap[newv] = ind;
                }
                minL = min(minL , newv);
                maxR = max(maxR , newv);
            }
        }
    }
}