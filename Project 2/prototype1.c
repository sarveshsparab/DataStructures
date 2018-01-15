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
char path[150];

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
} node;

//***********************************************
//function definitions
empRec *makeEmp(char [],char [],char [],char [],int);
node *makeNode();
node *makeLeaf();
node *primaryInsert(node *,int,empRec *);
empRec *searchRecord(node *,int);
node *searchLeaf(node *,int);
node *makeNewTree(int,empRec *);
node *insertLeaf(node *,int,empRec *);
node *insertLeafSplit(node *,node *,int,empRec *);
node *insertNewKeyToParent(node *,int,node *,node *);
node *createRoot(int,node *,node *);
node *insertNode(node *,int,node *,node *);
node *insertNodeSplit(node *,int,node *,node *);
node *primaryDelete(node *,int);
node *searchParentForKey(node *,int,node *);
node *deleteData(node *,int,node *,void *);
node *removeFromNode(node *,int,node *);
node *alterRoot(node *);
int getLeftSiblingIndex(node *);
node *borrowFromSibling(node *,node *,node *,int,int,int);
node *mergeWithSibling(node *,node *,node *,int,int,int);
void pathCreate(char []);
void pathConvert(char []);
node *fileRead(char [],node *,int *,char []);
void fileWrite(node *);
void dispMainMenu(int,node *);
void mainMenuFunc(int,node *);
void disp_ani(char [],int);
int height(node *);
int getNumRecords(node *);
void printTree(node *);
void displayRecord(empRec *);
empRec *getDataFromUser();
void rangeSearch(node *,int,int);
//***********************************************
//main function
main()
{
    int check;
    node *root=NULL;
    char choice[1],fileName[25];
    GetModuleFileName(NULL, path, sizeof(path));
    pathConvert(path);
    system("cls");
    printf("\n\t\t\tDATABASE INITIALIZING\n");
    printf("\n------------------------------------------------------------------------------\n");
    printf("\nImport data from a file? (y/n) : \n");
    scanf("%s",choice);
    if(strcmp(choice,"y")==0)
    {
        printf("\nUse Default File? (y/n) : \n");
        scanf("%s",choice);
        if(strcmp(choice,"y")==0)
        {
            printf("\nFILE : treeData.txt is being loaded !! \n");
            root=fileRead("treeData.txt",root,&check,path);
        }
        else
        {
            printf("\nEnter name of file : \n");
            scanf("%s",fileName);
            root=fileRead(fileName,root,&check,path);
        }
        if(check==0)
        {
            printf("\nFile does not exist!!\n");
        }
        else
        {
            printf("\nDatabase successfully loaded!!!\n");
        }
    }
    printf("\nPress any key to continue\n");
    getch();
    printf("\n------------------------------------------------------------------------------\n");
    dispMainMenu(0,root);
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
        getch();
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
        getch();
    }
    else
    {
        newNode->keys=malloc((defaultOrder-1) * sizeof(int));
        if(newNode->keys==NULL)
        {
            printf("\n\n Error code : 3 \n\n"); // +++++++++++++++++++++++++++++
            getch();
        }
        newNode->pointers=malloc((defaultOrder) * sizeof(void *));
        if(newNode->pointers==NULL)
        {
            printf("\n\n Error code : 4 \n\n"); // +++++++++++++++++++++++++++++
            getch();
        }
        newNode->isLeaf=0;
        newNode->numKeys=0;
        newNode->parent=NULL;
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
     empRec *temp;
     if(root==NULL)
     {
         altRoot=makeNewTree(key,newEmp);
     }
     else
     {
         if((temp=searchRecord(root,key))!=NULL)
         {
             altRoot=root; // duplicates eliminated update
             temp=newEmp;
             printf("\n\n Updated");
             getch();
         }
         else
         {
             tempLeaf=searchLeaf(root,key);
             if(tempLeaf->numKeys < (defaultOrder-1))
             {
                 tempLeaf=insertLeaf(tempLeaf,key,newEmp);
                 altRoot=root;
             }
             else
             {
                 altRoot=insertLeafSplit(root,tempLeaf,key,newEmp);
             }
         }
     }
     return altRoot;
 }
//Search for key value (on parent)..(gives empRecord for which key given)
empRec *searchRecord(node *root,int key)
{
    node *result;
    empRec *answer;
    int i=0,done=0;
    result=searchLeaf(root,key);
    if(result==NULL)
    {
        printf("\n\n Error code : 6 \n\n"); // +++++++++++++++++++++++++++++
        answer=NULL;
        getch();
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
        getch();
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
    node *newLeaf,*answer;
    newLeaf = makeLeaf();
    int *tempKeys;
    void **tempPointers;
    int place=0,newStart,i,j;
    tempKeys=(int *)malloc(defaultOrder * sizeof(int));
    if(tempKeys==NULL)
    {
        printf("\n\n Error code : 7 \n\n"); // +++++++++++++++++++++++++++++
        getch();
    }
    tempPointers=malloc(defaultOrder * sizeof(void *));
    if(tempPointers==NULL)
    {
        printf("\n\n Error code : 8 \n\n"); // +++++++++++++++++++++++++++++
        getch();
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
    answer=insertNewKeyToParent(root,newLeaf->keys[0],leaf,newLeaf);
    return answer;
}
//inserts new key into parent after leaf split
node *insertNewKeyToParent(node *root,int newKey,node *leftChild,node *rightChild)
{
    node *answer,*parent;
    parent=leftChild->parent;
    if(parent==NULL)
    {
        answer=createRoot(newKey,leftChild,rightChild);
    }
    else
    {
        if(parent->numKeys<(defaultOrder-1))
        {
            answer=insertNode(root,newKey,leftChild,rightChild);
        }
        else
        {
            answer=insertNodeSplit(root,newKey,leftChild,rightChild);
        }
    }
    return answer;
}
//Creates the root node for the very first time
node *createRoot(int key,node *leftChild,node *rightChild)
{
    node *newRoot;
    newRoot=makeNode();
    if(newRoot==NULL)
    {
        printf("\n\n Error code : 9 \n\n"); // +++++++++++++++++++++++++++++
        getch();
    }
    else
    {
        newRoot->keys[0]=key;
        newRoot->pointers[0]=(node *)leftChild;
        newRoot->pointers[1]=(node *)rightChild;
        newRoot->numKeys++;
        newRoot->parent=NULL;
        leftChild->parent=newRoot;
        rightChild->parent=newRoot;
    }
    return newRoot;
}
//Inserts into an existing node which is not full
node *insertNode(node *root,int key,node *leftChild,node *rightChild)
{
    node *updatedParent;
    int place=0,i;
    updatedParent=leftChild->parent;
    while(place<updatedParent->numKeys && (updatedParent->pointers[place])!=leftChild)
    {
        place++;
    }
    for(i=updatedParent->numKeys;i>place;i--)
    {
        updatedParent->keys[i]=updatedParent->keys[i-1];
        updatedParent->pointers[i]=updatedParent->pointers[i-1];
    }
    updatedParent->keys[place]=key;
    updatedParent->pointers[place+1]=rightChild;
    updatedParent->numKeys++;
    return root;
}
//Inserts into parent node after splitting it
node *insertNodeSplit(node *root,int key,node *leftChild,node *rightChild)
{
    node *answer,*newNode,*updatedParent;
    int place=0,newStart,i,j,newGrandParentKey;
    int *tempKeys;
    void **tempPointers;
    updatedParent=leftChild->parent;
    tempKeys=malloc(defaultOrder * sizeof(int));
    if(tempKeys==NULL)
    {
        printf("\n\n Error code : 7 \n\n"); // +++++++++++++++++++++++++++++
        getch();
    }
    tempPointers=malloc((defaultOrder+1) *sizeof(void *));
    if(tempPointers==NULL)
    {
        printf("\n\n Error code : 8 \n\n"); // +++++++++++++++++++++++++++++
        getch();
    }
    newNode=makeNode();
    while(place<(updatedParent->numKeys) && updatedParent->pointers[place]!=leftChild)
    {
        place++;
    }
    for(i=0;i<place;i++)
    {
        tempKeys[i]=updatedParent->keys[i];
        tempPointers[i]=updatedParent->pointers[i];
    }
    tempKeys[place]=key;
    tempPointers[place]=leftChild;
    tempPointers[place+1]=rightChild;
    for(i=place+1;i<defaultOrder;i++)
    {
        if(i<defaultOrder)
        {
            tempKeys[i]=updatedParent->keys[i-1];
        }
        tempPointers[i+1]=updatedParent->pointers[i];
    }
    if((defaultOrder)%2==0)
    {
        newStart=(defaultOrder)/2;
    }
    else
    {
        newStart=(defaultOrder)/2 + 1;
    }
    updatedParent->numKeys=0;
    for(i=0;i<=(newStart-1);i++)
    {
        if(i<(newStart-1))
        {
            updatedParent->keys[i]=tempKeys[i];
            updatedParent->numKeys++;
        }
        newGrandParentKey=tempKeys[i];
        updatedParent->pointers[i]=tempPointers[i];
    }
    for(i=newStart,j=0;i<=defaultOrder;i++,j++)
    {
        if(i<defaultOrder)
        {
            newNode->keys[j]=tempKeys[i];
            newNode->numKeys++;
        }
        newNode->pointers[j]=tempPointers[i];
    }
    free(tempKeys);
    free(tempPointers);
    newNode->parent=updatedParent->parent;
    for(i=0;i<=(newNode->numKeys);i++)
    {
        answer=(newNode->pointers[i]);  //here answer is just used as a temporary
        answer->parent=newNode;
    }
    answer=insertNewKeyToParent(root,newGrandParentKey,updatedParent,newNode);
    return answer;
}
//Main delete function
node *primaryDelete(node *root,int key)
{
    empRec *tempRec;
    node *tempNodeToRecord,*tempParentWithKey;
    if(root==NULL)
    {
        printf("\n\n Error code : 5 \n\n"); // +++++++++++++++++++++++++++++
        getch();
    }
    else
    {
        tempRec=searchRecord(root,key);
        if(tempRec==NULL)
        {
            printf("\n\n Error code : 10 \n\n"); // +++++++++++++++++++++++++++++
            printf("\nRecord Not found to delete!!\n");
            getch();
        }
        else
        {
            tempNodeToRecord=searchLeaf(root,key);
            root=deleteData(root,key,tempNodeToRecord,tempRec);
            free(tempRec);
        }
    }
    return root;
}
//Search node other than leaf having the same key
node *searchParentForKey(node *root,int key,node *leafWithKey)
{
    node *answer,*parent;
    int done=0,i;
    parent=leafWithKey->parent;
    if(parent==NULL)
    {
        answer=NULL;
    }
    else
    {
        while(parent!=root && !done)
        {
            for(i=0;i<(parent->numKeys) && !done;i++)
            {
                if(parent->keys[i]==key)
                {
                    done=1;
                    answer=parent;
                }
            }
            parent=parent->parent;
        }
        if(!done)
        {
            answer=NULL;
        }
    }
    return answer;
}
//Deletes record
node *deleteData(node *root,int key,node *nodePtr,void *rec)
{
    node *altRoot,*sibling,*parent;
    int minKeys,siblingIndex,keyInParentIndex,keyInParent,borrowWorth;
    nodePtr=removeFromNode(nodePtr,key,rec);
    if(nodePtr==root)
    {
        altRoot=alterRoot(nodePtr);
    }
    else
    {
        if(nodePtr->isLeaf)
        {
            if((defaultOrder-1)%2==0)
            {
                minKeys=(defaultOrder-1)/2;
            }
            else
            {
                minKeys=((defaultOrder-1)/2)+1;
            }
        }
        else
        {
            if(defaultOrder%2==0)
            {
                minKeys=defaultOrder/2;
            }
            else
            {
                minKeys=(defaultOrder/2)+1;
            }
            minKeys--;
        }
        if((nodePtr->numKeys)>=minKeys)
        {
            altRoot=root;
        }
        else
        {
            siblingIndex=getLeftSiblingIndex(nodePtr);
            if(siblingIndex==-1)
            {
                keyInParentIndex=0;
                sibling=(nodePtr->parent)->pointers[1];
            }
            else
            {
                keyInParentIndex=siblingIndex;
                sibling=(nodePtr->parent)->pointers[siblingIndex];
            }
            keyInParent=(nodePtr->parent)->keys[keyInParentIndex];
            if(nodePtr->isLeaf)
            {
                borrowWorth=defaultOrder;
            }
            else
            {
                borrowWorth=defaultOrder-1;
            }
            if((nodePtr->numKeys)+(sibling->numKeys)<borrowWorth)
            {
                altRoot=mergeWithSibling(root,nodePtr,sibling,siblingIndex,keyInParent,keyInParentIndex);
            }
            else
            {
                altRoot=borrowFromSibling(root,nodePtr,sibling,siblingIndex,keyInParent,keyInParentIndex);
            }
        }
    }
    return altRoot;
}
//Remove the key emtry from the given node
node *removeFromNode(node *nodePtr,int key,node *rec)
{
    int i=0,temp;
    while(nodePtr->keys[i]!=key)
    {
        i++;
    }
    for(++i;i<nodePtr->numKeys;i++)
    {
        nodePtr->keys[i-1]=nodePtr->keys[i];
    }
    if(nodePtr->isLeaf)
        temp=nodePtr->numKeys;
    else
        temp=nodePtr->numKeys;
    i=0;
    while(nodePtr->pointers[i]!=rec)
    {
        i++;
    }
    for(++i;i<temp;i++)
    {
        nodePtr->pointers[i-1]=nodePtr->pointers[i];
    }
    nodePtr->numKeys--;
    if(nodePtr->isLeaf)
    {
        for(i=nodePtr->numKeys;i<(defaultOrder-1);i++)
        {
            nodePtr->pointers[i]=NULL;
        }
    }
    else
    {
        for(i=nodePtr->numKeys+1;i<defaultOrder;i++)
        {
           nodePtr->pointers[i]=NULL;
        }
    }
    return nodePtr;
}
//changes root if deletion happens at root level and tree about to be empty
node *alterRoot(node *root)
{
    node *altRoot;
    if((root->numKeys)>0)
    {
        altRoot=root;
    }
    else
    {
        if(root->isLeaf)
        {
            altRoot=NULL;
        }
        else
        {
            altRoot=root->pointers[0];
            altRoot->parent=NULL;
        }
        free(root->keys);
        free(root->pointers);
        free(root);
    }
    return altRoot;
}
//Gives index in parent node for the left sibling of given node
int getLeftSiblingIndex(node *nodePtr)
{
    int index=0,i,done=0;
    node *parent=nodePtr->parent;
    for(i=0;i<=parent->numKeys && !done;i++)
    {
        if(parent->pointers[i]==nodePtr)
        {
            index=i-1;
            done=1;
        }
    }
    return index;
}
//Borrow function from sibling
node *borrowFromSibling(node *root,node *nodePtr,node *sibling,int siblingIndex,int keyInParent,int keyInParentIndex)
{
    int i;
    node *temp;
    if(siblingIndex!=-1)
    {
        if(!nodePtr->isLeaf)
        {
            nodePtr->pointers[(nodePtr->numKeys)+1]=nodePtr->pointers[(nodePtr->numKeys)];
        }
        for(i=nodePtr->numKeys;i>0;i--)
        {
            nodePtr->keys[i]=nodePtr->keys[i-1];
            nodePtr->pointers[i]=nodePtr->pointers[i-1];
        }
        if(nodePtr->isLeaf)
        {
            nodePtr->pointers[0]=sibling->pointers[(sibling->numKeys)-1];
            sibling->pointers[(sibling->numKeys)-1]=NULL;
            nodePtr->keys[0]=sibling->keys[(sibling->numKeys)-1];
            (nodePtr->parent)->keys[keyInParentIndex]=nodePtr->keys[0];
        }
        else
        {
            nodePtr->pointers[0]=sibling->pointers[(sibling->numKeys)];
            temp=(node *)nodePtr->pointers[0];
            temp->parent=nodePtr;
            sibling->pointers[sibling->numKeys]=NULL;
            nodePtr->keys[0]=keyInParent;
            (nodePtr->parent)->keys[keyInParentIndex]=sibling->keys[(sibling->numKeys)-1];
        }
    }
    else
    {
        if(nodePtr->isLeaf)
        {
            nodePtr->keys[nodePtr->numKeys]=sibling->keys[0];
            nodePtr->pointers[nodePtr->numKeys]=sibling->pointers[0];
            (nodePtr->parent)->keys[keyInParentIndex]=sibling->keys[1];
        }
        else
        {
            nodePtr->keys[nodePtr->numKeys]=keyInParent;
            nodePtr->pointers[(nodePtr->numKeys)+1]=sibling->pointers[0];
            temp=(node *)nodePtr->pointers[(nodePtr->numKeys)+1];
            temp->parent=nodePtr;
            (nodePtr->parent)->keys[keyInParentIndex]=sibling->keys[0];
        }
        for(i=0;i<(sibling->numKeys);i++)
        {
            sibling->keys[i]=sibling->keys[i+1];
            sibling->pointers[i]=sibling->pointers[i+1];
        }
        if(!nodePtr->isLeaf)
        {
            sibling->pointers[i]=sibling->pointers[i+1];
        }
    }
    nodePtr->numKeys++;
    sibling->numKeys--;
    return root;
}
//Merge function with sibling
node *mergeWithSibling(node *root,node *nodePtr,node *sibling,int siblingIndex,int keyInParent,int keyInParentIndex)
{
    int i,j,newStart,newEnd,flag=0,newKeyInParent,done=0;
    node * tmp;
    if(siblingIndex==-1)
    {
        tmp=nodePtr;
        nodePtr=sibling;
        sibling=tmp;
    }
    if(!nodePtr->isLeaf)
    {
        sibling->keys[sibling->numKeys]=keyInParent;
        sibling->numKeys++;
        newStart=0;
        newEnd=nodePtr->numKeys;
        if((nodePtr->numKeys + sibling->numKeys)>=defaultOrder)
        {
            flag=1;
            if(defaultOrder%2 == 0)
            {
                newEnd=defaultOrder/2;
            }
            else
            {
                newEnd=defaultOrder/2 + 1;
            }
            newEnd=newEnd-2;
        }
        for(j=0,i=(sibling->numKeys)+1;j<newEnd;j++,i++)
        {
            sibling->keys[i]=nodePtr->keys[j];
            sibling->pointers[i]=nodePtr->pointers[j];
            sibling->numKeys++;
            nodePtr->numKeys--;
            newStart++;
        }
        sibling->pointers[i]=nodePtr->pointers[j];
        if(flag)
        {
            newKeyInParent=nodePtr->keys[newStart];
            for(i=0,j=newStart+1;i<nodePtr->numKeys;i++,j++)
            {
                nodePtr->keys[i]=nodePtr->keys[j];
                nodePtr->pointers[i]=nodePtr->pointers[j];
            }
            nodePtr->pointers[i]=nodePtr->pointers[j];
            nodePtr->numKeys--;
        }
        for(i=0;i<(sibling->numKeys + 1);i++)
        {
            tmp=(node *)sibling->pointers[i];
            tmp->parent=sibling;
        }
    }
    else
    {
        for(i=sibling->numKeys,j=0;j<nodePtr->numKeys;j++,i++)
        {
            sibling->keys[i]=nodePtr->keys[j];
            sibling->pointers[i]=nodePtr->pointers[j];
            sibling->numKeys++;
        }
        sibling->pointers[defaultOrder-1]=nodePtr->pointers[defaultOrder-1];
    }
    if(!flag)
    {
        root=deleteData(root,keyInParent,nodePtr->parent,nodePtr);
        free(nodePtr->keys);
        free(nodePtr->pointers);
        free(nodePtr);
    }
    else
    {
        done=0;
        for(i=0;i<(nodePtr->parent)->numKeys && !done;i++)
        {
            if((nodePtr->parent)->pointers[i+1]==nodePtr)
            {
                (nodePtr->parent)->keys[i]=newKeyInParent;
                done=1;
            }
        }
    }
    return root;
}
//Path creation function
void pathCreate(char path[])
{
    char retPath[200];
    int i=0,j=0;
    if(strlen(path)!=0)
    {
        while(path[i]!='\0')
        {
            if(path[i]=='\\')
            {
                retPath[j]='\\';
                j++;
                retPath[j]='\\';
            }
            else
            {
                retPath[j]=path[i];
            }
            i++;
            j++;
        }
        retPath[j]='\0';
        strcpy(path,retPath);
    }
}
//Path convert function
void pathConvert(char path[])
{
    int i,len=strlen(path);
    for(i=len;path[i]!='\\';i--)
    {
        path[i]='\0';
    }
    pathCreate(path);
}
//File Read function
node *fileRead(char fileName[],node *root,int *status,char path[])
{
    empRec *newEmp;
    *status=1;
    char tempName[50],tempAddr[100],tempPhone[15],tempDesig[50];
    int tempEmpNum;
    strcat(path,fileName);
    FILE *fp;
    fp=fopen( path , "r");
    if(fp==NULL)
    {
        *status=0;
    }
    else
    {
        while(!feof(fp))
        {
            fscanf( fp , "%s" , tempName );
            fscanf( fp , "%s" , tempAddr );
            fscanf( fp , "%s" , tempDesig );
            fscanf( fp , "%s" , tempPhone );
            fscanf( fp , "%d" , &tempEmpNum );
            newEmp=makeEmp(tempName,tempAddr,tempDesig,tempPhone,tempEmpNum);
            root=primaryInsert(root,newEmp->empNum,newEmp);
        }
    }
    fclose(fp);
    return root;
}
//File Write function
void fileWrite(node *root)
{
    FILE *fp;
    int i;
    node *temp=root;
    empRec *t;
    i=strlen(path);
    if(path[i-1]!='t')
    {
        strcat(path,"treeData.txt");
    }
    fp=fopen( path , "w" );
    if(temp!=NULL)
    {
        while(!temp->isLeaf)
        {
            temp=temp->pointers[0];
        }
        while(temp!=NULL)
        {
            for(i=0;i<(temp->numKeys);i++)
            {
                t=(empRec *)temp->pointers[i];
                fprintf( fp , "%s\n" , t->name );
                fprintf( fp , "%s\n" , t->addr );
                fprintf( fp , "%s\n" , t->desig );
                fprintf( fp , "%s\n" , t->phone );
                if(i<((temp->numKeys)-1))
                    fprintf( fp , "%d\n" , t->empNum );
                else
                    fprintf( fp , "%d" , t->empNum );
            }
            temp=temp->pointers[defaultOrder-1];
        }
    }
    fclose(fp);
}
//Displays main menu
void dispMainMenu(int a,node *root)
{
    system("cls");
    int choice;
    printf("\n\n");
    //disp_ani("***Employee Record Database Management***",a);
    printf("\n\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("     **                                                        **\n");
    printf("     **\t    1. View Existing Employee Database                 **\n");
    printf("     **\t    2. Insert a new Record                             **\n");
    printf("     **\t    3. Delete a Record                                 **\n");
    printf("     **\t    4. Number of Active Records                        **\n");
    printf("     **\t    5. Search for Record                               **\n");
    printf("     **\t    6. Range Search                                    **\n");
    printf("     **\t    7. Height                                          **\n");
    printf("     **\t    8. Exit                                            **\n");
    printf("     **                                                        **\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    mainMenuFunc(choice,root);
}
//heading animation
void disp_ani(char str[],int speed)
{
    int i,spd;
    switch(speed)
    {
        case 0:
            spd=125;
            break;
        default:
            spd=0;
            break;
    }
    printf("\t\t");
    for(i=0;str[i]!='\0';i++)
    {
        printf("%c",str[i]);
        Sleep(spd);
    }
}
//Main menu choice Functions
void mainMenuFunc(int choice,node *root)
{
    empRec *newEmp;
    int k,j,i;
    switch(choice)
    {
    case 1:
        system("cls");
        printf("\n\t\t\tDISPLAY RECORDS\n");
        printf("\n------------------------------------------------------------------------------\n\n");
        printTree(root);
        printf("\n------------------------------------------------------------------------------\n\n");
        printf("\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(choice,root);
        break;
    case 2:
        system("cls");
        printf("\n\t\t\tDATA INSERTION MODE\n");
        printf("\n------------------------------------------------------------------------------\n\n");
        newEmp=getDataFromUser();
        if(newEmp!=NULL)
        {
            root=primaryInsert(root,newEmp->empNum,newEmp);
        }
        k=root->numKeys;
        for(i=0;i<k;i++)
        {
            printf("%d",root->keys[i]);
        }
        printf("\n------------------------------------------------------------------------------\n\n");
        printf("\n\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(choice,root);
        break;
    case 3:
        system("cls");
        printf("\n\t\t\tDATA DELETION MODE\n");
        printf("\n------------------------------------------------------------------------------");
        printf("\nEnter Employee ID: ");
        scanf("%d",&k);
        root=primaryDelete(root,k);
        if(root->isLeaf)
        {
            printf("\nits a root");
        }
        printf("\n------------------------------------------------------------------------------\n\n");
        printf("\n\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(choice,root);
        break;
    case 4:
        system("cls");
        printf("\n\t\t\tNUMBER OF RECORDS\n");
        printf("\n------------------------------------------------------------------------------\n");
        k=getNumRecords(root);
        if(k==-1)
        {
            printf("/n Tree non-existant!!!");
        }
        else
        {
            printf("\nThe Number of active records is : %d\n",k);
        }
        printf("\n------------------------------------------------------------------------------\n\n");
        printf("\n\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(choice,root);
        break;
    case 5:
        system("cls");
        printf("\n\t\t\tSEARCH A RECORD\n");
        printf("\n------------------------------------------------------------------------------\n");
        printf("\nEnter a Employee ID : ");
        scanf("%d",&k);
        newEmp=searchRecord(root,k);
        if(newEmp==NULL)
        {
            printf("\n Record does not exist in database");
        }
        else
        {
            printf("\n Record Found!!\n");
            displayRecord(newEmp);
        }
        printf("\n------------------------------------------------------------------------------\n\n");
        printf("\n\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(choice,root);
        break;
    case 6:
        system("cls");
        printf("\n\t\t\tRANGE SEARCH\n");
        printf("\n------------------------------------------------------------------------------");
        printf("\nEnter LOWER limit on range search : ");
        scanf("%d",&j);
        printf("\nEnter UPPER limit on range search : ");
        scanf("%d",&k);
        rangeSearch(root,j,k);
        printf("\n------------------------------------------------------------------------------\n\n");
        printf("\n\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(choice,root);
        break;
    case 7:
        system("cls");
        printf("\n\t\t\tHEIGHT OF THE TREE\n");
        printf("\n------------------------------------------------------------------------------");
        k=height(root);
        if(k==-1)
        {
            printf("\n Tree non-existant!!!");
        }
        else
        {
            printf("\nThe Height is : %d\n",k);
        }
        printf("\n------------------------------------------------------------------------------\n\n");
        printf("\n\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(choice,root);
        break;
    case 8:
        system("cls");
        printf("\n\t\t\t\tEXITING\n");
        printf("\n------------------------------------------------------------------------------\n");
        printf("\n\t");
        fileWrite(root);
        disp_ani("***!! Thank You !!***",0);
        printf("\n\n------------------------------------------------------------------------------\n");
        break;
    default:
        printf("\nInvalid Choice!!");
        printf("\nGoing back to main menu..... Press any key...");
        getch();
        dispMainMenu(7,root);
        break;
    }
}
//Height of tree
int height(node *root)
{
    int ht=1;
    node *temp=root;
    if(temp==NULL)
    {
        ht=-1;
    }
    else
    {
        while(!temp->isLeaf)
        {
            temp=temp->pointers[0];
            ht++;
        }
    }
    return ht;
}
//Gets number of active records
int getNumRecords(node *root)
{
    int num=0;
    node *temp=root;
    if(temp==NULL)
    {
        num=-1;
    }
    else
    {
        while(!temp->isLeaf)
        {
            temp=temp->pointers[0];
        }
        while(temp!=NULL)
        {
            num=num+temp->numKeys;
            temp=temp->pointers[defaultOrder-1];
        }
    }
    return num;
}
//Print tree function
void printTree(node *root)
{
    int i;
    node *temp=root;
    if(temp==NULL)
    {
        printf("\n\nDatabase Empty");
        getch();
    }
    else
    {
        while(!temp->isLeaf)
        {
            temp=temp->pointers[0];
        }
        while(temp!=NULL)
        {
            for(i=0;i<(temp->numKeys);i++)
            {
                displayRecord((empRec *)temp->pointers[i]);
            }
            temp=temp->pointers[defaultOrder-1];
        }
    }
}
//displays indivisual records
void displayRecord(empRec *rec)
{
    empRec *temp=rec;
    if(temp==NULL)
    {
        printf("\n\n Error code : 10 \n\n"); // +++++++++++++++++++++++++++++
        getch();
    }
    else
    {
        printf("------------------------------------------------------------------------------\n");
        printf("Name: %s \t\t ID: %d\n",temp->name,temp->empNum);
        printf("Designation: %s \t\t Phone: %s\n",temp->desig,temp->phone);
        printf("Address: %s\n",temp->addr);
        printf("------------------------------------------------------------------------------\n");
    }
}
//Takes input from user
empRec *getDataFromUser()
{
    empRec *newEmp;
    char tempName[50],tempAddr[100],tempPhone[15],tempDesig[50];
    int tempEmpNum;
    printf("\nEmployee Name : ");
    scanf("%s",tempName);
    printf("\nEmployee ID : ");
    scanf("%d",&tempEmpNum);
    printf("\nEmployee Designation : ");
    scanf("%s",tempDesig);
    printf("\nEmployee Address : ");
    scanf("%s",tempAddr);
    printf("\nEmployee Phone : ");
    scanf("%s",tempPhone);
    newEmp=makeEmp(tempName,tempAddr,tempDesig,tempPhone,tempEmpNum);
    return newEmp;
}
//Range search function
void rangeSearch(node *root,int lower,int upper)
{
    node *temp=root;
    empRec *rec;
    int done=0,i;
    if(temp==NULL)
    {
        printf("\nRange Search Failed\n");
    }
    else
    {
        while(!temp->isLeaf)
        {
            temp=temp->pointers[0];
        }
        while(temp!=NULL && !done)
        {
            for(i=0;i<(temp->numKeys) && temp->keys[i]<=upper;i++)
            {
                if(temp->keys[i]>=lower)
                    displayRecord((empRec *)temp->pointers[i]);
            }
            if(i<temp->numKeys && temp->keys[i]>upper)
            {
                done=1;
            }
            if(i==temp->numKeys)
            {
                temp=temp->pointers[defaultOrder-1];
            }
        }
    }
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
9: Root creation for the first time failed
10:Record does not exist
11:
12:
13:
*/
//***********************************************
//*****<--- End of program --->*****
//Sarvesh S. Parab
//12BT04CSE054
//DSPD-2 : Project :1
//***********************************************





