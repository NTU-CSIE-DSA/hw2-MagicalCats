// #include "testlib.h"
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
int N, M;
int main() {
    scanf("%d%d", &N, &M);
    vector<int> a(N), b(N);

    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
    for (int i = 0; i < N; i++) scanf("%d", &b[i]);

    unordered_map<int, ord_set> batree;
    map<int, int> amap;
    for (int i = 0; i < N; i++) {
        batree[b[i]].insert(a[i]);
        amap[a[i]] = i;
    }

    for (int i = 0; i < M; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, l, r;
            scanf("%d%d%d", &x, &l, &r);
            if (r < l) swap(l, r);
			if(batree.count(x) == 0){printf("0\n");continue;}
            printf("%d\n", batree[x].order_of_key(r + 1) - batree[x].order_of_key(l));
        } else if (op == 2) {
            int k;
            scanf("%d", &k);
            auto it = amap.find(a[k]);
            auto itn = next(it);
            assert(itn != amap.end() && it != amap.end());
            int h = itn->second;
            batree[b[k]].erase(a[k]);
            batree[b[h]].erase(a[h]);
            batree[b[k]].insert(a[h]);
            batree[b[h]].insert(a[k]);
            swap(it->second, itn->second);
            swap(a[k], a[h]);
        } else if (op == 3) {
            int x, s, t;
            scanf("%d%d%d", &x, &s, &t);
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
        }
    }
}