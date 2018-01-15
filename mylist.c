#include<stdio.h>
#include<stdlib.h>

typedef int item_type;
typedef struct node
{
    item_type data;
    struct node *next;
}node_type;

node_type *create_list(int);
node_type *insert_at_start(node_type *,item_type);

main()
{
    node_type *head;
    int num_nodes,node_present;
    head=NULL;
    printf("Enter number of nodes: \n");
    scanf("%d",&num_nodes);
    head=create_list(num_nodes); //allocates space for list
}

node_type *insert_at_start(node_type *head,item_type d)
{
    node_type *ptr;
    ptr=(node_type *)malloc(sizeof(node_type));
    ptr->data=d;
    ptr->next=head;
    head=ptr;
    return head;
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
