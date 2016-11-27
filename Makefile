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

.PHONY: clean
clean:
	rm $(BUILD_DIR)/* -r

