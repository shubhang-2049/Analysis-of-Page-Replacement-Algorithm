#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool hash[101]={false}; // Hashing array to keep track wheather the page is in the main memory or not

//Node struct for construction an individual element of the linked list
struct Node {
    int data;
    struct Node* next;
};

//Linked List structure that contains Three pointers
struct List {
    struct Node *front;   //Pointer to the first node of the linked list
    struct Node *rear;    //Pointer to the last node of the Linked List
    struct Node *curr;    //Pointer to the node of the Linked list that needs to be deleted whenever list is full and new page is to be pushed
    int size;   //size of the Linked List
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
void printList(struct List* q)
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
//This function Pushes the new page into the linked List/Main memory
void enQueue(struct List* q, int value,int frame_size)
{
    hash[value]=true;
    //If the first node is being entered then assign front,rear and curr to that node and increase size
    if(q->size==0){
        q->front=newNode(value);
        q->rear=q->front;
        q->curr=q->front;
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
    //This part is called when the list is full and we need to pop a page to push the new one
    else
    {
        //We use the curr pointer to check which node should be popped
        //starting from first node entered we pop the node to which curr is pointing
        // and then shift curr to the next node
        hash[q->curr->data]=false;
        q->curr->data=value; //change the value of the page to be deleted with the upcoming page
        if(q->curr->next!=NULL) q->curr=q->curr->next; //if curr is at the last node of the list shift it to the first node
        else q->curr=q->front; //else shift it to the next node
    }

}
//This function creates and empty list
struct List* createList()
{
    struct List* q = (struct List*)malloc(sizeof(struct List));
    q->front = q->rear = NULL;
    q->size=0;
    return q;
}
// Function which counts the Page hits
void FIFO(int *PageList,int n,int frame_size)
{
    int hits=0;
    struct List* list = createList();
    for(int i=0;i<n;i++)    //traverse the Page List
    {
        if(hash[PageList[i]])      //If it is a hit increase the count
        {
            hits++;
            printf("HIT {");
            printf("%d",PageList[i]);
            printf("}");
            printf("\n");
        }
        else                       //else push it into the list
        {
            enQueue(list,PageList[i],frame_size);
            printList(list);
            printf("\n");
        }
    }
    printf("No. of Page hits by FIFO algorithm : ");
    printf("%d",hits);}
int main() {
//    int pagelist[]={0, 2, 1, 6, 4, 0, 1, 0, 3, 1, 2, 1};
//    FIFO(pagelist,12,4);

    int pagelist[]={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    FIFO(pagelist,13,4);
    return 0;
}
