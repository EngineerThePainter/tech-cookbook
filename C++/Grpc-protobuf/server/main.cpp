#include <iostream>

#include "../proto/greeter.grpc.pb.h"
#include "../proto/greeter.pb.h"

namespace
{
class GreeterServerImpl final : public grpc_test::Greeter::Service
{
public:
  grpc_test::HelloReply SayHello(grpc::ServerContext* context, const grpc_test::HelloRequest* request)
  {
    grpc_test::HelloReply reply;
    reply.set_message("Hello " + request->name());
    return reply;
  }
};
} // namespace

int main()
{
  GreeterServerImpl service;
  return 0;
}