//***********************************************
//*****<--- Start of program --->*****
//Sarvesh S. Parab
//12BT04CSE054
//DSPD-2 : Project :2
//***********************************************

// Assumptions taken under consideration:
// Using a B+ tree to implement database
// Branching factor is : 4
#define defaultOrder 4

//***********************************************

//headers and constants
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define false 0
#define true 1

//***********************************************
//typedefs'
typedef struct data
{
    char name[50];
    char addr[100];
    char desig[50];
    char phone[15];
    int empNum;
}empRec;
typedef struct treeNode
{
    void ** pointers;
    int * keys;
    struct treeNode * parent;
    int isLeaf;
    int numKeys;
    //struct treeNode * next;
} node;

//***********************************************
//function definitions
empRec *makeEmp(char [],char [],char [],char [],int);
node *makeNode();
node *makeLeaf();
node *primaryInsert(node *,int,empRec *);
empRec *searchNode(node *,int);
node *searchLeaf(node *,int);
node *makeNewTree(int,empRec *);
node *insertLeaf(node *,int,empRec *);
node *insertLeafSplit(node *,node *,int,empRec *);

//***********************************************
//main function
main()
{

}

//***********************************************
//function definitions

//Makes an employee record and returns it back
empRec *makeEmp(char name[],char addr[],char desig[],char phone[],int empNum)
{
    empRec *newRec;
    newRec=(empRec *)malloc(sizeof(empRec));
    if(newRec==NULL)
    {
        printf("\n\n Error code : 1 \n\n"); // +++++++++++++++++++++++++++++
    }
    else
    {
        strcpy(newRec->name,name);
        strcpy(newRec->addr,addr);
        strcpy(newRec->desig,desig);
        strcpy(newRec->phone,phone);
       newRec->empNum=empNum;
    }
    return newRec;
}
//Makes a new node
node *makeNode()
{
    node *newNode;
    newNode=malloc(sizeof(node));
    if(newNode==NULL)
    {
        printf("\n\n Error code : 2 \n\n"); // +++++++++++++++++++++++++++++
    }
    else
    {
        newNode->keys=malloc((defaultOrder-1) * sizeof(int));
        if(newNode->keys==NULL)
        {
            printf("\n\n Error code : 3 \n\n"); // +++++++++++++++++++++++++++++
        }
        newNode->pointers=malloc((defaultOrder) * sizeof(void *));
        if(newNode->pointers==NULL)
        {
            printf("\n\n Error code : 4 \n\n"); // +++++++++++++++++++++++++++++
        }
        newNode->isLeaf=0;
        newNode->numKeys=0;
        newNode->parent=NULL;
        //newNode->next=NULL;
    }
    return newNode;
}
//Makes a new leaf node
node *makeLeaf()
{
    node *newLeaf;
    newLeaf=makeNode();
    newLeaf->isLeaf=1;
    newLeaf->pointers[defaultOrder-1]=NULL;
    return newLeaf;
}
//Main insert function
node *primaryInsert(node *root,int key,empRec *newEmp)
 {
     node *altRoot,*tempLeaf;
     if(root==NULL)
     {
         altRoot=makeNewTree(key,newEmp);
     }
     else
     {
         if(searchNode(root,key)!=NULL)
         {
             altRoot=root; // duplicates eliminated
         }
         else
         {
             tempLeaf=searchLeaf(root,key);
             if(tempLeaf->numKeys < (defaultOrder-1))
             {
                 tempLeaf=insertLeaf(tempLeaf,key,newEmp);
             }
             else
             {
                 //split leaf and insert
             }
         }
     }
     return altRoot;
 }
//Search for key value (on parent)..(gives empRecord for which key given)
empRec *searchNode(node *root,int key)
{
    node *result;
    empRec *answer;
    int i=0,done=0;
    if(root==NULL)
    {
        printf("\n\n Error code : 5 \n\n"); // +++++++++++++++++++++++++++++
        answer=NULL;
    }
    else
    {
        result=searchLeaf(root,key);
        if(result==NULL)
        {
            printf("\n\n Error code : 6 \n\n"); // +++++++++++++++++++++++++++++
            answer=NULL;
        }
        else
        {
            while(i<result->numKeys && !done)
            {
                if(result->keys[i]==key)
                {
                    done=1;
                }
                else
                {
                    i++;
                }
            }
            if(i==result->numKeys)
            {
                result=NULL;
                answer=NULL;
            }
            else
            {
                answer=(empRec *)result->pointers[i];
            }
        }
    }
    return answer;
}
//Search for leaf with given key (gives potential leaf for key to exist)
node *searchLeaf(node *root,int key)
{
    node *result;
    int i,done;
    result=root;
    if(result==NULL)
    {
        printf("\n\n Error code : 5 \n\n"); // +++++++++++++++++++++++++++++
    }
    else
    {
        while(result->isLeaf!=1)
        {
            i=done=0;
            while(i<result->numKeys && !done)
            {
                if(key>=result->keys[i])
                {
                    i++;
                }
                else
                {
                    done=1;
                }
            }
            result=(node *)result->pointers[i];
        }
    }
    return result;
}
//Makes new tree from scratch
node *makeNewTree(int key,empRec *newRec)
{
    node *temp;
    temp=makeLeaf();
    temp->keys[0]=key;
    temp->numKeys++;
    temp->parent=NULL;
    temp->pointers[0]=(empRec *)newRec;
    temp->pointers[defaultOrder-1]=NULL; //leaf node has equal keys and pointers
    return temp;
}
//Insert into leaf if not completely full
node *insertLeaf(node *leaf,int key,empRec *newEmp)
{
    int place=0,i=0;
    while(place<(leaf->numKeys) && (leaf->keys[place])<key)
    {
        place++;
    }
    for(i=leaf->numKeys;i>place;i--)
    {
        leaf->keys[i]=leaf->keys[i-1];
        leaf->pointers[i]=leaf->pointers[i-1];
    }
    leaf->keys[place]=key;
    leaf->pointers[place]=(empRec *)newEmp;
    leaf->numKeys++;
    return leaf;
}
//Insert into leaf when leaf is full and splitting is reqd
node *insertLeafSplit(node *root,node *leaf,int key,empRec *newEmp)
{
    node *newLeaf = makeLeaf();
    int *tempKeys;
    void **tempPointers;
    int place=0,newStart,i,j;
    tempKeys=(int *)malloc(defaultOrder * sizeof(int));
    if(tempKeys==NULL)
    {
        printf("\n\n Error code : 7 \n\n"); // +++++++++++++++++++++++++++++
    }
    tempPointers=malloc(defaultOrder * sizeof(void *));
    if(tempPointers==NULL)
    {
        printf("\n\n Error code : 8 \n\n"); // +++++++++++++++++++++++++++++
    }
    while(place<(defaultOrder-1) && leaf->keys[place]<key)
    {
        place++;
    }
    for(i=0,j=0;i<(leaf->numKeys);i++,j++)
    {
        if(j==place)
        {
            j++;
        }
        tempKeys[j]=leaf->keys[i];
        tempPointers[j]=(empRec *)leaf->pointers[i];
    }
    tempKeys[place]=key;
    tempPointers[place]=(empRec *)newEmp;
    if((defaultOrder-1)%2==0)
    {
        newStart=(defaultOrder-1)/2;
    }
    else
    {
        newStart=(defaultOrder-1)/2 + 1;
    }
    leaf->numKeys=0;
    for(i=0;i<newStart;i++)
    {
        leaf->keys[i]=tempKeys[i];
        leaf->pointers[i]=(empRec *)tempPointers[i];
        leaf->numKeys++;
    }
    for(i=newStart,j=0;i<defaultOrder;i++,j++)
    {
        newLeaf->keys[j]=tempKeys[i];
        newLeaf->pointers[j]=(empRec *)tempPointers[i];
        newLeaf->numKeys++;
    }
    free(tempKeys);
    free(tempPointers);
    newLeaf->pointers[defaultOrder-1]=(empRec *)(leaf->pointers[defaultOrder-1]);
    leaf->pointers[defaultOrder-1]=(empRec *)newLeaf;
    for(i=leaf->numKeys;i<(defaultOrder-1);i++)
    {
        leaf->pointers[i]=NULL;
    }
    for(i=newLeaf->numKeys;i<(defaultOrder-1);i++)
    {
        newLeaf->pointers[i]=NULL;
    }
    newLeaf->parent=leaf->parent;

}


















//***********************************************
//Error codes:
/*
1: Employee Record creation failure
2: New node creation Failure
3: Key-memory dynamic alloaction failure
4: Pointer-memory dynamic allocation failure
5: Empty tree
6: Leaf node empty
7: Temp keys array memory alloc failure
8: Temp pointers array memory alloc failure
9:
10:


*/







