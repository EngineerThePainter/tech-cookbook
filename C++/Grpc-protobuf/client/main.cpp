#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include "../proto/greeter.grpc.pb.h"
#include "../proto/greeter.pb.h"

namespace
{
class GreeterClient
{
public:
  GreeterClient(std::shared_ptr<grpc::Channel> channel) : stub_(grpc_test::Greeter::NewStub(channel)) {}

  void Greet(const std::string& name)
  {
    grpc::ClientContext context;
    grpc_test::HelloRequest request;
    request.set_name(name);

    grpc_test::HelloReply reply;
    grpc::Status status = stub_->SayHello(&context, request, &reply);
    if (status.ok()) {
      std::cout << "Greeter received: " << reply.message() << std::endl;
    } else {
      std::cout << "Greeter failed with status: " << status.error_code() << " (" << status.error_message() << ")"
                << std::endl;
    }
  }

private:
  std::unique_ptr<grpc_test::Greeter::Stub> stub_;
};

} // namespace

int main()
{
  GreeterClient client(grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials()));

  client.Greet("Hello");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  client.Greet("To");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  client.Greet("GRPC");
  return 0;
}