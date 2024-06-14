#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Queue.h"
#include "Graph.h"
#include "command_tree.h"
int main(int argc, char const *argv[])
{
    system("cls");
    printf("\nsupermanyousefi@gmail.com\nNO WARRANTY! \nwe suggest using online compilers.\nthis program is full of bugs and can drop into INFINITE LOOPS.\nThis can over heat your system. \nwe DO NOT take responsiblity.\n");

    Command_node * C;
    C=insert_string(C,"show_graph_matrix",1);
    C=insert_string(C,"add_edge",2);
    C=insert_string(C,"check_graph",3);
    C=insert_string(C,"BFS",4);
    C=insert_string(C,"dijkstra",5);
    C=insert_string(C,"help",6);
    C=insert_string(C,"remove_edge",7);
    C=insert_string(C,"clear",8);
    C=insert_string(C,"rest_graph_matrix",9);
    C=insert_string(C,"exit",0);
    
    short n;
    Graph * G=NULL;
    do
    {
        //system("cls");
        printf("\nnon-valid number(!)\nGraph is n*n\nEnter n:");
        scanf("%hd",&n);
        G=construct_Graph(n);
    } while (n < 2 || n>16);

    char * name=(char *)malloc(n*sizeof(char));
    {
        char a;bool score=0;
        for (short i = 0; i < n; i++)
        {
            if(a!=10)
            {
                printf("\ncharacter must be \"A to Z\" or \"a to z\" or \"_\"\n");
                printf("a character for vertex(%hd):",i);
            }

            scanf("%c",&a);
            if (check_char(a))
            {
                i--;
                continue;
            }
            bool flag=false;
            for (short j = 0; j <= i; j++)
            {
                if(a == *(name+j))
                {
                    flag=true;
                    break;
                }
            }
            if (flag)
            {
                i--;
                continue;
            }
            *(name+i)=a;
        }
    }

    G->name=name;
    char command[25],a;
    short key=0,i1,i2,weight;
    system("cls");
    printf("\nsupermanyousefi@gmail.com\nNO WARRANTY! \nwe suggest using online compilers.\nthis program is full of bugs and can drop into INFINITE LOOPS.\nThis can over heat your system. \nwe DO NOT take responsiblity.\n");
    printf("\ntype \"help\" to list commands\n");
    do
    {
        printf("\nCOMMAND>>");
        scanf("%s",command);
        key = command_output(C,command);
        //system("cls");
        switch (key)
        {
        case 1:
            show_graph_matrix(G);
            break;
        case 2:

            do
            {
                //system("cls");
                if(a!=10)printf("vertex 1:");
                scanf("%c",&a);
            } while (check_char(a));
            i1=-1;
            for (short i = 0; i < n; i++)
            {
                if (a == *(name+i)){i1=i;break;}
            }
            if (i1 == -1)
            {
                printf("\nvertex(%c) does not exist\n",a);
                break;
            }
            do
            {
                //system("cls");
                if(a!=10)printf("vertex 2:");
                scanf("%c",&a);
            } while (check_char(a));
            i2=-1;
            for (short i = 0; i < n; i++)
            {
                if (a == *(name+i)){i2=i;break;}
            }
            if (i2 == -1)
            {
                printf("\nvertex(%c) does not exist\n",a);
                break;
            }
            printf("weight:");
            scanf("%hd",&weight);
            add_edge(G,i1,i2,weight);
            break;
        case 3:
            check_graph(G);
            break;
        case 4:

            do
            {
                //system("cls");
                if(a!=10)printf("start vertex:");
                scanf("%c",&a);
            } while (check_char(a));
            i1=-1;
            for (short i = 0; i < n; i++)
            {
                if (a == *(name+i)){i1=i;break;}
            }
            if (i1 == -1)
            {
                printf("\nvertex(%c) does not exist\n",a);
                break;
            }
            BFS(G,i1);
            break;
        case 5:

            do
            {
                //system("cls");
                if(a!=10)printf("vertex 1:");
                scanf("%c",&a);
            } while (check_char(a));
            i1=-1;
            for (short i = 0; i < n; i++)
            {
                if (a == *(name+i)){i1=i;break;}
            }
            if (i1 == -1)
            {
                printf("\nvertex(%c) does not exist\n",a);
                break;
            }
            show_the_way(G,dijkstra(G,i1));
            break;
        case 6:
            list_commands(C);
            break;
        case 7:
            do
            {
                //system("cls");
                if(a!=10)printf("vertex 1:");
                scanf("%c",&a);
            } while (check_char(a));
            i1=-1;
            for (short i = 0; i < n; i++)
            {
                if (a == *(name+i)){i1=i;break;}
            }
            if (i1 == -1)
            {
                printf("\nvertex(%c) does not exist\n",a);
                break;
            }
            do
            {
                //system("cls");
                if(a!=10)printf("vertex 2:");
                scanf("%c",&a);
            } while (check_char(a));
            i2=-1;
            for (short i = 0; i < n; i++)
            {
                if (a == *(name+i)){i2=i;break;}
            }
            if (i2 == -1)
            {
                printf("\nvertex(%c) does not exist\n",a);
                break;
            }
            remove_edge(G,i1,i2);
            break;
        case 8:
            system("cls");
            break;
        case 9:
            reset_graph_matrix(G);
            break;

        }
    } while (key);
    
    
    return 0;
}
