#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MXSZ 300008
typedef struct cat {
    int a, b, id;
    struct cat *prev, *next;
} Cat;
int N, M;
int a[MXSZ], b[MXSZ];
int deqb[MXSZ];
Cat cats[MXSZ];
int a_srt[MXSZ];
Cat head, tail;
void newcat(Cat *nt, int x, int y) {
    nt->a = x;
    nt->b = y;
}
int catcmp(const void *AA, const void *BB) {
    Cat *A = (Cat *)AA, *B = (Cat *)BB;
    if (A->b != B->b) return A->b > B->b ? 1 : -1;
    if (A->a != B->a) return A->a > B->a ? 1 : -1;
    return 0;
}
int acmp(const void *AA, const void *BB) {
    int *A = (int *)AA, *B = (int *)BB;
    if (cats[*A].a != cats[*B].a) return cats[*A].a > cats[*B].a ? 1 : -1;
    return 0;
}
int intcmp(const void *A, const void *B) {
    return (*(int *)A - *(int *)B);
}
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
typedef struct Deq {
    int cap, st, l, r, b;
} Deq;
Deq *catdeq;
Cat *dqat(Deq *dq, int idx) {
    if (dq->l < 0) dq->l = dq->l % dq->cap + dq->cap;
    return &cats[dq->st + ((idx + dq->l) % dq->cap)];
}
Cat *dqbk(Deq *dq) {
    if (dq->r <= 0) dq->r = dq->r % dq->cap + dq->cap;
    return &cats[dq->st + ((dq->r - 1) % dq->cap)];
}
Cat *dqfr(Deq *dq) {
    if (dq->l < 0) dq->l = dq->l % dq->cap + dq->cap;
    return &cats[dq->st + dq->l % dq->cap];
}
int lower_bound(Deq *dq, int L, int R, Cat *tar) {
    while (R > L) {
        int mid = (R + L) / 2;
        if (catcmp(dqat(dq, mid), tar) == -1)
            L = mid + 1;
        else
            R = mid;
    }
    assert(R == dq->cap || catcmp(dqat(dq, R), tar) >= 0);
    return R;
}
int upper_bound(Deq *dq, int L, int R, Cat *tar) {
    while (R > L) {
        int mid = (R + L) / 2;
        if (catcmp(dqat(dq, mid), tar) != 1)
            L = mid + 1;
        else
            R = mid;
    }
    assert(R == dq->cap || catcmp(dqat(dq, R), tar) == 1);
    return R;
}
int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) scanf("%d", &a[i]);
    for (int i = 0; i < N; i++) scanf("%d", &b[i]);
    for (int i = 0; i < N; i++) a_srt[i] = i, cats[i].a = a[i], cats[i].b = b[i], cats[i].id = i;

    qsort(cats, N, sizeof(Cat), catcmp);
    qsort(a_srt, N, sizeof(int), acmp);

    head.next = &cats[a_srt[0]];
    cats[a_srt[0]].prev = &head;
    head.a = INT_MIN;
    tail.prev = &cats[a_srt[N - 1]];
    tail.a = INT_MAX;
    cats[a_srt[N - 1]].next = &tail;

    int cntb = 0;
    for (int i = 1; i < N; i++) {
        cats[a_srt[i - 1]].next = &cats[a_srt[i]];
        cats[a_srt[i]].prev = &cats[a_srt[i - 1]];
        if (cats[i].b != cats[i - 1].b) cntb++;
    }
    catdeq = (Deq *)malloc(sizeof(Deq) * (cntb + 8));
    memset(catdeq, 0, sizeof(Deq) * (cntb + 8));
    int deqsz = -1;
    int prevb = -1;
    for (int i = 0; i < N; i++) {
        assert(deqsz < MXSZ);
        if (prevb == -1 || catdeq[deqsz].b != cats[i].b) {
            deqsz++;
            catdeq[deqsz].st = i;
            catdeq[deqsz].l = catdeq[deqsz].r = 0;
            prevb = catdeq[deqsz].b = cats[i].b;
        }
        catdeq[deqsz].r++;
        catdeq[deqsz].cap++;
        deqb[deqsz] = cats[i].b;
    }
    deqsz++;
    for (int i = 0; i < M; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, l, r;
            scanf("%d%d%d", &x, &l, &r);
            int *bs = (int *)bsearch(&x, deqb, deqsz, sizeof(int), intcmp);
            if (bs == NULL) {
                printf("0\n");
                continue;
            }
            int xx = bs - deqb;
            Cat tmp;
            newcat(&tmp, l, x);
            int itl = lower_bound(&catdeq[xx], 0, catdeq[xx].cap, &tmp);
            newcat(&tmp, r, x);
            int itr = upper_bound(&catdeq[xx], 0, catdeq[xx].cap, &tmp);
            printf("%d\n", (int)(itr - itl));
        } else if (op == 2) {
            int k;
            scanf("%d", &k);
            Cat tmp;
            newcat(&tmp, a[k], b[k]);
            int *bs = (int *)bsearch(&b[k], deqb, deqsz, sizeof(int), intcmp);
            int xx = bs - deqb;
            int idx = lower_bound(&catdeq[xx], 0, catdeq[xx].cap, &tmp);
            Cat *ptr1 = dqat(&catdeq[xx], idx);
            Cat *ptr2 = ptr1->next;
            int k2 = ptr2->id;

            if (ptr1->b != ptr2->b) {
                swap(&ptr1->a, &ptr2->a);
                ptr1->next = ptr2->next;
                ptr2->prev = ptr1->prev;
                if (ptr1->next) ptr1->next->prev = ptr1;
                if (ptr2->prev) ptr2->prev->next = ptr2;
                ptr1->prev = ptr2;
                ptr2->next = ptr1;
            } else
                swap(&ptr1->id, &ptr2->id);
            swap(&a[k], &a[k2]);
        } else {
            int x, s, t;
            scanf("%d%d%d", &x, &s, &t);
            int newv = t ? tail.prev->a + 1 : head.next->a - 1;
            int xx = (int *)bsearch(&x, deqb, deqsz, sizeof(int), intcmp) - deqb;
            Cat *ptr;
            if (s) {
                ptr = dqbk(&catdeq[xx]);
                if (!t) {
                    catdeq[xx].l--;
                    catdeq[xx].r--;
                }
                ptr->a = newv;
            } else {
                ptr = dqfr(&catdeq[xx]);
                if (t) {
                    catdeq[xx].l++;
                    catdeq[xx].r++;
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