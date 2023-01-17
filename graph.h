#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int Dijkstra_distance;
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

typedef struct queue_
{
    pnode node_to;
    struct queue_ *next;
} queue, *pqueue;


char* read_next_input();
int is_cmd(char* str);
char get_cmd(char* str);
int read_int(char* str);
int exists(pnode *head, int node);
void create_node(pnode *head, int node_num);
pnode find_node(pnode *head, int node_num);
char* insert_new_node(pnode *head, int node_num);
void del_edges(pedge edges);
char* insert_edges(pnode node, pnode *head);
void delete_edge_to_node(pnode node, int node_num_to_delete_edge_to);
void rough_delete(pnode pointer);
char build_graph_cmd(pnode *head);
char insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
int shortsPath_cmd(pnode head, int source, int destination);
void TSP_cmd(pnode head);

#endif
