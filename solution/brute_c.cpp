#include<stdio.h>
#include<limits.h>
#define MXSZ 300008
typedef struct Cat {
    int a,b;
}Cat;
int N,M;
Cat cats[MXSZ];
void swap(int *a, int *b){
    int tmp = *a; *a=*b;*b=tmp;
}
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
int main(){

    scanf("%d%d",&N,&M);
    for(int i=0;i<N;i++)scanf("%d",&cats[i].a);
    for(int i=0;i<N;i++)scanf("%d",&cats[i].b);

    for(int i=0;i<M;i++){
        int op;
        scanf("%d",&op);
        if(op == 1){
            int x,l,r;
            scanf("%d%d%d",&x,&l,&r);
            int cnt = 0;
            for(int j = 0;j<N;j++){
                if(cats[j].a >= l && cats[j].a <= r && cats[j].b == x) cnt++;
            }
            printf("%d\n",cnt);
        }else if(op == 2){
            int k;
            scanf("%d",&k);
            int ind = -1 , cur = 1e9+87;
            for(int j=0;j<N;j++){
                if(cats[j].a > cats[k].a && cur > cats[j].a){
                    cur = cats[j].a;
                    ind = j;
                }
            }
            swap(&cats[ind].a , &cats[k].a);
        }else{
            int x,s,t;
            scanf("%d%d%d",&x,&s,&t);
            int newv = cats[0].a;
            if(t) for(int i=0;i<N;i++) newv = max(newv , cats[i].a + 1);
            else for(int i=0;i<N;i++) newv = min(newv , cats[i].a - 1);
            int ind = -1  , cur = s ? INT_MIN : INT_MAX ;
            if(s){
                for(int i=0;i<N;i++){
                    if(cats[i].a > cur && cats[i].b == x){
                        ind = i;
                        cur = cats[i].a;
                    }
                }
            }else{
                for(int i=0;i<N;i++){
                    if(cats[i].a < cur && cats[i].b == x){
                        ind = i;
                        cur = cats[i].a;
                    }
                }
            }
            cats[ind].a = newv;
        }
    }
    
}