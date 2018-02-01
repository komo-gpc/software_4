#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/time.h>

struct timeval s, e;
struct WORD
{
	int num; //番号
	char japa[256]; //日本語
	char eng[256]; //英語
};
struct WORD word[256];
int i,j;

void timer();
void file();

int main(){
	char test[256];
	file();
	//スタート
	gettimeofday(&s, NULL);
	for(i=1;i<j;i++){
		printf("%d %s %s\n",word[i].num,word[i].eng,word[i].japa);
	}
	printf("\n");
	scanf("%s",test);
	//終了
	timer();
}


void file(){
	FILE *fp;
	FILE *fo;
	int k,l,m,n,num,i,j;
	char filename[256];
	char rireki[256][256];
	char c;
	i=1;
	j=l=m=0;
	printf("\n");
	fo=fopen("rireki.txt","a+");
	while(1){
		c=fgetc(fo);
		if(c==EOF)break;
		if(c=='\n'){
			m=0;
			l++;
		}else{
			rireki[l][m]=c;
			m++;
		}
	}

	printf("入力するファイルの番号を選択してください\n");
	printf("\n");
	for(n=0;n<l;n++){
		printf("%d %s\n",n+1,rireki[n]);
	}
	printf("%d 新規ファイル\n",n+1);
	printf("%d 履歴を削除\n",n+2);
	printf("\n");
	scanf("%d",&num);
	if(num==l+1){
		scanf("%s",filename);
		fprintf(fo,"%s\n",filename);
	}else if(num==l+2){
		fclose(fo);
		fo=fopen("rireki.txt","w");
	}else{
		strcpy(filename,rireki[num-1]);
	}
	fclose(fo);
	fp=fopen(filename,"r");
	if( fp == NULL ){
   		printf( "%sファイルが開けません\n",fp);
		exit(1);
 	 }
	for(;;){
		word[i].num = i;
		if(fscanf(fp,"%[^,],%s",word[i].eng,word[i].japa)==EOF){
			//breakまで,と改行を区切りに文字を配列へ挿入
			i--;
			fclose(fp);
			break;
		}else{
			if(word[i].eng[0]=='\n'){
				for(k=0;k<255;k++){
					word[i].eng[k]=word[i].eng[k+1];
				}			
			}//改行が配列の先頭に入り出力にバグが起きるめ先頭を消去
			i++;
			j++;
		}
	}
}

void timer(){
	gettimeofday(&e, NULL);
	printf("time = %.2f\n", (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);
}









