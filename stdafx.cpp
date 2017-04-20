
#include "stdafx.h"



int mappath(int xi, int yi, int xe, int ye, Map mapp)   //搜索路径为:(xi,yi)->(xe,ye)
{
	int i, j, di; //di为四个方向
	int find = 0; //找到路径的标识码
	int ca = 0;  //用于选择坐标输出还是图像输出；
	Map map1;

	QuType qu; //
	qu.front = qu.rear = -1;
	qu.rear++;
	qu.data[qu.rear].row = xi;
	qu.data[qu.rear].col = yi; //xi, yi 入队.(xi,yi)为起点
	qu.data[qu.rear].pre = -1;

	mapp.map[xi][yi] = -1; //将其赋值-1,以避免回过来重复搜索

	while (qu.front != qu.rear && !find)
	{
		qu.front++; //出队
		i = qu.data[qu.front].row;
		j = qu.data[qu.front].col;
		if (i == xe && j == ye)//找到了最短路径,输出路径
		{
			find = 1;
			printf("请选择输出方式(选择1，2 或者3)\n");
			printf("1.坐标输出\n");
			printf("2.图像输出\n");
			printf("3，坐标和图像同时输出\n");
			scanf("%d", &ca);
			switch (ca)
			{
			case 1: print(qu, qu.front, mapp); //调用print函数输出路径
				break; 
			case 2: printphotograph(qu, qu.front, map1);//图像输出
				break; 
			case 3: print(qu, qu.front, mapp);
				 printphotograph(qu, qu.front, map1);
				 break;
			}
					
			return 1;  //找到一条路径时返回1
		}

		for (di = 0; di < 4; di++) //循环扫描每个方位,把每个可走的方块插入队列中
		{
			switch (di)
			{
			case 0:  //东
				i = qu.data[qu.front].row + 1;
				j = qu.data[qu.front].col;
				break;
			case 1:  //南
				i = qu.data[qu.front].row;
				j = qu.data[qu.front].col + 1;
				break;
			case 2:  //西
				i = qu.data[qu.front].row - 1;
				j = qu.data[qu.front].col;
				break;
			case 3:  //北
				i = qu.data[qu.front].row;
				j = qu.data[qu.front].col - 1;
				break;
			}
			if (mapp.map[i][j] == 0) //找到一个可走的坐标
			{
				qu.rear++;  //将该相邻方块插入到队列中
				qu.data[qu.rear].row = i;
				qu.data[qu.rear].col = j;
				qu.data[qu.rear].pre = qu.front; //该坐标的pre指向路径中上一个方块（front）的下标,这是能记录最短路径的关键，指向他能走的上一块。
				mapp.map[i][j] = -1;  //避免重复搜索
			}
		}
	}
	if (mapp.map[i][j] != 0)
	{
		printf("对不起，此终起点没有可达路径，请重新选择");
	}
}


int watch(Map map)
{
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 11; j++) 
		{
			if (i == 10) 
			{
				printf("---");
				continue;
			}
			if (i == 11 ) 
			{
				
				if (j == 10)
					printf("坐标");
				else
					printf("%d，", j);
				continue;
			}

			else if (j == 10 ) {
				printf("| %d ", i);
			}
			else
				printf("%d，", map.map[i][j]);
		}

		putchar('\n');
	}
	return 0;
}


void print(QuType qu, int front, Map mapp) //从队列qu中输出路径. front 为最后的 qu.front
{
	int k = front, j, ns = 0, nk = 0;
	int a[100], b[100];
	printf("\n");
	do {               //反向找到最短路径,将该路径上的方块的pre成员设置成-1
		j = k;
		k = qu.data[k].pre;        //k指向上一块
		qu.data[j].pre = -1;	//把这块的pre设置成-1，不再指向上一块
	}

	while (k != 0);  //初始化的 qu.rear = qu.front = -1, 当qu.front++, 所以第一个qu.front=0

	printf("最短路径为(坐标输出)：\n");

	k = 0;

	while (k <= front)
	{
		if (qu.data[k].pre == -1)
		{
			ns++;
			printf("\t(%d, %d)", qu.data[k].row, qu.data[k].col);
			if (ns % 5 == 0)
				printf("\n");  //每输出每5个方块后换一行
		}
		k++;
	}
	printf("\n");

}
void printphotograph(QuType qu, int front, Map mapp) //这个Map是没有被搜索过的
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //修改输出路径的颜色
	int k = front, j, ns = 0;
	int ni = 0, nj = 0;
	int maps[10][10];
	printf("\n");
	do {               //反向找到最短路径,将该路径上的方块的pre成员设置成-1
		j = k;
		k = qu.data[k].pre;        //k指向上一块
		qu.data[j].pre = -1;	//把这块的pre设置成-1，不再指向上一块
	}

	while (k != 0);  //初始化的 qu.rear = qu.front = -1, 当qu.front++, 所以第一个qu.front=0

	printf("最短路径为(图像输出)：\n");

	k = 0;

	while (k <= front)
	{
		if (qu.data[k].pre == -1)
		{
			maps[qu.data[k].row][qu.data[k].col] = 2;

		}
		k++;
	}

		for ( ni = 0; ni < 10; ni++)
		{
			for ( nj = 0; nj < 10; nj++)
			{
				if (maps[ni][nj] == 2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("+,");
					SetConsoleTextAttribute(hOut,   //颜色复原
						FOREGROUND_RED |   // 前景色_红色
						FOREGROUND_GREEN | // 前景色_绿色
						FOREGROUND_BLUE);
				}
				else
				{
					printf("%d,",mapp.map[ni][nj]);
				}
			}

			putchar('\n');
		}

	

	printf("\n");
}

int altermap1(Map map, int i, int j)  
{
	map.map[i][j] = 1;
	return map.map[i][j];
}

int altermap0(Map map, int i, int j)
{
	map.map[i][j] = 0;
	return map.map[i][j];
}

char *GetPasswd(void)  //密码输入
{
	char c;
	int i = 0;
	int len = MAX_STR_LEN - 1;
	Passwd passwod;
	while ((c = getch()) != '\r')
	{
		passwod.passwd[i] = c;
		putchar('*');
		i++;
		if (i >= len)
		{
			break;
		}
	}

	return passwod.passwd;
}

void clearscreen()  //清屏函数
{
	printf("\n\n\n\t\t 按回车键进行清屏.......");
	getchar();

	getchar();
	system("cls");
}


mapschange difition() //初始化地点
{
	int i,j,k;
	mapschange mapc;
	mapc.top = -1;

	strcpy(mapc.data[0].name, "校门口");
	strcpy(mapc.data[1].name, "会花坛");
	strcpy(mapc.data[2].name, "瞭望楼");
	strcpy(mapc.data[3].name, "正德楼");
	strcpy(mapc.data[4].name, "图书馆 ");
	strcpy(mapc.data[5].name, "青工楼");
	strcpy(mapc.data[6].name, "大食堂 ");
	strcpy(mapc.data[7].name, "小吃店 ");
	strcpy(mapc.data[8].name, "后  街");
	strcpy(mapc.data[9].name, "运动场");

	int a[10] = {1,1,2,3,4,5,6,1,8,8};
	int b[10] = {3,8,2,8,6,1,4,6,2,5};

	for (j = 0; j < 10; j++)
	{
		mapc.data[j].changei = a[j];
		mapc.top = j;
	}

	for (k = 0; k < 10; k++)
	{
		mapc.data[k].changej = b[k];
	}

	return mapc;
	
}

void printspot(mapschange mapc) //输出地点
{
	int i;
	for  (i = 0; i < mapc.top + 1; i++)
	{
		printf("\t%d. \t%s\t(%d, %d)\n",i+1,mapc.data[i].name, mapc.data[i].changei, mapc.data[i].changej);

	}
	printf("%d",mapc.top);
	

}

mapschange RemoveTheMap(int order,mapschange mapc) //删除景点
{
	int i;
	for (i = order; i < mapc.top + 1; i++)
	{
		strcpy(mapc.data[order].name, mapc.data[order + 1].name);
		mapc.data[order].changei = mapc.data[order + 1].changei;
		mapc.data[order].changej = mapc.data[order + 1].changej;
	}
	mapc.top -= 1;
	return mapc;
}

mapschange AddTheMap(int order, mapschange mapc, Map map) //添加景点
{
	int i,j;
	int placei, placej;
	char place[100];
	j = mapc.top++;
	for (i = 0; i < order; i++)
	{
		printf("请输入地点名：");
		scanf("%s", &place);
		strcpy(mapc.data[mapc.top].name, place);
		printf("输入该地点的坐标:");
		scanf("%d, %d",&placei, &placej);
		if (equalsMap(map, placei, placej))
		{
			printf("此点不可修改为景点，除非修改路径!\n");
			break;
		}
		mapc.data[mapc.top].changei = placei;
		mapc.data[mapc.top].changej = placej;
		mapc.top += 1 ;
	}
	mapc.top -= 1;
	if (i == order - 1)
	{
		printf("输入成功！");
	}

	return mapc;
}

boolean equalsMap(Map map, int i, int j)
{
	while (map.map[i][j] == 1)
	{
		return 1;
	}
	return 0;
}


