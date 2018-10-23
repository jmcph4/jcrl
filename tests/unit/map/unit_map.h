#include <stdbool.h>

#define UNIT_MAP_NUM_TESTS 23

bool test_map_init_normal(void);
bool test_map_init_null_params(void);

bool test_map_free_normal(void);
bool test_map_free_null_params(void);

bool test_map_get_normal(void);
bool test_map_get_null_params(void);
bool test_map_get_not_found(void);

bool test_map_set_normal(void);
bool test_map_set_null_params(void);

bool test_map_remove_normal(void);
bool test_map_remove_null_params(void);
bool test_map_remove_not_found(void);

bool test_map_size_normal(void);
bool test_map_size_null_params(void);
bool test_map_size_zero(void);

bool test_map_key_in_normal(void);
bool test_map_key_in_null_params(void);
bool test_map_key_in_not_found(void);

bool test_map_value_in_normal(void);
bool test_map_value_in_null_params(void);
bool test_map_value_in_not_found(void);

bool test_map_clear_normal(void);
bool test_map_clear_null_params(void);

