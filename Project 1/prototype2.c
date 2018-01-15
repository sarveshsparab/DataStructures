//***********************************************
//*****<--- Start of program --->*****
//Sarvesh S. Parab
//12BT04CSE054
//DSPD-2 : Project :1
//***********************************************

//headers added
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
//************************************************************************************************************
//typedefs'
typedef enum{FAILURE,SUCCESS} statusCode;
typedef struct employee
{
    char name[50];
    char proj[50];
    int hour;
    char addr[100];
    char phone[15];
    struct employee *next;
}empRec;
empRec *compA, *compB ,*compNet,*compTemp;
//************************************************************************************************************
//function declarations
void initialize(empRec *);
void disp_main_menu(int);
void disp_ani(char [],int);
void func_main_menu(int );
int sub_menu();
empRec *makeRecord(char [],char [],int ,char [],char []);
empRec *insertRecord(empRec *,statusCode *);
empRec *compareRecord(empRec *,empRec *);
empRec *deleteRecord(empRec *, statusCode *);
void traverseRecord(empRec *);
int isEmpty(empRec *);
empRec *sortEntry(empRec *);
empRec *divide(empRec *);
empRec *mergeSort(empRec *,empRec *);
statusCode fileRead(empRec **,int);
void fileWrite(empRec *,char []);
void dispRecord(empRec *);
empRec *searchRecord(empRec *,char [],char [],statusCode *);
void maxHours(empRec *);
int sub_menu_multiop();
empRec *unionOp(empRec *,empRec *,int *);
empRec *intersectOp(empRec *,empRec *,int *);
empRec *diffOp(empRec *,empRec *,int *);
empRec *symdiffOp(empRec *,empRec *,int *);
empRec *removeDuplicateInsert(empRec *);
empRec *uniqueList(empRec *);


//************************************************************************************************************
//main function
main()
{
    initialize(compA);
    initialize(compB);
    statusCode check1,check2;
    char choice[1];
    printf("\nImport data from a file? (y/n)\n");
    scanf("%s",choice);
    if(strcmp(choice,"y")==0)
    {
        check1=fileRead(&compA,1);
        if(!check1)
        {
            printf("\n\tFailed to load Caompany A database...!!");
        }
        else
        {
            printf("\n\tSuccessfully loaded Caompany A database...!!");
        }
        check2=fileRead(&compB,2);
        if(!check2)
        {
            printf("\n\tFailed to load Caompany B database...!!");
        }
        else
        {
            printf("\n\tSuccessfully loaded Caompany B database...!!");
        }
    }
    printf("\n\tPress any key to continue!!");
    getch();
    disp_main_menu(0);
}
//************************************************************************************************************
//Displays Menu
void disp_main_menu(int a)
{
    system("cls");
    int choice;
    printf("\n\n");
    disp_ani("***Employee Record Database Management***",a);
    printf("\n\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("     **                                                        **\n");
    printf("     **\t    1. View Existing Employee Database                 **\n");
    printf("     **\t    2. Insert a new Record                             **\n");
    printf("     **\t    3. Delete a Record                                 **\n");
    printf("     **\t    4. Number of Active Records                        **\n");
    printf("     **\t    5. Database Full or Empty Status                   **\n");
    printf("     **\t    6. Unique Listing (Duplicate Removal)              **\n");
    printf("     **\t    7. Max Hours Worked                                **\n");
    printf("     **\t    8. Multi-Database Operations                       **\n");
    printf("     **\t    9. Exit                                            **\n");
    printf("     **                                                        **\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    func_main_menu(choice);
}
//Linked list initialize
void initialize(empRec *ptr)
{
    ptr=NULL;
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

//main func choice operations
void func_main_menu(int choice)
{
    statusCode check;
    int num,temp;
    switch(choice)
    {
        case 1:
            switch(sub_menu())
            {
                case 1:
                    traverseRecord(compA);
                    break;
                case 2:
                    traverseRecord(compB);
                    break;
                default:
                    printf("\nInvalid Choice!!");
                    printf("\nGoing back..... Press any key...");
                    getch();
                    func_main_menu(choice);
                    break;
            }
            printf("\nGoing back..... Press any key...");
            getch();
            disp_main_menu(choice);
            break;
        case 2:
            switch(sub_menu())
            {
                case 1:
                    compA=insertRecord(compA,&check);
                    break;
                case 2:
                    compB=insertRecord(compB,&check);
                    break;
                default:
                    printf("\nInvalid Choice!!");
                    printf("\nGoing back..... Press any key...");
                    getch();
                    func_main_menu(choice);
                    break;
            }
            if(check==1)
            {
                printf("\nRecord added Successfully!!!\n");
            }
            else if(check==0)
            {
                printf("ERROR!!...Failed to add Record!!!\n");
            }
            printf("\nGoing back..... Press any key...");
            getch();
            disp_main_menu(choice);
            break;
        case 3:
            switch(sub_menu())
            {
                case 1:
                    compA=deleteRecord(compA,&check);
                    break;
                case 2:
                    compB=deleteRecord(compB,&check);
                    break;
                default:
                    printf("\nInvalid Choice!!");
                    printf("\nGoing back..... Press any key...");
                    getch();
                    func_main_menu(choice);
                    break;
            }
            if(check==1)
            {
                printf("\nRecord deleted Successfully!!!\n");
            }
            else if(check==0)
            {
                printf("\nERROR!!...Failed to delete Record!!!\n");
            }
            printf("\nGoing back..... Press any key...");
            getch();
            disp_main_menu(choice);
            break;
        case 4:
            switch(sub_menu())
            {
                case 1:
                    num=isEmpty(compA);
                    break;
                case 2:
                    num=isEmpty(compB);
                    break;
                default:
                    printf("\nInvalid Choice!!");
                    printf("\nGoing back..... Press any key...");
                    getch();
                    func_main_menu(choice);
                    break;
            }
            if(num)
            {
                printf("\n\nThe number of active records are: %d .\n",num);
            }
            else
            {
                printf("\n\nThere are no active records");
            }
            printf("\n\nPress any key to continue...!!!");
            getch();
            disp_main_menu(choice);
            break;
        case 5:
            switch(sub_menu())
            {
                case 1:
                    num=isEmpty(compA);
                    break;
                case 2:
                    num=isEmpty(compB);
                    break;
                default:
                    printf("\nInvalid Choice!!");
                    printf("\nGoing back..... Press any key...");
                    getch();
                    func_main_menu(choice);
                    break;
            }
            if(num)
            {
                printf("\n\nThe database is not Empty");
            }
            else
            {
                printf("\n\nThe database is EMPTY");
            }
            printf("\n\nPress any key to continue...!!!");
            getch();
            disp_main_menu(choice);
            break;
        case 6:
            compTemp=uniqueList(compTemp);
            printf("\n\n Unique Listings: \n\n");
            traverseRecord(compTemp);
            printf("\n\nPress any key to continue...!!!");
            getch();
            disp_main_menu(choice);
            break;
        case 7:
            switch(sub_menu())
            {
                case 1:
                    maxHours(compA);
                    break;
                case 2:
                    maxHours(compB);
                    break;
                default:
                    printf("\nInvalid Choice!!");
                    printf("\nGoing back..... Press any key...");
                    getch();
                    func_main_menu(choice);
                    break;
            }
            printf("\nGoing back..... Press any key...");
            getch();
            disp_main_menu(choice);
            break;
        case 8:
            temp=0;
            switch(sub_menu_multiop())
            {
                case 1:
                    //union operations
                    compNet=unionOp(compA,compB,&temp);
                    break;
                case 2:
                    //intersection operations
                    compNet=intersectOp(compA,compB,&temp);
                    break;
                case 3:
                    //diff operations
                    compNet=diffOp(compA,compB,&temp);
                    break;
                case 4:
                    //symm-diff operations
                    compNet=symdiffOp(compA,compB,&temp);
                    break;
                default:
                    printf("\nInvalid Choice!!");
                    printf("\nGoing back..... Press any key...");
                    getch();
                    func_main_menu(choice);
                    break;
            }
            if(temp==0)
            {
                printf("\n\nOperation Unsuccessful!!!!!\n");
            }
            else
            {
                printf("\n\nOperation Successful!!!!!\n");
                traverseRecord(compNet);
            }
            printf("\nGoing back..... Press any key...");
            getch();
            disp_main_menu(choice);
            break;
        case 9:
            system("cls");
            printf("\n\n\n\n\n\t");
            fileWrite(compA,"companyA.txt");
            fileWrite(compB,"companyB.txt");
            disp_ani("***!! Thank You !!***",0);
            getch();
            break;
        default:
            printf("\nInvalid Choice!!");
            printf("\nGoing back to main menu..... Press any key...");
            getch();
            disp_main_menu(choice);
            break;
    }
}

// Sub menu function
int sub_menu()
{
    int choice;
    system("cls");
    printf("\n\n");
    printf("     *********************************************\n");
    printf("     *********************************************\n");
    printf("     **                                         **\n");
    printf("     **\t\t    COMPANY SELECTION           **\n");
    printf("     **                                         **\n");
    printf("     **\t    1. Company A                        **\n");
    printf("     **\t    2. Company B                        **\n");
    printf("     **                                         **\n");
    printf("     *********************************************\n");
    printf("     *********************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    return choice;
}

// Sub menu for multi-database operations function
int sub_menu_multiop()
{
    int choice;
    system("cls");
    printf("\n\n");
    printf("     ***************************************************\n");
    printf("     ***************************************************\n");
    printf("     **                                               **\n");
    printf("     **\t\t MULTI-DATABASE OPERATION             **\n");
    printf("     **                                               **\n");
    printf("     **\t    1. Union of both companies                **\n");
    printf("     **\t    2. Intersetion of both companies          **\n");
    printf("     **\t    3. Difference of both companies           **\n");
    printf("     **\t    4. Symmetric-Diff. of both companies      **\n");
    printf("     **                                               **\n");
    printf("     ***************************************************\n");
    printf("     ***************************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    return choice;
}

//compares two records and returns corresponding record
empRec *compareRecord(empRec *rec1,empRec *rec2)
{
    empRec *ans;
    if(strcmp(rec1->name,rec2->name)<0)
    {
        ans=rec1;
    }
    else if(strcmp(rec1->name,rec2->name)>0)
    {
        ans=rec2;
    }
    else
    {
        if(strcmp(rec1->proj,rec2->proj)<0)
        {
            ans=rec1;
        }
        else if(strcmp(rec1->proj,rec2->proj)>0)
        {
            ans=rec2;
        }
        else
        {
            ans=NULL;
        }
    }
    return ans;
}

//Insert a new node or record
empRec *insertRecord(empRec *head,statusCode *sc)
{
    *sc=SUCCESS;
    empRec *ptr,*temp,*xtra_head,*prev,*cmp;
    int tempHour,done;
    char tempPhone[15],tempName[50],tempProj[50],tempAddr[100];
    printf("\nEnter new employee details:");
    printf("\n     ** Employee Name : ");
    scanf("%s",tempName);
    printf("\n     ** Project Name  : ");
    scanf("%s",tempProj);
    printf("\n     ** No. of Hours  : ");
    scanf("%d",&tempHour);
    printf("\n     ** Address       : ");
    scanf("%s",tempAddr);
    printf("\n     ** Phone Number  : ");
    scanf("%s",tempPhone);
    ptr=makeRecord(tempName,tempProj,tempHour,tempAddr,tempPhone);
    if(ptr==NULL)
    {
        *sc=FAILURE;
    }
    else
    {
        if(head==NULL) // first record
        {
            head=ptr;
        }
        else
        {
            ptr->next=head;
            head=ptr;
            head=sortEntry(head);
            head=removeDuplicateInsert(head);
        }
    }
    return head;
}

//sorts the recent entered element in list
empRec *sortEntry(empRec *p)
{
    empRec *q;
    empRec *head=p;
    if(p!=NULL && p->next!=NULL)
    {
        q=divide(p);
        p=sortEntry(p);
        q=sortEntry(q);
        head=mergeSort(p,q);
    }
    return head;
}

//divide function for sorting
empRec *divide(empRec *p)
{
    empRec *r,*q;
    q=p;
    r=p->next->next;
    while(r!=NULL)
    {
        r=r->next;
        q=q->next;
        if(r!=NULL)
        {
            r=r->next;
        }
    }
    r=q;
    q=q->next;
    r->next=NULL;
    return q;
}

//merge sort funtion
empRec *mergeSort(empRec *p,empRec *q)
{
    empRec *head,*tail;
    if(strcmp(p->name,q->name)<0 || (strcmp(p->name,q->name)==0 && strcmp(p->proj,q->proj)<0))
    {
        head=p;
        p=p->next;
    }
    else
    {
        head=q;
        q=q->next;
    }
    tail=head;
    while(p!=NULL && q!=NULL)
    {
        if(strcmp(p->name,q->name)<0 || (strcmp(p->name,q->name)==0 && strcmp(p->proj,q->proj)<0))
        {
            tail->next=p;
            tail=p;
            p=p->next;
        }
        else
        {
            tail->next=q;
            tail=q;
            q=q->next;
        }
    }
    if(p!=NULL)
    {
        tail->next=p;
    }
    else
    {
        tail->next=q;
    }
    return head;
}

//Delete a node or record
empRec *deleteRecord(empRec *head, statusCode *sc)
{
    *sc=SUCCESS;
    statusCode searchResult;
    empRec *tempPtr,*resultPtr,*xtra;
    tempPtr=head;
    char tempName[50],tempProj[50],choice[1];
    printf("\n\nEnter details of the record to be deleted!!\n");
    printf("\n     ** Employee Name : ");
    scanf("%s",tempName);
    printf("\n     ** Project Name  : ");
    scanf("%s",tempProj);
    resultPtr=searchRecord(tempPtr,tempName,tempProj,&searchResult);
    if(searchResult)
    {
        if(resultPtr==NULL)
        {
            *sc=FAILURE;
        }
        else
        {
            dispRecord(resultPtr);
            printf("\n\nThis is the record you wish to delete: (y/n)\n");
            scanf("%s",choice);
            if(strcmp(choice,"y")==0)
            {
                if(tempPtr==resultPtr) //delete at start
                {
                    tempPtr=tempPtr->next;
                }
                else
                {
                    xtra=tempPtr;
                    while(xtra->next!=resultPtr)
                    {
                        xtra=xtra->next;
                    }
                    if(resultPtr->next==NULL) //delete at end
                    {
                        xtra->next=NULL;
                    }
                    else //delete in between
                    {
                       xtra->next=resultPtr->next;
                    }
                }
                free(resultPtr);
            }
            else
            {
                *sc=FAILURE;
            }
        }
    }
    else
    {
        *sc=FAILURE;
    }
    return tempPtr;
}

//makes a new record
empRec *makeRecord(char name[],char proj[],int hour,char addr[],char phone[])
{
    empRec *ptr;
    ptr=(empRec *)malloc(sizeof(empRec));
    if(ptr!=NULL)
    {
        strcpy(ptr->name,name);
        strcpy(ptr->proj,proj);
        ptr->hour=hour;
        strcpy(ptr->addr,addr);
        strcpy(ptr->phone,phone);
        ptr->next=NULL;
    }
    return ptr;
}

//traverse a linked list and display on the screen
void traverseRecord(empRec *head)
{
    if(isEmpty(head))
    {
        system("cls");
        printf("\n");
        while(head!=NULL)
        {
            printf("------------------------------------------------------------------------------\n");
            printf("Name: %s \t\t Project-Name: %s\n",head->name,head->proj);
            printf("Phone: %s \t\t No. of Hours: %d\n",head->phone,head->hour);
            printf("Address: %s\n",head->addr);
            head=head->next;
        }
    }
    else
    {
        printf("\n\nDatabase Empty... NO records to display\n\n");
    }
}

//Checks if full or empty linked list
int isEmpty(empRec *head)
{
    int num_rec=0;
    if(head==NULL)
    {
        num_rec=0;
    }
    else
    {
        while(head!=NULL)
        {
            num_rec++;
            head=head->next;
        }
    }
    return num_rec;
}

//Reads data from file
statusCode fileRead(empRec **head,int fileChoice)
{
    FILE *fp;
    empRec *ptr,*last;
    statusCode sc=SUCCESS;
    int tempHour,line_count,i;
    char tempPhone[15],tempName[50],tempProj[50],tempAddr[100];
    if(fileChoice==1)
    {
        fp = fopen( "companyA.txt" , "r");
    }
    else if(fileChoice==2)
    {
        fp = fopen( "companyB.txt" , "r");
    }
    else if(fileChoice==3)
    {
        fp = fopen( "data.txt" , "r");
    }
    if(fp==NULL)
    {
        sc=FAILURE;
    }
    else
    {
        fscanf( fp , "%d" , &line_count );
        for(i=0;i<line_count;i++)
        {
            fscanf( fp , "%s" , tempName );
            fscanf( fp , "%s" , tempProj );
            fscanf( fp , "%d" , &tempHour );
            fscanf( fp , "%s" , tempAddr );
            fscanf( fp , "%s" , tempPhone );
            ptr=makeRecord(tempName,tempProj,tempHour,tempAddr,tempPhone);
            if(ptr==NULL)
            {
                sc=FAILURE;
            }
            else
            {
                if(*head==NULL)
                {
                    *head=ptr;
                    last=ptr;
                }
                else
                {
                    last->next=ptr;
                    last=ptr;
                }
            }
        }
    }
    fclose(fp);
    return sc;
}

//Writes back data to txt files
void fileWrite(empRec *head,char fileChoice[])
{
    FILE *fp;
    int line_count;
    line_count=isEmpty(head);
    fp = fopen( "fileChoice" , "w");
    fprintf( fp , "%d\n" , line_count );
    while(head!=NULL)
    {
        fprintf( fp , "%s\n" , head->name );
        fprintf( fp , "%s\n" , head->proj );
        fprintf( fp , "%d\n" , head->hour );
        fprintf( fp , "%s\n" , head->addr );
        fprintf( fp , "%s\n" , head->phone );
        head=head->next;
    }
    fclose(fp);
}

//Display the requested record
void dispRecord(empRec *ptr)
{
    if(ptr==NULL)
    {
        printf("\n\nThe record does not exist\n");
    }
    else
    {
        printf("------------------------------------------------------------------------------\n");
        printf("Name: %s \t\t Project-Name: %s\n",ptr->name,ptr->proj);
        printf("Phone: %s \t\t No. of Hours: %d\n",ptr->phone,ptr->hour);
        printf("Address: %s\n",ptr->addr);
        printf("------------------------------------------------------------------------------\n");
    }
    //printf("\n\nPress any key to continue...!!");
    //getch();
}

//seacrh existance of a node
empRec *searchRecord(empRec *head,char name[],char proj[],statusCode *outcome)
{
    int found;
    *outcome=FAILURE;
    empRec *result;
    if(head==NULL)
    {
        *outcome=FAILURE;
        result=NULL;
    }
    else
    {
        /*while(head!=NULL && found!=0)
        {
            if(strcmp(name,head->name)<0)
            {
                sc=FAILURE;
                found=FAILURE;
                temp=NULL;
            }
            else
            {
                if(strcmp(name,head->name)==0)
                {
                    if(strcmp(proj,head->proj)<0)
                    {
                        sc=FAILURE;
                        found=FAILURE;
                        temp=NULL;
                    }
                    else
                    {
                        if(strcmp(proj,head->proj)==0)
                        {
                            found=SUCCESS;
                            temp=head;
                        }
                    }
                }
            }
            head=head->next;
        }*/
        found=0;
        while(head!=NULL && found==0)
        {
            if(strcmp(name,head->name)==0)
            {
                if(strcmp(proj,head->proj)==0)
                {
                    found=1;
                    result=head;
                    *outcome=SUCCESS;
                }
                else
                {
                    result=NULL;
                }
            }
            else
            {
                result=NULL;
            }
            head=head->next;
        }
    }
    return result;
}

//get maximum hours
void maxHours(empRec *head)
{
    char tempProj[50];
    empRec *temp;
    int found=0,maximum;
    printf("\n\nEnter a project name: \n");
    scanf("%s",tempProj);
    if(head!=NULL)
    {
        maximum=head->hour;
        temp=head;
        printf("\nThe list of employees under project: %s\n",tempProj);
        printf("------------------------------------------------------------------------------\n");
        printf("Employee Name \t\t Hours \n");
        printf("------------------------------------------------------------------------------\n");
        while(head!=NULL && found ==0)
        {
            if(strcmp(tempProj,head->proj)==0)
            {
                if((head->hour)>maximum)
                {
                    maximum=head->hour;
                    temp=head;
                }
                printf("%s \t\t\t %d\n",head->name,head->hour);
            }
            head=head->next;
        }
        printf("\nThe employee: %s has spent the maximum of %d hours on project: %s\n",temp->name,maximum,temp->proj);
    }
    else
    {
        found=1;
    }
}

//union operation
empRec *unionOp(empRec *head1,empRec *head2,int *choice)
{
    empRec *result,*temp,*last;
    result=NULL;
    if(head1==NULL && head2!=NULL)
    {
        while(head2!=NULL)
        {
            temp=makeRecord(head2->name,head2->proj,head2->hour,head2->addr,head2->phone);
            if(result==NULL)
            {
                result=temp;
                last=temp;
            }
            else
            {
                last->next=temp;
                last=temp;
            }
            head2=head2->next;
        }
        *choice=1;
    }
    else if(head2==NULL && head1!=NULL)
    {
        while(head1!=NULL)
        {
            temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
            if(result==NULL)
            {
                result=temp;
                last=temp;
            }
            else
            {
                last->next=temp;
                last=temp;
            }
            head1=head1->next;
        }
        *choice=1;
    }
    else if(head1!=NULL && head2!=NULL)
    {
        while(head1!=NULL && head2!=NULL)
        {
            if(strcmp(head1->name,head2->name)==0 && strcmp(head1->proj,head2->proj)==0)
            {
                temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
                if(result==NULL) //first record added
                {
                    result=temp;
                    last=temp;
                }
                else //record insert at end
                {
                    last->next=temp;
                    last=temp;
                }
                head1=head1->next;
                head2=head2->next;
            }
            else if(strcmp(head1->name,head2->name)==0 && strcmp(head1->proj,head2->proj)<0)
            {
                temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
                if(result==NULL) //first record added
                {
                    result=temp;
                    last=temp;
                }
                else //record insert at end
                {
                    last->next=temp;
                    last=temp;
                }
                head1=head1->next;
            }
            else if(strcmp(head1->name,head2->name)==0 && strcmp(head1->proj,head2->proj)>0)
            {
                temp=makeRecord(head2->name,head2->proj,head2->hour,head2->addr,head2->phone);
                if(result==NULL) //first record added
                {
                    result=temp;
                    last=temp;
                }
                else //record insert at end
                {
                    last->next=temp;
                    last=temp;
                }
                head2=head2->next;
            }
            else if(strcmp(head1->name,head2->name)<0)
            {
                temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
                if(result==NULL) //first record added
                {
                    result=temp;
                    last=temp;
                }
                else //record insert at end
                {
                    last->next=temp;
                    last=temp;
                }
                head1=head1->next;
            }
            else if(strcmp(head1->name,head2->name)>0)
            {
                temp=makeRecord(head2->name,head2->proj,head2->hour,head2->addr,head2->phone);
                if(result==NULL) //first record added
                {
                    result=temp;
                    last=temp;
                }
                else //record insert at end
                {
                    last->next=temp;
                    last=temp;
                }
                head2=head2->next;
            }
        }
        while(head1!=NULL)
        {
            temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
            last->next=temp;
            last=temp;
            head1=head1->next;
        }
        while(head2!=NULL)
        {
            temp=makeRecord(head2->name,head2->proj,head2->hour,head2->addr,head2->phone);
            last->next=temp;
            last=temp;
            head2=head2->next;
        }
        *choice=1;
    }
    else
    {
        result=NULL;
        *choice=0;
    }
    return result;
}

//intersection operation
empRec *intersectOp(empRec *head1,empRec *head2,int *choice)
{
    empRec *result,*temp,*last,*head2_temp;
    *choice=0;
    result=NULL;
    if(head1==NULL || head2==NULL)
    {
        result=NULL;
        *choice=1;
    }
    else
    {
        while(head1!=NULL)
        {
            head2_temp=head2;
            while(head2_temp!=NULL)
            {
                if(strcmp(head1->name,head2_temp->name)==0 && strcmp(head1->proj,head2_temp->proj)==0)
                {
                    temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
                    if(result==NULL)
                    {
                        result=temp;
                        last=temp;
                    }
                    else
                    {
                        last->next=temp;
                        last=temp;
                    }
                }
                head2_temp=head2_temp->next;
            }
            head1=head1->next;
        }
        *choice=1;
    }
    return result;
}

//difference operation
empRec *diffOp(empRec *head1,empRec *head2,int *choice)
{
    empRec *result,*last,*temp,*head2_temp;
    result=NULL;
    int flag1,flag2=0;
    *choice=0;
    if(head1==NULL)
    {
        result=NULL;
        *choice=1;
    }
    else if(head2==NULL)
    {
        while(head1!=NULL)
        {
            temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
            if(result==NULL)
            {
                result=temp;
                last=temp;
            }
            else
            {
                last->next=temp;
                last=temp;
            }
            head1=head1->next;
        }
        *choice=1;
    }
    else
    {
        while(head1!=NULL)
        {
            head2_temp=head2;
            flag1=0;
            while(head2_temp!=NULL && flag1==0)
            {
                if(strcmp(head1->name,head2_temp->name)==0 && strcmp(head1->proj,head2_temp->proj)==0)
                {
                    flag1=1;
                }
                else
                {
                    flag1=0;
                }
                head2_temp=head2_temp->next;
            }
            if(flag1==0)
            {
                temp=makeRecord(head1->name,head1->proj,head1->hour,head1->addr,head1->phone);
                if(result==NULL)
                {
                    result=temp;
                    last=temp;
                }
                else
                {
                    last->next=temp;
                    last=temp;
                }
            }
            head1=head1->next;
        }
        *choice=1;
    }
    return result;
}

//symmetric-differnece operation
empRec *symdiffOp(empRec *head1,empRec *head2,int *choice)
{
    empRec *result,*u,*i,*d;
    result=NULL;
    *choice=0;
    int check;
    u=unionOp(head1,head2,&check);
    if(check==0)
    {
        *choice=0;
    }
    else
    {
        i=intersectOp(head1,head2,&check);
        if(check==0)
        {
            *choice=0;
        }
        else
        {
            result=diffOp(u,i,&check);
            if(check==0)
            {
                *choice=0;
            }
            else
            {
                *choice=1;
            }
        }
    }

    return result;
}

//Remove duplicates while inserting
empRec *removeDuplicateInsert(empRec *head)
{
    empRec *result,*xtra,*temp,*ptr;
    if(head==NULL || head->next==NULL) // check if no node or one node only
    {
        result=head;
    }
    else
    {
        xtra=head->next;
        temp=head;
        ptr=head;
        while(xtra!=NULL)
        {
            ptr=head;
            if(strcmp(temp->name,xtra->name)==0 && strcmp(temp->proj,xtra->proj)==0)
            {
                if(temp==head)
                {
                    result=head->next;
                }
                else
                {
                    while(ptr->next!=temp)
                    {
                        ptr=ptr->next;
                    }
                    ptr->next=temp->next;
                }
                free(temp);
                printf("\nRecord Updated!!\n");
            }
            else
            {
                temp=temp->next;
                xtra=xtra->next;
            }
        }
    }
    return result;
}

//unique listing function
empRec *uniqueList(empRec *head)
{
    system("cls");
    empRec *xtra,*ptr,*result;
    int num,i;
    int tempHour;
    char tempPhone[15],tempName[50],tempProj[50],tempAddr[100];
    char check[1];
    statusCode check1;
    printf("\n\tDo you want to import data from FILE: data.txt (y/n)");
    scanf("%s",check);
    if(strcmp(check,"y")==0)
    {
        check1=fileRead(&head,3);
        if(!check1)
        {
            printf("\n\tFailed to load the file...!!");
        }
        else
        {
            printf("\n\tSuccessfully loaded file...!!");
            result=sortEntry(head);
        }
        if(result!=NULL)
        {
            xtra=result->next;
        }
        else
        {
            xtra=result;
        }
        while(xtra!=NULL)
        {
            if(strcmp(head->name,xtra->name)==0 && strcmp(head->proj,xtra->proj)==0)
            {
                if(xtra==NULL)
                {
                    head->next=NULL;
                }
                else
                {
                    head->next=xtra->next;
                }
                free(xtra);
            }
            head=head->next;
            xtra=xtra->next;
        }
    }
    else
    {
        printf("\nEnter number of terms to be inserted: \n");
        scanf("%d",&num);
        for(i=0;i<num;i++)
        {
            printf("\nEnter new employee details:");
            printf("\n     ** Employee Name : ");
            scanf("%s",tempName);
            printf("\n     ** Project Name  : ");
            scanf("%s",tempProj);
            printf("\n     ** No. of Hours  : ");
            scanf("%d",&tempHour);
            printf("\n     ** Address       : ");
            scanf("%s",tempAddr);
            printf("\n     ** Phone Number  : ");
            scanf("%s",tempPhone);
            ptr=makeRecord(tempName,tempProj,tempHour,tempAddr,tempPhone);
            if(head==NULL)
            {
                head=ptr;
            }
            else
            {
                ptr->next=head;
                head=ptr;
                head=sortEntry(head);
                head=removeDuplicateInsert(head);
            }
            result=head;
        }
    }
    return result;
}

//***********************************************
//*****<--- End of program --->*****
//Sarvesh S. Parab
//12BT04CSE054
//DSPD-2 : Project :1
//***********************************************
