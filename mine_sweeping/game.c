#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

static void Create_Board(char mine[MROW][MCOL], char show[MROW][MCOL], const int level, int *row, int *col){
		int i=0, j=0;
		*row=level;
		*col=level;
		for(i=0; i<MROW; i++)
		{
			for(j=0; j<MCOL; j++)
			{
				mine[i][j]='0';
				show[i][j]='#';
			}
		}
}

void PutMine(char mine[MROW][MCOL], const int row, const int col, int Fx, int Fy, int *count)
{
	int i=0, j=0;
	int x=0, y=0;
	int ss=0;

	*count = row + (int)pow(2,(col/4));			//雷数   一级： 12颗      二级：32颗    三级：88颗

	for (i=0; i<*count; i++)
	{
		x=rand()%row + 1;
		y=rand()%col + 1;
		if(mine[x][y]=='1' || ((x==Fx) && (y==Fy)) )
		{
			i--;
			continue;
		}
		mine[x][y]='1';
		ss++;
		//			printf("第%d颗雷的位置是 (%d, %d)\n", ss, x ,y);
	}
}

void Init_Board(char mine[MROW][MCOL], char show[MROW][MCOL], int *row, int *col){
	int choose;
	int c=0;
	printf("请选择难度（  1：容易  2：一般  3：困难 ）>");
	scanf("%d", &choose);
	while((c = getchar()) != '\n' && c != EOF);
	while(choose!=1 && choose!=2 && choose!=3)
	{
		printf("输入有误，请重新选择难度（  1：容易  2：一般  3：困难 ）>");
		scanf("%d", &choose);
		while((c = getchar()) != '\n' && c != EOF);
	}
	switch (choose){
		case 1:Create_Board(mine,show, EAZY, row, col); break;
		case 2:Create_Board(mine, show,ORDINARY, row, col); break;
		case 3: Create_Board(mine,show, DIFFICUTE, row, col);break;
		default: printf("输入错误\n");
	}
}


void Show_Board( const char board[MROW][MCOL], const int row, const int col){
	int i = 0, j = 0;
	for(i=0; i<row+1; i++)
	{
		if (i==0)
		{
			for (j=0; j<row+1; j++)		(j<10) ? printf("  %d ", j) : printf(" %d ", j);
		
			printf("\n");
		}
		else
		{
			for(j=0; j<col+1; j++)		(j==0) ? printf("   ") : printf(" ---");
			
			printf("\n");
			for (j=0; j<col+1; j++)
			{
				if (j==0)	(i<10) ? printf("  %d", i) : printf(" %d", i); 
				
				else printf("| %c ",board[i][j]);
			}

			printf("|\n");
			if(i==row)
				for(j=0; j<col+1; j++)   	(j==0) ? printf("   ") : printf(" ---");
					
		}
		
	}
	printf("\n\n");
}

int Check_Legal(const int row, const int col, const int x, const int y)
{
	return ( x<row+1  && x>0 && y<col+1 && y>0 ); 
}

static void Mark_MineCount(char mine[MROW][MCOL], char show[MROW][MCOL], const int  row, const int col, const int x, const int y)
{
	char c = '0';

	if (  Check_Legal(row, col, x, y) !=1 )
	{
		return;
	}
	else if (mine[x][y] == '1' || mine[x][y] == '-' || show[x][y]!='#')
	{
		return;
	}
	else
	{
		if(mine[x-1][y-1] !='-')  (c = c + mine[x-1][y-1] - '0');
		if(mine[x-1][y] !='-')	 (c = c + mine[x-1][y] - '0');
		if(mine[x-1][y+1] !='-')  (c = c + mine[x-1][y+1] - '0');

		if(mine[x][y-1] !='-')  (c = c + mine[x][y-1] - '0');
		if(mine[x][y+1] !='-')  (c = c + mine[x][y+1] - '0');

		if(mine[x+1][y-1] !='-')  (c = c + mine[x+1][y-1] - '0');
		if(mine[x+1][y] !='-')  (c = c + mine[x+1][y] - '0');
		if(mine[x+1][y+1] !='-')  (c = c + mine[x+1][y+1] - '0');

		if(c == '0') show[x][y] = ' ';
		else show[x][y] = c;
		mine[x][y] = '-';
	}
}

int expand(const char mine[MROW][MCOL], char show[MROW][MCOL], const int row, const int col, const int x, const int y)
{
	
	if (  Check_Legal(row, col, x, y) !=1 )
	{
		return -1;
	}
	else if (mine[x][y] == '1' || mine[x][y] == '-')
	{
		return -2;
	}

	else
	{
		Mark_MineCount(mine, show, row, col, x, y);
		if(show[x][y] == ' ')
		{
			expand(mine, show, row, col, x-1, y-1);
			expand(mine, show, row, col, x-1, y);
			expand(mine, show, row, col, x-1, y+1);
			expand(mine, show, row, col, x, y-1);
			expand(mine, show, row, col, x, y+1);
			expand(mine, show, row, col, x+1, y-1);
			expand(mine, show, row, col, x+1, y);
			expand(mine, show, row, col, x+1, y+1);
		}
	}
	return 0;
}


int  Player_Do(char mine[MROW][MCOL], char show[MROW][MCOL], const int row, const int col, int dead[2], int *Fx, int *Fy)
{
	int x=0, y=0;
	int c=0;
	x=*Fx; y=*Fy;
Reput:	
	if (*Fx ==-1 && *Fy ==-1)
	{
		printf("选择位置：>");
		scanf("%d%d", &x, &y);
		while((c = getchar()) != '\n' && c != EOF);
	}

	*Fx=-1;  *Fy=-1;
	if(Check_Legal(row, col, x, y)==1)
	{
		if(mine[x][y]=='1')
		{
			dead[0] = x; 
			dead[1] = y;
			return 1;
		}
		else if (mine[x][y] == '-')
		{
			printf("此位置无效， 再次");
			goto Reput;
		}
		else
		{
			expand(mine, show, row, col, x, y);
		}
	}

	else
	{
		printf("输入位置不合法，再次");
		goto Reput;
	}
	return 0;
}


int Check_Win(static char show[MROW][MCOL], static int row, static int col, int count)
{
	int i=0, j=0;
	for (i=1; i<=row; i++)
	{
		for(j=1; j<=col; j++)
		{
			if (show[i][j]=='#')
			{
//				printf("show[%d][%d]=%c  ", i, j, show[i][j]);
				count--;
			}
//			else printf("show[%d][%d]=  ", i, j);
		}
//		printf("\n");
	}
//	printf("\n");
	if (count<0)
	{
		return 0;
	}
	return 1;
}