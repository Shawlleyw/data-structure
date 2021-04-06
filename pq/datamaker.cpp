#include<bits/stdc++.h>
using namespace std;
int r1(){
    return (rand() % 3) + 1 ;
}
int r2(){
    return rand();
}
int main(){
    srand(time(0));
    FILE *fp;
    fp = fopen("data.in","w");
    int T; T = 100000;
    //scanf("%d",&T);
    fprintf(fp,"%d\n",T);
    int cnt = 0, c, val = 0, tmp = 0;
    while(T--){
    	//printf("%d\n",T);
        c = r1();
        while(cnt <= 0 && (c == 2 || c == 3) ) c = r1();
        if(c==1){
        	val = r2();
        	fprintf(fp,"1 %d ",val);
        	cnt++;
		}
		else{
			fprintf(fp,"%d",c);
			if(c == 2)cnt --;
		}
        //while(tmp <= 5 && ( c == 4 || c == 5)) c = r1();
        /*if(c == 1){
            for(int i=1;i<=5&&T>=0;i++,T--){
                val = r2();
                fprintf(fp,"1 %d ",val);
                if(i != 5)fputs("\n",fp);
                cnt++;
            }
        }
        else{
            if(tmp == 10) tmp = 0, c = rand()%2+4;
            fprintf(fp,"%d",c);
            if(c == 2) cnt--;
            T--;
        }*/
        fputs("\n",fp);
        //tmp++;
    }
    fclose(fp);
    return 0;
}
