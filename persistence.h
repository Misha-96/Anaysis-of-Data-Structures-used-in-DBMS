/* This module writes the data into a flat file and calculates the time
of execution of that method. */

#include <stdio.h>
#include <stdlib.h>

void writer();
void reader();

void writer(int data)
{
        FILE *fp;
        fp=fopen("data.dat","a");

        fprintf(fp,"%d\n",data);
        fclose(fp);
}

void reader()
{       int number;
        FILE *file;
        file=fopen("data.dat","r");
        while(fscanf(file,"%d",&number) == 1)
       {
         printf("%d ", number);
       }

}
