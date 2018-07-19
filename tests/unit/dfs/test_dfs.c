#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unit_dfs.h"

/* test names */
const char* tests[UNIT_DFS_NUM_TESTS] = {
    "test_dfs_digraph_normal",
    "test_dfs_digraph_null_params",
    "test_dfs_digraph_out_of_bounds",
    "test_dfs_digraph_empty"
};

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_DFS_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_DFS_NUM_TESTS);

    results[t] = test_dfs_digraph_normal();
    t++;
    results[t] = test_dfs_digraph_null_params();
    t++;
    results[t] = test_dfs_digraph_out_of_bounds();
    t++;
    results[t] = test_dfs_digraph_empty();
    t++;

    /* check for test failure */
    for(unsigned int i=0;i<t;i++)
    {
        if(results[i])
        {
            printf("TEST %s: PASS\n", tests[i]);
        }
        else
        {
            printf("!TEST %s: FAIL\n", tests[i]);
        }
    }
    return EXIT_SUCCESS;
}
