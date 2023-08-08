# Grpc communication

Based on this [tutorial](https://grpc.io/docs/languages/cpp/basics/).

To generate message classes:
```
protoc --cpp_out=proto greeter.
```

To generate service classes:
```
protoc --grpc_out=proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` greeter.proto
```

