#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

struct Seting{
        int h;
        int w;
};
struct stansh{
};

void creat(int k){
   /* if (k>14){

    }
    else{*/
    int i,j;
        for(i=0;i<4;i++){
            for(j=0;j<4;j++){
                move(1+i*7,7+j*20);
                addch('A');
            }
    }


return;
}
int main()
        {
        int c;
        struct Seting windows;


        printf("Введите количество станцый: ");
        scanf("%d", &c);
        initscr();
        //getmaxyx(stdscr, windows.h, windows.w);
        creat(10);
         while((c=getch())!=27){
        refresh();
         usleep(30);
         }
         endwin();
         //getch();
         return 0;
}
