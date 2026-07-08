CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
SRCS     := $(wildcard *.cpp)
TARGET   := shell

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
