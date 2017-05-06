#include "plot.h"
int mainresults()
{
 writeplot();
  system("gnuplot -p -e \"load '/home/erick/Minor_GM/plot.p'\"");
 int quit=0;
 while(quit!=1){
  printf("\n");
  system("clear");
  printf("\n");
  char quitl;
  clock_t start, end;
  double cpu_time_used1,cpu_time_used2,cpu_time_used3,cpu_time_used4,cpu_time_used5,cpu_time_used6,cpu_time_used7,cpu_time_used8,cpu_time_used9;
  int num,i ;
  int a[2000000];

  //printf("Enter the size");
  //scanf("%d",&num);


    //FOR BST

    start = clock();
    for (i=0;i<100;i++){
     a[i]= rand()%100000;  //%num is the range between 1 - num you want
     insertbst(&root,a[i]);
      }
    end = clock();
    cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (i=0;i<10000;i++){
     a[i]= rand()%100000;  //%num is the range between 1 - num you want
     insertbst(&root,a[i]);
      }
    end = clock();
    cpu_time_used2 = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (i=0;i<100000;i++){
     a[i]= rand()%100000;  //%num is the range between 1 - num you want
     insertbst(&root,a[i]);
      }
    end = clock();
    cpu_time_used3 = ((double) (end - start)) / CLOCKS_PER_SEC;


    //FOR AVL
    struct nodeavl *root = NULL;
     start = clock();
       for (i=0;i<100;i++)
       {
        a[i]= rand()%100000;  //%num is the range between 1 - num you want
        root = insertavl(root,a[i]);
     //   writer(a[i]);
        }
       end = clock();
       cpu_time_used4 = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
       for (i=0;i<10000;i++)
       {
        a[i]= rand()%100000;  //%num is the range between 1 - num you want
        root = insertavl(root,a[i]);
     //  writer(a[i]);
        }
       end = clock();
       cpu_time_used5 = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
       for (i=0;i<100000;i++)
       {
        a[i]= rand()%100000;  //%num is the range between 1 - num you want
        root = insertavl(root,a[i]);
       // writer(a[i]);
        }
       end = clock();
       cpu_time_used6 = ((double) (end - start)) / CLOCKS_PER_SEC;


    //FOR BTREE
    start = clock();
               for (i=0;i<100;i++){
                a[i]= rand()%100000;  //%num is the range between 1 - num you want
                insertionbtree(a[i]);

                }
               end = clock();
               cpu_time_used7 = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
               for (i=0;i<10000;i++){
                a[i]= rand()%100000;  //%num is the range between 1 - num you want
                insertionbtree(a[i]);

                }
               end = clock();
               cpu_time_used8 = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
               for (i=0;i<500000;i++){
                a[i]= rand()%10000000;  //%num is the range between 1 - num you want
                insertionbtree(a[i]);

                }
               end = clock();
               cpu_time_used9 = ((double) (end - start)) / CLOCKS_PER_SEC;

    system("setterm -bold on");
    printf(" \n                      Insertion Cases\n");
    system("setterm -bold off");
    printf("\n\n\n");
    printf("-------------------------------------------------------------\n");
    printf("| Name     |     100       |       10000   |     100000     |\n");
    printf("-------------------------------------------------------------\n");
    printf("|          |               |                |               |\n");
    printf("| BST      |  %7f ms  |%11f ms  |%10f ms  |\n", cpu_time_used1*1000, cpu_time_used2*1000, cpu_time_used3*1000);
    printf("| AVL TREE |  %7f ms  |%11f ms  |%10f ms  |\n", cpu_time_used4*1000, cpu_time_used5*1000, cpu_time_used6*1000);
    printf("| B-TREE   |  %7f ms  |%11f ms  |%10f ms  |\n", cpu_time_used7*1000, cpu_time_used8*1000, cpu_time_used9*1000);
    printf("|          |               |                |               |\n");
    printf("-------------------------------------------------------------\n");



 printf("\n\n\n\n\nType E and press enter to exit: ");
 quitl=getchar();
 int iquitl= quitl;
 if(iquitl == 69)
 {
  quit=1;
 }



 }
    return 0;

}
