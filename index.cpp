#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <time.h>
#define STACK_SIZE 4096

HANDLE hthread;

typedef struct horseinfo// все, что касается лошадей
{
HANDLE hmtx;
BOOL hflag;   // лошадиный флаг
int dest;     // номер города
};

struct horseinfo horses[48];  //массив лошадей

typedef struct maninfo // для пассажиров
{
HANDLE mmtx;
int dest;
};

struct maninfo mans[30];

int BornNum; //Общая область для всех потоков
int BornHorseDest;  //Город, в котором рождается лошадь
int BornCowboyDest; // Город, где рождается ямщик
int BornCowboyNumber; // Номер ямщика, с которым он рождается

void horsethread(void *arg) // Данная функция отвечает за лошадей
{
int num=BornNum;
printf("%d horse in the town ",num);
printf("%d\n",horses[num].dest);
while (TRUE)
 {
  printf("Horse %d is ready \n ",num);
  while (horses[num].hflag) {}
  Sleep(300);
  while (!horses[num].hflag) {}
  WaitForSingleObject(horses[num].hmtx, INFINITE); // лошадь спит
 	  printf("Horse %d is sleep \n",num);
  Sleep(2000);
  ReleaseMutex(horses[num].hmtx);   //лошадь просыпается
 }
}

void cowboythread(void *arg) // Данная функция отвечает за ямщиков с пассажирами
{
int i = 0;
int num=BornCowboyNumber;
int dest=BornCowboyDest;
int next=0;

int countmans=3;
int j=0;
int k=0;
int currentman=0;

srand(time(NULL));
next=(rand()%7)+1;
printf("Cowboy in the town ");
printf("%d Destination ",dest);
printf("Next is %d\n",next);
while (TRUE)
{
 for (i=0;i<=48;i++)
 		 {
   if (horses[i].dest==dest)
 			   {
   			   WaitForSingleObject(horses[i].hmtx, INFINITE);
   			   printf("Cowboy %d going to the \n",num);
   			   printf(" %d",next);
   			   horses[i].hflag=FALSE;
    			  for (j=0;j<=32;j++)
	{
     				  if (mans[j].dest==dest)
	{
	WaitForSingleObject(mans[j].mmtx, INFINITE);
	printf("Cowboy %d get passager",num);
	printf("%d\n",j);
	currentman=j;
	}
	}
      			printf("Cowboy %d get horse",num);
  			printf("%d\n",i);
   			Sleep(300);
   			horses[i].dest=next;
    			dest=next;
  			mans[j].dest=dest;
  			printf("Cowboy %d ",num);
   			printf("in the %d\n",dest);
      			srand(time(NULL));
     			next = (rand()%7)+1;
      			horses[i].hflag=TRUE;
     			printf("Cowboy %d push horse",num);
      			printf("%d\n",i);
      			mans[currentman].dest=dest;
      			ReleaseMutex(mans[currentman].mmtx);
     			ReleaseMutex(horses[i].hmtx);
     			i=48;
    			}
 		 }
  	}
}

HANDLE horsesmutex;

int main(void)
{
void cowboythread(void *arg);
void horsethread(void *arg);
unsigned long threadid;

//Born horses
int i,k,j;
k=0; i=0; j=0;
horsesmutex=CreateMutex	(NULL, FALSE, NULL);
srand(time(NULL));
for (i=1; i<=8; i++)
{
 for (j=1; j<=6; j++)
  {
  		   mans[k].dest=i;
     mans[k].mmtx = CreateMutex(NULL, FALSE, NULL); // инициализируется семафор
  }
}
k=0;
for (i=1; i<=8; i++)
{
  	for (j=1; j<=6; j++)
  		 {
     		horses[k].dest=i;
   		horses[k].hflag=TRUE;
     		horses[k].hmtx = CreateMutex(NULL, FALSE, NULL); // инициализируется семафор
   		BornNum=k;
   		hthread=(HANDLE)_beginthreadex(horsethread, STACK_SIZE, NULL, NULL,  0, &threadid); //запускает лошадь
   		k++;
   		Sleep(200);
 		}
 }

//Born cowboys
for (i=1;i<=8;i++)
{
 for (j=1; j<=4;j++)
 		 {
   		 BornCowboyDest=i;
  		 BornCowboyNumber=j;
  		 hthread=(HANDLE) 	(cowboythread, STACK_SIZE, NULL, NULL,  0, &threadid); //запускаем ямщиков
 		  Sleep(20);
  }
   }
while (TRUE) {} //вечный цикл
 }

