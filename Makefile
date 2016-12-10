PROJ_NAME = jcrl
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests/unit
CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -pedantic-errors -std=c11

$(PROJ_NAME):
	$(CC) -c $(SRC_DIR)/*.c $(CFLAGS) -g
	mv *.o $(BUILD_DIR)
	ar -cvq $(BUILD_DIR)/lib$(PROJ_NAME).a $(BUILD_DIR)/*.o
	ar -t $(BUILD_DIR)/lib$(PROJ_NAME).a

test_sources:= $(wildcard $(TEST_DIR)/*.c)
test_executables:= $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(test_sources))

#$(BUILD_DIR)/%: $(TEST_DIR)/%.c
#	$(CC) $< -o $@ $(CFLAGS) -g -I$(SRC_DIR) -L$(BUILD_DIR) -ljcrl

.PHONY: tests
#tests: $(test_executables)
tests:
	# singly-linked list
	$(CC) $(TEST_DIR)/unit_slist.c $(TEST_DIR)/test_slist.c $(CFLAGS) -g -I$(SRC_DIR) -L$(BUILD_DIR) -ljcrl -o $(BUILD_DIR)/test_slist
    
    	# singly-linked list
	$(CC) $(TEST_DIR)/unit_dlist.c $(TEST_DIR)/test_dlist.c $(CFLAGS) -g -I$(SRC_DIR) -L$(BUILD_DIR) -ljcrl -o $(BUILD_DIR)/test_dlist
    
    	# stack
	$(CC) $(TEST_DIR)/unit_stack.c $(TEST_DIR)/test_stack.c $(CFLAGS) -g -I$(SRC_DIR) -L$(BUILD_DIR) -ljcrl -o $(BUILD_DIR)/test_stack
    
    	# queue
	$(CC) $(TEST_DIR)/unit_queue.c $(TEST_DIR)/test_queue.c $(CFLAGS) -g -I$(SRC_DIR) -L$(BUILD_DIR) -ljcrl -o $(BUILD_DIR)/test_queue

	# bubblesort
	$(CC) $(TEST_DIR)/unit_bubblesort.c $(TEST_DIR)/test_bubblesort.c $(CFLAGS) -g -I$(SRC_DIR) -L $(BUILD_DIR) -ljcrl -o $(BUILD_DIR)/test_bubblesort

.PHONY: clean
clean:
	rm $(BUILD_DIR)/* -r

