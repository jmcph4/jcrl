ROOT_DIR = ../

include $(ROOT_DIR)/make_vars

$(BUILD_DIR)/$(PROJ_NAME):
	$(CC) -c $(SRC_DIR)/*.c $(REL_CFLAGS)
	mv *.o $(BUILD_DIR)
	ar -cvq $(BUILD_DIR)/lib$(PROJ_NAME).a $(BUILD_DIR)/*.o
	ar -t $(BUILD_DIR)/lib$(PROJ_NAME).a
	rm $(BUILD_DIR)/*.o


.PHONY: debug
debug:
	$(CC) -c $(SRC_DIR)/*.c $(DBG_CFLAGS)
	mv *.o $(BUILD_DIR)
	ar -cvq $(BUILD_DIR)/lib$(PROJ_NAME).a $(BUILD_DIR)/*.o
	ar -t $(BUILD_DIR)/lib$(PROJ_NAME).a

.PHONY: clean
clean:
	rm $(BUILD_DIR)/* -r

