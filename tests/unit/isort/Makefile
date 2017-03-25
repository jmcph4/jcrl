ROOT_DIR = ../../..

include $(ROOT_DIR)/make_vars

TEST_NAME = isort

$(BUILD_DIR)/test_$(TEST_NAME): *.h *.c
	$(CC) $^ $(UNIT_TEST_CFLAGS) -o $@

