#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unit_map.h"

/* test names */
const char* tests[UNIT_MAP_NUM_TESTS] = {
    "test_map_init_normal",
    "test_map_init_null_params",
    "test_map_free_normal",
    "test_map_free_null_params",
    "test_map_get_normal",
    "test_map_get_null_params",
    "test_map_get_not_found",
    "test_map_set_normal",
    "test_map_set_null_params",
    "test_map_remove_normal",
    "test_map_remove_null_params",
    "test_map_remove_not_found",
    "test_map_size_normal",
    "test_map_size_null_params",
    "test_map_size_zero",
    "test_map_key_in_normal",
    "test_map_key_in_null_params",
    "test_map_key_in_not_found",
    "test_map_value_in_normal",
    "test_map_value_in_null_params",
    "test_map_value_in_not_found",
    "test_map_clear_normal",
    "test_map_clear_null_params",
};

int main(void)
{
    unsigned int t = 0;
    bool results[UNIT_MAP_NUM_TESTS];
    memset(results, 0, sizeof(bool) * UNIT_MAP_NUM_TESTS);

    results[t] = test_map_init_normal();
    t++;
    results[t] = test_map_init_null_params();
    t++;

    results[t] = test_map_free_normal();
    t++;
    results[t] = test_map_free_null_params();
    t++;

    results[t] = test_map_get_normal();
    t++;
    results[t] = test_map_get_null_params();
    t++;
    results[t] = test_map_get_not_found();
    t++;

    results[t] = test_map_set_normal();
    t++;
    results[t] = test_map_set_null_params();
    t++;

    results[t] = test_map_remove_normal();
    t++;
    results[t] = test_map_remove_null_params();
    t++;
    results[t] = test_map_remove_not_found();
    t++;

    results[t] = test_map_size_normal();
    t++;
    results[t] = test_map_size_null_params();
    t++;
    results[t] = test_map_size_zero();
    t++;

    results[t] = test_map_key_in_normal();
    t++;
    results[t] = test_map_key_in_null_params();
    t++;
    results[t] = test_map_key_in_not_found();
    t++;

    results[t] = test_map_value_in_normal();
    t++;
    results[t] = test_map_value_in_null_params();
    t++;
    results[t] = test_map_value_in_not_found();
    t++;

    results[t] = test_map_clear_normal();
    t++;
    results[t] = test_map_clear_null_params();
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
