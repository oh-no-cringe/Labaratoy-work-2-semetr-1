CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Isrc
SRC      := $(shell find src -name '*.cpp')
OBJ      := $(patsubst src/%.cpp, build/%.o, $(SRC))
BIN      := build/dbms

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN) --file data/file.data --query '$(Q)'

clean:
	rm -rf build

.PHONY: all run clean