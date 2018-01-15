#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define net_main_lib 5
#define net_dept_lib 5

struct book_record
{
    char name_book[100];
    char name_author[100];
    int year;
    int copies;
}main_lib[net_main_lib],dept_lib[net_dept_lib],new_lib[net_dept_lib+net_main_lib],tem,temp1[net_dept_lib+net_main_lib],temp2[net_dept_lib+net_main_lib];

    void initialize(struct book_record lib[],int n);
    void menu();
    int sub_menu(int);
    void display(struct book_record lib[],int n);
    void display_rec(struct book_record lib[],int n);
    void insertion(struct book_record lib[],int n);
    void deletion(struct book_record lib[],int n,int source);
    int searching(struct book_record lib[],int n,char temp_name_author[],char temp_name_book[],int source);
    int num_records(struct book_record lib[],int n);
    void rem_duplicate(struct book_record lib[],int n);
    int full_empty(struct book_record lib[],int n);
    void list_union(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3);
    void list_intersection(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3);
    void list_difference(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3);
    void list_symdifference(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3);
    void sorting(struct book_record lib[],int n,int new_ele);
    void top_most(struct book_record lib[],int n);

main()
{
    initialize(main_lib,net_main_lib);
    initialize(dept_lib,net_dept_lib);
    initialize(new_lib,net_main_lib+net_dept_lib);
    menu();
}

void initialize(struct book_record lib[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        lib[i].name_book[0]='\0';
        lib[i].name_author[0]='\0';
        lib[i].year=0;
        lib[i].copies=0;
    }
}

void menu()
{
    system("cls");
    int choice,temp,ret_val;
    char temp_name_book[100],temp_name_author[100];
    printf("\n\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("     **                                                        **\n");
    printf("     **\t\t    LIBRARY RECORDS MANAGEMENT TOOL            **\n");
    printf("     **                                                        **\n");
    printf("     **\t    1. Insert New Record                               **\n");
    printf("     **\t    2. Book Search                                     **\n");
    printf("     **\t    3. Delete a Record                                 **\n");
    printf("     **\t    4. Number of Active Records                        **\n");
    printf("     **\t    5. Multi-Library Management                        **\n");
    printf("     **\t    6. Unique Listing (Duplicate Removal)              **\n");
    printf("     **\t    7. Library Full or Empty Status                    **\n");
    printf("     **\t    8. Display all Library records                     **\n");
    printf("     **\t    9. Top Most Book Author                            **\n");
    printf("     **\t    10.Exit                                            **\n");
    printf("     **                                                        **\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        temp=sub_menu(1);
        if(temp==1)
            insertion(main_lib,net_main_lib);
        else if(temp==2)
            insertion(dept_lib,net_dept_lib);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        break;
    case 2:
        temp=sub_menu(1);
        printf("\n\n Enter the book details to search :\n");
        printf("\n\tName   : ");
        scanf("%s",temp_name_book);
        printf("\n\tAuthor : ");
        scanf("%s",temp_name_author);
        if(temp==1)
            ret_val=searching(main_lib,net_main_lib,temp_name_author,temp_name_book,2);
        else if(temp==2)
            ret_val=searching(dept_lib,net_dept_lib,temp_name_author,temp_name_book,2);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        break;
    case 3:
        temp=sub_menu(1);
        if(temp==1)
            deletion(main_lib,net_main_lib,3);
        else if(temp==2)
            deletion(dept_lib,net_dept_lib,3);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        break;
    case 4:
        temp=sub_menu(1);
        if(temp==1)
            ret_val=num_records(main_lib,net_main_lib);
        else if(temp==2)
            ret_val=num_records(dept_lib,net_dept_lib);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        printf("\n\n The number of active record entries are: %d \n",ret_val);
        printf("\nGoing back to main menu....Press any key to continue!!");
        getch();
        menu();
        break;
    case 5:
        temp=sub_menu(2);
        if(temp==1)
            list_union(main_lib,net_main_lib,dept_lib,net_dept_lib,new_lib,net_dept_lib+net_main_lib);
        else if(temp==2)
            list_intersection(main_lib,net_main_lib,dept_lib,net_dept_lib,new_lib,net_dept_lib+net_main_lib);
        else if(temp==3)
            list_difference(main_lib,net_main_lib,dept_lib,net_dept_lib,new_lib,net_dept_lib+net_main_lib);
        else if(temp==4)
            list_symdifference(main_lib,net_main_lib,dept_lib,net_dept_lib,new_lib,net_dept_lib+net_main_lib);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        break;
    case 6:
        temp=sub_menu(1);
        if(temp==1)
            rem_duplicate(main_lib,net_main_lib);
        else if(temp==2)
            rem_duplicate(dept_lib,net_dept_lib);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        break;
    case 7:
        temp=sub_menu(1);
        switch(temp)
        {
        case 1:
            ret_val=full_empty(main_lib,net_main_lib);
            break;
        case 2:
            ret_val=full_empty(dept_lib,net_dept_lib);
            break;
        default:
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
            break;
        }
        temp=ret_val;
        switch(temp)
        {
        case 0:
            printf("\nThe library is completely empty!!! \n");
            break;
        case 1:
            printf("\nThe library is completely full!!! \n");
            break;
        case 2:
            printf("\nThe library is neither completely full nor completely empty!!! \n");
            break;
        default:
            break;
        }
        printf("\n\n\t Press ANY key to continue!!");
        getch();
        menu();
        break;
    case 8:
        temp=sub_menu(3);
        if(temp==1)
            display(main_lib,net_main_lib);
        else if(temp==2)
            display(dept_lib,net_dept_lib);
        else if(temp==3)
            display(new_lib,net_dept_lib+net_main_lib);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        break;
    case 9:
        temp=sub_menu(1);
        if(temp==1)
            top_most(main_lib,net_main_lib);
        else if(temp==2)
            top_most(dept_lib,net_dept_lib);
        else
        {
            printf("Invalid Input!!!\n\n Going back to Main Menu...!!\n");
            getch();
            menu();
        }
        break;
    case 10:
        printf("\n\n\t\t Thank You!!");
        getch();
        break;
    default:
        printf("\n Enter proper Choice!!\n");
        getch();
        menu();
        break;
    }
}
int sub_menu(int a)
{
    system("cls");
    int choice;
    switch(a)
    {
    case 1:
    printf("\n\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("     **                                                        **\n");
    printf("     **\t\t    LIBRARY SELECTION                          **\n");
    printf("     **                                                        **\n");
    printf("     **\t    1. Main Library Record Management                  **\n");
    printf("     **\t    2. Department Library Record Management            **\n");
    printf("     **                                                        **\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    return choice;
    break;

    case 2:
    printf("\n\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("     **                                                        **\n");
    printf("     **\t\t    MULTI-LIBRARY OPERATIONS                   **\n");
    printf("     **                                                        **\n");
    printf("     **\t    1. Union of both Libraries                         **\n");
    printf("     **\t    2. Intersection of both Libraries                  **\n");
    printf("     **\t    3. Difference of both Libraries                    **\n");
    printf("     **\t    4. Symmetric Difference of both Libraries          **\n");
    printf("     **                                                        **\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    return choice;
    break;

    case 3:
    printf("\n\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("     **                                                        **\n");
    printf("     **\t\t    LIBRARY SELECTION                          **\n");
    printf("     **                                                        **\n");
    printf("     **\t    1. Main Library Record Management                  **\n");
    printf("     **\t    2. Department Library Record Management            **\n");
    printf("     **\t    3. Newly Formed Library                            **\n");
    printf("     **                                                        **\n");
    printf("     ************************************************************\n");
    printf("     ************************************************************\n");
    printf("\n\n");
    printf("Enter your Choice : \n");
    scanf("%d",&choice);
    return choice;
    break;

    default:
        break;
    }
}
void insertion(struct book_record lib[],int n)
{
    int check,i=0,temp_year,temp_copies,update,temp=0;
    char choice[1],temp_name_author[100],temp_name_book[100];
    check=full_empty(lib,n);
    if(check==1)
    {
        printf("\n Sorry!! The Library has reaches its maximum limit.\n");
        printf("\n Would you like to DELETE(d) / MODIFY(m) / DO NOTHING(n) an entry?(d/m/n)");
        scanf("%s",choice);
        if(strcmp(choice,"d")==0)
        {
            deletion(lib,n,1);
        }
        else if(strcmp(choice,"n")==0)
        {
            printf("\n\n Taking you back to main menu!! Press key to continue\n");
            getch();
            menu();
        }
        else if(strcmp(choice,"m")==0)
        {
            temp=1;
        }
        else
        {
            printf("\n\n Enter proper input!! Press key to continue to main menu\n");
            getch();
            menu();
        }
    }
    if (check!=1 || temp==1)
    {
        printf("\n\n Enter the book details:\n");
        printf("\n\tName                : ");
        scanf("%s",temp_name_book);
        printf("\n\tAuthor              : ");
        scanf("%s",temp_name_author);
        printf("\n\tYear of publication : ");
        scanf("%d",&temp_year);
        printf("\n\tCopies              : ");
        scanf("%d",&temp_copies);
        update=searching(lib,n,temp_name_author,temp_name_book,3);
        if(update==-1 && temp!=1)
        {
            i=num_records(lib,n);
            strcpy(lib[i].name_author,temp_name_author);
            strcpy(lib[i].name_book,temp_name_book);
            lib[i].copies=temp_copies;
            lib[i].year=temp_year;
            printf("\n\n\t BOOK ADDED!! \n");
            sorting(lib,n,i);
        }
        else if(update!=-1)
        {
            i=update;
            strcpy(lib[i].name_author,temp_name_author);
            strcpy(lib[i].name_book,temp_name_book);
            lib[i].copies=temp_copies;
            lib[i].year=temp_year;
            printf("\n\n\t BOOK UPDATED!! \n");
            sorting(lib,n,i);
        }
        else if(update==-1 && temp==1)
        {
            printf("\nThe entry does not exist to be modified!!\n");
            printf("Taking you back to main menu... press any key to continue!!\n");
            getch();
            menu();
        }
        printf("\n\nDo you want to add another book in this library? (y / n)\n");
        scanf("%s",choice);
        if(strcmp(choice,"y")==0)
        {
            insertion(lib,n);
        }
        else if(strcmp(choice,"n")==0)
        {
            printf("\n\nGoing back to main menu!!...Press any key to continue\n");
            getch();
            menu();
        }
    }
}
void deletion(struct book_record lib[],int n,int source)
{
    int check,last=0,i,temp;
    char choice[1],temp_name_book[100],temp_name_author[100];
    printf("\n\n Enter the book details to be deleted:\n");
    printf("\n\tName   : ");
    scanf("%s",temp_name_book);
    printf("\n\tAuthor : ");
    scanf("%s",temp_name_author);
    check=searching(lib,n,temp_name_book,temp_name_author,3);
    temp=check;
    if(check==-1)
    {
        printf("\n\nThe book you are requesting does not exist in our library!!");
        printf("\nDo you want to try another record to delete? (y / n)");
        scanf("%s",choice);
        if(strcmp(choice,"n")==0)
        {
            if(source==1)
            {
                printf("\n\n Since your requested entry does not exist to be delelted...\n You cannot insert new entry....\n\n Taking you back to main menu.....\t Press key to continue!!");
                getch();
                menu();
            }
            else
            {
                printf("\n\nTaking you back to main menu.... Press any key to continue!!");
                getch();
                menu();
            }
        }
        else if(strcmp(choice,"y")==0)
        {
            deletion(lib,n,source);
        }
    }
    else
    {
        printf("\n\nThe book record you requested is: \n");
        display_rec(lib,check);
        printf("\nConfirm deletion? (y / n)");
        scanf("%s",choice);
        if(strcmp(choice,"n")==0)
        {
            printf("Taking you back to main menu.... Press any key to continue!");
            getch();
            menu();
        }
        else if(strcmp(choice,"y")==0)
        {
            last=num_records(lib,n);
            for(i=check;i<last-1;i++)
            {
                lib[i]=lib[i+1];
            }
            lib[i].name_book[0]='\0';
            lib[i].name_author[0]='\0';
            lib[i].year=0;
            lib[i].copies=0;
            printf("\nBook record deleted!!!\n");
            if(source==1)
            {
                printf("\nTaking you back to insert new record!!");
                printf("\nPress any key to continue!!");
                getch();
                insertion(lib,n);
            }
            else if(source==3)
            {
                printf("\ntaking you back to main menu... Press any key to continue!!\n");
                getch();
                menu();
            }
        }
    }
}
int searching(struct book_record lib[],int n,char temp_name_author[],char temp_name_book[],int source)
{
    char choice[1];
    int i,found=0,ret_author=-1,ret_name=-1;
    for(i=0;i<n && found==0;i++)
    {
        if(strcmp(lib[i].name_author,temp_name_author)==0)
        {
            found=1;
            ret_author=i;
        }
    }
    if(ret_author==-1)
    {
        if(source==2)
        {
            printf("\n\nThe record you trying to search does not exist!! \n\n");
            printf("\n Do you want to try a new search? (y / n)");
            scanf("%s",choice);
            if(strcmp(choice,"n")==0)
            {
                printf("\nTaking you back to main menu... Press any key to continue");
                getch();
                menu();
            }
            else if(strcmp(choice,"y")==0)
            {
                printf("\n\n Enter the book details to search :\n");
                printf("\n\tName   : ");
                scanf("%s",temp_name_book);
                printf("\n\tAuthor : ");
                scanf("%s",temp_name_author);
                searching(lib,n,temp_name_author,temp_name_book,2);
            }
        }
        else if(source==3)
        {
            return -1;
        }
    }
    else
    {
        found=0;
        for(i=ret_author;strcmp(lib[i].name_author,temp_name_author)==0 && found==0;i++)
        {
            if(strcmp(lib[i].name_book,temp_name_book)==0)
            {
                found=1;
                ret_name=i;

            }
        }
        if(ret_name==-1)
        {
            if(source==2)
            {
                printf("\n\nThe record you trying to search does not exist!! \n\n");
                printf("\n Do you want to try a new search? (y / n)");
                scanf("%s",choice);
                if(strcmp(choice,"n")==0)
                {
                    printf("\nTaking you back to main menu... Press any key to continue");
                    getch();
                    menu();
                }
                else if(strcmp(choice,"y")==0)
                {
                    printf("\n\n Enter the book details to search :\n");
                    printf("\n\tName   : ");
                    scanf("%s",temp_name_book);
                    printf("\n\tAuthor : ");
                    scanf("%s",temp_name_author);
                    searching(lib,n,temp_name_author,temp_name_book,2);
                }
            }
            else if(source==3)
            {
                return -1;
            }
        }
        else
        {
            if(source==2)
            {
                printf("\n\n Found!!!\n");
                printf("The Record you requested is : \n");
                display_rec(lib,ret_name);
                printf("\n Taking you back to main menu...Press any to continue \n");
                getch();
                menu();
            }
            else if(source==3)
            {
                return ret_name;
            }
        }
    }
}
int num_records(struct book_record lib[],int n)
{
    int i=0;
    while(strcmp(lib[i].name_author,"\0")!=0 && strcmp(lib[i].name_book,"\0")!=0)
        {
            i++;
        }
    return i;
}
void rem_duplicate(struct book_record lib[],int n)
{
    int check,ran_val,i;
    check=num_records(lib,n);
    printf("\nEnter the number of random entries");
    scanf("%d",&ran_val);
    if(ran_val>(n-check))
    {
        printf("\n The library has only %d empty places left\n");
        printf("Taking you back to main menu... press any key to continue!!");
        getch();
        menu();
    }
    else
    {
        for(i=0;i<ran_val;i++)
        {
            printf("Enter book detail for book no : %d\n",i+1);
            check=num_records(lib,n);
            printf("Enter book name : \n");
            scanf("%s",lib[check].name_book);
            printf("Enter author name : \n");
            scanf("%s",lib[check].name_author);
            printf("Enter publication year : \n");
            scanf("%d",&lib[check].year);
            printf("Enter copies : \n");
            scanf("%d",&lib[check].copies);
            sorting(lib,n,check);
        }
    }
    printf("\n\nGoing back to main menu... press any key to continue!!");
    getch();
    menu();
}
int full_empty(struct book_record lib[],int n)
{
    int i=0;
    while(strcmp(lib[i].name_book,"\0")!=0 && strcmp(lib[i].name_author,"\0")!=0)
    {
        i++;
    }
    if(i==0)
        return(0);
    else if(i==n)
        return(1);
    else
        return(2);
}
void list_union(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3)
{
    int i=0,j=0,k=0;
    n1=num_records(lib1,n1);
    n2=num_records(lib2,n2);
    if(full_empty(lib1,n1)==0 && full_empty(lib2,n2)==2)
    {
        lib3=lib2;
    }
    else if(full_empty(lib2,n2)==0 && full_empty(lib1,n1)==2)
    {
        lib3=lib1;
    }
    else
    {
        while(i<n1 && j<n2)
        {
            if(strcmp(lib1[i].name_author,lib2[j].name_author)==0 && strcmp(lib1[i].name_book,lib2[j].name_book)==0)
            {
                if(lib1[i].year>lib2[j].year)
                {
                    lib3[k++]=lib1[i++];
                    j++;
                }
                else
                {
                    lib3[k++]=lib2[j++];
                    i++;
                }
            }
            else if(strcmp(lib1[i].name_author,lib2[j].name_author)==0 && strcmp(lib1[i].name_book,lib2[j].name_book)>0)
            {
                lib3[k++]=lib2[j++];
            }
            else if(strcmp(lib1[i].name_author,lib2[j].name_author)==0 && strcmp(lib1[i].name_book,lib2[j].name_book)<0)
            {
                lib3[k++]=lib1[i++];
            }
            else if(strcmp(lib1[i].name_author,lib2[j].name_author)>0)
            {
                lib3[k++]=lib2[j++];
            }
            else if(strcmp(lib1[i].name_author,lib2[j].name_author)<0)
            {
                lib3[k++]=lib1[i++];
            }
        }
        while(i<n1)
        {
            lib3[k++]=lib1[i++];
        }
        while(j<n2)
        {
            lib3[k++]=lib2[j++];
        }
    }
    printf("\n\n\tUNION OPERATION SUCCESSFUL!!\n");
    printf("Taking you back to main menu... Press any to continue!\n");
    getch();
    menu();
}
void list_intersection(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3)
{
    int i=0,j=0,k=0;
    n1=num_records(lib1,n1);
    n2=num_records(lib2,n2);
    if(full_empty(lib1,n1)==0)
    {
        printf("\nSince Main Library is empty... Intersection Operation gives empty New Library\n!!");
        lib3=lib1;
    }
    else if(full_empty(lib2,n2)==0)
    {
        printf("\nSince Department Library is empty... Intersection Operation gives empty New Library\n!!");
        lib3=lib2;
    }
    else
    {
        while(i<n1 && j<n2)
        {
            if(strcmp(lib1[i].name_author,lib2[j].name_author)==0 && strcmp(lib1[i].name_book,lib2[j].name_book)==0)
            {
                if(lib1[i].copies<lib2[j].copies)
                {
                    lib3[k++]=lib1[i++];
                    j++;
                }
                else
                {
                    lib3[k++]=lib2[j++];
                    i++;
                }
            }
            else
            {
                i++;
                j++;
            }
        }
    }
    printf("\n\n\tINTERSECTION OPERATION SUCCESSFUL!!\n");
    printf("Taking you back to main menu... Press any to continue!\n");
    getch();
    menu();
}
void list_difference(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3)
{
    int i=0,j=0,k=0,temp;
    n1=num_records(lib1,n1);
    n2=num_records(lib2,n2);
    if(full_empty(lib1,n1)==0)
    {
        printf("\nSince Main Library is empty... Difference Operation gives empty New Library\n!!");
        lib3=lib1;
    }
    else if(full_empty(lib2,n2)==0)
    {
        printf("\nSince Department Library is empty... Difference Operation gives New Library as main Library\n!!");
        lib3=lib1;
    }
    else
    {
        while(i<n1)
        {
            temp=searching(lib2,n2,lib1[i].name_author,lib1[i].name_book,2);
            if(temp==-1)
            {
                lib3[k++]=lib1[i];
            }
            i++;
        }
    }
    printf("\n\n\tDIFFERENCE OPERATION SUCCESSFUL!!\n");
    printf("Taking you back to main menu... Press any to continue!\n");
    getch();
    menu();
}
void list_symdifference(struct book_record lib1[],int n1,struct book_record lib2[],int n2,struct book_record lib3[],int n3)
{
    int temp_n1=num_records(lib1,n1),temp_n2=num_records(lib2,n2);
    if(full_empty(lib1,temp_n1)==0)
    {
        printf("\nSince Main Library is empty... Symmetric Difference Operation gives New Library as Dept Library\n!!");
        lib3=lib2;
    }
    else if(full_empty(lib2,temp_n2)==0)
    {
        printf("\nSince Department Library is empty... Symmetric Difference Operation gives New Library as Main Library\n!!");
        lib3=lib1;
    }
    else
    {
        list_union(lib1,n1,lib2,n2,temp1,n1+n2);
        list_intersection(lib1,n1,lib2,n2,temp2,n1+n2);
        list_difference(temp1,n1+n2,temp2,n2+n1,lib3,n1+n2);
    }
    printf("\n\n\tSYMMETRIC DIFFERENCE OPERATION SUCCESSFUL!!\n");
    printf("Taking you back to main menu... Press any to continue!\n");
    getch();
    menu();
}
void sorting(struct book_record lib[],int n,int new_ele)
{
    int i=0,flag=0,k=0,j,m;
    while(i<new_ele && flag==0)
    {
        if(strcmp(lib[new_ele].name_author,lib[i].name_author)<0)
        {
            tem=lib[new_ele];
            for(k=new_ele;k>i;k--)
            {
                lib[k]=lib[k-1];
            }
            lib[k]=tem;
            flag=1;
        }
        i++;
    }
    if(flag==0)
    {
        k=new_ele;
    }
    while((strcmp(lib[k].name_author,lib[k-1].name_author)==0) && k>0)
    {
        if(strcmp(lib[k].name_book,lib[k-1].name_book)<0)
        {
            tem=lib[k];
            lib[k]=lib[k-1];
            lib[k-1]=tem;
        }
        k--;
    }
}
void display(struct book_record lib[],int n)
{
    int i;
    n=num_records(lib,n);
    printf("\n Book Name \t Author \t Publication \t Copies\n");
    printf(" ********* \t ****** \t *********** \t ******\n");
    for(i=0;i<n;i++)
    {
        printf("\n %s \t %s \t %d \t %d",lib[i].name_book,lib[i].name_author,lib[i].year,lib[i].copies);
    }
    printf("\n\n");
    printf("Going back to main menu...Press key to continue...!!");
    getch();
    menu();
}
void display_rec(struct book_record lib[],int n)
{
    printf("************************************");
    printf("\n Name : %s",lib[n].name_book);
    printf("\n Author : %s",lib[n].name_author);
    printf("\n Year of publication : %d",lib[n].year);
    printf("\n Copies : %d\n",lib[n].copies);
    printf("************************************");
}
void top_most(struct book_record lib[],int n)
{
    int i,j=0,sorted=0;
    char temp_name_book[100];
    printf("\nEnter name of book: \n");
    scanf("%s",temp_name_book);
    for(i=0;i<n;i++)
    {
        if(strcmp(temp_name_book,lib[i].name_book)==0)
        {
            temp1[j++]=lib[i];
        }
    }
    n=num_records(temp1,n);
    for(i=0;i<n-1 && sorted==0;i++)
    {
        sorted=1;
        for(j=0;j<n-i-1;j++)
        {
            if(temp1[j].copies<temp1[j+1].copies)
            {
                tem=temp1[j];
                temp1[j]=temp1[j+1];
                temp1[j+1]=tem;
                sorted=0;
            }
        }
    }
    display(temp1,n);
}
