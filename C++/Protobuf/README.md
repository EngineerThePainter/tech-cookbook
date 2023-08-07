# Google Protobuf

Based on this [tutorial](https://protobuf.dev/getting-started/cpptutorial/).

Just be sure you have protobuf library installed.

Usage

```
protoc --cpp_out=proto addressbook.proto
```
To build with protobuf compiler header and source to the `proto` directory.

Then just `make` reader and writer (call it from their directories, since they include generated `pb.h` header).