CXX := clang++
CPP_FLAGS := -Wall -Wextra -O2
LIBS := -lPocoFoundation
SRC := main.cpp
TARGET := delegates

.PHONY: all clean

all: $(TARGET)
$(TARGET) : $(SRC)
	$(CXX) $(CPP_FLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)