#include<bits/stdc++.h>
using namespace std;
#define MXSZ 300008
typedef struct Cat {
    int a,b , id;
    Cat * prev , *next;
    Cat(int x , int y):a(x),b(y),prev(NULL),next(NULL){};
    Cat(){a=b=0;prev=next=NULL;};
    inline bool operator<(const Cat &C) const{
        return b != C.b ? b < C.b : a < C.a;
    };
    
}Cat;
int N,M;
int a[MXSZ] , b[MXSZ];
deque<Cat*> *catdeq;
int deqb[MXSZ];
Cat cats[MXSZ];
int a_srt[MXSZ];

int main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    
    scanf("%d%d",&N,&M);
    catdeq = new deque<Cat*>[N];
    for(int i=0;i<N;i++)cin >> a[i];
    for(int i=0;i<N;i++)cin >> b[i];
    for(int i=0;i<N;i++)a_srt[i] = i , cats[i].a = a[i] , cats[i].b = b[i] , cats[i].id = i;

    sort(cats , cats+N);
    sort(a_srt , a_srt + N , [&](int &x , int &y){
        return cats[x].a < cats[y].a;
    });

    Cat head=Cat() , tail = Cat();
    head.next = &cats[a_srt[0]];
    cats[a_srt[0]].prev = &head;
    tail.prev = &cats[a_srt[N-1]];
    cats[a_srt[N-1]].next = &tail;
    
    for(int i=1;i<N;i++){
        cats[a_srt[i-1]].next = &cats[a_srt[i]];
        cats[a_srt[i]].prev = &cats[a_srt[i-1]];
    }

    int deqsz = 0;

    for(int i=0;i<N;i++){
        assert(deqsz < MXSZ);
        if(!catdeq[deqsz].empty() && catdeq[deqsz].back()->b != cats[i].b){
            deqsz++;
        }
        catdeq[deqsz].push_back(&cats[i]);
        deqb[deqsz] = cats[i].b;
    }
    deqsz++;
    auto cmp = [](Cat * pa, Cat *pb){
        return (*pa) < (*pb);
    };
    auto getidx = [&](int color){
        return lower_bound(deqb , deqb + deqsz , color) - deqb;
    };
    
    for(int i=0;i<M;i++){
        int op;
        cin >> op;
        if(op == 1){
            int x,l,r;
            scanf("%d%d%d",&x,&l,&r);
            int xx = getidx(x);
            Cat tmp = Cat(l,x);
            auto itl = lower_bound(catdeq[xx].begin() , catdeq[xx].end() , &tmp , cmp);
            tmp = Cat(r,x);
            auto itr = upper_bound(catdeq[xx].begin() , catdeq[xx].end() , &tmp , cmp);
            printf("%d\n",(int)(itr - itl));
        }else if(op == 2){
            int k;
            scanf("%d",&k);
            Cat tmp = Cat(a[k] , b[k]);
            int xx = getidx(b[k]);
            auto itsrc = lower_bound(catdeq[xx].begin() , catdeq[xx].end() , &tmp , cmp);
            Cat * ptr1 = *itsrc;
            Cat * ptr2 = ptr1->next;
            if(ptr2 == &tail){
                fprintf(stderr , "%d %d\n" , ptr1->a , a[k]);
                Cat * h = head.next;
                int cc= 0;
                while(h && cc<30) fprintf(stderr , "%d " , h->a), cc++;
                fprintf(stderr , "\n");
            }
            assert(ptr2 != &tail);
            int k2 = ptr2->id;

            if(ptr1->b != ptr2->b){
                swap(ptr1->a, ptr2->a);
                ptr1-> next = ptr2->next;
                ptr2-> prev = ptr1->prev;
                if(ptr1->next) ptr1->next->prev = ptr1;
                if(ptr2->prev) ptr2->prev->next = ptr2;
                ptr1->prev = ptr2;
                ptr2->next = ptr1;
            }
            else swap(ptr1->id , ptr2->id);
            swap(a[k] , a[k2]);
            Cat * h = head.next;
            int cc= 0;

        }else{
            assert(0);
        }
    }
    
}