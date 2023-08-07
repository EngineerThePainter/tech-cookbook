CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -O3 -g
LIBS := -lprotobuf -labsl_log_internal_proto -labsl_log_internal_check_op -labsl_log_internal_message

SRC := main.cpp ../proto/addressbook.pb.cc
TARGET := reader

all: $(TARGET)
.PHONY: all clean

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)