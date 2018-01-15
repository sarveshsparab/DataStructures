#include<stdio.h>
#include<stdlib.h>

typedef int item_type;
typedef struct node
{
    item_type data;
    struct node *next;
}node_type;

node_type *create_list(int);
void traverse_list(node_type *);
void delete_list(node_type *);
int list_size(node_type *);

main()
{
    node_type *list_ptr;
    int num_nodes,node_present;
    list_ptr=NULL;
    printf("Enter number of nodes: \n");
    scanf("%d",&num_nodes);
    list_ptr=create_list(num_nodes); //allocates space for list
    traverse_list(list_ptr);
    node_present=list_size(list_ptr);
    printf("\nSize: %d",node_present);
    getch();
    delete_list(list_ptr);
    node_present=list_size(list_ptr);
    printf("\nSize: %d",node_present);
    getch();
}

node_type *create_list(int num)
{
    int i=0;
    node_type *ptr,*head;
    head=NULL;
    while(i<num)
    {
        ptr=(node_type *)malloc(sizeof(node_type));
        ptr->data=i;
        ptr->next=head;
        head=ptr;
        i++;
    }
    return head;
}

void traverse_list(node_type *ptr)
{
    printf("\n");
    while(ptr!=NULL)
    {
        printf("%d\n",ptr->data);
        ptr=ptr->next;
    }
}

void delete_list(node_type *head)
{
    node_type *ptr;
    while(head!=NULL)
    {
        ptr=head;
        head=head->next;
        free(ptr);
    }
}

int list_size(node_type *ptr)
{
    int counter=0;
    while(ptr!=NULL)
    {
        counter++;
        ptr=ptr->next;
    }
    return counter;
}
