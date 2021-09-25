#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool hash[101]={false};// Hashing array to keep track wheather the page is in the mian memory or not

//Node struct for construction an individual element of the linked list
struct Node {
    int data;
    struct Node* next;
};

//Queue structure that contains two pointers
struct Queue {
    struct Node *front;   //Pointer to the first node of the Queue
    struct Node *rear;    //Pointer to the last node of the Queue
    int size;   //size of the Queue
};
//A function to create a new node with dat field specified
struct Node* newNode(int value)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}
//This Function Print the Linked List
void printList(struct Queue* q)
{
    struct Node* temp=q->front; // Create a Temporary pointer that will traverse the list
    printf("[");
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        if(temp->next!=NULL)printf("|");
        temp=temp->next;
    }
    printf("]");

}
void printHash()
{
    printf("  ");
    for(int i=0;i<10;i++)
    {
        printf("%d",hash[i]);
    }
    printf("\n");

}
//This function searches for the specified node and move it to the end of the queue
void moveToBottom(struct Queue *q,int value)
{
    struct Node *temp=q->front;
    struct Node * prev=NULL; //prev contain the address of the node previous to the specified node
    while(temp!=NULL)
    {
        if(temp->data==value) break;
        prev=temp;
        temp=temp->next;
    }
    if(temp==q->front)
    {
        q->front=q->front->next; //If the node is at the top shift the front pointer
    }
    else prev->next=temp->next;  //else link the prev node with the node next to temp
    q->rear->next=temp; //link temp to the end
    q->rear=temp;  //update the rear pointer
    q->rear->next=NULL;
}
//This function Pushes the new page into the linked List/Main memory
void enQueue(struct Queue* q, int value,int frame_size)
{
//    printList(q);
//    printf("\n");
//
    //If the first node is being entered then assign front and rear to that node and increase size
    if(q->size==0)
    {
        q->front=newNode(value);
        q->rear=q->front;
        q->size=q->size+1;
    }
    //If there are fewer node in the list than the frame size then create a new node and push it to the end of the list
    else if(q->size<frame_size)
    {
        struct Node* temp = newNode(value);
        q->rear->next=temp;  // joining the new node after rear
        q->rear=temp;        //updating the rear pointer
        q->size=q->size+1;   //increasing the size
    }
    //This part is called when the queue is full and we need to pop a page to push the new one
    else
    {
        hash[q->front->data]=false;
        q->rear->next=q->front; //Link the page at the top to the end
        q->front->data=value;   //change the page in that node
        q->rear=q->rear->next;  //update the value of the rear pointer
        q->front=q->front->next;//update the value of the front pointer
        q->rear->next=NULL;
    }
    hash[value]=true;
}
//This function creates and empty queue
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size=0;
    return q;
}
// Function which counts the Page hits
void LRU(int *PageList,int n,int frame_size)
{
    int hits=0;
    struct Queue* queue = createQueue();
    for(int i=0;i<n;i++)                            //traverse the Page List
    {
        if(hash[PageList[i]]==1)
        {
            hits++; //If it is a hit increase the count and move that page to the bottom of the queue
            moveToBottom(queue,PageList[i]);
            printf("HIT {");
            printf("%d",PageList[i]);
            printf("}");
            printf("\n");
        }
        else                     //else push it into the list
        {
            enQueue(queue,PageList[i],frame_size);
            printList(queue);
            printf("\n");
        }
    }
    printf("No. of Page hits by LRU algorithm : ");
    printf("%d",hits);
}
int main() {
//    int pagelist[]={0, 2, 1, 6, 4, 0, 1, 0, 3, 1, 2, 1};
//    LRU(pagelist,12,4);

    int pagelist[]={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    LRU(pagelist,13,4);
    return 0;
}\
