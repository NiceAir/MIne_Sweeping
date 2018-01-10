#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

int main(){
	char mine[MROW][MCOL];
	char show[MROW][MCOL];
	int row=0, col=0;
	int count=0;
	int dead[2]={0};
	char again[3]={'5'};
	int c=0;
	int Fx=-1, Fy=-1;
	int WinSign=0;
	srand((unsigned int) time(NULL));

AGAIN :	Init_Board(mine,show, &row, &col);
	Show_Board(show, row, col);
	while(1)
	{
		printf("选择位置：>");
		scanf("%d%d", &Fx, &Fy);
		if ( Check_Legal(row, col, Fx, Fy) !=1)
		{
			printf("输入位置不合法，再次");
			continue;
		}
		break;
	}
	while((c = getchar()) != '\n' && c != EOF);     //清除键盘缓冲区的万能写法
	PutMine(mine, row, col, Fx, Fy, &count);
	while(Player_Do(mine, show, row, col, dead, &Fx, &Fy) ==0)
	{
		if(!Check_Win(show, row, col, count))
		{
			WinSign=0;
	//		Show_Board(mine, row, col);
			Show_Board(show, row, col);
			printf("*********************共有%d颗雷********************\n", count);
		}
		else
		{
			WinSign=1;
			break;
		}
	}
		if (WinSign==1)
		{
			Show_Board(show, row, col);
			printf("恭喜你，排完了所有雷!\n");
		}
		else
		{
			show[dead[0]][dead[1]] = '*'; 
			Show_Board(show, row, col);
		}
		printf("**********************************游戏结束****************************************\n");
		Sleep(2500);
		printf("你还想再玩一局吗？(Y/N)  >");
		scanf("%c", &again);
		while((c = getchar()) != '\n' && c != EOF);     //清除键盘缓冲区的万能写法
		if ( strcmp(again, "Y")==0 || strcmp(again, "y")==0 || strcmp(again, "YES")==0 || strcmp(again, "yes")==0 || strcmp(again, "Yes")==0 ) goto AGAIN ;
	
	return	0;
}