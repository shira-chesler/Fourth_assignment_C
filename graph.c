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
            pointer = new;
            available_space = RESIZE_SIZE;
        }
        pointer[place_in_array] = cur;
        available_space--;
        place_in_array++;
        cur = fgetc(stdin);

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
        free(str);
        return 'Z';
    }
    else
    {
        char a= str[0];
        free(str);
        return a;
    }
    
}

int read_int(char* str)
{
    int x = 0;
    //x = atoi(str);
    sscanf(str,"%d",&x);
    //x = str[0]-'0';
    free(str);
    return x;
}

int exists(pnode *head, int node)
{
    pnode* cur_node = head;
    int i = 1;
    while ((*cur_node))
    {
        if ((*cur_node)->node_num==node)
        {
            return i;
        }
        i++;
        cur_node = &((*cur_node)->next);
        
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
    to_node->edges = NULL;
    to_node->Dijkstra_distance = __INT_MAX__;
    (*cur_node)->next = to_node;
}

pnode find_node(pnode *head, int node_num)
{
    pnode* cur_node = head;
    while (*cur_node)
    {
        if ((*cur_node)->node_num==node_num)
        {
            return *cur_node;
        }
        cur_node=&((*cur_node)->next);
        
    }
    return NULL;
}

char* insert_new_node(pnode *head, int node_num)
{
    pnode* cur_node = head;
    if (exists(head,node_num))
    {
        return insert_edges(find_node(head,node_num), head);
    }
    while ((*cur_node)!=NULL && (*cur_node)->next)
    {
        cur_node = &((*cur_node)->next);
    }
    pnode new_node = (pnode)malloc(sizeof(node));
    if (!new_node)
    {
        printf("error occured during malloc");
    }
    new_node->node_num = node_num;
    new_node->next=NULL;
    new_node->Dijkstra_distance = __INT_MAX__;
    if (*cur_node==NULL)
    {
        *cur_node = new_node;
    }
    else
    {
        (*cur_node)->next = new_node;
    }
    return insert_edges(new_node, head);
    
}

char build_graph_cmd(pnode *head)
{
    //0 2 3 n 5 2
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
            free(cur_input);
            cur_input = read_next_input();
        }
    }
}

void del_edges(pedge edges)
{
    pedge cur=edges;
    pedge prev=NULL;
    while (cur!=NULL && cur->next)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    free(cur);
}

char* insert_edges(pnode node, pnode *head)
{
    pedge* cur_edge= NULL;
    char* cur_input = read_next_input();
    while (1)
    {
        if (is_cmd(cur_input))
        {
            return cur_input;
        }
        if (cur_input[0]=='n')
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
                new_edge->next=NULL;
                new_edge->weight = weight;
                if (!exists(head, other_node)) 
                {
                    create_node(head, other_node); 
                }
                new_edge->endpoint = find_node(head, other_node); 
                node->edges = new_edge;
                cur_edge = &(node->edges);
            }
            else
            {
                pedge new_edge = (pedge)malloc(sizeof(edge));
                if (!new_edge)
                {
                    printf("error occured during malloc");
                }
                new_edge->next=NULL;
                new_edge->weight = weight;
                if (!exists(head, other_node)) 
                {
                    create_node(head, other_node);
                }
                new_edge->endpoint = find_node(head, other_node);
                (*cur_edge)->next= new_edge;
                cur_edge = &((*cur_edge)->next);
            }
            
        }
        cur_input = read_next_input();
    }
}

char insert_node_cmd(pnode *head)
{
    int node_value = read_int(read_next_input());
    if (exists(head, node_value))
    {
        pnode nodepointer = find_node(head, node_value);
        del_edges(nodepointer->edges);
        return get_cmd(insert_edges(nodepointer, head));
    }
    else
    {
        return get_cmd(insert_new_node(head, node_value));
    }
    
    
}

void delete_edge_to_node(pnode node, int node_num_to_delete_edge_to)
{
    pedge cur = node->edges;
    pedge prev = node->edges;
    while (cur)
    {
        if (cur->endpoint->node_num==node_num_to_delete_edge_to)
        {
            if (cur==prev)
            {
                node->edges=cur->next;
                cur->next=NULL;
                cur->weight=0;
            }
            else
            {
                prev->next = cur->next;
            }
            free(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    
}

void delete_node_cmd(pnode *head)
{
    int value = read_int(read_next_input());
    int placement_in_graph = exists(head, value);
    pnode cur = *head;
    while (cur)
    {
        if (cur->node_num==value)
        {
            cur = cur->next;
            continue;
        }
        delete_edge_to_node(cur, value);
        cur = cur->next;
    }
    if ((*head)->node_num==value)
    {
        pnode to_delete = *head;
        *head = (*head)->next;
        del_edges((to_delete)->edges);
        free(to_delete);
    }
    else
    {
        int i=2;
        pnode prev = *head;
        pnode cur = prev->next;
        while (i<placement_in_graph)
        {
            prev = cur;
            cur = cur->next;
            i++;
        }
        prev->next = cur->next;
        del_edges(cur->edges);
        free(cur);
        
    } 
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
            //printf("%d\n", cure->weight);
            //printf("%d\n", cure->endpoint->node_num);
            printf("    Edge no' %d; to vertic: %d, weight: %d\n", i, cure->endpoint->node_num, cure->weight);
            cure = cure->next;
            i++;
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

void initialize_Dijkstra_distance(pnode head, int source_value)
{
    pnode cur = head;
    while (cur)
    {
        if (cur->node_num==source_value)
        {
            cur->Dijkstra_distance = 0;
        }
        else
        {
            cur->Dijkstra_distance = __INT_MAX__/2;
        }
        cur = cur->next;
    }
    
}

int in_queue(pqueue head_of_q, int node_to_check)
{
    
    pqueue cur_pointer = head_of_q;
    int i = 1;
    while (cur_pointer)
    {
        if (cur_pointer->node_to->node_num==node_to_check)
        {
            return i;
        }
        i++;
        cur_pointer = cur_pointer->next;
        
    }
    return 0;
}

void remove_from_q(pqueue *head_of_queue,int placement_in_queue)
{
    if (placement_in_queue==1)
    {
        pqueue to_remove = *head_of_queue;
        (*head_of_queue) = to_remove->next;
        free(to_remove);
    }
    else
    {
        int i=2;
        pqueue cur = (*head_of_queue)->next;
        pqueue prev = (*head_of_queue);
        while (i<placement_in_queue)
        {
            prev = cur;
            cur = cur->next;
            i++;
        }
        prev->next=cur->next;
        free(cur);   
    }
    
}

void insert_to_priority_q(pqueue *head_of_q, pnode node_to_insert)
{
    pqueue* cur = head_of_q;
    if (!(*cur)) //q is empty
    {
        pqueue first = (pqueue) malloc(sizeof(queue));
        if (!first)
        {
            printf("problem during malloc");
            return;
        }
        (*head_of_q) = first;
        first->next = NULL;
        first->node_to = node_to_insert;
    }
    else
    {
        int placement_in_queue = in_queue((*cur), node_to_insert->node_num);
        if (placement_in_queue)
        {
            remove_from_q(head_of_q, placement_in_queue);
        }
        pqueue new = (pqueue) malloc(sizeof(queue));
        if (!new)
        {
            printf("problem during malloc");
            return;
        }
        new->next = NULL;
        new->node_to = node_to_insert;
        pqueue curcur = (*cur);
        pqueue prev = (*cur);
        while (curcur!=NULL && new->node_to->Dijkstra_distance>=curcur->node_to->Dijkstra_distance)
        {
            prev = curcur;
            curcur = curcur->next;
        }
        if ((*cur)==prev)//need to insert at head of q, cur==head_of_q
        {
            *cur=new;
            new->next = prev;
        }
        else
        {
            prev->next = new;
            new->next = curcur;
        } 
    }
    
}

void dijkstra_from_source(pnode source)
{
    //pnode cur = source;
    pedge cur_edge = source->edges;
    pqueue q = NULL;
    while (cur_edge)
    {
        if (cur_edge->endpoint->Dijkstra_distance>source->Dijkstra_distance+cur_edge->weight)
        {
            cur_edge->endpoint->Dijkstra_distance = source->Dijkstra_distance+cur_edge->weight;
            insert_to_priority_q(&q, cur_edge->endpoint);//
        }
        cur_edge = cur_edge->next;
    }
    pqueue cur = q;
    pqueue prev = NULL;
    while (cur)
    {
        cur_edge = cur->node_to->edges;
        while (cur_edge)
        {
            if (cur_edge->endpoint->Dijkstra_distance>cur->node_to->Dijkstra_distance+cur_edge->weight)
            {
                cur_edge->endpoint->Dijkstra_distance = cur->node_to->Dijkstra_distance+cur_edge->weight;
                insert_to_priority_q(&q, cur_edge->endpoint);
            }
            cur_edge = cur_edge->next;
        }
        prev = cur;
        cur = cur->next;
        remove_from_q(&q, in_queue(q, prev->node_to->node_num));//
    }
    
    
}

int shortsPath_cmd(pnode head, int source, int destination)
{
    initialize_Dijkstra_distance(head, source);
    pnode src = find_node(&head, source);
    dijkstra_from_source(src);
    int dijkstra_of_dest = find_node(&head, destination)->Dijkstra_distance;
    return dijkstra_of_dest;    
}

void TSP_cmd(pnode head)
{
    int k = read_int(read_next_input());
    int **n_matrix = (int**) calloc(k+1, sizeof(int*));
    for (int i = 0; i < k+1; i++)
    {
        n_matrix[i] = (int*) calloc((k+1),sizeof(int));
    }
    for (int i = 1; i < k+1; i++)
    {
        n_matrix[0][i] = read_int(read_next_input());
        n_matrix[i][0] = read_int(read_next_input());
    }
    for (int i = 1; i < k+1; i++)
    {
        shortsPath_cmd(head, n_matrix[0][i], n_matrix[0][i]);
        for (int j = 1; j < k+1; k++)
        {
            if (i==j)
            {
                continue;
            }
            else 
            {
                n_matrix[i][j] = find_node(&head, n_matrix[0][j])->Dijkstra_distance;
            }
            
        }
        
    }
    
    
}