/*
・表示問題の抽出(重み付け?)
・幅調整
・メモリ関連。動的確保
・同じ行に表示？
・行数カウント関数か？
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>

/*構造体定義*/
struct word_d
{
	/*ナンバー*/
	int num;
	/*英文*/
	char eng[256];
	/*日本語分*/
	char jp[256];
};
/*時間計測用構造体*/
struct timeval start,end;

/*プロトタイプ宣言*/
void shuffle_ch(char [][99], int);
void shuffle_num(int [],int);
int check_answer(char [][99],struct word_d[],int,int,int);
void display(char [][99],int,int);
void timer();
void file(FILE **,struct word_d[]);


int main()
{
	int i,j,ans,ans1;
	/*正答率計算用変数*/
	float cnt,bans;
	FILE *fp;
	
	const int item = 4;	//単語数
	const int wide = 3;	//横幅。文字サイズにもよるが5ぐらいがデフォルトだと限界？
	const int high = 3;	//高さ
	const int size = item *2 ;	//枠の数。基本単語数の2倍?
	int line;	//読み取った単語数
	int temp[item];
	char str[size][99];	//一時保存用配列
	
	/*構造体配列*/
	struct word_d word[256];
	
	/*fpを引数として渡し、返す*/
	file(&fp,word);
	
	/*行数カウント*/
	char buf[256];	//一行最大文字数
	line=0;
	rewind(fp);		//ファイルポインタをファイルの先頭に戻す。
	while(fgets(buf,256,fp)!=NULL)
	{
		line++;
	}
	
	/*問題ランダム*/
	srand((unsigned)time(NULL));
	for(i=0;i<item;i++)
	{
		temp[i]=(int)(rand()*(double)line/(double)RAND_MAX);
		for(j=i-1;j>-1;j--)
		{
			if(temp[i]==temp[j])
			{
				i--;
			}
		}
	}
	
	//shuffle_num(temp,item);
	
	j=0;
	/*一時保存用配列への入力*/
	for(i=0;i<item;i++)
	{
		strcpy(str[j],word[temp[i]].eng);
		j++;
		strcpy(str[j],word[temp[i]].jp);
		j++;
	}
	
	/*シャッフル*/
	shuffle_ch(str,size);
	
	/*乱数設定*/
	/*
	srand((unsigned)time(NULL));
	乱数のシードを現在時刻を用いて設定
	printf("%d\n",RAND_MAX);
	srand((unsigned)time(NULL));
	for(i=0;i<100;i++)
	{
		printf("%d ",(int)(rand()*(5.0/(float)RAND_MAX)));
	}
	printf("\n");
	
	
	2147483647.0	//学校環境でのRAND_MAX(?)
	*/

	/*メイン実行部*/
	i=cnt=bans=0;
	
	gettimeofday(&start,NULL);
	/*i=itemの時、全問正解*/
	while(i<item)
	{
		/*表示*/
		display(str,wide,high);
		printf("答えを入力してください\n");
		fflush(stdout);
		while(1)
		{
			/*解答読み込み*/
			scanf("%d %d",&ans,&ans1);
			if(ans<1 || ans>(size) || ans1<1 || ans1>(size))
			{
				printf("入力が不正です。もう一度入力してください。\n");
				fflush(stdout);
			}else break;
		}
		cnt++;
		switch(check_answer(str,word,ans,ans1,line))
		{
			/*正解*/
			case 0:
				printf("正解です\n");
				fflush(stdout);
				/*正解した単語を消す*/
				strcpy(str[ans-1],"---");
				strcpy(str[ans1-1],"---");
				i++;
				break;
				
			/*不正解*/
			case 1:	
				printf("間違いです\n");
				fflush(stdout);
				bans++;
				break;
				
			/*check_answerでのerror*/
			case 2:
				printf("check error\n");
				fflush(stdout);
				cnt--;
				break;
				
			default:
				printf("switch error\n");
				fflush(stdout);
				cnt--;
				break;
		}
	}
	printf("おめでとう！正答率は%.1f%%です\n",100*(1-(bans/cnt)));
	fflush(stdout);
	timer();
	
	return 0;
}

/*シャッフル関数
Fisher-Yates法
出た乱数の配列から順に外側の配列と入れ替えていく*/
void shuffle_ch(char str[][99],int size)
{
	int i=size;
	while(i>1)
	{
		/*現在時刻からの乱数生成*/
		srand((unsigned)time(NULL));
		/*乱数
		この書き方は簡単だが一桁目の数字が同じ数(すう)の数(かず)にはわずかに差があるため、厳密性に欠ける。
		(int)(rand()*((double)[欲しい乱数の幅(size)]/(double)RAND_MAX))
		だと厳密である？*/
		int j = rand() % i; //厳密性に欠ける書き方
		i--;
		/*退避用配列*/
		char t[99];
		strcpy(t,str[i]);
		strcpy(str[i],str[j]);
		strcpy(str[j],t);
	}
}

void shuffle_num(int num[],int size)
{
	int i=size;
	while(i>1)
	{
		srand((unsigned)time(NULL));
		int j = rand() % i;
		i--;
		int k;
		k=num[i];
		num[i]=num[j];
		num[j]=k;
	}
}

/*正解確認関数*/
int check_answer(char str[][99],struct word_d word[],int ans,int ans1,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		/*回答と同じ文字列を一時保存用配列から探す。
		一致したものが見つかれば、次は二番目の配列と英文(日本語分)を比較。
		一致した場合正解,不一致なら不正解とし、一時保存用配列から一致するものが見つからなかった場合はエラーを返す*/
		if(strcmp(str[ans-1],word[i].eng)==0)
		{
			if(strcmp(str[ans1-1],word[i].jp)==0)
				return 0;	//正解
			else return 1;	//不正解
		}else if(strcmp(str[ans-1],word[i].jp)==0)
		{
			if(strcmp(str[ans1-1],word[i].eng)==0)
				return 0;
			else return 1;
		}
	}
	
	return 2;	//エラー
}

/*表示用関数
説明は面倒なので気が向いたら。アルゴリズムもクソもない*/
void display(char str[][99],int wide,int high)
{
	int i,l,m,j;
	j=0;
	
	for(i=0;i<high*4+1;i++)
	{
		if((i % 4 == 0) || (i==0))
		{
			printf("*");
			for(l=0;l<wide;l++)
			{
				printf("**************");
			}
			printf("\n");
		}else if(((i+1) % 2) ==0)
		{
			printf("\n");
		}
		else
		{
			for(l=0;l<wide;l++)
			{
				printf("* %d",j+1);
				
				for(m=0;(m<(int)((11-strlen(str[j])))/2-2	);m++)
				{
					printf(" ");
				}
				printf(" %s ",str[j]);
				for(m=0;(m<(int)((11-strlen(str[j])))/2);m++)
				{
					printf(" ");
				}
				j++;
			}
			printf("*\n");
		}
	}
	fflush(stdout);
}

void file(FILE **fp,struct word_d word[])
{
	FILE *fo;
	
	int k,l,m,n,i;
	int num;
	char filename[256];
	char rireki[256][256];
	char c;
	i=l=m=0;
	
	printf("\n");
	fflush(stdout);
	fo=fopen("rireki.txt","a+");
	while(1)
	{
		c=fgetc(fo);
		if(c==EOF) break;
		if(c=='\n')
		{
			m=0;
			l++;
		}else
		{
			rireki[l][m]=c;
			m++;
		}
	}

	printf("入力するファイルの番号を選択してください\n\n");
	fflush(stdout);
	
	for(n=0;n<l;n++)
	{
		printf("%d %s\n",n+1,rireki[n]);
	}
	
	printf("%d 新規ファイル\n%d 履歴を削除\n\n",n+1,n+2);
	fflush(stdout);
	
	scanf("%d",&num);
	
	if(num==l+1)
	{
		scanf("%s",filename);
		fprintf(fo,"%s\n",filename);
		fflush(stdout);
	}else if(num==l+2)
	{
		fclose(fo);
		fo=fopen("rireki.txt","w");
	}else
	{
		strcpy(filename,rireki[num-1]);
	}
	
	fclose(fo);
	
	*fp=fopen(filename,"r");
	if(*fp == NULL)
	{
   		printf("ファイルが開けません\n");
   		fflush(stdout);
		exit(1);
 	 }
 	 
	for(;;)
	{
		word[i].num = i+1;
		if(fscanf(*fp,"%[^,],%s",word[i].eng,word[i].jp)==EOF)
		{
			//breakまで,と改行を区切りに文字を配列へ挿入
			i--;
			//fclose(fp);
			break;
		}else if(word[i].eng[0]=='\n')
		{
			for(k=0;k<255;k++)
			{
				word[i].eng[k]=word[i].eng[k+1];
			}
			//改行が配列の先頭に入り出力にバグが起きるため先頭を消去
			i++;
		}
	}
}



void timer()
{
	gettimeofday(&end, NULL);
	printf("かかった時間は%.2f秒です。\n", (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)*1.0E-6);
	fflush(stdout);
}
