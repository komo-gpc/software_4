#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void shuffle(char [][256], int);
int check_answer(char [][256],struct [],int,int);

struct word_d
{
	int num;
	char *eng;
	char *jp;
};

int main()
{
	int wide,high,size,item;
	int i,l,m,j,a,a1;
	
	item = 4;	//単語数
	size = item *2 ;	//枠の数
	wide = 3;	//横幅
	high = 3;	//高さ
	j=0;
	
	
	char str[15];
	struct word_d word[item];
	
	strcpy(word[0].eng,"cat");
	strcpy(word[0].jp,"猫");
	strcpy(word[1].eng,"dog");
	strcpy(word[1].jp,"犬");
	strcpy(word[2].eng,"fish");
	strcpy(word[2].jp,"魚");
	strcpy(word[3].eng,"picture");
	strcpy(word[3].jp,"写真");
	
	for(i=0;i<item;i++)
	{
		word[i].num=i;
	}
	
	char str1[size][256];
	
	
	
	strcpy(str1[0],"cat");
	strcpy(str1[2],"dog");
	strcpy(str1[4],"fish");
	strcpy(str1[6],"picture");
	strcpy(str1[1],"猫");
	strcpy(str1[3],"犬");
	strcpy(str1[5],"魚");
	strcpy(str1[7],"写真");

	shuffle(str1,size);

	strcpy(str,"tyamaura");
	
	/*乱数設定*/
	//srand((unsigned)time(NULL));
	//乱数のシードを現在時刻を用いて設定
	//printf("%d\n",RAND_MAX);
	/*
	srand((unsigned)time(NULL));
	for(i=0;i<100;i++)
	{
		printf("%d ",(int)(rand()*(5.0/(float)RAND_MAX)));
	}
	printf("\n");
	
	
	2147483647.0
	*/
	

	/*表示部*/
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
				
				for(m=0;(m<(int)((11-strlen(str1[j])))/2-2	);m++)
				{
					printf(" ");
				}
				printf(" %s ",str1[j]);
				for(m=0;(m<(int)((11-strlen(str1[j])))/2);m++)
				{
					printf(" ");
				}
				j++;
			}
			printf("*\n");
		}
	}
	
	scanf("%d %d",&a,&a1);
	i=check_answer(str1,word,a,a1);

	/*
	・表示問題の抽出(重み付け?)
	・表示配列の構造体化？
	・正解確認方法
	・終了後サイン
	・幅調整
	*/
	return 0;
}


void shuffle(char array[15][256],int size)
{
	int i=size;
	while(i>1)
	{
		srand((unsigned)time(NULL));
		//乱数生成
		int j = rand() % i; //厳密性に欠ける書き方
		i--;
		//退避
		char t[10];
		strcpy(t,array[i]);
		strcpy(array[i],array[j]);
		strcpy(array[j],t);
	}
}

int check_answer(char str[],struct word_d word[],int a,int a1)
{
	int i;
	for(i=0;i<4;i++)
	{
		
		if(strcmp(str[a-1],word[i].eng)==0)
		{
			if(strcmp(str[a1-1],word[i].jp)==0)
				return 0;	//正解
			else return 1;	//不正解
		}else if(strcmp(str[a-1],word[i].jp)==0)
		{
			if(strcmp(str[a1-1],word[i].eng)==0)
				return 0;
			else return 1;
		}else return 3;
	}
}
			
/*test hoge*/