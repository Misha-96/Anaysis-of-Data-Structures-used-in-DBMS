//#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
struct nodeavl
{
    int key;
    struct nodeavl *left;
    struct nodeavl *right;
    int height;
};

void reader();
void writer(int data);


int max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

int height(struct nodeavl *N){
    if(N == NULL)
        return 0;

    return N->height;
}

struct nodeavl* newnodeavl(int key){
    struct nodeavl* nodeavl = (struct nodeavl*)
			malloc(sizeof(struct nodeavl));

    nodeavl->key = key;
    nodeavl->left = NULL;
    nodeavl->right = NULL;
    nodeavl->height = 1;
    return(nodeavl);

}

struct nodeavl *rightRotate(struct nodeavl *y){
    struct nodeavl *x = y->left;
    struct nodeavl *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    return x;
}
struct nodeavl *leftRotate(struct nodeavl *x){
    struct nodeavl *y = x->right;
    struct nodeavl *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    return y;
}

int getBalance(struct nodeavl *N){
    if(N==NULL){
            return 0;
      }
    return height(N->left) - height(N-> right);
}

struct nodeavl* insertavl(struct nodeavl* nodeavl , int key){
    if(nodeavl == NULL){
        return (newnodeavl(key));
  }

    if(key< nodeavl->key){
        nodeavl->left = insertavl(nodeavl->left , key);
  }
    else{
        nodeavl->right = insertavl(nodeavl->right , key);
    }

    nodeavl->height = max(height(nodeavl->left),height(nodeavl->right))+1;

    int balance = getBalance(nodeavl);

    if(balance > 1 && getBalance(nodeavl->left)>=0){
        return rightRotate(nodeavl);
    }
    if(balance > 1 && getBalance(nodeavl->left)<0){
        nodeavl->left = leftRotate(nodeavl->left);
        return rightRotate(nodeavl);
    }
    if(balance < -1 && getBalance(nodeavl->right)<=0){
        return leftRotate(nodeavl);
    }
    if(balance < -1 && getBalance(nodeavl->right)>0){
        nodeavl->right = rightRotate(nodeavl->right);
        return leftRotate(nodeavl);
    }

    return nodeavl;
}

void preorder(struct nodeavl *root){
    if(root != NULL){
//        printf("%d ",root->key);
        preorder(root->left);
        preorder(root->right);
    }

}
struct nodeavl * minValuenodeavl(struct nodeavl* nodeavl)
{
    struct nodeavl* current = nodeavl;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct nodeavl* deletenodeavl(struct nodeavl* root, int key){
    if(root == NULL){
        return root;
    }
    if(key < root->key){
        root->left = deletenodeavl(root->left, key);

    }
    else if(key > root->key){
        root->right = deletenodeavl(root->right, key);
    }
    else{
        if((root->left == NULL) || (root->right==NULL)){
            struct nodeavl *temp = root->left ? root->left :root->right;
            if(temp == NULL){
                temp = root;
                root = NULL;
            }
            else{
                *root = *temp;

            }

            free(temp);
        }

        else{
            struct nodeavl* temp = minValuenodeavl(root->right);
            root->key = temp->key;
            root->right = deletenodeavl(root->right, temp->key);
        }
    }

    if(root == NULL){
        return root;
    }

    root->height = max(height(root->left), height(root->right))+1;

    int balance = getBalance(root);
    if(balance > 1 && getBalance(root->left)>=0){
        return rightRotate(root);
    }
    if(balance > 1 && getBalance(root->left)<0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right)<=0){
        return leftRotate(root);
    }
    if(balance < -1 && getBalance(root->right)>0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
  }



struct nodeavl* searchavl(struct nodeavl* root, int key){
    if(root->key == key){
        printf("element found");
         //return root;
    }
    if(root == NULL){
        printf("Not found");
        //return root;
    }
    if(key< root->key){
        root->left = searchavl(root->left, key);
    }
    else if( key> root->key){
        root->right = searchavl(root->right, key);
    }

}

int mainavl() {
    FILE *fp;
    clock_t start, end;
    double cpu_time_used;
    int num,i;
    int option;
    int a[2000000];
    int m=1;
    struct nodeavl *root = NULL;
     /*root = insertavl(root, 10);
     root = insertavl(root, 20);
     root = insertavl(root, 30);
     root = insertavl(root, 40);
     root = insertavl(root, 50);
     root = insertavl(root, 25);
     */

    while(m!=0){
     system("clear");
     system("setterm -bold on");
     printf("  AVL TREE \n");
     system("setterm -bold off");
     printf("\n1. Insert Elements \n");
     printf("2. Pre order traversal\n");
    // printf("3. Search \n");
     printf("3. Exit \n");
     printf("\n\n\n\n");
     printf("  Choice: ");

    // printf("Pre order traversal is \n");
     scanf("%d",&option);

     switch(option){

     case 1:
     fp=fopen("data.dat","w");
     fclose(fp);
      //system("clear");
      printf("  How many number of elements do you want to insert in avl ?\n");
      printf("  ");
      scanf("%d",&num);
   // printf("does this print");

      start = clock();
       for (i=0;i<num;i++)
       {
        a[i]= rand()%10000;  //%num is the range between 1 - num you want
        root = insertavl(root,a[i]);
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
     // for (i=0;i<num;i++)
      // {
      // printf("%d ",a[i]);  //%num is the range between 1 - num you want
      // }

      //printf("%d ",root);
      break;

     case 2:

      system("clear");
      printf("Pre order traversal is: \n");
      reader();
      start = clock();
      preorder(root);
      end=clock();
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      printf("\n");

      system("setterm -bold on");
      printf("\n\nExecution time is: %.2f ms\n",cpu_time_used*1000);
      system("setterm -bold off");
      printf("\n\n");
      sleep(4);


      break;

     case 3:

      system("clear");
      //printf("\n");
      printf("Exiting to main menu..");
      free(root);
      printf("\n");
      sleep(1);
      system("clear");
      m=0;
      //root = deletenodeavl(root, 40);
      break;
  }
 }
return 0;
}
