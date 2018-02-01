//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define  ESC    0x1B

int view(int *x,int *y,int xo,int yo);
int keisan(void);
void shuffle(int array[], int size);
void ans_view(int *x,int *y);

int i=0,k=0,enter;
struct kiroku{
	int kotae;
	int s;
// s:正誤判定 0:true 1:false
};
struct kiroku math[10][10];

int main()
{
 keisan();
 return 0;
}

int keisan()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int b[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int size = 10;
	int ans;
	float miss=0;
	char intput[100];
	
	//math[10][10]を初期化
	for(i=0;i<10;i++){
		for(k=0;k<10;k++){
			math[i][k].kotae=0;
			math[i][k].s=0;
		}
	}

	//srand()でrand()に初期値として現在時刻をセット
	srand(time(NULL));

	struct timeval s,e;

	printf("エンターキーを押すと開始します。\n");
	scanf("%c",&enter);
	while(1){
		if(enter=='\n');
		break;
	}

	gettimeofday(&s,NULL);
	
	printf("10 ×  10 \n");

    shuffle(a, size);
    shuffle(b, size);
	for(i=0;i<10;i++){
		for(k=0;k<10;k++){
		  view(a,b,k,i);
			printf("%d ×  %d =",a[k],b[i]);
		//intput	
		//
			scanf("%d",&ans);
			while(ans<0 || ans>999){
			printf("誤った入力です.もう一度入力してください。\n");
			scanf("%d",&ans);
			}

			//正誤判定
			if(a[k]*b[i]!=ans){
				math[i][k].s=1;
				miss++;
			}
			printf("%d\n",ans);
			math[i][k].kotae=ans;
		}
	}
	ans_view(a,b);
	printf("正答率は %0.2f% です。\n",100*(1-miss/100));
  gettimeofday(&e,NULL);
  printf("タイムは %.2f秒 でした。\n", (e.tv_sec - s.tv_sec) + (e.tv_usec -s.tv_usec)*1.0E-6);
	
}

void shuffle(int array[], int size)
{
    int i = size;
    while (i > 1) {
        int j = rand() % i;
        i--;
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
    }
}


int view(int *x,int *y ,int xo, int yo)
{
	int n,m;
	printf("   ");
	for(n=0;n<10;n++) {
					if(n==xo){
									printf("%c[33m%3d%c[39m ",ESC,x[n],ESC);
					}else {
									printf("%3d ",x[n]);
					}

	}
		printf("\n");
	for(n=0;n<24;n++) printf("ー");
		printf("\n");
	for(n=0;n<10;n++){
					if(n==yo){
									printf("%c[33m%3d%c[39m",ESC,y[n],ESC);
					}else	{
									printf("%3d",y[n]);
					}
					printf("|");
		
		//ans view
		for(m=0;m<10;m++) printf("%3d ",math[n][m].kotae);
		printf("\n");
	}
}

void ans_view(int *x,int *y)
{
	int n,m;
	printf("   ");
	for(n=0;n<10;n++) printf("%3d ",x[n]);
	printf("\n");
	for(n=0;n<24;n++) printf("ー");
	printf("\n");
	for(n=0;n<10;n++){
		printf("%3d ",y[n]);
		//ans view
		for(m=0;m<10;m++){
						if(math[n][m].s==1){
							printf("%c[31m%3d%c[39m ",ESC,math[n][m].kotae,ESC);
						}else{
							printf("%3d ",math[n][m].kotae);
						}
		}
		printf("\n");
	}
}
