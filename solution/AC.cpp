#include <bits/stdc++.h>
using namespace std;
#define MXSZ 300008
typedef struct Cat {
    int a, b, id;
    Cat *prev, *next;
    Cat(int x, int y) : a(x), b(y), prev(NULL), next(NULL){};
    Cat() {
        a = b = 0;
        prev = next = NULL;
    };
    inline bool operator<(const Cat &C) const {
        return b != C.b ? b < C.b : a < C.a;
    };

} Cat;
int N, M;
int a[MXSZ], b[MXSZ];
deque<Cat *> *catdeq;
int deqb[MXSZ];
Cat cats[MXSZ];
int a_srt[MXSZ];

int main() {
    scanf("%d%d", &N, &M);
    catdeq = new deque<Cat *>[N];
    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
    for (int i = 0; i < N; i++) scanf("%d", &b[i]);
    for (int i = 0; i < N; i++)
        a_srt[i] = i, cats[i].a = a[i], cats[i].b = b[i], cats[i].id = i;

    sort(cats, cats + N);
    sort(a_srt, a_srt + N, [&](int &x, int &y) { return cats[x].a < cats[y].a; });

    Cat head = Cat(), tail = Cat();
    head.next = &cats[a_srt[0]];
    cats[a_srt[0]].prev = &head;
    head.a = INT_MIN;
    tail.prev = &cats[a_srt[N - 1]];
    tail.a = INT_MAX;
    cats[a_srt[N - 1]].next = &tail;

    for (int i = 1; i < N; i++) {
        cats[a_srt[i - 1]].next = &cats[a_srt[i]];
        cats[a_srt[i]].prev = &cats[a_srt[i - 1]];
    }

    int deqsz = 0;

    for (int i = 0; i < N; i++) {
        assert(deqsz < MXSZ);
        if (!catdeq[deqsz].empty() && catdeq[deqsz].back()->b != cats[i].b) {
            deqsz++;
        }
        catdeq[deqsz].push_back(&cats[i]);
        deqb[deqsz] = cats[i].b;
    }
    deqsz++;

    auto cmp = [](Cat *pa, Cat *pb) { return (*pa) < (*pb); };
    auto getidx = [&](int color) {
        return lower_bound(deqb, deqb + deqsz, color) - deqb;
    };

    for (int i = 0; i < M; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, l, r;
            scanf("%d%d%d", &x, &l, &r);
            int xx = getidx(x);
            Cat tmp = Cat(l, x);
            auto itl = lower_bound(catdeq[xx].begin(), catdeq[xx].end(), &tmp, cmp);
            tmp = Cat(r, x);
            auto itr = upper_bound(catdeq[xx].begin(), catdeq[xx].end(), &tmp, cmp);
            printf("%d\n", (int)(itr - itl));
        } else if (op == 2) {
            int k;
            scanf("%d", &k);
            Cat tmp = Cat(a[k], b[k]);
            int xx = getidx(b[k]);
            auto itsrc = lower_bound(catdeq[xx].begin(), catdeq[xx].end(), &tmp, cmp);
            Cat *ptr1 = *itsrc;
            Cat *ptr2 = ptr1->next;
            int k2 = ptr2->id;

            if (ptr1->b != ptr2->b) {
                swap(ptr1->a, ptr2->a);
                ptr1->next = ptr2->next;
                ptr2->prev = ptr1->prev;
                if (ptr1->next) ptr1->next->prev = ptr1;
                if (ptr2->prev) ptr2->prev->next = ptr2;
                ptr1->prev = ptr2;
                ptr2->next = ptr1;
            } else
                swap(ptr1->id, ptr2->id);
            swap(a[k], a[k2]);
        } else {
            int x, s, t;
            scanf("%d%d%d", &x, &s, &t);
            int newv = t ? tail.prev->a + 1 : head.next->a - 1;
            int xx = getidx(x);
            Cat *ptr;
            if (s) {
                ptr = catdeq[xx].back();
                if (!t) {
                    catdeq[xx].push_front(catdeq[xx].back());
                    catdeq[xx].pop_back();
                }
                ptr->a = newv;
            } else {
                ptr = catdeq[xx].front();
                if (t) {
                    catdeq[xx].push_back(catdeq[xx].front());
                    catdeq[xx].pop_front();
                }
                ptr->a = newv;
            }
            a[ptr->id] = ptr->a;
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
            if (t) {
                ptr->prev = tail.prev;
                ptr->prev->next = ptr;
                ptr->next = &tail;
                tail.prev = ptr;
            } else {
                ptr->next = head.next;
                ptr->next->prev = ptr;
                ptr->prev = &head;
                head.next = ptr;
            }
        }
    }
}