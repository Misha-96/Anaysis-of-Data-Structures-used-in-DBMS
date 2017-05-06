#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node {
    struct node *left;
    int data;
    struct node *right;
};
struct node *root = NULL;
void insertbst (struct node **node,int val)
{
    if ((*node)==NULL)
    {
        (*node)=(struct node *)malloc(sizeof(struct node));
        (*node)->data=val;
        (*node)->left=NULL;
        (*node)->right=NULL;
    }
    else if ((*node)->data> val)
    {
        insertbst(&(*node)->left,val);
    }

    else
    {
        insertbst(&(*node)->right, val);
    }

}//End of insert function

void searchbst(struct node *node,int val)
{
    if(node->data=val){
        printf("Element found in dataset");
        return ;
        }
    else if(node->data>val)
    {
        searchbst(node->left,val);
    }
    else if(node->data<val)
    {
        searchbst(node->right,val);
    }
    else{
    printf("Not Found");
    return ;}
}//end searching function

void intraversebst(struct node *node) {
    if (node) {
        intraversebst(node->left);
        intraversebst(node->right);
    }
    return;
}


int mainbst()
{
    clock_t start, end;
    double cpu_time_used;
    int data, ch;
    int m=0;
    int num,i ;
    int a[2000000];
    while (m!=1) {
        system("clear");
        system("setterm -bold on");
        printf("   Binary Search TREE \n");
        system("setterm -bold off");
        printf("\n1. Insertion\n");
        //printf("2. Deletion in Binary Search Tree\n");
      //  printf("2. Search Element\n");
        printf("2. Inorder traversal\n3. Exit\n");

        printf("\n\n\n\n  Choice: ");
        scanf("%d", &ch);
        switch (ch) {


        case 1:
               printf("\n\n  How many number of elements do you want to insert ?\n");
               printf("  ");
               scanf("%d", &num);

               start = clock();
               for (i=0;i<num;i++){
                a[i]= rand()%10000;  //%num is the range between 1 - num you want
                insertbst(&root,a[i]);
                writer(a[i]);
                }
               end = clock();
               cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
               system("setterm -bold on");
               printf("  Execution time is: %.2f ms\n",cpu_time_used*1000);
               printf("  Inserted successfully\n");
               system("setterm -bold off");
               sleep(2);
               system("clear");
               break;

        case 2:
            system("clear");

            printf("Inorder Traversal:\n");


            start = clock();
            intraversebst(root);
            reader();
            end = clock();

            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            printf("\n");
            system("setterm -bold on");
            printf("\n\n  Execution time is: %.2f ms\n",cpu_time_used*1000);
            printf("\n");
            system("setterm -bold off");
            sleep(2);
            break;
        case 3:

            system("clear");
            printf("Exiting to main menu..");
            printf("\n");
            sleep(1);
            m=1;
            break;

        default:
            printf("entered wrong option\n");
            break;
        }
    }
    return 0;

}
