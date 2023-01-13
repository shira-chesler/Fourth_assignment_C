#include <stdio.h>
#include "graph.h"

int main()
{
    char cur;
    cur = fgetc(stdin);
    pnode* head = NULL;
    while (cur != EOF)
    {
        if (cur=='A')
        {
            if (head!=NULL)
            {
                deleteGraph_cmd(head);
            }
            build_graph_cmd(head);

        }
        if (cur=='B')
        {
            insert_node_cmd(head);
        }
        if (cur=='D')
        {
            delete_node_cmd(head);
        }
        if (cur=='S')
        {
            shortsPath_cmd(head);
        }
        if (cur=='T')
        {
            TSP_cmd(head);
        }
        
        
        
    }
    
}