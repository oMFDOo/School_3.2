#pragma once
#pragma once

#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>


#define col GetStdHandle(STD_OUTPUT_HANDLE) // 콘솔창의 핸들정보 받기

#define BLACK SetConsoleTextAttribute(col, 0x0000);
#define RED SetConsoleTextAttribute(col, 0x000c); // 빨간색
#define BLUE SetConsoleTextAttribute(col, 0x0001 | 0x0008); // 파란색
#define HIGH SetConsoleTextAttribute(col, 0x000a); // 연두색
#define WHITE SetConsoleTextAttribute(col, 0x000f); // 흰색
#define SKY SetConsoleTextAttribute(col, 0x000b); // 하늘색
#define YEL SetConsoleTextAttribute(col, 0x000e); // 노랑색
#define HIG SetConsoleTextAttribute(col, 0x000d); // 형광색
#define GOLD SetConsoleTextAttribute(col, 0x0006); // 금색
#define JAJU SetConsoleTextAttribute(col, 0x0005); // 자주색
#define PII SetConsoleTextAttribute(col, 0x0004); // 피색
#define GREEN SetConsoleTextAttribute(col, 0x0002); // 녹색
#define VIO SetConsoleTextAttribute(col, 0x0001 | 0x0008 | 0x000c); // 보라색
#define UP 72
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77
#define ENTER 13

#pragma comment (lib,"winmm.lib")	

//////////////////////////////// 그리기 /////////////////////////////////////////
void removeCursor(void)
{ // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void gotoxy(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void showCursor(void)
{ // 커서를 보이게 한다
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void cls(int bg_color, int text_color) // 화면 지우기
{
	char cmd[100];
	int fg_color = 0;
	system("cls");
	sprintf_s(cmd, 100, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

char* aaaa[158] =
{
	//{ "                                                                                                                                                  " }, //0 
	//{ "                                                                                                                                                  " },
	//{ "　　┌   시점   ───────────────────────┐　　　　　　　　　　　　┌ 　플레이 　────────────────────┐" },
	//{ "　　│                                                        │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　│                                                        │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　│    케릭터이동 : 화살표 왼쪽 버튼과 오른쪽 버튼         │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" }, //5
	//{ "　　│  　             모두 이용하여 유저의 속도를            │　　　　　　　　　　　　│　　                                          　　　│" },
	//{ "　　│  　             조절할 수 있습니다.                    │　　　　　　　　　　　　│　　　　　　　　 　                             　　│" },
	//{ "　　│  　                                                    │　　　　　　　　　　　　│　　　　　　　　　                                　│" },
	//{ "　　│   　                                                   │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　│    　                                                  │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" }, //10
	//{ "　　│  　△ 마우스 : 마우스를 이용해 왼쪽 버튼 클릭 후       │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　│   　           드래그를 하게되면 왼쪽 오른쪽으로       │　　　　　　　　　　　　│　　　　　　　 　　　　　 　　　　　 　　　　　   　│" },
	//{ "　　│    　          시점을 변화시킬 수 있습니다.            │　　　　　　　　　　　　│　　　　　　　　　　　　　　 　　　　　 　　　  　　│" },
	//{ "　　│     　                                                 │　　　　　　　　　　　　│　　　　　　　　       　　　　　 　 　 　     　 　│" },
	//{ "　　│   　                                                   │　　　　　　　　　　　　│　　　　　　　　　 　　　　　 　　　　　 　　　　   │" }, //15
	//{ "　　│ 　                                                     │　　　　　　　　　　　　│　　　　　　　　　 　　　　　 　　　　　  　　　　  │" },
	//{ "　　│ 　 △ 키보드 1. 'w', 's' 버튼을 통해 카메라의 y축      │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　│   　            위치를 조절할 수 있습니다.             │　　　　　　　　　　　　│　　                                           　 　│" },
	//{ "　　│     　       2. 'a', 'd' 버튼을 통해 카메라의 z축      │　　　　　　　　　　　　│　　　　　　　　                     　　　　　　 　│" },
	//{ "　　│                 위치를 조절할 수 있습니다.             │　　　　　　　　　　　　│　　　　　　　  　                       　　　　　 │" }, // 20
	//{ "　　│                                                        │　　　　　　　　　　　　│　　　　　　　  　                                　│" },
	//{ "　　│                                                        │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　│                                                        │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　│                                                        │　　　　　　　　　　　　│　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　　└────────────────────────────┘　　　　　　　　　　　　└──────────────────────────┘" }, //25
	//{ "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" },
	//{ "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" },
	//{ "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" },
	//{ "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" },
	//{ "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　" }, //30
	//{ "　┌─────────────────────────────────────────────────────────────────────┐" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" }, //35
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },  //40
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" }, //45
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" },
	//{ "　└─────────────────────────────────────────────────────────────────────┘" },

};

void intro_start()
{
	system("mode con: cols=160 lines=58");				// 게임 창(콘솔창) 크기를 바꿔줌
	printf("게임 설명 \n");
	for (int i = 0; i < 50; i++)
	{
		WHITE;
		gotoxy(1, i);
		printf("%s", aaaa[i]);
	}
	GREEN; gotoxy(8, 33); printf("그래픽스 텀 프로젝트");
	BLUE; gotoxy(8, 35); printf("컴퓨터 공학과");
	GOLD; gotoxy(8, 37); printf("1392056 김준희");

	SKY; gotoxy(8, 40); printf("화살표 키를 통해 유저의 속도를 조절해 모든 적들을 제치고 도착지에 가장 빨리 도착하면 이기는 게임입니다.");
	SKY; gotoxy(8, 42); printf("유저의 속도는 자동으로 조금씩 느려집니다.\n");
	removeCursor();
}