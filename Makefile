BLD_DIR 	= build
BIN_DIR 	= bin
SRC_DIR 	= src
TESTS_DIR 	= $(SRC_DIR)/tests
TESTS_BIN	= $(BIN_DIR)/vector_test \
			  $(BIN_DIR)/selection_sort_test \
			  $(BIN_DIR)/insertion_sort_test \
			  $(BIN_DIR)/merge_sort_test \
			  $(BIN_DIR)/heap_sort_test \
			  $(BIN_DIR)/quicksort_test \

CC 			= gcc
CFLAGS 		= -I$(SRC_DIR)

tests: mkdirs $(TESTS_BIN)

$(BIN_DIR)/%_test: $(TESTS_DIR)/%.c $(BLD_DIR)/vector.o $(BLD_DIR)/sort.o
	$(CC) $(CFLAGS) -o $@ $^

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: mkdirs
mkdirs:
	mkdir -p $(BLD_DIR) $(BIN_DIR)

.PHONY: clean
clean:
	rm -r $(BLD_DIR) $(BIN_DIR)
