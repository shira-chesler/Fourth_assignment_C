#include <stdio.h>
#include "graph.h"

int main()
{
    char* cur;
    cur = read_next_input();
    char cmd = get_cmd(cur);
    
    pnode p=NULL;
    while (cmd != 'Z')
    {
        if (cmd=='A')
        {
            if (p!=NULL)
            {
                deleteGraph_cmd(&p);
            }
            cmd = build_graph_cmd(&p);
            printGraph_cmd(p);
        }
        if (cmd=='B')
        {
            cmd = insert_node_cmd(&p);
            printGraph_cmd(p);
        }
        if (cmd=='D')
        {
            delete_node_cmd(&p);
            cmd = get_cmd(read_next_input());
            printGraph_cmd(p);
        }
        if (cmd=='S')
        {
            int dijkstra_dist_of_dest = shortsPath_cmd(p);
            if (dijkstra_dist_of_dest!=__INT_MAX__/2)
            {
                printf("Dijsktra shortest path: %d \n", dijkstra_dist_of_dest);
            }
            else
            {
                printf("Dijsktra shortest path: %d \n", -1);
            }
            cmd = get_cmd(read_next_input());
        }
        if (cmd=='T')
        {
            TSP_cmd(p);
        }
        
        
        
    }
    
}