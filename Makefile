ROOT_DIR = .

include $(ROOT_DIR)/make_vars

$(BUILD_DIR)/$(PROJ_NAME):
	cd $(SRC_DIR); make

.PHONY: debug
debug:
	cd $(SRC_DIR); make debug
	cd $(UNIT_TESTS_DIR); make


.PHONY: clean
clean:
	rm $(BUILD_DIR)/* -r


