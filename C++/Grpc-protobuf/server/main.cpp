#include <iostream>
#include <memory>

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "../proto/greeter.grpc.pb.h"
#include "../proto/greeter.pb.h"

namespace
{
class GreeterServerImpl final : public grpc_test::Greeter::Service
{
public:
  grpc::Status SayHello(grpc::ServerContext* /*context*/, const grpc_test::HelloRequest* request, grpc_test::HelloReply* response) override
  {
    response->set_message("Hello " + request->name());
    return grpc::Status::OK;
  }
};

void RunServer(const std::string& port)
{
  GreeterServerImpl service;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(port, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server up and running, listens on port " << port << std::endl;
  server->Wait();
}

} // namespace

int main()
{
  RunServer("0.0.0.0:50051");
  return 0;
}