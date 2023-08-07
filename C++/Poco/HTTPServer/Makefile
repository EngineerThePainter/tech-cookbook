CXX := clang++
CPP_FLAGS := -Wall -Wextra -O2
LIBS := -lPocoFoundation -lPocoUtil -lPocoNet
SRC := main.cpp
TARGET := http_server

.PHONY: all clean

all: $(TARGET)
$(TARGET) : $(SRC)
	$(CXX) $(CPP_FLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGET)