#include "testlib.h"
using namespace std;

int main() {
	registerValidation();
	int N = inf.readInt(1, 300000 ,"N");  
	inf.readSpace();
	int M = inf.readInt(1, 300000 ,"M");
	inf.readEoln();
	for(int i=0;i<N;i++){
		inf.readInt(1, 1000000000 ,"a");
		if (i == N-1)
			inf.readEoln();
		else 
			inf.readSpace();
	}
	for(int i=0;i<N;i++){
		inf.readInt(1, 1000000000 ,"b");
		if (i == N-1)
			inf.readEoln();
		else 
			inf.readSpace();
	}
	for(int i=0;i<M;i++){
		int op = inf.readInt(1,3 ,"op");
		inf.readSpace();
		if(op == 1){
			inf.readInt(1, 1000000000,"x");
			inf.readSpace();
			int l = inf.readInt(1, 1000000000,"l");
			inf.readSpace();
			int r = inf.readInt(1, 1000000000,"r");
			inf.readEoln();
			ensuref(r >= l ,"r >= l");
		}else if(op == 2){
			inf.readInt(0, N-1,"k");
			inf.readEoln();
		}else{
			inf.readInt(1, 1000000000,"x");
			inf.readSpace();
			inf.readInt(0, 1,"s");
			inf.readSpace();
			inf.readInt(0, 1,"t");
			inf.readEoln();
		}
	}
	inf.readEof();
	return 0;
}
