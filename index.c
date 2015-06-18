#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <time.h>
#include <conio.h>

//
int width =80;
int height =25;
//
struct Point{
int x;
int y;
};
//8 -почтовых станцый (5-7 лошедей дл€ одной станции)
//лошади отдыхаит после поездки
//Ќа четырЄх ведущих станци€х, моделирующих города
void gotoxy(struct Point t)
{
	COORD scrn;// = t;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = t.x; scrn.Y = t.x;

	SetConsoleCursorPosition(hOuput, scrn);
}
struct Loshad{
    struct Point cord;
    BOOL Otdix;
};
struct Station{
    struct Point cord;
};

struct Station st[8];
struct Loshad losh[8][7];
void CreatLoshad(int k){
    int i;
    for(i=0;i<(5-rand()%2);i++){
        losh[k][i].cord.x = st[k].cord.x;
        losh[k][i].cord.y = st[k].cord.y;
    }

}
void CreatStation(){
    int i;
    for(i=0;i<8;i++){
        st[i].cord.x = rand()%width;
        st[i].cord.y = rand()%height;
        CreatLoshad(i);
    }
}
void print(){
    int i;
    for(i=0;i<4;i++){
        printf("");
    }
}

int main()
{

}
