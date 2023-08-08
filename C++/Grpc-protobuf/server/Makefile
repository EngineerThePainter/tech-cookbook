CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -O3 -g

LIBS := -lprotobuf -pthread -lgrpc++_reflection -lgrpc -lgpr -lgrpc++ -ldl -labsl_log_internal_proto -labsl_log_internal_check_op -labsl_log_internal_message -labsl_cord -labsl_cordz_info -labsl_cordz_functions -labsl_synchronization

SRC := main.cpp ../proto/greeter.pb.cc ../proto/greeter.grpc.pb.cc

TARGET := grpc_server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $^

clean:
	rm -f $(TARGET)