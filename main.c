#include <stdio.h>
#include "graph.h"

int main()
{
    char* cur;
    cur = read_next_input();
    char cmd = get_cmd(cur);
    pnode* p=NULL;
    while (cmd != 'Z')
    {
        if (cmd=='A')
        {
            if (p!=NULL)
            {
                deleteGraph_cmd(p);
            }
            cmd = build_graph_cmd(p);
            printGraph_cmd(*p);

        }
        if (cmd=='B')
        {
            cmd = insert_node_cmd(p);
        }
        if (cmd=='D')
        {
            delete_node_cmd(p);
            cmd = get_cmd(read_next_input());
        }
        if (cmd=='S')
        {
            shortsPath_cmd(*p);
        }
        if (cmd=='T')
        {
            TSP_cmd(*p);
        }
        
        
        
    }
    
}