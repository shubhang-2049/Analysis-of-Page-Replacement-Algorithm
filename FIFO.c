#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool hash[101]={false};
struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node *front;
    struct Node *rear;
    struct Node *curr;
    int capacity,size;
};

struct Node* newNode(int value)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}
void printList(struct Queue* q)
{
    struct Node* temp=q->front;
    while(temp!=NULL)
    {
        printf("%d",temp->data," ");
        temp=temp->next;
    }
}
void printHash()
{
    printf("  ");
    for(int i=0;i<7;i++)
    {
        printf("%d",hash[i]);
    }
    printf("\n");

}
void enQueue(struct Queue* q, int value,int frame_size)
{
    hash[value]=true;
    if(q->size==0){
        q->front=newNode(value);
        q->rear=q->front;
        q->curr=q->front;
        q->size=q->size+1;
    }
    else if(q->size<=frame_size)
    {
        struct Node* temp = newNode(value);
        q->rear->next=temp;
        q->rear=temp;
        q->size=q->size+1;
    }
    else
    {
        hash[q->curr->data]=0;
        q->curr->data=value;
        if(q->curr->next!=NULL) q->curr=q->curr->next;
        else q->curr=q->front;
    }
    printList(q);
    printHash();
}

struct Queue* createQueue(int frame_size)
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size=0;
    q->capacity=frame_size;
    return q;
}

void FIFO(int *PageList,int n)
{
    int hits=0;
    struct Queue* queue = createQueue(5);
    for(int i=0;i<n;i++)
    {
        if(hash[PageList[i]]==1)
        {
            hits++;
        }
        else
        {
            enQueue(queue,PageList[i],5);
        }
    }
    printf("%d",hits);
}
int main() {
    int pagelist[]={1,3,0,3,5,6,3};
    FIFO(pagelist,7);
    return 0;
}