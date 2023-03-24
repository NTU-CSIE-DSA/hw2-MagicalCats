#include<bits/stdc++.h>
using namespace std;
#define MXSZ 300008
typedef struct Cat {
    int a,b;
    Cat(int x , int y):a(x),b(y){};
    Cat(){};
    inline bool operator<(const Cat &C) const{
        return b != C.b ? b < C.b : a < C.a;
    };
    
}Cat;
int N,M;
Cat cats[MXSZ];
int ba_srt[MXSZ];
pair<int ,int> a_srt[MXSZ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> M;
    for(int i=0;i<N;i++)cin >> cats[i].a;
    for(int i=0;i<N;i++)cin >> cats[i].b;

    for(int i=0;i<M;i++){
        int op;
        cin >> op;
        if(op == 1){
            int x,l,r;
            cin >> x >> l >> r;
            int cnt = 0;
            for(int j = 0;j<N;j++){
                if(cats[j].a >= l && cats[j].a <= r && cats[j].b == x) cnt++;
            }
            cout << cnt << '\n';
        }else if(op == 2){
            int k;
            cin >> k;
            int ind = -1 , cur = 1e9+87;
            for(int j=0;j<N;j++){
                if(cats[j].a > cats[k].a && cur > cats[j].a){
                    cur = cats[j].a;
                    ind = j;
                }
            }
            assert(ind != -1);
            swap(cats[ind].a , cats[k].a);
        }else{
            int x,s,t;
            cin >> x >> s >> t;
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