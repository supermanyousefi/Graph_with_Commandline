#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct {short size,rear,front, * items; } Queue;

Queue * construct_queue(short n)
{
    
    if (n<2)
    {
        printf("\nError:\tconstruct_queue(%hd)\n%hd is less than two!\n",n,n);
        return NULL;
    }
    
    Queue *Q=(Queue *)malloc(sizeof(Queue));
    if (Q==NULL)
    {
        printf("\nError:\tconstruct_queue(%hd)\ncouldn't allocate memmory\n",n);
        return NULL;
    }
    
    Q->size=n;
    Q->front=0;
    Q->rear=-1;
    Q->items=(short *)malloc(n*sizeof(short));
    
    if (Q->items==NULL)
    {
        printf("\nError:\tconstruct_queue(%hd)\ncouldn't allocate memmory\n",n);
        return NULL;
    }
    
    //printf("\nSuccess:\tconstruct_queue(%hd)\nqueue constructed!\n",n);
    return Q;
}

Queue * deconstruct_queue(Queue * Q)
{
    if (Q!=NULL)
    {
        free(Q->items);
        free(Q);
    }
    return NULL;
}

bool is_empty(Queue * Q)
{
    if (Q->rear==-1)
    {
        //printf("\nReport:\tis_empty(%p)\nQueue is Empty.\n",Q);
        return true;
    }
    //printf("\nReport:\tis_empty(%p)\nQueue is not Empty\n",Q);
    return false;
}

bool is_full(Queue * Q)
{
    if (Q->rear==-1)
    {
        //printf("\nReport:\tis_full(%p)\nQueue is not Full\n",Q);
        return false;
    }
    
    if ((Q->rear+1)%Q->size == Q->front)
    {
        //printf("\nReport:\tis_full(%p)\nQueue is Full\n",Q);
        return true;
    }
    
    //printf("\nReport:\tis_full(%p)\nQueue is not Full\n",Q);
    return false; 
}



/*
bool enqueue(Queue * Q,short item)//returns true in case of failuer
{
    if (Q == NULL)
    {
        printf("\nError:\tenqueue(%p,%hd)\nQueue is Null !\n",Q,item);
        return true;
    }
    if (is_full(Q))
    {
        printf("\nError:\tenqueue(%p,%hd)\ncan't enque since it's full !\n",Q,item);
        return true;
    }

    Q->rear=(Q->rear+1)%Q->size;
    *(Q->items+Q->rear)=item;

    printf("\nSuccess:\tenqueue(%p,%hd)\n%hd is enqueued!\n",Q,item,item);
    return false;
}

short dequeue(Queue * Q)//returns -1 in case of failuer
{
    if (Q == NULL)
    {
        printf("\nError:\tdequeue(%p)\nQueue is Null!\n",Q);
        return -1;
    }
    
    if (is_empty(Q))
    {
        printf("\nError:\tdequeue(%p)\ncan't dequeue since Queue is empty!\n",Q);
        return -1;
    }
    
    short item = *(Q->items+Q->front);
    if (Q->front==Q->rear)
    {
        Q->front=Q->rear=-1;
    }

    Q->front=(Q->front+1)%Q->size;
    printf("\nSuccess:\tdequeue(%p)\n %hd is dequeued!\n",Q,item);
    return item;
}

void showQueue(Queue * Q)
{
    if (Q == NULL)
    {
        printf("\nError:\tshowQueue(%p)\nQueue is Null , can't show them!\n",Q);
        return ;
    }
    
    if (is_empty(Q))
    {
        printf("\nReport:\tshowQueue(%p)\nQueue is empty!\n",Q);
        return;
    }
    
    printf("\n[");
    for (short i = Q->front; i != Q->rear; i=(i+1)%Q->size)
    {
        printf("%hd|",*(Q->items+i));
    }
    printf("%hd",*(Q->items+Q->rear));
    printf("]\n");
    //printf("\nSuccess:\tshowQueue(%p)\nsuccessfull!\n",Q);
    return;
}*/

