/* Given a sinngly Linked List, write a code that segregates the even and odd numbers in the linked list */
// The code is given as :
// The time Complexity is O(n), where n is the number of nodes
#include<stdio.h>
#include<stdlib.h>
struct node                                                   // Declaring the node
{
    int info;
    struct node *link;
};
struct node *create_list(struct node *start);
void display(struct node *start);
struct node *addatbeg(struct node *start,int data);
struct node *addatend(struct node *start,int data);
void EvenOdd(struct node *start1,struct node **start2,struct node **start3 );
int main()
{
        struct node *start1=NULL,*start2=NULL,*start3=NULL;
        start1=create_list(start1);
        EvenOdd(start1, &start2, &start3);
        printf("\nOriginal List L1 is :\n");
        display(start1);
        printf("Odd Numbers List L2 is :\n");
        display(start2);
        printf("Even Numbers List L3 is :\n");
        display(start3);
		return 0;
}
void EvenOdd(struct node *start1,struct node **start2,struct node **start3 )               // Function to segregate even and odd nodes in linked list
{
        struct node *p1=start1, *p2=*start2, *p3=*start3;
		while(p1!=NULL)
        {
                if( (p1->info)%2 != 0 )
                {
                    if(*start2==NULL)
                        *start2 = addatbeg(*start2,p1->info);
                    else
                        *start2 = addatend(*start2,p1->info);
                }
                else
                {
                    if(*start3==NULL)
                        *start3 = addatbeg(*start3,p1->info);
                    else
                        *start3 = addatend(*start3,p1->info);
                }
                p1=p1->link;
        }
}
struct node *create_list(struct node *start)                                               // Function to create a linked list with n nodes ( user input )
{
        int i,n,data;
        printf("Enter the number of nodes : ");
        scanf("%d",&n);
        start=NULL;
        if(n==0)
            return start;
		printf("\nEnter the element to be inserted : ");
        scanf("%d",&data);
        start=addatbeg(start,data);
		for(i=2;i<=n;i++)
        {
            printf("\nEnter the element to be inserted : ");
            scanf("%d",&data);
            start=addatend(start,data);
        }
        return start;
}
void display(struct node *start)                                                          // Function to display a linked list
{
        struct node *p;
        if(start==NULL)
        {
            printf("Empty\n");
            return;
        }
        p=start;
		while(p!=NULL)
        {
            printf("%d ",p->info);
            p=p->link;
        }
        printf("\n\n");
}
struct node *addatbeg(struct node *start,int data)                                               // Function to add nodes at beginning of Linked List 
{
        struct node *temp;
        temp=(struct node *)malloc(sizeof(struct node));
        temp->info=data;
        temp->link=start;
        start=temp;
        return start;
}
struct node *addatend(struct node *start,int data)                                              // Function to add nodes at end of linked list
{
        struct node *p,*temp;
        temp=(struct node *)malloc(sizeof(struct node));
        temp->info=data;
        p=start;
        while(p->link!=NULL)
            p=p->link;
        p->link=temp;
        temp->link=NULL;
        return start;
}
