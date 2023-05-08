#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MXSZ 300008
typedef struct cat {
    int app, color, id;
    struct cat *prev, *next;  // sorted appetite linked list
} Cat;

int N, M;
int app[MXSZ], color[MXSZ];

Cat cats[MXSZ];
int app_sort[MXSZ];
Cat head, tail;

typedef struct Deq {
    int cap, st, l, r, color;
} Deq;
Deq *catdeq;
int deq_colors[MXSZ];
void assigncat(Cat *nt, int x, int y) {
    nt->app = x;
    nt->color = y;
}
int cat_cmp(const void *AA, const void *BB) {
    // compare by ( color , appetite)
    Cat *A = (Cat *)AA, *B = (Cat *)BB;
    if (A->color != B->color) return A->color > B->color ? 1 : -1;
    if (A->app != B->app) return A->app > B->app ? 1 : -1;
    return 0;
}
int app_cmp(const void *AA, const void *BB) {
    // compare by appetite
    int *A = (int *)AA, *B = (int *)BB;
    if (cats[*A].app != cats[*B].app) return cats[*A].app > cats[*B].app ? 1 : -1;
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

Cat *deq_at(Deq *dq, int idx) {
    // Access dq's i'th element
    if (dq->l < 0) dq->l = dq->l % dq->cap + dq->cap;
    return &cats[dq->st + ((idx + dq->l) % dq->cap)];
}
Cat *deq_back(Deq *dq) {
    if (dq->r <= 0) dq->r = dq->r % dq->cap + dq->cap;
    return &cats[dq->st + ((dq->r - 1) % dq->cap)];
}
Cat *deq_front(Deq *dq) {
    if (dq->l < 0) dq->l = dq->l % dq->cap + dq->cap;
    return &cats[dq->st + dq->l % dq->cap];
}
int lower_bound(Deq *dq, int L, int R, Cat *tar) {
    // Find first Cat with app >= tar.app
    while (R > L) {
        int mid = (R + L) / 2;
        if (cat_cmp(deq_at(dq, mid), tar) == -1)
            L = mid + 1;
        else
            R = mid;
    }
    assert(R == dq->cap || cat_cmp(deq_at(dq, R), tar) >= 0);
    return R;
}
int upper_bound(Deq *dq, int L, int R, Cat *tar) {
    // Find first Cat with app > tar.app
    while (R > L) {
        int mid = (R + L) / 2;
        if (cat_cmp(deq_at(dq, mid), tar) != 1)
            L = mid + 1;
        else
            R = mid;
    }
    assert(R == dq->cap || cat_cmp(deq_at(dq, R), tar) == 1);
    return R;
}
int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) scanf("%d", &app[i]);
    for (int i = 0; i < N; i++) scanf("%d", &color[i]);
    for (int i = 0; i < N; i++) app_sort[i] = i, cats[i].app = app[i], cats[i].color = color[i], cats[i].id = i;

    qsort(cats, N, sizeof(Cat), cat_cmp);  // sort by (appetite, color)

    qsort(app_sort, N, sizeof(int), app_cmp);  // sort indices array by appetite

    // Create sorted appetite linked list's head and tail,
    //  we will instead link the struct cat directly
    head.next = &cats[app_sort[0]];
    cats[app_sort[0]].prev = &head;
    head.app = INT_MIN;
    tail.prev = &cats[app_sort[N - 1]];
    tail.app = INT_MAX;
    cats[app_sort[N - 1]].next = &tail;

    int cnt_color = 0;
    // link the appetite linked list , and count number of each color
    for (int i = 1; i < N; i++) {
        cats[app_sort[i - 1]].next = &cats[app_sort[i]];
        cats[app_sort[i]].prev = &cats[app_sort[i - 1]];
        if (cats[i].color != cats[i - 1].color) cnt_color++;
    }
    // Create deque for each color , we will use the space of cats array.
    // Since cats array is sorted, and deque size will not change, we only need to record what range a deque will use in struct Deq.
    catdeq = (Deq *)malloc(sizeof(Deq) * (cnt_color + 8));
    memset(catdeq, 0, sizeof(Deq) * (cnt_color + 8));

    int deqsz = -1;
    int prev_color = -1;
    for (int i = 0; i < N; i++) {
        assert(deqsz < MXSZ);
        if (prev_color == -1 || catdeq[deqsz].color != cats[i].color) {
            deqsz++;
            catdeq[deqsz].st = i;
            catdeq[deqsz].l = catdeq[deqsz].r = 0;
            prev_color = catdeq[deqsz].color = cats[i].color;
        }
        catdeq[deqsz].r++;
        catdeq[deqsz].cap++;
        deq_colors[deqsz] = cats[i].color;
    }
    deqsz++;

    // Handle query here
    for (int i = 0; i < M; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, l, r;
            scanf("%d%d%d", &x, &l, &r);
            int *bs = (int *)bsearch(&x, deq_colors, deqsz, sizeof(int), intcmp);  // find color deque
            if (bs == NULL) {
                printf("0\n");
                continue;
            }
            int dq_idx = bs - deq_colors;
            Cat tmp;
            assigncat(&tmp, l, x);  // create a dummy cat for binary search
            int itl = lower_bound(&catdeq[dq_idx], 0, catdeq[dq_idx].cap, &tmp);
            assigncat(&tmp, r, x);
            int itr = upper_bound(&catdeq[dq_idx], 0, catdeq[dq_idx].cap, &tmp);
            printf("%d\n", (int)(itr - itl));
        } else if (op == 2) {
            int k;
            scanf("%d", &k);
            Cat tmp;
            assigncat(&tmp, app[k], color[k]);  // create a dummy cat for binary search
            int *bs = (int *)bsearch(&color[k], deq_colors, deqsz, sizeof(int), intcmp);
            int dq_idx = bs - deq_colors;

            int idx = lower_bound(&catdeq[dq_idx], 0, catdeq[dq_idx].cap, &tmp);  // cat index in deque
            Cat *ptr1 = deq_at(&catdeq[dq_idx], idx);
            Cat *ptr2 = ptr1->next;
            int k2 = ptr2->id;

            if (ptr1->color != ptr2->color) {
                // swap in deque and linked list
                swap(&ptr1->app, &ptr2->app);
                ptr1->next = ptr2->next;
                ptr2->prev = ptr1->prev;
                if (ptr1->next) ptr1->next->prev = ptr1;
                if (ptr2->prev) ptr2->prev->next = ptr2;
                ptr1->prev = ptr2;
                ptr2->next = ptr1;
            } else
                swap(&ptr1->id, &ptr2->id);  // if cats' color are same, swap id instead
            swap(&app[k], &app[k2]);         // array to find appetite by index
        } else {
            int x, s, t;
            scanf("%d%d%d", &x, &s, &t);
            int newv = t ? tail.prev->app + 1 : head.next->app - 1;
            int dq_idx = (int *)bsearch(&x, deq_colors, deqsz, sizeof(int), intcmp) - deq_colors;
            Cat *ptr;
            if (s) {
                ptr = deq_back(&catdeq[dq_idx]);
                if (!t) {
                    // pop back, push front
                    catdeq[dq_idx].l--;
                    catdeq[dq_idx].r--;
                }
                ptr->app = newv;
            } else {
                ptr = deq_front(&catdeq[dq_idx]);
                if (t) {
                    // push back, pop front
                    catdeq[dq_idx].l++;
                    catdeq[dq_idx].r++;
                }
                ptr->app = newv;
            }
            // move the magic target to head/tail of appetite linked list
            app[ptr->id] = ptr->app;
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