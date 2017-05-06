#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

  #define MAX 4
  #define MIN 2

  struct btreeNode {
        int val[MAX + 1], count;
        struct btreeNode *link[MAX + 1];
  };

  struct btreeNode *btreeroot;

  /* creating new node */
  struct btreeNode * createNode(int val, struct btreeNode *child) {
        struct btreeNode *newNode;
        newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
        newNode->val[1] = val;
        newNode->count = 1;
        newNode->link[0] = btreeroot;
        newNode->link[1] = child;
        return newNode;
  }

  /* Places the value in appropriate position */
  void addValToNode(int val, int pos, struct btreeNode *node,
                        struct btreeNode *child) {
        int j = node->count;
        while (j > pos) {
                node->val[j + 1] = node->val[j];
                node->link[j + 1] = node->link[j];
                j--;
        }
        node->val[j + 1] = val;
        node->link[j + 1] = child;
        node->count++;
  }

  /* split the node */
  void splitNode (int val, int *pval, int pos, struct btreeNode *node,
     struct btreeNode *child, struct btreeNode **newNode) {
        int median, j;

        if (pos > MIN)
                median = MIN + 1;
        else
                median = MIN;

        *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
        j = median + 1;
        while (j <= MAX) {
                (*newNode)->val[j - median] = node->val[j];
                (*newNode)->link[j - median] = node->link[j];
                j++;
        }
        node->count = median;
        (*newNode)->count = MAX - median;

        if (pos <= MIN) {
                addValToNode(val, pos, node, child);
        } else {
                addValToNode(val, pos - median, *newNode, child);
        }
        *pval = node->val[node->count];
        (*newNode)->link[0] = node->link[node->count];
        node->count--;
  }

  /* sets the value val in the node */
  int setValueInNode(int val, int *pval,
     struct btreeNode *node, struct btreeNode **child) {

        int pos;
        if (!node) {
                *pval = val;
                *child = NULL;
                return 1;
        }

        if (val < node->val[1]) {
                pos = 0;
        } else {
                for (pos = node->count;
                        (val < node->val[pos] && pos > 1); pos--);
                if (val == node->val[pos]) {
                       // printf("Duplicates not allowed\n");
                        return 0;
                }
        }
        if (setValueInNode(val, pval, node->link[pos], child)) {
                if (node->count < MAX) {
                        addValToNode(*pval, pos, node, *child);
                } else {
                        splitNode(*pval, pval, pos, node, *child, child);
                        return 1;
                }
        }
        return 0;
  }

  /* insert val in B-Tree */
  void insertionbtree(int val) {
        int flag, i;
        struct btreeNode *child;

        flag = setValueInNode(val, &i, btreeroot, &child);
        if (flag)
                btreeroot = createNode(i, child);
  }

  /* copy successor for the value to be deleted */
  void copySuccessor(struct btreeNode *myNode, int pos) {
        struct btreeNode *dummy;
        dummy = myNode->link[pos];

        for (;dummy->link[0] != NULL;)
                dummy = dummy->link[0];
        myNode->val[pos] = dummy->val[1];

  }

  /* removes the value from the given node and rearrange values */
  void removeVal(struct btreeNode *myNode, int pos) {
        int i = pos + 1;
        while (i <= myNode->count) {
                myNode->val[i - 1] = myNode->val[i];
                myNode->link[i - 1] = myNode->link[i];
                i++;
        }
        myNode->count--;
  }

  /* shifts value from parent to right child */
  void doRightShift(struct btreeNode *myNode, int pos) {
        struct btreeNode *x = myNode->link[pos];
        int j = x->count;

        while (j > 0) {
                x->val[j + 1] = x->val[j];
                x->link[j + 1] = x->link[j];
        }
        x->val[1] = myNode->val[pos];
        x->link[1] = x->link[0];
        x->count++;

        x = myNode->link[pos - 1];
        myNode->val[pos] = x->val[x->count];
        myNode->link[pos] = x->link[x->count];
        x->count--;
        return;
  }

  /* shifts value from parent to left child */
  void doLeftShift(struct btreeNode *myNode, int pos) {
        int j = 1;
        struct btreeNode *x = myNode->link[pos - 1];

        x->count++;
        x->val[x->count] = myNode->val[pos];
        x->link[x->count] = myNode->link[pos]->link[0];

        x = myNode->link[pos];
        myNode->val[pos] = x->val[1];
        x->link[0] = x->link[1];
        x->count--;

        while (j <= x->count) {
                x->val[j] = x->val[j + 1];
                x->link[j] = x->link[j + 1];
                j++;
        }
        return;
  }

  /* merge nodes */
  void mergeNodes(struct btreeNode *myNode, int pos) {
        int j = 1;
        struct btreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];

        x2->count++;
        x2->val[x2->count] = myNode->val[pos];
        x2->link[x2->count] = myNode->link[0];

        while (j <= x1->count) {
                x2->count++;
                x2->val[x2->count] = x1->val[j];
                x2->link[x2->count] = x1->link[j];
                j++;
        }

        j = pos;
        while (j < myNode->count) {
                myNode->val[j] = myNode->val[j + 1];
                myNode->link[j] = myNode->link[j + 1];
                j++;
        }
        myNode->count--;
        free(x1);
  }

  /* adjusts the given node */
  void adjustNode(struct btreeNode *myNode, int pos) {
        if (!pos) {
                if (myNode->link[1]->count > MIN) {
                        doLeftShift(myNode, 1);
                } else {
                        mergeNodes(myNode, 1);
                }
        } else {
                if (myNode->count != pos) {
                        if(myNode->link[pos - 1]->count > MIN) {
                                doRightShift(myNode, pos);
                        } else {
                                if (myNode->link[pos + 1]->count > MIN) {
                                        doLeftShift(myNode, pos + 1);
                                } else {
                                        mergeNodes(myNode, pos);
                                }
                        }
                } else {
                        if (myNode->link[pos - 1]->count > MIN)
                                doRightShift(myNode, pos);
                        else
                                mergeNodes(myNode, pos);
                }
        }
  }

  /* delete val from the node */
  int delValFromNode(int val, struct btreeNode *myNode) {
        int pos, flag = 0;
        if (myNode) {
                if (val < myNode->val[1]) {
                        pos = 0;
                        flag = 0;
                } else {
                        for (pos = myNode->count;
                                (val < myNode->val[pos] && pos > 1); pos--);
                         if (val == myNode->val[pos]) {
                                flag = 1;
                        } else {
                                flag = 0;
                        }
                }
                if (flag) {
                        if (myNode->link[pos - 1]) {
                                copySuccessor(myNode, pos);
                                flag = delValFromNode(myNode->val[pos], myNode->link[pos]);
                                if (flag == 0) {
                                        printf("Given data is not present in B-Tree\n");
                                }
                        } else {
                                removeVal(myNode, pos);
                        }
                } else {
                        flag = delValFromNode(val, myNode->link[pos]);
                }
                if (myNode->link[pos]) {
                        if (myNode->link[pos]->count < MIN)
                                adjustNode(myNode, pos);
                }
        }
        return flag;
  }

  /* delete val from B-tree */
  void deletion(int val, struct btreeNode *myNode) {
        struct btreeNode *tmp;
        if (!delValFromNode(val, myNode)) {
                printf("Given value is not present in B-Tree\n");
                return;
        } else {
                if (myNode->count == 0) {
                        tmp = myNode;
                        myNode = myNode->link[0];
                        free(tmp);
                }
        }
        btreeroot = myNode;
        return;
  }

  /* search val in B-Tree */
  void searching(int val, int *pos, struct btreeNode *myNode) {
        if (!myNode) {
                return;
        }

        if (val < myNode->val[1]) {
                *pos = 0;
        } else {
                for (*pos = myNode->count;
                        (val < myNode->val[*pos] && *pos > 1); (*pos)--);
                if (val == myNode->val[*pos]) {
                        printf("Given data %d is present in B-Tree", val);
                        return;
                }
        }
        searching(val, pos, myNode->link[*pos]);
        return;
  }

  /* B-Tree Traversal */
  void traversalbtree(struct btreeNode *myNode) {
        int i;
        if (myNode) {
                for (i = 0; i < myNode->count; i++) {
                        traversalbtree(myNode->link[i]);
//                        printf("%d ", myNode->val[i + 1]);
                }
                traversalbtree(myNode->link[i]);
        }
  }

  void mainbtree() {

        clock_t start, end;
    double cpu_time_used;
    int data, ch;
    int m=0;
    int num,i ;
    int a[2000000];
    while (m!=1) {
        system("clear");
        system("setterm -bold on");
        printf("   B-TREE \n");
        system("setterm -bold off");
        printf("\n1. Insertion\n");
        //printf("2. Deletion in Binary Search Tree\n");
      //  printf("2. Search Element\n");
        printf("2. Traversal\n3. Exit\n");

        printf("\n\n\n\n  Choice: ");
        scanf("%d", &ch);
        switch (ch) {


        case 1:

               printf("\n\n  How many number of elements do you want to insert ?\n");
               printf("  ");
               scanf("%d", &num);

               start = clock();
               for (i=0;i<num;i++){
                a[i]= rand()%100000;  //%num is the range between 1 - num you want
                insertionbtree(a[i]);
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
    /*    case 2:
            printf("Enter your data:");
            scanf("%d", &data);
            deletionbst(&root, NULL, data);
            break;
      */
      /*  case 2:
            printf("\n\nEnter value for data:");
            scanf("%d", &data);
            start = clock();
             searchbst(root, data);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("  Execution time is: %.2f ms\n",cpu_time_used*1000);

            printf("\n");
            sleep(2);
            system("clear");

            break;
      */
        case 2:
            system("clear");

            printf("Traversal:\n");
            start = clock();
            traversalbtree(btreeroot);
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
            //printf("\n");
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
    return ;

  }
