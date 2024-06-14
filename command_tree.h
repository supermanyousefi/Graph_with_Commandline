#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

struct command_tree
{   char data; 
    short output; 
    struct command_tree * left,*bottom,*right;
};

typedef struct command_tree Command_node;

Command_node * construct_Command_node(char data,short output)
{
    Command_node * N = (Command_node *)malloc(sizeof(Command_node));if(N==NULL) return NULL;
    N->data=data;
    N->output=output;
    N->left=NULL;N->bottom=NULL;N->right= NULL;
    return N;
}

Command_node ** insert_char(Command_node ** head,char data,short output)//returns address of the bottom of the created Command_node 
{
    if (*head == NULL) 
    {
        Command_node * X = construct_Command_node(data,output);if(X==NULL) return NULL;
        *head=X ;
        return &(X->bottom);
    }
    if (data < (*head)->data) return insert_char(&((*head)->left),data,output);
    if (data > (*head)->data) return insert_char(&((*head)->right),data,output);
    if (data == (*head)->data)return &((*head)->bottom);
}

bool check_char(char a)//returns true in case of error
{
    bool score=false;//score of error
        score+=(a >= 'A')&&(a<= 'Z');
        score+=(a >= 'a')&&(a <= 'z');
        score+=(a == '_');
        return !score;
}
Command_node * insert_string(Command_node * head,char command[],short output)//must be assigned to itself
{
    if (command == NULL) return head;
    bool score=false;
    short n=0;
    //checks if non valid character exists
    for (n = 0; command[n]!='\0'; n++)
    {
        if (check_char(command[n]))
        {
            printf("\nwrong character in command string\ncommand must only contain alphabets or underscore\n");
            return head;
        }
    }
    if (n > 31)
    {
        printf("\nERROR: insert_string(%p,%s,%hd)\ncommand length must not be more than 30 characters.\n",head,command,output);
        return head;
    }
    
    Command_node ** temp=&head;short i;
    for (i = 0; i < n-1; i++)
    {
        temp=insert_char(temp,command[i],-1);
    }
    if ((*temp)!=NULL)
    {
        if (((*temp)->data == command[i])&&((*temp)->output > -1))
        {
            printf("\nERROR:command exists\n");
            return head;
        }
        
    }
    temp=insert_char(temp,command[i],output);
    return head;
}

void list_commands_rec(Command_node * head,char buffer[],short index)
{
    if (head == NULL)return;
    list_commands_rec(head->left,buffer,index);
    buffer[index]=head->data;
    if (head->output > -1)
    {
        buffer[index+1]='\0';
        printf("%s\n",buffer);
    }
    
    list_commands_rec(head->bottom,buffer,index+1);
    list_commands_rec(head->right,buffer,index);

}

void list_commands(Command_node * head)
{
    if (head == NULL)return;
    char buffer[31];short index=0;
    list_commands_rec(head,buffer,index);
    
}
Command_node * search(Command_node * head,char data)
{
    if(head == NULL)return NULL;
    if (data > head->data)return search(head->right,data);
    if (data < head->data)return search(head->left,data);
    return head;//in case of equality
}

short command_output(Command_node * h,char command[])
{
    if(h==NULL)return -1;
    short i;
    for ( i = 0; command[i+1]!='\0'; i++)
    {
        h=search(h,command[i]);
        if (h == NULL)
        {
            printf("\n\"%s\" does not exist as a command\n",command);
            return -1;
        }
        h=h->bottom;
    }
    h=search(h,command[i]);
    if (h == NULL)
    {
        printf("\n%s does not exist as a command\n",command);
        return -1;
    }
    if (h->output==-1)
    {
        printf("\n%s does not exist as a command\n",command);
        return -1;
    }
    return h->output;

}


/*
int main(int argc, char const *argv[])
{
    Command_node * head;
    head=insert_string(head,"show_graph",1);
    head=insert_string(head,"add_edge",2);
    head=insert_string(head,"BFS",3);
    head=insert_string(head,"BFSG",3);
    head=insert_string(head,"BFSG",3);
    list_commands(head,1);
    printf("%hd\n",command_output(head,"BFS"));
    printf("%hd\n",command_output(head,"BFSG"));
    printf("%hd\n",command_output(head,"add_edge"));
    printf("%hd\n",command_output(head,"add_edges"));
    
    return 0;
}
*/
