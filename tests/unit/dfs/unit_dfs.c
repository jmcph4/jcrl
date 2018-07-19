#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "macros.h"
#include "list.h"
#include "digraph.h"
#include "dfs.h"

#include "unit_dfs.h"

bool test_dfs_digraph_normal(void)
{
    bool pass = false;
    
    unsigned int n = 12;
    unsigned int v[n];
    unsigned int e = 0;

    Digraph d;
    digraph_init(&d);

    for(unsigned int i=1;i<=n;i++)
    {
        digraph_vertex_insert(G_INT(i), &v[i-1], &d);
    }

    /* create edges */
    digraph_connect(G_INT(0), 1, 2, &e, &d);
    digraph_connect(G_INT(0), 2, 3, &e, &d);
    digraph_connect(G_INT(0), 3, 4, &e, &d);
    digraph_connect(G_INT(0), 3, 5, &e, &d);
    digraph_connect(G_INT(0), 2, 6, &e, &d);
    digraph_connect(G_INT(0), 1, 7, &e, &d);
    digraph_connect(G_INT(0), 1, 8, &e, &d);
    digraph_connect(G_INT(0), 8, 12, &e, &d);
    digraph_connect(G_INT(0), 8, 9, &e, &d);
    digraph_connect(G_INT(0), 9, 10, &e, &d);
    digraph_connect(G_INT(0), 9, 11, &e, &d);

    List expected;
    list_init(&expected);

    for(unsigned int i=1;i<n;i++)
    {
        list_append(G_INT(i), &expected);
    }

    List actual;
    list_init(&actual);

    unsigned int res = dfs_digraph(&actual, 1, &d);

    bool equal = false;
    list_equal(&equal, &actual, &expected);

    list_free(NULL, &actual);
    list_free(NULL, &expected);
    digraph_free(NULL, &d);

    if(res == JCRL_ERR_OK && equal)
    {
        pass = true;
    }

    return pass;
}

bool test_dfs_digraph_null_params(void)
{
    bool pass = false;

    unsigned int res = dfs_digraph(NULL, 0, NULL);

    if(res == JCRL_ERR_NULL_PARAM)
    {
        pass = true;
    }

    return pass;
}

bool test_dfs_digraph_out_of_bounds(void)
{
    bool pass = false;

    Digraph d;
    digraph_init(&d);

    /* arbitrary data for insertion */
    unsigned int a = 12;
    unsigned int b = 33;

    /* vertex numbers */
    unsigned int v_1 = 0;
    unsigned int v_2 = 0;

    digraph_vertex_insert(G_INT(a), &v_1, &d);
    digraph_vertex_insert(G_INT(b), &v_2, &d);

    List output;
    list_init(&output);

    unsigned int res = dfs_digraph(&output, v_2 + 1, &d);

    list_free(NULL, &output);
    digraph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

bool test_dfs_digraph_empty(void)
{
    bool pass = false;
 
    Digraph d;
    digraph_init(&d);

    List output;
    list_init(&output);

    unsigned int res = dfs_digraph(&output, 0, &d);

    list_free(NULL, &output);
    digraph_free(NULL, &d);

    if(res == JCRL_ERR_OUT_OF_BOUNDS)
    {
        pass = true;
    }

    return pass;
}

