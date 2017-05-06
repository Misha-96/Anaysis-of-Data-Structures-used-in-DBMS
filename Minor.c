#include <locale.h>
#include <stdio.h>
#include "avltree.h"
#include "bst.h"
#include "btree.h"
#include <stdlib.h>
#include <unistd.h>
#include "persistence.h"
#include "results.h"
//#include "plot.h"
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

void writer();
void reader(int data);

int main()
{
  int t=1;
  char option;
  FILE *fp;

  while(t!=0)
  {
   system("clear");
   system("setterm -bold on");
   printf("                       ||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
   printf("\n\n                                ANALYSIS OF DATA STRUCTURE ALGORITHMS\n\n");
   printf("\n                       ||||||||||||||||||||||||||||||||||||||||||||||||||||||");
   printf("  \n\n\n\n");
   system("setterm -bold off");
   printf("\n                            Which algorithm you want to test?\n");
   printf("                            --------------------------------\n\n\n\n");
   system("setterm -bold on");
   printf("                              IN-MEMORY ALGORITHMS\n\n");
   system("setterm -bold off");
   printf("                              1. Algorithm AVL TREE\n");
   printf("                                 ------------------\n");
   printf("                              2. Algorithm Binary Search TREE\n");
   printf("                                 ----------------------------\n\n");
   printf("                         ------------------------------------------------------\n");
   printf("                         ------------------------------------------------------\n\n\n");
   system("setterm -bold on");
   printf("                              ON-DISK ALGORITHMS\n\n");
   system("setterm -bold off");

   printf("                              3. Algorithm B TREE\n");
   printf("                                 ----------------\n");
   printf("                              4. Demo Module\n");
   printf("                                 -----------\n");
 //  printf("                              5. Exit\n");
  // printf("                                 ----\n\n");
   printf("                         ------------------------------------------------------\n");
   printf("                         ------------------------------------------------------\n\n\n");
   system("setterm -bold on");
   printf("                              Results\n");
   system("setterm -bold off");
   printf("\n\n\n\n");
   printf("                              Choice: ");
   printf("\n\n\n\n");
   printf("                              Type R for Results and E to exit\n");
   gotoxy(30,38);
   option=getchar();
   int ioption=option;
   printf("\n");
   switch(ioption)
    {
     case 49 :
     fp=fopen("data.dat","w");
     fclose(fp);
     system("clear");
     printf("Loading AVL..\n\n");
     sleep(1);
     mainavl();
     break;

     case 50:
     fp=fopen("data.dat","w");
     fclose(fp);
     system("clear");
     printf("Loading BST..\n\n");
     sleep(1);
     mainbst();
     break;

     case 51:
     fp=fopen("data.dat","w");
     fclose(fp);
     system("clear");
     printf("Loading B-Tree..\n\n");
     sleep(1);
     mainbtree();
     break;

     case 52:
     fp=fopen("data.dat","w");
     fclose(fp);
     system("clear");
     printf("Loading Demo Case..\n\n");
     printf("Sorry no module exists\n");
     sleep(1);
     //call main function of module here
     printf(" ");
     break;

     case 69:
     printf("Exiting...\n");
     sleep(1);
     system("clear");
     t=0;
     break;


     case 82:
     system("clear");

     printf("Loading Results..\n");
     sleep(1);

     mainresults();



     default :
     printf("Can't find the choice\n");




   //  sleep(1);
     break;

   }
  }
}
