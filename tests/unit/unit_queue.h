/*
 * unit_queue.h
 *
 * Declarations of unit tests for the queue implementation. For unit test
 * definitions, see unit_queue.c.
*/
#include "queue.h"

#define UNIT_QUEUE_NUM_TESTS 21

/* Initialisation */
bool test_queue_init_normal(void);
bool test_queue_init_null_params(void);

bool test_queue_free_normal(void);
bool test_queue_free_null_params(void);
bool test_queue_free_empty_queue(void);

/* Equality */
bool test_queue_equal_normal(void);
bool test_queue_equal_null_params(void);
bool test_queue_equal_unequal_queues(void);
bool test_queue_equal_same_queues(void);

/* Access */
bool test_queue_peek_normal(void);
bool test_queue_peek_null_params(void);
bool test_queue_peek_empty_queue(void);

bool test_queue_length_normal(void);
bool test_queue_length_null_params(void);
bool test_queue_length_empty_queue(void);

/* Operations */
bool test_queue_push_normal(void);
bool test_queue_push_null_params(void);
bool test_queue_push_empty_queue(void);

bool test_queue_pop_normal(void);
bool test_queue_pop_null_params(void);
bool test_queue_pop_empty_queue(void);
