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
void moveToBottom(struct Queue *q,int value)
{
    struct Node *temp=q->front;
    struct Node * prev=NULL;
    while(temp!=NULL)
    {
        if(temp->data==value) break;
        prev=temp;
        temp=temp->next;
    }
    prev->next=temp->next;
    q->rear->next=temp;
    q->rear=temp;
    q->rear->next=NULL;
}
void enQueue(struct Queue* q, int value,int frame_size)
{
    if(hash[value]) moveToBottom(q,value);
    else if(q->size==0)
    {
        q->front=newNode(value);
        q->rear=q->front;
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
        hash[q->front->data]=false;
        q->rear->next=q->front;
        q->front->data=value;
        q->rear=q->rear->next;
        q->front=q->front->next;
        q->rear->next=NULL;
    }
    hash[value]=true;
}

struct Queue* createQueue(int frame_size)
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size=0;
    q->capacity=frame_size;
    return q;
}

void LRU(int *PageList,int n)
{
    int hits=0;
    struct Queue* queue = createQueue(5);
    for(int i=0;i<n;i++)
    {
        if(hash[PageList[i]]==1)
        {
            hits++;
        }
        enQueue(queue,PageList[i],5);
    }
    printf("%d",hits);
}
int main() {
    int pagelist[]={7,0,1,2,0,3,0,4,2,3,0,3,2};
    LRU(pagelist,13);
    return 0;
}