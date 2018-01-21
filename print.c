#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct word_d
{
	int num;
	char eng[15];
	char jp[15];
};

void shuffle(char [][99], int);
int check_answer(char [][99],struct word_d[],int,int);
void display(char [][99],int,int);

int main()
{
	int wide,high,size,item;
	int i,a,a1;
	
	item = 4;	//単語数
	size = item *2 ;	//枠の数
	wide = 3;	//横幅
	high = 3;	//高さ
	
	
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
	
	char str1[size][99];
	
	
	
	strcpy(str1[0],"cat");
	strcpy(str1[2],"dog");
	strcpy(str1[4],"fish");
	strcpy(str1[6],"picture");
	strcpy(str1[1],"猫");
	strcpy(str1[3],"犬");
	strcpy(str1[5],"魚");
	strcpy(str1[7],"写真");

	shuffle(str1,size);
	
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
	
	display(str1,wide,high);
	
	i=0;
	while(i!=item)
	{
		printf("答えを入力してください");
		scanf("%d %d",&a,&a1);
		switch(check_answer(str1,word,a,a1))
		{
			case 0:	//正解
				printf("正解です\n");
				strcpy(str1[a-1],"---");
				strcpy(str1[a1-1],"---");
				i++;
				break;
			case 1:	//不正解
				printf("間違いです\n");
				break;
			case 2:
				printf("check error\n");
				break;
			default:
				printf("switch error\n");
				break;
		}
		display(str1,wide,high);
	}
	/*
	・表示問題の抽出(重み付け?)
	・表示配列の構造体化？
	・正解確認方法
	・終了後サイン
	・幅調整
	*/
	return 0;
}


void shuffle(char array[][99],int size)
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

int check_answer(char str[][99],struct word_d word[],int a,int a1)
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
		}
	}
	
	return 2;
}

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
}