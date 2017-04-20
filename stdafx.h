// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#ifndef NAVIGATION_NAVIFATION_H
#define NAVIGATION_NAVIFATION_H
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<windows.h> 
#include <cstdlib>
#include <stdio.h>
#include<conio.h>
#define MAX_STR_LEN  32 
#define Maxmaze 200
#define M 8
#define N 8


//char passwd[MAX_STR_LEN] = { 0 };

typedef struct {  //密码长度
	char passwd[MAX_STR_LEN] = {0};
}Passwd;

typedef struct {
	int changei, changej;
	char name[100];
}box2;

typedef struct {
	box2 data[100];
	int top = 0;
}mapschange;



typedef struct {
	int row, col;  //方块的位置
	int pre;    //上一方块的下标

} Box;   //方块类型
typedef  struct {
	Box data[Maxmaze];
	int front, rear;  //队列的头指针， 尾指针

}QuType;

typedef struct {
	int map[M + 2][N + 2] =  //校园地图
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,0,0,0,0,0,0,1 },
		{ 1,1,0,0,1,1,0,1,0,1 },
		{ 1,1,1,0,1,1,0,1,0,1 },
		{ 1,1,0,0,0,0,0,0,0,1 },
		{ 1,0,0,1,1,1,0,1,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,1,1,0,1,1,0,0,1 },
		{ 1,0,0,0,0,0,0,0,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 }
	};
}Map;

void print(QuType qu, int front, Map smallmap);
int mappath(int xi, int yi, int xe, int ye, Map smallmap);
int watch(Map map);
void printphotograph(QuType qu, int front, Map mapp);
int altermap1(Map map, int i, int j);
int altermap0(Map map, int i, int j);
char *GetPasswd(void);
void clearscreen();  
void ChangeTheMap();

mapschange difition();
void printspot(mapschange mapc);

mapschange RemoveTheMap(int order,mapschange mapc);
mapschange AddTheMap(int order, mapschange mapc, Map map);
boolean equalsMap(Map map, int i, int j);

#endif //NAVIGATION_NAVIFATION_H

