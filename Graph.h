#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef enum {not_visited,in_Queue,visited} status;
typedef struct{short n,* matrix; char * name;status * state;} Graph;




bool enqueue_graph(Graph * G, Queue * Q,short item)//returns true in case of failuer
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

    printf("\n%c is enqueued!\n",*(G->name+item));
    return false;
}

short dequeue_graph(Graph * G, Queue * Q)//returns -1 in case of failuer
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
    printf("\n%c is dequeued!\n",*(G->name+item));
    return item;
}

void showQueue_graph(Graph * G, Queue * Q)
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
    short index=*(Q->items+Q->front);
    printf("\n[");
    for (short i = Q->front; i != Q->rear; i=(i+1)%Q->size)
    {
        index=*(Q->items+i);
        printf("%c|",*( G->name+index ));
    }
    index=*(Q->items+Q->rear);
    printf("%c",*( G->name+index ));
    printf("]\n");
    //printf("\nSuccess:\tshowQueue(%p)\nsuccessfull!\n",Q);
    return;
}


//must be assigned to itself
Graph * deconstruct_Graph(Graph * g)
{
    if (g != NULL)
    {
        if (g->state != NULL)free(g->state);
        if (g->name != NULL)free(g->name);
        if(g->matrix!=NULL) free(g->matrix);
        free(g);
    }
    return NULL;
}

Graph * construct_Graph(short n)
{

    if(n<2)
    {
        printf("\nError:\tconstruct_graph(%hd)\n%hd is less than 2!\n",n,n);
        return NULL;
    }
    if(n>16)
    {
        printf("\nError:\tconstruct_graph(%hd)\n%hd is more than 16!\n",n,n);
        return NULL;
    }
    Graph * g = (Graph *) malloc(sizeof(Graph));
    if (g == NULL)
    {
        printf("\nError:\tconstruct_graph(%hd)\ncould't allocate memory for bode holder struct\n",n);
        return NULL;
    }

    g->n=n;
    g->matrix=(short *)calloc(n*n,sizeof(Graph));
    if (g->matrix == NULL)
    {
        printf("\nError:\tconstruct_Graph(%hd)\ncouldn't allocate memory for matrix\n",n);
        return deconstruct_Graph(g);
    }

    g->name=NULL;
    
    g->state=(status *)calloc(n,sizeof(status));
    if (g->state==NULL)
    {
        printf("\nError:\tconstruct_Graph(%hd)\ncouldn't allocate memmory for state array\n",n);
        return deconstruct_Graph(g);
    }
    printf("\nSuccess:\tconstruct_Graph(%hd)\ngraph created\n",n);
    return g; 
}

bool check_graph(Graph * g)
{
    if (g==NULL)
    {
        printf("\nError:\tcheck_graph(null)\nnull can not be checked\n");
        return true;
    }

    for (short flag,i = 0; i < g->n; i+=g->n+1)
    {
        flag=0;
        for (short j = 0; j < g->n; j++)
        {
            if (*(g->matrix+(i*g->n)+j)!= 0)
            {
                flag++;
            }
            
        }
        if (flag==0)
        {
            printf("\nError:\tcheck_graph(%p)\nvertex %c is alone\n",g,*(g->name+i));
            return true;
        }
    }
    
    return false;
}

//returns True in case of Error
bool add_edge(Graph *g,short index1,short index2,short weight)
{
    if (g==NULL)
    {
        printf("\nError:\tadd_edge(%p,%hd,%hd)\ncan't add edge to a null graph\n",g,index1,index2);
        return true;
    }

    short error_score=0;
    error_score+=(g->matrix == NULL);
    error_score+=(index1 >= g->n);
    error_score+=(index2 >= g->n);
    error_score+=(index1 == index2);
    error_score+=(index1 < 0);
    error_score+=(index2 < 0);
    error_score+=(weight < 1);
    
    if (error_score)
    {
        printf("\nError:\tadd_edge(%p,%hd,%hd)\nerror score is %hd\n",g,index1,index2,error_score);
        return true;
    }
   
    *((g->matrix)+(index1 * g->n)+(index2))=weight;
    *((g->matrix)+(index2 * g->n)+(index1))=weight;
    printf("\nSuccess:\tadd_edge(%p,%hd,%hd)\nedge added!\n",g,index1,index2);
    return false;
}

//returns True in case of Error
bool remove_edge(Graph *g,short index1,short index2)
{
    if (g==NULL)
    {
        printf("\nError:\tadd_edge(%p,%hd,%hd)\ncan't add edge to a null graph\n",g,index1,index2);
        return true;
    }

    short error_score=0;
    error_score+=(g->matrix == NULL);
    error_score+=(index1 >= g->n);
    error_score+=(index2 >= g->n);
    error_score+=(index1 == index2);
    error_score+=(index1 < 0);
    error_score+=(index2 < 0);
    
    if (error_score)
    {
        printf("\nError:\tadd_edge(%p,%hd,%hd)\nerror score is %hd\n",g,index1,index2,error_score);
        return true;
    }
   
    *((g->matrix)+(index1 * g->n)+(index2))=0;
    *((g->matrix)+(index2 * g->n)+(index1))=0;
    printf("\nSuccess:\tremove_edge(%p,%hd,%hd)\nedge removed!\n",g,index1,index2);
    return false;
}

void show_graph_matrix(Graph * g)
{
    if (g==NULL)
    {
        printf("\nError: show_graph(%p)\ngraph is null\n",g);
        return;
    }

    if (g->matrix==NULL)
    {
        printf("\nError: show_graph(%p)\ngraph has no matrix\n",g);
        return;
    }

    printf("\n#");
    for (short i = 0; i < g->n; i++)
    {
        printf("\t%c",*(g->name+i));
    }
    
    printf("\n");
    for (short i = 0; i < (g->n)*(g->n); i++)
    {
        if(i%(g->n) == 0)
        {
            printf("\n%c",*(g->name+(i/g->n)));
        }
        if (*(g->matrix+i)==0)
        {
            printf("\tN/E");
        }
        else
        {
            printf("\t%hd",*(g->matrix+i));
        }
    }
    printf("\n");
}



// DIJKSTRA implementation

typedef struct
{
    unsigned short distance_from_start;
    short index;
} vertex;

typedef struct
{
    short start_index;
    short n;
    unsigned short * distance_from_start;
    short * previous; 
} dijkstra_output;

dijkstra_output * dijkstra(Graph * g,short start_index)
{
    if (g==NULL)
    {
        printf("\nError: dijkstra()\ngraph is null\n");
        return NULL;
    }
    if (start_index < 0 || start_index >= g->n)
    {
        printf("\nError: dijkstra()\nentered index is not in range\n");
        return NULL;
    }
    if (check_graph(g))
    {
        printf("\nGraph has a problem, add edges to fix this issue\n");
        return NULL;
    }
    
    dijkstra_output * O=(dijkstra_output *)malloc(sizeof(dijkstra_output));
    if (O == NULL)
    {
        printf("\nError: dijkstra()\nmemory not allocated\n");
        return NULL;
    }
    O->start_index=start_index;
    O->n=g->n;
    O->distance_from_start=(unsigned short *)malloc(g->n * sizeof(unsigned short));
    O->previous=(short *)malloc(g->n * sizeof(short));
    if (O->distance_from_start == NULL || O->previous == NULL)
    {
        printf("\nError: dijkstra()\nmemory not allocated\n");
        return NULL;
    }
    //previous[3]=5 means before meet 3 you must meet 5, or you can say first you must meet 5 then go to 3
    //if start is 3 and distance_from_start[5] is equal to 6 then it means: the distance from vertex3 to vertex5 is equal to 6
    
    bool visited[g->n];
    for (short i = 0; i < g->n; i++)
    {
        //assign maximum value that a short int can take:
        *(O->distance_from_start+i)=0-1;//it's a method that assigns the maximum number that an unsigned short variable can take to itself
        visited[i]=false;
        *(O->previous+i)=0-1;// 0-1 means no way
    }
    *(O->distance_from_start+start_index)=0;
    vertex v;
    for (short i = 0; i < g->n; i++)
    {
        //find nearest unvisited node and set it as current
        //v will hold index and distance of the nearest vertex and will be set as current
        v.distance_from_start=0-1;
        v.index=-1;
        for (short k = 0; k < g->n; k++)
        {
            if (*(O->distance_from_start+k) < v.distance_from_start && !visited[k])
            {
                v.distance_from_start=*(O->distance_from_start+k);
                v.index=k;
            }
        }
        if(v.index == -1) break;
        
        visited[v.index]=true;
        //now we already have visited v
        //v is current
        
        //the next step is to scan unvisited neighbors of v, then set the distance for each of them
        for (short j = 0; j < g->n; j++)
        {
            if (*(g->matrix+(v.index*g->n)+j) != 0 && !visited[j])
            {
                if (*(O->distance_from_start+j) > *(g->matrix+(v.index * g->n)+j)+ *(O->distance_from_start+v.index))
                {
                    *(O->distance_from_start+j) = *(g->matrix+(v.index * g->n)+j)+ *(O->distance_from_start+v.index);
                    *(O->previous+j)=v.index;//means you must meet v before meeting j;
                }
            }
        }
        
    }
    return O;
}

void function(Graph * G,dijkstra_output *O, short index)
{
    if(*(O->previous)==0-1)
    { printf("no way!"); return;}
    else{
        printf("(%c)<--",*(G->name+index));
    }
    if (index == O->start_index)
    {
        printf("\b\b\b\n");
        return;
    }
    function(G,O,*(O->previous+index));
}
void show_the_way(Graph * G,dijkstra_output * O)
{
    if (G==NULL)
    {
        return;
    }
    
    if (O == NULL)
    {
        return;
    }

    if (O->distance_from_start == NULL || O->previous == NULL)
    {
        return;
    }
    
    for (short i = 0; i < O->n; i++)
    {
        function(G,O,i);
    }
}

bool BFS(Graph * G,short start_index)
{
    if (G==NULL)
    {
        printf("\nError:\tBFS(%hd)\ngraph is null\n",start_index);
        return true;
    }

    if (start_index < 0 || start_index>=G->n)
    {
        printf("\nError:\tBFS(%p,%hd)\n%hd is not valid as start index, since its out of range\n",G,start_index,start_index);
        return true;
    }

    if (check_graph(G))
    {
        printf("\nError:\tBFS(%p,%hd)\ngraph has a problem. add some edges to fix this issue\n",G,start_index);
        return true;
    }
    
    Queue * Q=construct_queue(G->n);
    if (Q == NULL)
    {
        printf("\nError:\tBFS(%p,%hd)\ncouldn't make Queue\n",G,start_index);
        return true;
    }

    short current_vertex_index=start_index;
    enqueue_graph(G,Q,current_vertex_index);
    *(G->state+current_vertex_index)=in_Queue;
    showQueue_graph(G,Q);
    for (short i = 0; ! is_empty(Q); i++)
    {
        current_vertex_index=dequeue_graph(G,Q);
        *(G->state+current_vertex_index)=visited;
        printf("\n%c is visited!\n",*(G->name+current_vertex_index));
        for (short j = 0; j < G->n; j++)
        {
            if ((*(G->matrix+(current_vertex_index*G->n)+j)==1)&&(*(G->state+j)==not_visited))//(state != visited) is different than (state == not_visited)    first one means those who do not belong to visited which means those who belong to noy_visited or in_queue but the second means those who belong to not_visited so dont belong to in_queue and visited
            {
                enqueue_graph(G,Q,j);
                *(G->state+j)=in_Queue;
            }
        }
        showQueue_graph(G,Q);
    }

    short flag=0;
    for (short i = 0; i < G->n; i++)
    {
        if (*(G->state+i)!=visited)
        {
            flag++;
        }
    }

    if (flag)
    {
        printf("\nError:\tBFS(%p,%hd)\nsome flags are not visited\n",G,start_index);
    }
    else
    {
        printf("\nSuccess:\tBFS(%p,%hd)\nAll flags are visited\n",G,start_index);
    }
    Q=deconstruct_queue(Q);
}

bool reset_graph_matrix(Graph * G)
{
    if (G==NULL)
    {
        printf("\ngraph is null\n");
        return true;
    }
    for (short i = 0; i < G->n*G->n; i++)
    {
        *(G->matrix+i)=0;
    }
    return false;
}