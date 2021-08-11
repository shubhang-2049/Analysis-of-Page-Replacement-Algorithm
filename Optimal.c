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
//This function finds which page from the list whill be called farthest into the future
struct Node* getOptimal(struct List *q,int *PageList,int i,int n)
{
    struct Node *max_add_node,*temp=q->front; //max_add_node will point to the node in the list which will be called agin farthest into the future
    int dist_max=0;
    while(temp!=NULL)  //Traverse the list
    {
        int dist=0;
        //For every element in the list check its occurance in the Page request list after index i
        for(int j=i;j<n;j++)
        {
            if(PageList[j]==temp->data) break;
            dist++;      //find the distance between i and the index of next occurance of temp
        }
        if(dist>dist_max) // find the greatest of all dist and farthest of all nodes
        {
            dist_max=dist;
            max_add_node=temp;
        }
        temp=temp->next;
    }
    return max_add_node;
}
//This function Pushes the new page into the linked List/Main memory
void enList(struct List* q, int i,int *PageList,int n,int frame_size)
{
    int value=PageList[i];
    //If the first node is being entered then assign front,rear and curr to that node and increase size
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
    //This part is called when the list is full and we need to pop a page to push the new one
    else
    {
        struct Node* add=getOptimal(q,PageList,i,n); // find the optimal page to delete
        hash[add->data]=false;
        add->data=value; // change the page of node to be deleted to the node to be pushed
    }
    hash[value]=true;
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
void Optimal(int *PageList,int n,int frame_size)
{
    int hits=0;
    struct List* list = createList();
    for(int i=0;i<n;i++)         //traverse the Page List
    {
        if(hash[PageList[i]]==true)         //If it is a hit increase the count
        {
            hits++;
            printf("HIT {");
            printf("%d",PageList[i]);
            printf("}");
            printf("\n");
        }
        else
        {
            enList(list,i,PageList,32,frame_size);      //else push it into the list
            printList(list);
            printf("\n");
        }

    }
    printf("No. of Page hits by Optimal algorithm : ");
    printf("%d",hits);}
int main() {
//    int pagelist[]={0, 2, 1, 6, 4, 0, 1, 0, 3, 1, 2, 1};
//    Optimal(pagelist,12,4);

    int pagelist[]={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    Optimal(pagelist,13,4);
    return 0;
}