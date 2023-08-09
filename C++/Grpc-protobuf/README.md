# Grpc communication

Based on this [tutorial](https://grpc.io/docs/languages/cpp/basics/).

Create directory named `proto` in the root directory for your compiled protobufs.

To generate message classes:
```
protoc --cpp_out=proto greeter.
```

To generate service classes:
```
protoc --grpc_out=proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` greeter.proto
```

Then just `make` both client and server. Client is really simple - just sends three request each after one second. The call is synchronous.

