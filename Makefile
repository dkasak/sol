.PHONY: all optimized debug clean distclean dbmp test
CFLAGS   := -std=c99 -Wextra -Wall -I include/ -pedantic
CXXFLAGS := -std=c++11 -Wextra -Wall -I include/ -pedantic -Wuninitialized \
            -Wno-reorder -Wno-unused-parameter
LDFLAGS  := -lm -lstdc++

EXE         := sol
SRC_DIR     := src
INCLUDE_DIR := include
OBJ_DIR     := obj
BUILD_DIR   := build

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) \
             $(OBJ_DIR)/dbmp.o $(OBJ_DIR)/sol.o
SRC_FILES += $(SRC_DIR)/dbmp.c

MKDIR := mkdir -p $(OBJ_DIR) $(BUILD_DIR)

all: debug

sol: $(OBJ_FILES) | $(BUILD_DIR)
	$(CXX) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	$(MKDIR)

$(BUILD_DIR):
	$(MKDIR)

$(OBJ_DIR)/sol.o: sol.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

dbmp: $(OBJ_DIR)/dbmp.o
$(OBJ_DIR)/dbmp.o: $(SRC_DIR)/dbmp.c

optimized: CXXFLAGS += -O2
optimized: CFLAGS += -O2
optimized: sol

debug: CXXFLAGS += -Og -g
debug: CFLAGS += -Og -g
debug: sol

TESTS := $(addprefix $(BUILD_DIR)/,test_write test_load test_vector)

test: $(TESTS)
	$(BUILD_DIR)/test_write
	$(BUILD_DIR)/test_load
	$(BUILD_DIR)/test_vector

$(BUILD_DIR)/test_write: $(OBJ_DIR)/test_write.o $(OBJ_DIR)/dbmp.o
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/test_load: $(OBJ_DIR)/test_load.o $(OBJ_DIR)/dbmp.o
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/test_vector: $(OBJ_DIR)/test_vector.o $(OBJ_DIR)/Vector.o
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/test_vector.o: tests/test_vector.cpp | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test_load.o: tests/test_load.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test_write.o: tests/test_write.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	-rm -rf obj/ build/

distclean: clean
	-rm -rf *.bmp

run: optimized
	./sol
	sxiv output.bmp
