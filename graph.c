#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RESIZE_SIZE 10

char* read_next_input()
{
    char* pointer = (char*) calloc(sizeof(char), RESIZE_SIZE);
    if (pointer==NULL)
    {
        printf("problem with calloc");
        return NULL; //problem with calloc
    }
    
    char cur;
    cur = fgetc(stdin);
    int cur_length = RESIZE_SIZE;
    int available_space = RESIZE_SIZE-1;
    int place_in_array = 0;
    while (cur!=' ' && cur!='\n' && cur!=EOF)
    {
        if (available_space==0)
        {
            cur_length = cur_length+RESIZE_SIZE;
            char* new = (char*) realloc(pointer, cur_length*sizeof(char));
            if (new==NULL)
            {
                return NULL; //problem with realloc
            }
            free(pointer);
            pointer = new;
            available_space = RESIZE_SIZE;
        }
        pointer[place_in_array] = cur;
        available_space--;
        place_in_array++;
    }
    pointer[place_in_array] = '\0';
    return pointer;
}

int is_cmd(char* str)
{
    if (strlen(str)>1)
    {
        return 0;
    }
    if (strlen(str)==0)
    {
        return 1;
    }
    else
    {
        if (str[0]>='A' && str[0]<='Z')
        {
            return 1;
        }
        return 0;
    }
}

char get_cmd(char* str)
{
    if (strlen(str)==0)
    {
        return 'Z';
    }
    else
    {
        return str[0];
    }
    
}

int read_int(char* str)
{
    return atoi(str);
}

int exists(pnode *head, int node)
{
    pnode* cur_node = head;
    while ((*cur_node)->next)
    {
        if ((*cur_node)->node_num==node)
        {
            return 1;
        }
        
    }
    return 0;
}

void create_node(pnode *head, int node_num)
{
    pnode* cur_node = head;
    while ((*cur_node)->next)
    {
        cur_node = &((*cur_node)->next);
    }
    pnode to_node = (pnode)malloc(sizeof(node));
    if (!to_node)
    {
        printf("error occured while malloc");
    }
    
    to_node->node_num = node_num;
    (*cur_node)->next = to_node;
}

pnode find_node(pnode *head, int node_num)
{
    pnode* cur_node = head;
    while ((*cur_node)->next)
    {
        if ((*cur_node)->node_num==node_num)
        {
            return *cur_node;
        }
        
    }
    return NULL;
}

char* insert_new_node(pnode *head, int node_num)
{
    pnode* cur_node = head;
    while ((*cur_node)->next)
    {
        cur_node = &((*cur_node)->next);
    }
    pnode new_node = (pnode)malloc(sizeof(node));
    if (!new_node)
    {
        printf("error occured during malloc");
    }
    new_node->node_num = node_num;
    (*cur_node)->next = new_node;
    //*cur_node = &new_node;
    return insert_edges(new_node, head);
    
}

char build_graph_cmd(pnode *head)
{
    char* cur_input = read_next_input();
    while (1)
    {
        if (is_cmd(cur_input))
        {
            return get_cmd(cur_input);
        }
        if (cur_input[0]=='n')
        {
            int main_node = read_int(read_next_input());
            cur_input = insert_new_node(head, main_node);
        }
        else
        {
            cur_input = read_next_input;
        }
    }
}

void del_edges(pedge edges)
{
    pedge cur=edges;
    pedge prev=NULL;
    while (cur->next)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    free(cur);
}

char insert_edges(pnode node, pnode *head)
{
    pedge* cur_edge= NULL;
    char* cur_input = read_next_input();
    while (1)
    {
        if (is_cmd(cur_input))
        {
            return cur_input;
        }
        else
        {
            int other_node = read_int(cur_input);
            int weight = read_int(read_next_input());
            if (!cur_edge)
            {
                pedge new_edge = (pedge)malloc(sizeof(edge));
                if (!new_edge)
                {
                    printf("error occured during malloc");
                }
                new_edge->weight = weight;
                if (!exists(head, other_node)) //!!!!!!!!!
                {
                    create_node(head, other_node); //!!!!!!!!!
                }
                new_edge->endpoint = find_node(head, other_node); //!!!!!!!!!
                cur_edge = &new_edge;
                node->edges = &new_edge;
            }
            pedge new_edge = (pedge)malloc(sizeof(edge));
            if (!new_edge)
            {
                printf("error occured during malloc");
            }
            
            new_edge->weight = weight;
            if (!exists(head, other_node)) 
            {
                create_node(*head, other_node);
            }
            new_edge->endpoint = find_node(head, other_node);
            (*cur_edge)->next= new_edge;
            cur_edge = &new_edge;
            
        }
        cur_input = read_next_input();
    }
}

char insert_node_cmd(pnode *head)
{
    int node_value = read_int(read_next_input());
    if (exist(head, node_value))
    {
        pnode nodepointer = find_node(head, node_value);
        del_edges(nodepointer->edges);
        return insert_edges(nodepointer, head);
    }
    else
    {
        return insert_new_node(head, node_value);
    }
    
    
}

void delete_node_cmd(pnode *head)
{
    
}
void printGraph_cmd(pnode head)
{
    pnode cur = head;
    while (cur)
    {
        printf("Node num: %d\n", cur->node_num);
        pedge cure = cur->edges;
        int i = 1;
        while(cure)
        {
            printf("    Edge no' %d is to vertic %d, ant the weight is %d\n", i, cure->endpoint->node_num, cure->weight);
            cure = cure->next;
        }
        cur = cur->next;
    }
    
}

void rough_delete(pnode pointer)
{
    del_edges(pointer->edges);
    free(pointer);
}

void deleteGraph_cmd(pnode* head)
{
    pnode *cur = head;
    pnode *prev;
    while ((*cur)->next)
    {
        prev = cur;
        cur = &((*cur)->next);
        rough_delete(*prev);
    }
    rough_delete(*cur);
}

void shortsPath_cmd(pnode head)
{

}
void TSP_cmd(pnode head)
{

}