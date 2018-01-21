#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*構造体定義*/
struct word_d
{
	/*ナンバー*/
	int num;
	/*英文*/
	char eng[15];
	/*日本語分*/
	char jp[15];
};
/*プロトタイプ宣言*/
void shuffle(char [][99], int);
int check_answer(char [][99],struct word_d[],int,int,int);
void display(char [][99],int,int);

int main()
{
	int i,j,ans,ans1;
	/*正答率計算用変数*/
	float cnt,bans;
	
	const int item = 4;	//単語数
	const int wide = 3;	//横幅。文字サイズにもよるが5ぐらいがデフォルトだと限界？
	const int high = 3;	//高さ
	const int size = item *2 ;	//枠の数。基本単語数の2倍?
	
	char str[size][99];	//一時保存用配列
	
	/*構造体配列*/
	struct word_d word[item];
	
	/*テスト用データ入力*/
	strcpy(word[0].eng,"cat");
	strcpy(word[0].jp,"猫");
	strcpy(word[1].eng,"dog");
	strcpy(word[1].jp,"犬");
	strcpy(word[2].eng,"fish");
	strcpy(word[2].jp,"魚");
	strcpy(word[3].eng,"picture");
	strcpy(word[3].jp,"写真");
	
	/*枠番号代入*/
	for(i=0;i<item;i++)
	{
		word[i].num=i;
	}
	
	j=0;
	/*一時保存用配列への入力*/
	for(i=0;i<item;i++)
	{
		strcpy(str[j],word[i].eng);
		j++;
		strcpy(str[j],word[i].jp);
		j++;
	}
	
	/*シャッフル*/
	shuffle(str,size);
	
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
	/*i=itemの時、全問正解*/
	while(i<item)
	{
		/*表示*/
		display(str,wide,high);
		printf("答えを入力してください\n");
		while(1)
		{
			/*解答読み込み*/
			scanf("%d %d",&ans,&ans1);
			if(ans<1 || ans>(size) || ans1<1 || ans1>(size))
			{
				printf("入力が不正です。もう一度入力してください。\n");
			}else break;
		}
		cnt++;
		switch(check_answer(str,word,ans,ans1,size))
		{
			/*正解*/
			case 0:
				printf("正解です\n");
				/*正解した単語を消す*/
				strcpy(str[ans-1],"---");
				strcpy(str[ans1-1],"---");
				i++;
				break;
				
			/*不正解*/
			case 1:	
				printf("間違いです\n");
				bans++;
				break;
				
			/*check_answerでのerror*/
			case 2:
				printf("check error\n");
				cnt--;
				break;
				
			default:
				printf("switch error\n");
				cnt--;
				break;
		}
	}
	printf("おめでとう！正答率は%.1f%%です",100*(1-(bans/cnt)));
	
	/*
	・表示問題の抽出(重み付け?)
	・表示配列の構造体化？
	・正解確認方法
	・終了後サイン
	・幅調整
	・メモリ関連。動的確保
	・同じ行に表示？
	・不正入力対策
	
	*/
	return 0;
}

/*シャッフル関数
Fisher-Yates法
出た乱数の配列から順に外側の配列と入れ替えていく*/
void shuffle(char str[][99],int size)
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
		char t[10];
		strcpy(t,str[i]);
		strcpy(str[i],str[j]);
		strcpy(str[j],t);
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
}