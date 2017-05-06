/*#include <locale.h>
#include <stdio.h>
#include "avltree.h"
#include "bst.h"
#include "btree.h"
#include <stdlib.h>
#include <unistd.h>
#include "persistence.h"
*/
float calc_bst_time(int nos);
float calc_avl_time(int nos);
float calc_btree_time(int nos);
void writeplot();

int a[2000000];

float calc_bst_time(int nos)
{       int i;
        clock_t start,end;
        double cpu_time_used;
        start=clock();
        for (i=0;i<nos;i++){
         a[i]= rand()%10000;  //%num is the range between 1 - num you want
         insertbst(&root,a[i]);
         }
         end = clock();
         cpu_time_used = ((float)(end - start)) / CLOCKS_PER_SEC;
         return cpu_time_used*1000;
}

float calc_avl_time(int nos)
{       int i;
        clock_t start,end;
        double cpu_time_used;
        struct nodeavl *root = NULL;

        start = clock();
         for (i=0;i<nos;i++)
         {
          a[i]= rand()%10000;  //%num is the range between 1 - num you want
          root = insertavl(root,a[i]);
          }
         end = clock();
         cpu_time_used = ((float)(end - start)) / CLOCKS_PER_SEC;
         return cpu_time_used*1000;
}

float calc_btree_time(int nos)
{       int i;
        clock_t start,end;
        double cpu_time_used;
        start = clock();
        for (i=0;i<nos;i++){
         a[i]= rand()%100000;  //%num is the range between 1 - num you want
         insertionbtree(a[i]);
         writer(a[i]);
         }
        end = clock();
        cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
        return cpu_time_used*1000;
}

void writeplot()
{
        int arr[]={100,500,1000,5000,10000};
        int i;
        FILE *fp;

        fp=fopen("plotter.dat","w");
        fprintf(fp,"#Number of values, Execution Time for BST, Execution Time for AVL, Execution Time for B-Tree");
        for(i=0;i<5;i++)
        {
                fprintf(fp,"%d %.3f %.3f %.3f\n",arr[i],calc_bst_time(arr[i]),calc_avl_time(arr[i]),calc_btree_time(arr[i]));
        }
        fclose(fp);
}
