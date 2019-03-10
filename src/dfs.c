#include <stdlib.h>
#include <stdint.h>

#include "constants.h"
#include "list.h"
#include "stack.h"
#include "digraph.h"
#include "macros.h"
#include "dfs.h"

unsigned int dfs_digraph(List* walk, unsigned int root, Digraph* digraph)
{
    if(walk == NULL || digraph == NULL) /* null guard */
    {
        return JCRL_ERR_NULL_PARAM;
    }

    if(root >= digraph->v) /* bounds check */
    {
        return JCRL_ERR_OUT_OF_BOUNDS;
    }

    Stack S; /* stack for storing vertices to be processed */
    unsigned int res = stack_init(&S);
    PASS_UP_ON_FAIL(res);

    Set found_set; /* set of all discovered vertices */
    res = set_init(&found_set);
    PASS_UP_ON_FAIL(res);

    unsigned int v = root;

    res = stack_push(G_INT(v), &S);
    PASS_UP_ON_FAIL(res);

    unsigned int depth = 0;
    res = stack_depth(&depth, &S);
    PASS_UP_ON_FAIL(res);

    bool already_found = false;

    while(depth > 0)
    {
        /* pop vertex, v, off of stack, S */
        res = stack_pop(&v, &S);
        PASS_UP_ON_FAIL(res);

        /* check to see if v is already discovered */
        res = set_in(&already_found, G_INT(v), &found_set);
        PASS_UP_ON_FAIL(res);

        Set neighbours;
        List neighbours_list;

        if(!already_found) /* if v is not yet discovered */
        {
            /* add v to the set of all discovered vertices */
            res = set_add(G_INT(v), &found_set);
            PASS_UP_ON_FAIL(res);

            /* add v to the output walk */
            res = list_append(G_INT(v), walk);
            PASS_UP_ON_FAIL(res);

            /* initialise data structures */
            res = set_init(&neighbours);
            PASS_UP_ON_FAIL(res);

            res = digraph_out_neighbours(&neighbours, v, digraph);
            PASS_UP_ON_FAIL(res);

            res = list_init(&neighbours_list);
            PASS_UP_ON_FAIL(res);

            /* convert set to list */
            res = set_enumerate(&neighbours_list, &neighbours);
            PASS_UP_ON_FAIL(res);

            /* get number of neighbours */
            unsigned int num_neighbours = 0;

            res = list_length(&num_neighbours, &neighbours_list);
            PASS_UP_ON_FAIL(res);

            unsigned long w = 0; /* store neighbour's vertex number */

            /* traverse list of all edges incident to v */
            for(int i=num_neighbours-1;i>=0;i--)
            {
                /* get neighbour */
                res = list_get((void**)&w, i, &neighbours_list);
                PASS_UP_ON_FAIL(res);

                /* push vertex onto stack */
                res = stack_push(G_INT(w), &S);
                PASS_UP_ON_FAIL(res);
            }

            /* free local data structures */
            res = set_free(NULL, &neighbours);
            PASS_UP_ON_FAIL(res);

            res = list_free(NULL, &neighbours_list);
            PASS_UP_ON_FAIL(res);
        }

        /* update stack depth */
        res = stack_depth(&depth, &S);

        PASS_UP_ON_FAIL(res);
    }

    /* free stack */
    res = stack_free(NULL, &S);
    PASS_UP_ON_FAIL(res);

    /* free set of discovered vertices */
    res = set_free(NULL, &found_set);
    PASS_UP_ON_FAIL(res);

    return JCRL_ERR_OK;
}
