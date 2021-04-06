#include<bits/stdc++.h>
#include "p_q.h"
using namespace std;

int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
    Priority_Queue<int>H;
    int T;
    scanf("%d",&T);
    int x,c;
    while(T--){
        scanf("%d",&c);
        switch (c){
            case 1 : scanf("%d",&x); H.push (x);break;
            case 2 : H.pop();break;
            case 3 : printf("%d\n",H.top());break;
            case 4 : printf("%d\n",H.size());break;
            case 5 : printf(H.empty()?"YES":"NO");break;
        }
        puts("");
    }
    return 0;
}
